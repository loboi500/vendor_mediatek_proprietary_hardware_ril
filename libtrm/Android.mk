ifeq ($(MTK_RIL_MODE), c6m_1rild)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    src/libtrm.c \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES:= \
    libmtkrillog
#  libmtkutils libmtkrillog libmtkcutils libmtkproperty

# If not declare LOCAL_MULTILIB, it will build both 32/64 bit lib.
# In c6m_rild 64bit project, all modules that use libmtkutils are
# 64bit, it is not necessary to build 32bit libmtkrilutils.
LOCAL_MULTILIB := both

LOCAL_HEADER_LIBRARIES:= libMtkLogHeaders

#LOCAL_CFLAGS += -DUNIT_TEST

LOCAL_MODULE:= libtrm
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

LOCAL_EXPORT_C_INCLUDE_DIRS := \
  $(LOCAL_PATH)/include

include $(MTK_SHARED_LIBRARY)

endif
