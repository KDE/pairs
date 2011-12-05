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

macro(create_translation _baseName)

    set(_source ${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}.ts)
    set(_endfile ${CMAKE_CURRENT_SOURCE_DIR}/${_baseName}.qm)
    add_custom_target(${_baseName} ALL DEPENDS ${_endfile})
    add_custom_command(OUTPUT ${_endfile}
            COMMAND lrelease ${_source}
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    install(FILES ${_endfile} DESTINATION ${DATA_INSTALL_DIR}/pairs/trans)
endmacro(create_translation)

create_translation(lang_it)
create_translation(lang_de)
