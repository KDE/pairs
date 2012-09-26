project( mainwindow )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
find_package( KDE4 REQUIRED )
SET( MAIN_PROJECT_NAME ${PROJECT_NAME})



INCLUDE_DIRECTORIES( ${KDE4_INCLUDES}  )

SET(CPACK_SET_DESTDIR "ON")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include_directories( ${KDE4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

add_definitions( ${KDE4_DEFINITIONS} )

set( ptedit_SOURCES mainwindow.cpp main.cpp pairstheme.cpp thememodel.cpp elementitem.cpp
                    featureitem.cpp )

set( mainwindow_cfg_UI mainwindow.ui )

kde4_add_ui_files( ptedit_SOURCES ${mainwindow_cfg_UI} )

kde4_add_executable( ptedit ${ptedit_SOURCES} )

target_link_libraries( ptedit ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${QT_QTXMLPATTERNS_LIBRARY})
install(TARGETS ptedit ${INSTALL_TARGETS_DEFAULT_ARGS})



