/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  Copyright (c) [2020], MediaTek Inc. All rights reserved.
*  This software/firmware and related documentation ("MediaTek Software") are
*  protected under relevant copyright laws.
*
*  The information contained herein is confidential and proprietary to
*  MediaTek Inc. and/or its licensors. Except as otherwise provided in the
*  applicable licensing terms with MediaTek Inc. and/or its licensors, any
*  reproduction, modification, use or disclosure of MediaTek Software, and
*  information contained herein, in whole or in part, shall be strictly
*  prohibited.
*****************************************************************************/

#include "platform.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include "mipc_hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <mtk_log.h>

static int fd = -1;
static char port_name[32];
FILE *debug_fp = 0;

#ifdef UNIT_TEST
static uint8_t unit_test_read_buf[65536];
static uint8_t unit_test_write_buf[65536];
static uint32_t unit_test_read_buf_len;
static uint32_t unit_test_write_buf_len;

static EVENT *unit_test_event;
static uint8_t unit_test_reset = 0;

void UNIT_TEST_RESET()
{
    memset(unit_test_read_buf, 0, sizeof(unit_test_read_buf));
    unit_test_read_buf_len = 0;
    memset(unit_test_write_buf, 0, sizeof(unit_test_write_buf));
    unit_test_write_buf_len = 0;
    unit_test_reset = 1;
    WAKE_EVENT(unit_test_event, NULL);
}

void UNIT_TEST_READ_BUF_ADD(uint8_t *ptr, uint32_t ptr_len)
{
    MEMCPY(unit_test_read_buf, ptr, ptr_len);
    unit_test_read_buf_len = ptr_len;
    WAKE_EVENT(unit_test_event, NULL);
}

uint8_t *UNIT_TEST_WRITE_BUF_GET(uint32_t *len_ptr)
{
    *len_ptr = unit_test_write_buf_len;
    return unit_test_write_buf;
}
#endif

int32_t CHECK_MIPC_SUPPORT()
{
    struct stat st;
#ifdef OPENWRT
    //wait MD ready
    do {
        char buf[64];
        int ccci_fd = open("/sys/kernel/ccci/boot", O_RDONLY);
        if (ccci_fd >= 0) {
            memset(buf, 0, sizeof(buf));
            read(ccci_fd, buf, sizeof(buf));
            close(ccci_fd);

            if (strncmp(buf, "md1:4", 5) == 0) {
                //MD1 is ready
                break;
            }
        }
        sleep(1);
    } while (1);
#endif

    //check if the file is existed
    if (stat("/dev/ttyCMIPC0", &st) < 0) {
        return 0;
    } else {
        return 1;
    }
}

void INITIALIZE()
{
#ifndef UNIT_TEST
//    fd = -1;
#else
    unit_test_event = CREATE_EVENT(0);
#endif
}

void SETCOM(const char *port_name_ptr)
{
    memset(port_name, 0, sizeof(port_name));
    if (snprintf(port_name, sizeof(port_name), "%s", port_name_ptr) < 0) {
        mtkAssert((char*)"SETCOM fail");
    }
}

int32_t GETCOM()
{
    return fd;
}


const char *FINDCOM(const char *process_name_ptr)
{
    if (strlen(port_name)) {
        return port_name;
    } else {
        return "/dev/ttyCMIPC0";
    }
}

