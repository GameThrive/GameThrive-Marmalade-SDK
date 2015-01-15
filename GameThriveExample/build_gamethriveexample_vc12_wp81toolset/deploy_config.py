# -*- coding: utf-8 -*-
# Deployment settings for GameThriveExample.
# This file is autogenerated by the mkb system and used by the s3e deployment
# tool during the build process.

config = {}
cmdline = ['C:/Marmalade/7.4/s3e/makefile_builder/mkb.py', 'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/GameThriveExample.mkb', '--deploy-only', '--hub-data', 'C:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/project_GameThriveExample/mkb-wp81.txt', '--buildenv=VC12', '--buildenv-toolset=WP81']
mkb = 'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/GameThriveExample.mkb'
mkf = ['c:\\marmalade\\7.4\\s3e\\s3e-default.mkf', 'c:\\users\\josh\\documents\\gamethrive\\sdk\\marmalade\\s3egamethrive\\s3egamethrive.mkf', 'c:\\marmalade\\7.4\\modules\\iwutil\\iwutil.mkf', 'c:\\marmalade\\7.4\\modules\\third_party\\libjpeg\\libjpeg.mkf', 'c:\\marmalade\\7.4\\modules\\third_party\\libpng\\libpng.mkf', 'c:\\marmalade\\7.4\\modules\\third_party\\zlib\\zlib.mkf']

class DeployConfig(object):
    pass

######### ASSET GROUPS #############

assets = {}

assets['Default'] = [
    ('c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/android/assets/api_key.txt', 'api_key.txt', 0),
]

######### DEFAULT CONFIG #############

class DefaultConfig(DeployConfig):
    embed_icf = -1
    name = 'GameThriveExample'
    pub_sign_key = 0
    priv_sign_key = 0
    caption = 'GameThriveExample'
    long_caption = 'GameThriveExample'
    version = [0, 0, 1]
    config = ['c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/data/app.icf']
    data_dir = 'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/data'
    mkb_dir = 'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample'
    iphone_link_lib = ['s3eGameThrive']
    osx_ext_dll = []
    wp81_extra_pri = []
    ws8_ext_capabilities = []
    android_external_res = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/incoming/android/res', 'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/android/res']
    win32_ext_dll = []
    wp8_ext_capabilities = []
    ws8_extra_res = []
    ws81_ext_managed_dll = []
    iphone_link_libdir = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/lib/iphone']
    wp81_ext_capabilities = []
    android_extra_application_manifest = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/extras.application.txt']
    ws8_ext_native_dll = []
    android_external_assets = []
    blackberry_extra_descriptor = []
    android_extra_manifest = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/extras.manifest.txt', 'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/GameThriveExtraManifest.xml']
    wp81_ext_sdk_ref = []
    iphone_link_libdirs = []
    wp81_ext_device_capabilities = []
    wp8_custom_manifest = 'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/GameThriveCustomWP8Manifest.xml'
    wp8_custom_manifest_fill = 0
    linux_ext_lib = []
    ws8_ext_managed_dll = []
    ws8_ext_sdk_manifest_part = []
    ws8_ext_device_capabilities = []
    ws81_extra_pri = []
    android_external_jars = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/incoming/android/GameThriveSDK.jar', 'c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/lib/android/s3eGameThrive.jar', 'c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/incoming/android/google-play-services.jar', 'c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/incoming/android/android-support-v4.jar']
    win8_winrt_extra_res = []
    wp81_ext_sdk_manifest_part = []
    android_supports_gl_texture = []
    wp81_extra_res = []
    wp81_ext_managed_dll = []
    ws81_ext_sdk_manifest_part = []
    ws81_ext_device_capabilities = []
    ws8_ext_sdk_ref = []
    iphone_extra_string = ['GTDummyKey,</string><key>UIBackgroundModes</key><array><string>remote-notification</string></array><key>GTDummyKey2</key><string>']
    tizen_so = []
    wp8_ext_native_dll = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/lib/wp8/s3eGameThriveExtension.dll']
    win8_phone_extra_res = []
    win8_store_extra_res = []
    iphone_link_opts = ['-weak_framework UIKit', '-weak_framework UIKit']
    ws81_ext_sdk_ref = []
    wp8_extra_res = []
    ws81_ext_native_dll = []
    ws8_extra_pri = []
    wp8_ext_managed_dll = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/incoming/wp8/GameThriveSDK.dll', 'c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/incoming/wp8/Newtonsoft.Json.dll', 'c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/lib/wp8/s3eGameThriveManaged.dll']
    android_extra_packages = []
    android_so = ['c:/users/josh/documents/gamethrive/sdk/marmalade/s3egamethrive/lib/android/libGameThrive.so']
    wp8_ext_sdk_ref = []
    osx_extra_res = []
    ws81_extra_res = []
    wp81_ext_native_dll = []
    ws81_ext_capabilities = []
    iphone_link_libs = []
    target = {
         'wp81-arm' : {
                   'debug'   : r'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/build_gamethriveexample_vc12_wp81toolset/Debug_GameThriveExample_VC12_WP81TOOLSET_arm/GameThriveExample.s86',
                   'release' : r'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/build_gamethriveexample_vc12_wp81toolset/Release_GameThriveExample_VC12_WP81TOOLSET_arm/GameThriveExample.s86',
                 },
         'wp81-x86' : {
                   'debug'   : r'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/build_gamethriveexample_vc12_wp81toolset/Debug_GameThriveExample_VC12_WP81TOOLSET_x86/GameThriveExample.s86',
                   'release' : r'c:/Users/Josh/Documents/GameThrive/SDK/Marmalade/GameThriveExample/build_gamethriveexample_vc12_wp81toolset/Release_GameThriveExample_VC12_WP81TOOLSET_x86/GameThriveExample.s86',
                 },
        }
    arm_arch = ''
    assets_original = assets
    assets = assets['Default']

default = DefaultConfig()
