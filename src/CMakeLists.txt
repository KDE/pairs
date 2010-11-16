set(kmemory_SRCS memorytheme.cpp newmemorydialog.cpp carditem.cpp
   kmemory.cpp
   main.cpp
   kmemoryview.cpp
 )

kde4_add_ui_files(kmemory_SRCS newmemorydialog.ui)

kde4_add_kcfg_files(kmemory_SRCS settings.kcfgc )

kde4_add_executable(kmemory ${kmemory_SRCS})

target_link_libraries(kmemory ${KDE4_KDEUI_LIBS} )

install(TARGETS kmemory ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES kmemory.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES kmemory.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES kmemoryui.rc  DESTINATION  ${DATA_INSTALL_DIR}/kmemory )
