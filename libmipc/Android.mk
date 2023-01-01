ifeq ($(MTK_RIL_MODE), c6m_1rild)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    src/common/platform_mtk.c \
    src/msg/hashmap.c \
    src/msg/list.c \
    src/msg/msg.c \
    src/msg/msg_host.c \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
    $(TOP)/$(MTK_PATH_SOURCE)/hardware/ril/libmipc/include \
    $(TOP)/$(MTK_PATH_SOURCE)/hardware/ril/libmipc/include/api \
    $(TOP)/$(MTK_PATH_SOURCE)/hardware/ril/libmipc/include/common \
    $(TOP)/$(MTK_PATH_SOURCE)/hardware/ril/libmipc/include/msg \


LOCAL_SHARED_LIBRARIES:= \
    libmtkrillog libtrm
#  libmtkutils libmtkrillog libmtkcutils libmtkproperty

# If not declare LOCAL_MULTILIB, it will build both 32/64 bit lib.
# In c6m_rild 64bit project, all modules that use libmtkutils are
# 64bit, it is not necessary to build 32bit libmtkrilutils.
LOCAL_MULTILIB := both

#LOCAL_CFLAGS += -DUNIT_TEST

LOCAL_CFLAGS += -DTRM_SUPPORT

LOCAL_HEADER_LIBRARIES:= libMtkLogHeaders

LOCAL_MODULE:= libmipc
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

LOCAL_EXPORT_C_INCLUDE_DIRS := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/include/api \
    $(LOCAL_PATH)/include/common \
    $(LOCAL_PATH)/include/msg
include $(MTK_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=libmipc_includes
LOCAL_EXPORT_C_INCLUDE_DIRS := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/include/api \
    $(LOCAL_PATH)/include/common \
    $(LOCAL_PATH)/include/msg
include $(BUILD_HEADER_LIBRARY)

endif
