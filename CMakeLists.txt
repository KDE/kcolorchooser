cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

# KDE Application Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "20")
set(RELEASE_SERVICE_VERSION_MINOR "08")
set(RELEASE_SERVICE_VERSION_MICRO "0")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(kcolorchooser VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION     "5.7.0")
set(KF5_MIN_VERSION    "5.30.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMInstallIcons)
include(ECMAddAppIcon)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMSetupVersion)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
  Core
  Gui
  Widgets)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
  I18n
  XmlGui)

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)


if (KF5ConfigWidgets_VERSION VERSION_GREATER "5.56.0")
        add_definitions(-DQT_NO_FOREACH)
        MESSAGE(STATUS "compile without foreach")
endif()

ecm_setup_version(${RELEASE_SERVICE_VERSION} VARIABLE_PREFIX KCOLORCHOOSER VERSION_HEADER kcolorchooser_version.h)

set(kcolorchooser_SRCS kcolorchooser.cpp )

add_executable(kcolorchooser ${kcolorchooser_SRCS})

target_link_libraries(kcolorchooser Qt5::Gui KF5::I18n KF5::XmlGui)

install(TARGETS kcolorchooser  ${INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kcolorchooser.desktop DESTINATION  ${XDG_APPS_INSTALL_DIR})

ecm_install_icons(ICONS
  16-apps-kcolorchooser.png
  22-apps-kcolorchooser.png
  DESTINATION ${KDE_INSTALL_ICONDIR}
  THEME hicolor)

install(FILES org.kde.kcolorchooser.appdata.xml  DESTINATION  ${KDE_INSTALL_METAINFODIR})
