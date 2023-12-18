cmake_minimum_required (VERSION 3.16 FATAL_ERROR)

# KDE Application Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "24")
set(RELEASE_SERVICE_VERSION_MINOR "01")
set(RELEASE_SERVICE_VERSION_MICRO "85")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(kcolorchooser VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION     "6.5.0")
set(KF5_MIN_VERSION    "5.240.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMInstallIcons)
include(ECMAddAppIcon)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMSetupVersion)
include(ECMDeprecationSettings)

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
  Core
  Gui
  Widgets)
find_package(KF6 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
  CoreAddons
  I18n
  XmlGui)

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
ecm_set_disabled_deprecation_versions(QT 6.5
     KF 5.240.0
    )

ecm_setup_version(${RELEASE_SERVICE_VERSION} VARIABLE_PREFIX KCOLORCHOOSER VERSION_HEADER kcolorchooser_version.h)

add_executable(kcolorchooser)
target_sources(kcolorchooser PRIVATE kcolorchooser.cpp )


target_link_libraries(kcolorchooser
	Qt6::Gui
	KF6::CoreAddons
	KF6::I18n
	KF6::XmlGui
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
