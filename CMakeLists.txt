cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0063)
  cmake_policy(SET CMP0063 NEW)
endif()

project(kcolorchooser)

set (QT_MIN_VERSION "5.2.0")

find_package(ECM 1.7.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMInstallIcons)
include(ECMAddAppIcon)
include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
  Core
  Gui
  Widgets)
find_package(KF5 REQUIRED COMPONENTS
  I18n
  XmlGui)

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
