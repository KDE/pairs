# This file is part of Pairs
#
#  Copyright (C) <2010>       <Albert Astals Cid>   <aacid@kde.org>
#  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
#  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@gmail.com>
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


set(pairs_SRCS 
   pairstheme.cpp 
   pairsthemebase.cpp
   carditem.cpp
   pairs.cpp
   main.cpp
   pairsview.cpp
   pairsplayer.cpp
   themesmodel.cpp
   playersmodel.cpp
   themeiconsprovider.cpp
 )

qt4_add_resources(pairs_SRCS resources.qrc)

kde4_add_app_icon(pairs_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../icons/hi*-apps-pairs*")

kde4_add_executable(pairs ${pairs_SRCS})

target_link_libraries(pairs ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_PHONON_LIBS}
    ${QT_QTXMLPATTERNS_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY} ${KDE4_KNEWSTUFF3_LIBS}
    ${QT_QTOPENGL_LIBRARY} kdeclarative
)

install(TARGETS pairs ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES pairs.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
