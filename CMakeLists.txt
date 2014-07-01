#  This file is part of Pairs
#
#  Copyright (C) <2010>       <Albert Astals Cid>   <aacid@kde.org>
#  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
#  Copyright (C) <2012>       <Marco Calignano>     <marco.calignano@gmail.com>
#  Copyright (C) <2014>       <Marco Calignano>     <marco.calignano@gmail.com>
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
cmake_minimum_required(VERSION 2.8.12)

project(pairs)


find_package(ECM 0.0.11 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(KF5 REQUIRED COMPONENTS CoreAddons Solid)

add_subdirectory( game )
add_subdirectory( pairseditor )
add_subdirectory( icons )
add_subdirectory( players )
add_subdirectory( gameicons )
add_subdirectory( themes )
add_subdirectory( doc )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

install(FILES pairs.appdata.xml DESTINATION ${SHARE_INSTALL_PREFIX}/appdata/)

