project(pairs-editor)
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
find_package( KDE4 REQUIRED )

INCLUDE_DIRECTORIES( ${KDE4_INCLUDES}  )

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include_directories( ${KDE4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

add_definitions( ${KDE4_DEFINITIONS} )

set(pairseditor_SOURCES  mainwindow.cpp main.cpp pairsthemeeditor.cpp mainwindowview.cpp
    thememodel.cpp elementitem.cpp featureitem.cpp ../game/pairsthemebase.cpp)

kde4_add_ui_files( pairseditor_SOURCES mainwindowview.ui )

kde4_add_executable( pairseditor ${pairseditor_SOURCES} )

target_link_libraries( pairseditor ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${QT_QTXMLPATTERNS_LIBRARY})
install(TARGETS pairseditor ${INSTALL_TARGETS_DEFAULT_ARGS})
install( FILES pairseditorui.rc pairseditor.desktop DESTINATION  ${XDG_APPS_INSTALL_DIR})



