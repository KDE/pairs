project(pairseditor)

set(pairseditor_SOURCES  mainwindow.cpp main.cpp pairsthemeeditor.cpp mainwindowview.cpp
    thememodel.cpp elementitem.cpp featureitem.cpp ../game/pairsthemebase.cpp)

qt5_wrap_ui( pairseditor_SOURCES mainwindowview.ui )

#kde4_add_app_icon(pairs_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../icons/hi*-apps-pairseditor*")

add_executable( pairseditor ${pairseditor_SOURCES} )

target_link_libraries( pairseditor Qt5::Xml KF5::XmlGui Phonon::phonon4qt5 KF5::KDELibs4Support KF5::Archive)
install(TARGETS pairseditor ${INSTALL_TARGETS_DEFAULT_ARGS})
install( FILES pairseditor.desktop DESTINATION  ${XDG_APPS_INSTALL_DIR})
install( FILES pairseditorui.rc DESTINATION ${DATA_INSTALL_DIR}/pairseditor)



