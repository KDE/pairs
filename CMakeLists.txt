
project(ptedit)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

set(ptedit_SRCS 
   ptedit.cpp 
   main.cpp
 )

kde4_add_ui_files(ptedit_SRCS ptedit.ui)

kde4_add_executable(ptedit ${ptedit_SRCS})

target_link_libraries(ptedit ${KDE4_KDEUI_LIBS})

install(TARGETS ptedit ${INSTALL_TARGETS_DEFAULT_ARGS} )