int32_t OPENCOM(const char *port_name_ptr)
{
    int32_t retry_count = 30;
    int32_t read_count = 0;

#ifndef UNIT_TEST
    struct termios options;
#if 1//def OPENWRT
    //wait MD ready
    do {
        char buf[64];
        int ccci_fd = open("/sys/kernel/ccci/boot", O_RDONLY);
        if (ccci_fd >= 0) {
            memset(buf, 0, sizeof(buf));
            read_count = read(ccci_fd, buf, sizeof(buf));
            close(ccci_fd);
            if (read_count < 0) {
                sleep(1);
                continue;
            }

            if (strncmp(buf, "md1:4", 5) == 0) {
                //MD1 is ready
                break;
            }
        }
        sleep(1);
    } while (1);
#endif

    DbgMsg("OPENCOM start");
    while ((--retry_count > 0) && ((fd = open(port_name_ptr, O_RDWR | O_NOCTTY | O_NONBLOCK)) < 0)) {
        ErrMsg("OPENCOM fail, count = %d, errno = %d (%s)", retry_count, errno, strerror(errno));
        sleep(1);
    }

    if (fd < 0) {
        ErrMsg("OPENCOM fail - end");
        return -1;
    } else {
        // clear non-blocking
        int flags = fcntl(fd, F_GETFL);
        DbgMsg("OPENCOM %s", port_name_ptr);
        flags &= ~O_NONBLOCK;
        if (fcntl(fd, F_SETFL, flags) < 0) {
            ErrMsg("fcntl F_SETFL error");
        }
    }

    //set terminal options

    tcgetattr(fd, &options);
    cfmakeraw(&options);
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

#endif
    return 0;
}

void CLOSECOM()
{
#ifndef UNIT_TEST
    if (fd >= 0) {
        close(fd);
    }
#endif
    fd = -1;
}

int32_t WRITECOM(uint8_t *buf_ptr, const uint32_t buf_len)
{
    uint16_t total_write_bytes;
#ifndef UNIT_TEST
    int32_t write_bytes;

    total_write_bytes = 0;
    while (write_bytes = write(fd, buf_ptr + total_write_bytes, buf_len - total_write_bytes)) {
        InfoMsg("write_bytes=%d", write_bytes);
        if (write_bytes < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;
        }
        total_write_bytes += write_bytes;
        if (total_write_bytes == buf_len) {
            break;
        }
    }
#else
    total_write_bytes = (buf_len > sizeof(unit_test_write_buf)) ? sizeof(unit_test_write_buf) : buf_len;
    MEMCPY(unit_test_write_buf, buf_ptr, total_write_bytes);
    unit_test_write_buf_len = total_write_bytes;
#endif
    return total_write_bytes;
}

int32_t READCOM(uint8_t *buf_ptr, const uint32_t buf_len)
{
    uint16_t total_read_bytes;
#ifndef UNIT_TEST
    int32_t read_bytes;

    total_read_bytes = 0;
    while (read_bytes = read(fd, buf_ptr + total_read_bytes, buf_len - total_read_bytes)) {
        InfoMsg("read_bytes=%d", read_bytes);
        if (read_bytes < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;
        }
        total_read_bytes += read_bytes;
        if (total_read_bytes == buf_len) {
            break;
        }
    }
#else
    if (unit_test_read_buf_len == 0 ) {
        unit_test_event->ready = 0;
        WAIT_EVENT(unit_test_event);
    }

    if (unit_test_reset == 0) {
        total_read_bytes = (buf_len > sizeof(unit_test_read_buf)) ? sizeof(unit_test_read_buf) : buf_len;
        MEMCPY(buf_ptr, unit_test_read_buf, total_read_bytes);
        unit_test_read_buf_len -= total_read_bytes;
        if (unit_test_read_buf_len) {
            MEMCPY(unit_test_read_buf, unit_test_read_buf + total_read_bytes, unit_test_read_buf_len);
        }
    } else {
        unit_test_reset = 0;
        total_read_bytes = 0;
    }
#endif
    return total_read_bytes;
}

void *_THREAD_FUNC(void *priv_ptr)
{
    THREAD *thread_ptr = (THREAD *)priv_ptr;

    thread_ptr->func(thread_ptr->func_priv_ptr);

    return NULL;
}

THREAD *CREATE_THREAD(THREAD_FUNC func, void *func_priv_ptr)
{
    THREAD *thread_ptr = ALLOC(sizeof(THREAD));

    if (thread_ptr) {
        thread_ptr->func = func;
        thread_ptr->func_priv_ptr = func_priv_ptr;
        pthread_create(&thread_ptr->tid, NULL, _THREAD_FUNC, thread_ptr);
        pthread_detach(thread_ptr->tid); // pthread_detach() should be called for each thread
    }

    return thread_ptr;
}

void DELETE_THREAD(THREAD *thread_ptr)
{
    if (thread_ptr){
        FREE(thread_ptr);
    }
}

