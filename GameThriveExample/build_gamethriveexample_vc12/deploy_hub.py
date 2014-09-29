# -*- coding: utf-8 -*-
#
# (C) 2001-2012 Marmalade. All Rights Reserved.
#
# This document is protected by copyright, and contains information
# proprietary to Marmalade.
#
# This file consists of source code released by Marmalade under
# the terms of the accompanying End User License Agreement (EULA).
# Please do not use this program/source code before you have read the
# EULA and have agreed to be bound by its terms.
#
import deploy_config

config = deploy_config.config
cmdline = deploy_config.cmdline
mkb = deploy_config.mkb
mkf = deploy_config.mkf

assets = deploy_config.assets

class HubConfig(deploy_config.DefaultConfig):
    android_icon_group = {}
    android_install_location = 1
    android_pkgname = r"com.GameThrive.GameThriveExample"
    icon = r"C:/Users/Kasten/Documents/GameThrive/SDK/Marmalade/GameThriveExample/icons"
    assets = assets["Default"]
    config = [r"C:/Users/Kasten/Documents/GameThrive/SDK/Marmalade/GameThriveExample/data/app.icf"]
    name = r"GameThriveExample"
    caption = r"GameThriveExample"
    provider = r"GameThrive"
    copyright = r"(C) GameThrive"
    version = [0, 0, 1]
    android_keystore = r"C:/Users/Kasten/.android/debug.keystore"
    android_storepass = r"android"
    android_aliasname = r"androiddebugkey"
    android_keypass = r"android"
    pass

default = HubConfig()