#ifndef ANDROID
#   define ANDROID 1
#endif
#ifndef I3D_ARCH_ARM
#   define I3D_ARCH_ARM 1
#endif
#ifndef I3D_OS_LINUX
#   define I3D_OS_LINUX 1
#endif
#ifndef I3D_PLATFORM_LINUX
#   define I3D_PLATFORM_LINUX 1
#endif
#ifndef IW_ASSERTION_CHANNEL_GAMETHRIVE
#   define IW_ASSERTION_CHANNEL_GAMETHRIVE 1
#endif
#ifndef IW_MKF_EDK
#   define IW_MKF_EDK 1
#endif
#ifndef IW_MKF_S3EGAMETHRIVE_BUILD
#   define IW_MKF_S3EGAMETHRIVE_BUILD 1
#endif
#ifndef IW_MKF_S3E_DEFAULT
#   define IW_MKF_S3E_DEFAULT 1
#endif
#ifndef IW_PLATFORM_LINUX
#   define IW_PLATFORM_LINUX 1
#endif
#ifndef IW_SDK
#   define IW_SDK 1
#endif
#ifndef IW_TRACE_CHANNEL_GAMETHRIVE
#   define IW_TRACE_CHANNEL_GAMETHRIVE 1
#endif
#ifndef IW_TRACE_CHANNEL_GAMETHRIVE_VERBOSE
#   define IW_TRACE_CHANNEL_GAMETHRIVE_VERBOSE 2
#endif
#ifndef S3E_ANDROID
#   define S3E_ANDROID 1
#endif
#ifndef S3E_BUILD_EXT
#   define S3E_BUILD_EXT 1
#endif
#ifndef S3E_EXT_GAMETHRIVE
#   define S3E_EXT_GAMETHRIVE 1
#endif

/* including "extra_body" specified by the mkb plugin */

#if !defined I3D_ARCH_32_BIT && !defined I3D_ARCH_64_BIT
    #if defined I3D_ARCH_AARCH64 || defined I3D_ARCH_AMD64
        #define I3D_ARCH_64_BIT
    #else
        #define I3D_ARCH_32_BIT
    #endif
#endif