EVENT *CREATE_EVENT(uint32_t timeout_ms)
{
    EVENT *event_ptr = (EVENT *)ALLOC(sizeof(EVENT));

    if (event_ptr) {
        pthread_cond_init(&event_ptr->cond, NULL);
        pthread_mutex_init(&event_ptr->lock, NULL);
        event_ptr->ready = 0;
        event_ptr->timeout_ms = timeout_ms;
    }

    return event_ptr;
}

void DELETE_EVENT(EVENT *event_ptr)
{
    if (event_ptr) {
        FREE(event_ptr);
    }
}

int32_t WAIT_EVENT(EVENT *event_ptr)
{
    if (event_ptr) {
        struct timespec to;
        if (event_ptr->timeout_ms) {
            clock_gettime(CLOCK_REALTIME, &to);
            if (event_ptr->timeout_ms < 1000) {
                to.tv_sec += 1;
            } else {
                to.tv_sec += (event_ptr->timeout_ms / 1000);
            }
            pthread_mutex_lock(&event_ptr->lock);
            //infinite
            while (event_ptr->ready == 0) {
                if (pthread_cond_timedwait(&event_ptr->cond, &event_ptr->lock, &to) == ETIMEDOUT) {
                    break;
                }
            }
            pthread_mutex_unlock(&event_ptr->lock);
        } else {
            pthread_mutex_lock(&event_ptr->lock);
            //infinite
            while (event_ptr->ready == 0) {
                pthread_cond_wait(&event_ptr->cond, &event_ptr->lock);
            }
            pthread_mutex_unlock(&event_ptr->lock);
        }

        if (event_ptr->ready == 1) {
            return 0;
        } else {
            return 1; //timeout
        }
    }

    return 0;
}

void WAKE_EVENT(EVENT *event_ptr, void *result_ptr)
{
    if (event_ptr) {
        pthread_mutex_lock(&event_ptr->lock);
        event_ptr->ready = 1;
        event_ptr->result_ptr = result_ptr;
        pthread_cond_signal(&event_ptr->cond);
        pthread_mutex_unlock(&event_ptr->lock);
    }
}

MUTEX *CREATE_MUTEX()
{
    MUTEX *mutex_ptr = (MUTEX *)ALLOC(sizeof(MUTEX));

    if (mutex_ptr) {
        pthread_mutex_init(&mutex_ptr->hMutex, NULL);
    }

    return mutex_ptr;
}

void DELETE_MUTEX(MUTEX *mutex_ptr)
{
    if (mutex_ptr) {
        FREE(mutex_ptr);
    }
}

void LOCK_MUTEX(MUTEX *mutex_ptr)
{
    if (mutex_ptr) {
        pthread_mutex_lock(&mutex_ptr->hMutex);
    }
}

void UNLOCK_MUTEX(MUTEX *mutex_ptr)
{
    if (mutex_ptr) {
        pthread_mutex_unlock(&mutex_ptr->hMutex);
    }
}

uint64_t GETTID()
{
    return (uint64_t)pthread_self();
}

void* mtkAllocAssert(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        mtkAssert((char*)"malloc memroy fail");
    }
    return ptr;
}

#ifdef TRM_SUPPORT
int mipc_reset()
{
    if (fd >= 0 && LIBTRM_RESET) {
        LIBTRM_RESET(fd);
        return 0;
    }
    return -1;
}

int mipc_power_off()
{
    if (fd >= 0 && LIBTRM_POWER_OFF_MD) {
        LIBTRM_POWER_OFF_MD(fd);
        return 0;
    }
    return -1;
}

int mipc_power_on()
{
    if (fd >= 0 && LIBTRM_POWER_ON_MD) {
        LIBTRM_POWER_ON_MD(fd);
        return 0;
    }
    return -1;
}

void mipc_md_event_register(MIPC_MD_EVENT_CB cb, void *cb_priv_ptr)
{
    if (LIBTRM_MD_EVENT_REGISTER) {
        LIBTRM_MD_EVENT_REGISTER(cb, cb_priv_ptr);
    }
}
#endif
