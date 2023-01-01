#include "libtrm.h"
#include "log.h"
#include <pthread.h>

static int init = 0;
static int mon_thread_init = 0;
static int fd = -1;
static pthread_t tid;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static LIBTRM_MD_EVENT_CB md_event_cb;
static void *md_event_cb_priv_ptr;

void libtrm_init()
{
    if (init == 1) {
        LOGD("libtrm_init already called.\n");
    } else {
        LOGD("libtrm_init.\n");
        //openlog("libtrm", LOG_PID, LOG_DAEMON);
        init = 1;
    }
}

void libtrm_deinit()
{
    if (init == 0) {
        LOGD("libtrm_deinit - not init yet.\n");
    } else {
        LOGD("libtrm_deinit.\n");
        //closelog();
        init = 0;
    }
}

int libtrm_reset(int ccci_fd)
{
    int reset_parm = -1;

    LOGD("libtrm_reset: reset modem\n");

    if (ioctl(ccci_fd, CCCI_IOC_MD_RESET, &reset_parm) == 0) {
        return 0;
    } else {
        LOGD("libtrm_reset: reset control error (%s)\n", strerror(errno));
        return -1;
    }
}

int libtrm_power_off_md(int ccci_fd)
{
    int parm = -1;

    LOGD("libtrm_power_off_md\n");

    if (ioctl(ccci_fd, CCCI_IOC_ENTER_DEEP_FLIGHT_ENHANCED, &parm) == 0) {
        return 0;
    } else {
        LOGD("libtrm_reset: reset control error (%s)\n", strerror(errno));
        return -1;
    }
}

int libtrm_power_on_md(int ccci_fd)
{
    int parm = -1;

    LOGD("libtrm_power_off_md\n");

    if (ioctl(ccci_fd, CCCI_IOC_LEAVE_DEEP_FLIGHT_ENHANCED, &parm) == 0) {
        return 0;
    } else {
        LOGD("libtrm_reset: reset control error (%s)\n", strerror(errno));
        return -1;
    }
}

static void *libtrm_monitor_thread(void *priv_ptr)
{
    int count;
    struct md_status_event status_buf;

    do {
        count = read(fd, &status_buf, sizeof(struct md_status_event));
        if (count < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                LOGD("libtrm_monitor_thread: read error (%s)\n", strerror(errno));
                break;
            }
        }

        if (count > 0) {
            LOGD("libtrm_monitor_thread: receive status event (%d)\n", status_buf.event_type);
            if (md_event_cb) {
                md_event_cb(md_event_cb_priv_ptr, &status_buf);
            }
        }
    } while(1);

    LOGI("libtrm_monitor_thread: exit.\n");

    pthread_mutex_lock(&mutex);

    close(fd);
    fd = -1;
    mon_thread_init = 0;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void libtrm_md_event_register(LIBTRM_MD_EVENT_CB cb, void *cb_priv_ptr)
{
    md_event_cb = cb;
    md_event_cb_priv_ptr = cb_priv_ptr;

    pthread_mutex_lock(&mutex);
    if (cb) {
        if (mon_thread_init == 0) {
            fd = open("/dev/ccci_md1_sta", O_RDWR);
            if (fd >= 0) {
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

                int err = pthread_create(&tid, &attr, libtrm_monitor_thread, NULL);
                if (err == 0) {
                    mon_thread_init = 1;
                    LOGI("libtrm_md_event_register: mon. thread started.\n");
                } else {
                    LOGE("libtrm_md_event_register: mon. thread create fail (%s)\n",
                            strerror(err));
                    close(fd);
                    fd = -1;
                }
            }
        } else {
            LOGI("libtrm_md_event_register: mon. thread already exist.\n");
        }
    } else {
        if (fd >= 0) {
            close(fd);
            fd = -1;
        }
    }
    pthread_mutex_unlock(&mutex);
}
