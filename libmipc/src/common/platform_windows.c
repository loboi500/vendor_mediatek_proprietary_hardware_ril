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

static HANDLE hCom;
//static HANDLE hThread;
static OVERLAPPED oRead;
static OVERLAPPED oWrite;
static char port_name[32] = {0};
FILE *debug_fp = 0;

int32_t CHECK_MIPC_SUPPORT()
{
    return -1;
}

void INIT()
{
    //memset(&hCom, 0, sizeof(hCom));
    //memset(&hThread, 0, sizeof(hThread));

    memset(&oRead, 0, sizeof(oRead));
    oRead.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    memset(&oWrite, 0, sizeof(oWrite));
    oWrite.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

void SETCOM(const char *port_name_ptr)
{
    memset(port_name, 0, sizeof(port_name));
    snprintf(port_name, sizeof(port_name), "\\\\.\\%s", port_name_ptr);
}

int32_t GETCOM()
{
    return -1;
}

const char *FINDCOM(const char *process_name_ptr)
{
    //have to be modified
    if (strlen(port_name)) {
        return port_name;
    } else {
        return "\\\\.\\COM20";
    }
}

int32_t OPENCOM(const char *port_name_ptr)
{
    DCB com_config;
    COMMTIMEOUTS com_timeout;

    hCom = CreateFile(port_name_ptr, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);

    if (hCom == INVALID_HANDLE_VALUE) {
        ErrMsg("CreateFile failed with error %d.\n", GetLastError());
        return -1;
    }

    GetCommState(hCom, &com_config);
    com_config.BaudRate = 115200;
    com_config.ByteSize = 8;
    com_config.Parity = NOPARITY;
    com_config.StopBits = TWOSTOPBITS;
    SetCommState(hCom, &com_config);

    //SetupComm(hCom, 1024, 1024);
    SetupComm(hCom, 64, 64);

    memset(&com_timeout, 0, sizeof(com_timeout));
    SetCommTimeouts(hCom, &com_timeout);

    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
    return 0;
}

void CLOSECOM()
{
    CloseHandle(hCom);
}

int32_t WRITECOM(uint8_t *buf_ptr, const uint32_t buf_len)
{
    DWORD write_bytes;
    uint16_t total_write_bytes;

    total_write_bytes = 0;
    for (;;) {
        if (!WriteFile(hCom, buf_ptr + total_write_bytes, buf_len - total_write_bytes, &write_bytes, &oWrite)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                break;
            }

            WaitForSingleObject(oWrite.hEvent, INFINITE);
            if (!GetOverlappedResult(hCom, &oWrite, &write_bytes, FALSE)) {
                break;
            }
        }
        total_write_bytes += write_bytes;
        if (total_write_bytes == buf_len) {
            break;
        }
    }

    return total_write_bytes;
}

int32_t READCOM(uint8_t *buf_ptr, const uint32_t buf_len)
{
    DWORD read_bytes;
    uint16_t total_read_bytes;

    total_read_bytes = 0;
    for (;;) {
        if (!ReadFile(hCom, buf_ptr + total_read_bytes, buf_len - total_read_bytes, &read_bytes, &oRead)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                break;
            }

            WaitForSingleObject(oRead.hEvent, INFINITE);
            if (!GetOverlappedResult(hCom, &oRead, &read_bytes, FALSE)) {
                break;
            }
        }
        total_read_bytes += read_bytes;
        if (total_read_bytes == buf_len) {
            break;
        }
    }

    return total_read_bytes;
}

DWORD WINAPI _THREAD_FUNC(LPVOID priv_ptr)
{
    THREAD *thread_ptr = (THREAD *)priv_ptr;

    thread_ptr->func(thread_ptr->func_priv_ptr);

    return 0;
}

THREAD *CREATE_THREAD(THREAD_FUNC func, void *func_priv_ptr)
{
    THREAD *thread_ptr = ALLOC(sizeof(THREAD));

    if (thread_ptr) {
        thread_ptr->func = func;
        thread_ptr->func_priv_ptr = func_priv_ptr;
        thread_ptr->tid = CreateThread(NULL, 0, _THREAD_FUNC, thread_ptr, 0, NULL);
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
        event_ptr->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        event_ptr->timeout_ms = timeout_ms;
    }

    return event_ptr;
}

void DELETE_EVENT(EVENT *event_ptr)
{
    if (event_ptr) {
        CloseHandle(event_ptr->hEvent);
        FREE(event_ptr);
    }
}

int32_t WAIT_EVENT(EVENT *event_ptr)
{
    DWORD dwMilliseconds;
    if (event_ptr) {
        if (event_ptr->timeout_ms == 0) {
            dwMilliseconds = INFINITE;
        } else {
            dwMilliseconds = event_ptr->timeout_ms;
        }
        if (WaitForSingleObject(event_ptr->hEvent, dwMilliseconds) == WAIT_TIMEOUT) {
            return 1; //timeout
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

void WAKE_EVENT(EVENT *event_ptr, void *result_ptr)
{
    if (event_ptr) {
        event_ptr->result_ptr = result_ptr;
        SetEvent(event_ptr->hEvent);
    }
}


MUTEX *CREATE_MUTEX()
{
    MUTEX *mutex_ptr = (MUTEX *)ALLOC(sizeof(MUTEX));

    if (mutex_ptr) {
        mutex_ptr->hMutex = CreateMutex(NULL, FALSE, NULL);
    }

    return mutex_ptr;
}

void DELETE_MUTEX(MUTEX *mutex_ptr)
{
    if (mutex_ptr) {
        CloseHandle(mutex_ptr->hMutex);
        FREE(mutex_ptr);
    }
}

void LOCK_MUTEX(MUTEX *mutex_ptr)
{
    if (mutex_ptr) {
        WaitForSingleObject(mutex_ptr->hMutex, INFINITE);
    }
}

void UNLOCK_MUTEX(MUTEX *mutex_ptr)
{
    if (mutex_ptr) {
        ReleaseMutex(mutex_ptr->hMutex);
    }
}

uint64_t GETTID()
{
    return (uint64_t)GetCurrentThreadId();
}
