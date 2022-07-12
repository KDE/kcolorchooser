cmake_minimum_required (VERSION 3.16 FATAL_ERROR)

# KDE Application Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "22")
set(RELEASE_SERVICE_VERSION_MINOR "11")
set(RELEASE_SERVICE_VERSION_MICRO "70")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(kcolorchooser VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION     "5.15.0")
set(KF5_MIN_VERSION    "5.90.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMInstallIcons)
include(ECMAddAppIcon)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMSetupVersion)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
  Core
  Gui
  Widgets)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
  CoreAddons
  I18n
  XmlGui)

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_definitions(
    -DQT_DISABLE_DEPRECATED_BEFORE=0x050f00
    -DQT_DEPRECATED_WARNINGS_SINCE=0x060000
    -DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x055900
    -DKF_DEPRECATED_WARNINGS_SINCE=0x060000
)

ecm_setup_version(${RELEASE_SERVICE_VERSION} VARIABLE_PREFIX KCOLORCHOOSER VERSION_HEADER kcolorchooser_version.h)

add_executable(kcolorchooser)
target_sources(kcolorchooser PRIVATE kcolorchooser.cpp )


target_link_libraries(kcolorchooser
	Qt${QT_MAJOR_VERSION}::Gui
	KF5::CoreAddons
	KF5::I18n
	KF5::XmlGui
)

install(TARGETS kcolorchooser  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kcolorchooser.desktop DESTINATION  ${KDE_INSTALL_APPDIR})

ecm_install_icons(ICONS
  16-apps-kcolorchooser.png
  22-apps-kcolorchooser.png
  DESTINATION ${KDE_INSTALL_ICONDIR}
  THEME hicolor)

install(FILES org.kde.kcolorchooser.appdata.xml  DESTINATION  ${KDE_INSTALL_METAINFODIR})

ki18n_install(po)
