project(pairseditor)

set(pairseditor_SOURCES  mainwindow.cpp main.cpp pairsthemeeditor.cpp mainwindowview.cpp
    thememodel.cpp elementitem.cpp featureitem.cpp ../game/pairsthemebase.cpp)

kde4_add_ui_files( pairseditor_SOURCES mainwindowview.ui )

kde4_add_app_icon(pairs_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../icons/hi*-apps-pairseditor.png")

kde4_add_executable( pairseditor ${pairseditor_SOURCES} )

target_link_libraries( pairseditor ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_PHONON_LIBS}
					${QT_QTXMLPATTERNS_LIBRARY})
install(TARGETS pairseditor ${INSTALL_TARGETS_DEFAULT_ARGS})
install( FILES pairseditor.desktop DESTINATION  ${XDG_APPS_INSTALL_DIR})
install( FILES pairseditorui.rc DESTINATION ${DATA_INSTALL_DIR}/pairseditor)



