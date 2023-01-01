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

#ifndef _PLATFORM_WINDOWS_H_
#define _PLATFORM_WINDOWS_H_

#include "windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef NO_EXPORT
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

#define HTOML(x) (x)
#define HTOMS(x) (x)
#define MTOHL(x) (x)
#define MTOHS(x) (x)
#define ALLOC malloc
#define FREE free
#define SLEEP(x) Sleep((x)*1000)
#define MEMCPY memcpy
#define MEMCMP memcmp
#define MEMSET memset

typedef uint32_t (*THREAD_FUNC)(void *priv_ptr);

typedef struct {
    HANDLE tid;
    THREAD_FUNC func;
    void *func_priv_ptr;
} THREAD;

typedef struct {
    HANDLE hEvent;
    void *result_ptr;
    uint32_t timeout_ms;
} EVENT;

typedef struct {
    HANDLE hMutex;
} MUTEX;

#ifdef __cplusplus
extern "C" {
#endif

THREAD *CREATE_THREAD(THREAD_FUNC func, void *func_priv_ptr);
void DELETE_THREAD(THREAD *thread_ptr);

//
EVENT *CREATE_EVENT();
void DELETE_EVENT(EVENT *event_ptr);
int32_t WAIT_EVENT(EVENT *event_ptr);
void WAKE_EVENT(EVENT *event_ptr, void *result_ptr);
//
MUTEX *CREATE_MUTEX();
void DELETE_MUTEX(MUTEX *mutex_ptr);
void LOCK_MUTEX(MUTEX *mutex_ptr);
void UNLOCK_MUTEX(MUTEX *mutex_ptr);
//
int32_t CHECK_MIPC_SUPPORT();
//
void INIT();
//
DLL_EXPORT void SETCOM(const char *port_name_ptr);
int32_t GETCOM();
const char *FINDCOM(const char *process_name_ptr);
int32_t OPENCOM(const char *port_name_ptr);
void CLOSECOM();
int32_t WRITECOM(uint8_t *buf_ptr, const uint32_t buf_len);
int32_t READCOM(uint8_t *buf_ptr, const uint32_t buf_len);

uint64_t GETTID();

#ifdef __cplusplus
}
#endif

extern FILE *debug_fp;

#ifdef DEBUG
#define SRC_FILE_OFFSET (0)
#define ErrMsg(format, ...) do {SYSTEMTIME st;GetLocalTime(&st);printf("[%04d-%02d-%02d %02d:%02d:%02d] (%s:%d) "format"\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,&__FILE__[SRC_FILE_OFFSET],__LINE__,##__VA_ARGS__);}while(0);
#define DbgMsg(format, ...) do {SYSTEMTIME st;GetLocalTime(&st);printf("[%04d-%02d-%02d %02d:%02d:%02d] (%s:%d) "format"\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,&__FILE__[SRC_FILE_OFFSET],__LINE__,##__VA_ARGS__);}while(0);
#define InfoMsg(format, ...) do {printf("  "format"\n",##__VA_ARGS__);}while(0);
#define Info2Msg(format, ...) do {printf("    "format"\n",##__VA_ARGS__);}while(0);
#else
#define SRC_FILE_OFFSET (0)
#define ErrMsg(format, ...) while(debug_fp) {SYSTEMTIME st;GetLocalTime(&st);fprintf(debug_fp, "[%04d-%02d-%02d %02d:%02d:%02d] (%s:%d) "format"\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,&__FILE__[SRC_FILE_OFFSET],__LINE__,##__VA_ARGS__); fflush(debug_fp); break;}
#define DbgMsg(format, ...) while(debug_fp) {SYSTEMTIME st;GetLocalTime(&st);fprintf(debug_fp, "[%04d-%02d-%02d %02d:%02d:%02d] (%s:%d) "format"\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,&__FILE__[SRC_FILE_OFFSET],__LINE__,##__VA_ARGS__); fflush(debug_fp); break;}
#define InfoMsg(format, ...) while(debug_fp) {fprintf(debug_fp, "  "format"\n",##__VA_ARGS__); fflush(debug_fp); break;}
#define Info2Msg(format, ...) while(debug_fp) {fprintf(debug_fp, "    "format"\n",##__VA_ARGS__); fflush(debug_fp); break;}
#endif


#endif
