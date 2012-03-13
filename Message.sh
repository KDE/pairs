#!/bin/bash

EXTRACTRC=/usr/bin/extractrc
XGETTEXT=/usr/bin/xgettext

 
# invoke the extractrc script on all .ui, .rc, and .kcfg files in the sources
# the results are stored in a pseudo .cpp file to be picked up by xgettext.
$EXTRACTRC `find . -name \*.rc -o -name \*.ui -o -name \*.kcfg` >> rc.cpp

# call xgettext on all source files. If your sources have other filename
# extensions besides .cc, .cpp, and .h, just add them in the find call.
$XGETTEXT --keyword=i18n `find . -name \*.cc -o -name \*.cpp -o -name \*.h -o -name \*.qml` -o pairs.pot
