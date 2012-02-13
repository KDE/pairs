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

macro(filter_strings output regex)
    set(${output} "")
    foreach(a IN ITEMS ${ARGN})
        if(NOT a MATCHES ${regex})
            message(STATUS "---- ${a}")
            list(APPEND ${output} ${a})
        endif()
    endforeach(a)
endmacro(filter_strings)

function(create_theme _baseName)
    if(WIN32)
        set(_template ${CMAKE_CURRENT_BINARY_DIR}/${_baseName}.pairs.zip)
    else(WIN32)
        set(_template ${CMAKE_CURRENT_BINARY_DIR}/${_baseName}.pairs.tar.bz2)
    endif(WIN32)
    
    file(GLOB _files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}/" "${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}/*" )
    filter_strings(_files "~" ${_files})
    add_custom_target(${_baseName} ALL DEPENDS ${_template})

    if(WIN32)
        add_custom_command(OUTPUT ${_template}
            COMMAND zip ARGS -r
                ${_template} ${_files}
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}"
        )
    else(WIN32)
        add_custom_command(OUTPUT ${_template}
            COMMAND tar ARGS cjf
                ${_template} ${_files}
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}"
        )
    endif(WIN32)
    
    install(FILES ${_template} DESTINATION ${DATA_INSTALL_DIR}/pairs/themes)
endfunction(create_theme)

create_theme(animals)
create_theme(kde)
create_theme(zoo)
create_theme(linux)
install( FILES right.ogg wrong.ogg game.xsd DESTINATION  ${DATA_INSTALL_DIR}/pairs/themes )
install( FILES pairs.knsrc  DESTINATION  ${CONFIG_INSTALL_DIR} )
