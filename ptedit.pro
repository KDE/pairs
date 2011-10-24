TEMPLATE = app
TARGET = ptedit
QT += core \
    gui \
    xml \
    xmlpatterns
HEADERS += ptedit.h
SOURCES += build/ptedit_automoc.cpp \
    build/CMakeTmp/check_qt_visibility.cpp \
    build/CMakeFiles/CompilerIdC/CMakeCCompilerId.c \
    build/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.cpp \
    main.cpp \
    ptedit.cpp
FORMS += ptedit.ui
RESOURCES += 
