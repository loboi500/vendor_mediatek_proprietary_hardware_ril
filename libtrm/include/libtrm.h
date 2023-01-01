#ifndef _LIBTRM_H_
#define _LIBTRM_H_

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define CCCI_IOC_MAGIC 'C'
#define CCCI_IOC_MD_RESET _IO(CCCI_IOC_MAGIC, 0)
#define CCCI_IOC_ENTER_DEEP_FLIGHT_ENHANCED _IO(CCCI_IOC_MAGIC,  123)
#define CCCI_IOC_LEAVE_DEEP_FLIGHT_ENHANCED _IO(CCCI_IOC_MAGIC,  124)
#define CCCI_IOC_RILD_POWER_OFF_MD _IO(CCCI_IOC_MAGIC,  125)

enum md_bc_event {
    MD_STA_EV_INVALID = 0,
    MD_STA_EV_RESET_REQUEST,
    MD_STA_EV_F_ASSERT_REQUEST,
    MD_STA_EV_STOP_REQUEST,
    MD_STA_EV_START_REQUEST,
    MD_STA_EV_ENTER_FLIGHT_REQUEST,
    MD_STA_EV_LEAVE_FLIGHT_REQUEST,
    MD_STA_EV_ENTER_FLIGHT_E_REQUEST,
    MD_STA_EV_LEAVE_FLIGHT_E_REQUEST,
    MD_STA_EV_HS1,
    MD_STA_EV_READY,
    MD_STA_EV_EXCEPTION,
    MD_STA_EV_STOP,
};

struct md_status_event {
    struct timeval time_stamp;
    int md_id;
    int event_type;
    char reason[32];
};

typedef void (*LIBTRM_MD_EVENT_CB)(void *priv_ptr, struct md_status_event*);

void libtrm_init();
void libtrm_deinit();

int libtrm_reset(int ccci_fd);
void libtrm_md_event_register(LIBTRM_MD_EVENT_CB cb, void *cb_priv_ptr);

#endif
