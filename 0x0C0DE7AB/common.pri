DEFINES += _6IT_QT
DEFINES += _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += $(_6IT_ROOT)/6it

osx {
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
}

linux {
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -std=c99
}

message("6IT_ROOT: $(_6IT_ROOT)")
message("mkspec: $$QMAKESPEC")

win32 {
    winrt {
        DEFINES += _6IT_QT_WINRT
        winphone {
            DEFINES += _6IT_QT_WINRT_PHONE _6IT_UI_MOBILE
            CONFIG += ui_mobile
            message("Platform: WinRT Phone (mobile)")
        } else {
            DEFINES += _6IT_QT_WINRT_DESKTOP _6IT_UI_MOBILE
            CONFIG += ui_mobile
            message("Platform: WinRT Desktop (mobile)")
        }
    } else:windows {
        DEFINES += _6IT_QT_WINDOWS _6IT_UI_DESKTOP
        CONFIG += ui_desktop
        message("Platform: Windows (desktop)")
    } else {
        error("Platform: UNKNOWN (Windows variant)")
    }
}
else:mac {
    osx {
        DEFINES += _6IT_QT_OSX _6IT_UI_DESKTOP
        CONFIG += ui_desktop
        message("Platform: OSX (desktop)")
    } else:ios {
        DEFINES += _6IT_QT_IOS _6IT_UI_MOBILE
        CONFIG += ui_mobile
        message("Platform: iOS (mobile)")
    } else {
        message($$CONFIG)
        error("Platform: UNKNOWN (mac variant)")
    }
} else:linux {
    DEFINES += _6IT_QT_LINUX

    android {
        DEFINES += _6IT_QT_ANDROID _6IT_UI_MOBILE
        CONFIG += ui_mobile
        message("Platform: Android (mobile)")
    } else {
        DEFINES += _6IT_QT_LINUX_DESKTOP _6IT_UI_DESKTOP
        CONFIG += ui_desktop
        message("Platform: Linux (desktop)")
    }
} else {
    message($$CONFIG)
    error("Platform: UNKNOWN")
}

#========================================================================================================

#message($$CONFIG)

#desktop lex yacc debug exceptions depend_includepath testcase_targets
#import_plugins import_qpa_plugin rtti_off incremental_off windows qt
#warn_on release link_prl incremental flat precompile_header
#autogen_precompile_source debug_and_release debug_and_release_target
#embed_manifest_dll embed_manifest_exe c++11 release shared rtti
#no_plugin_manifest qpa win32 msvc copy_dir_files debug

#winrt lex yacc debug exceptions depend_includepath testcase_targets
#import_plugins import_qpa_plugin rtti_off incremental_off windows qt
#warn_on release link_prl incremental flat precompile_header
#autogen_precompile_source debug_and_release debug_and_release_target
#no_generated_target_info package_manifest rtti release shared rtti
#no_plugin_manifest cross_compile qpa winrt win32 msvc copy_dir_files debug
#DebugBuild Debug build_pass debug debug DebugBuild Debug build_pass

#winrt phone lex yacc debug exceptions depend_includepath testcase_targets
#import_plugins import_qpa_plugin rtti_off incremental_off windows qt
#warn_on release link_prl incremental flat precompile_header
#autogen_precompile_source debug_and_release debug_and_release_target
#no_generated_target_info package_manifest rtti release shared rtti
#no_plugin_manifest cross_compile qpa winphone winrt win32 msvc copy_dir_files
#release ReleaseBuild Release build_pass

#osx lex yacc debug exceptions depend_includepath testcase_targets
#import_plugins import_qpa_plugin sdk rez qt warn_on release link_prl
#app_bundle incremental global_init_link_order lib_version_first plugin_no_soname
#clang_pch_style shared qpa no_mocdepend release qt_framework
#osx macx mac darwin unix posix gcc clang llvm debug x86_64

#ios lex yacc debug exceptions depend_includepath testcase_targets
#import_plugins import_qpa_plugin sdk rez qt warn_on release link_prl
#app_bundle reduce_exports incremental global_init_link_order lib_version_first
#plugin_no_soname sdk clang_pch_style cross_compile iphonesimulator_and_iphoneos
#static qpa no_mocdepend debug qt_no_framework macx-xcode ios mac darwin unix
#posix gcc clang llvm iphoneos

#android lex yacc debug exceptions depend_includepath testcase_targets import_plugins
#import_qpa_plugin qt warn_on release link_prl android_install unversioned_soname
#unversioned_libname android_deployment_settings android-9 release shared rtti
#no_plugin_manifest cross_compile android-style-assets qpa
#android linux unix posix gcc copy_dir_files debug

# desktop: windows qt c++11 win32 msvc
# winrt: windows qt winrt win32 msvc
# winrt phone: windows qt winphone winrt win32 msvc
# osx: osx macx mac darwin unix posix gcc clang llvm debug x86_64
# ios: iphonesimulator_and_iphoneos macx-xcode ios mac darwin unix posix gcc clang llvm iphoneos
# android: android_install android_deployment_settings android-style-assets android linux unix posix gcc
