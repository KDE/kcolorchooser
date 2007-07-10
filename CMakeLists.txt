project(kcolorchooser)

set(kcolorchooser_SRCS kcolorchooser.cpp )


kde4_add_executable(kcolorchooser ${kcolorchooser_SRCS})

target_link_libraries(kcolorchooser ${KDE4_KDEUI_LIBS})

install(TARGETS kcolorchooser  DESTINATION ${BIN_INSTALL_DIR} )
install( FILES kcolorchooser.desktop  DESTINATION  ${XDG_APPS_DIR} )

kde4_install_icons( ${ICON_INSTALL_DIR}   )

