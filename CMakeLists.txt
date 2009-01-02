project(kcolorchooser)

set(kcolorchooser_SRCS kcolorchooser.cpp )

kde4_add_app_icon(kcolorchooser_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/hi*-app-kcolorchooser.png")

kde4_add_executable(kcolorchooser ${kcolorchooser_SRCS})

target_link_libraries(kcolorchooser ${KDE4_KDEUI_LIBS})

install(TARGETS kcolorchooser  ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES kcolorchooser.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )

kde4_install_icons( ${ICON_INSTALL_DIR}   )

