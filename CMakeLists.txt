project(kcolorchooser)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules )

# search packages used by KDE
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

add_definitions (${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${QDBUS_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

set(kcolorchooser_SRCS kcolorchooser.cpp )

kde4_add_app_icon(kcolorchooser_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/hi*-app-kcolorchooser.png")

kde4_add_executable(kcolorchooser ${kcolorchooser_SRCS})

target_link_libraries(kcolorchooser ${KDE4_KDEUI_LIBS})

install(TARGETS kcolorchooser  ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS kcolorchooser.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )

kde4_install_icons( ${ICON_INSTALL_DIR}   )

