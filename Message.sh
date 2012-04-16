#  This file is part of Pairs
#
#  Copyright (C) <2012>       <Marco Calignano>   <marco.calignano@googlemail.com>   
#
#  This program is free software; you can redistribute it and/or 
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of   
#  the License or (at your option) version 3 or any later version   
#  accepted by the membership of KDE e.V. (or its successor approved
#  by the membership of KDE e.V.), which shall act as a proxy
#  defined in Section 14 of version 3 of the license.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.


#!/bin/bash

EXTRACTRC=/usr/bin/extractrc
XGETTEXT=/usr/bin/xgettext

 
# invoke the extractrc script on all .ui, .rc, and .kcfg files in the sources
# the results are stored in a pseudo .cpp file to be picked up by xgettext.
$EXTRACTRC `find . -name \*.rc -o -name \*.ui -o -name \*.kcfg` >> rc.cpp

# call xgettext on all source files. If your sources have other filename
# extensions besides .cc, .cpp, and .h, just add them in the find call.
$XGETTEXT --keyword=i18n `find . -name \*.cc -o -name \*.cpp -o -name \*.h -o -name \*.qml` -o $podir/pairs.pot
