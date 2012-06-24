project( ptedit_1 )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
find_package( KDE4 REQUIRED )
SET( MAIN_PROJECT_NAME ${PROJECT_NAME})



INCLUDE_DIRECTORIES( ${KDE4_INCLUDES}  )

SET(CPACK_SET_DESTDIR "ON")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include_directories( ${KDE4_INCLUDE_DIRS} ${libkdepim_INCLUDES})

add_definitions( ${KDE4_DEFINITIONS} )

set( SOURCES ptedit_1.cpp 
main.cpp)

set( SOURCES ptedit_1.ui )
kde4_add_ui_files( SOURCES ${UI} )

kde4_add_executable( SOURCES ${SOURCES})


target_link_libraries( ptedit_1 
${KDE4_KDEUI_LIBS}
)
install(TARGETS ptedit_1 ${INSTALL_TARGETS_DEFAULT_ARGS})



