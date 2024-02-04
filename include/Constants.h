/* 
dsv-cprog-space-invaders - A space invaders inspired shooter written in C++ with SDL2
Copyright (C) 2024 Edwin Sundberg and Erik Lind Gou-Said

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
typedef unsigned long long wlong;
namespace constants
{
    //gResPath-contains the relative path to your resources.
    //if '/resources/' is used, use the following:
	const std::string gResPath = "../../resources/";
    
    //if '/build/debug/resources/' is used, use the following:

    // const std::string gResPath = "./resources/";
    const unsigned int FPS = 80;
}

#endif