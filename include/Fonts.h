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
#ifndef FONTS_H
#define FONTS_H

#include <string>

// Spelmotorklass - abstraktion för Roboto-fonten
enum Font {
    BLACK,
    BLACK_ITALIC,
    BOLD,
    BOLD_ITALIC,
    ITALIC,
    LIGHT,
    LIGHT_ITALIC,
    MEDIUM,
    MEDIUM_ITALIC,
    REGULAR,
    THIN,
    THIN_ITALIC
};

inline std::string get_font_path(Font font) {
    switch (font) {
        case BLACK:
            return "fonts/Roboto-Black.ttf";
        case BLACK_ITALIC:
            return "fonts/Roboto-BlackItalic.ttf";
        case BOLD:
            return "fonts/Roboto-Bold.ttf";
        case BOLD_ITALIC:
            return "fonts/Roboto-BoldItalic.ttf";
        case ITALIC:
            return "fonts/Roboto-Italic.ttf";
        case LIGHT:
            return "fonts/Roboto-Light.ttf";
        case LIGHT_ITALIC:
            return "fonts/Roboto-LightItalic.ttf";
        case MEDIUM:
            return "fonts/Roboto-Medium.ttf";
        case MEDIUM_ITALIC:
            return "fonts/Roboto-MediumItalic.ttf";
        case REGULAR:
            return "fonts/Roboto-Regular.ttf";
        case THIN:
            return "fonts/Roboto-Thin.ttf";
        case THIN_ITALIC:
            return "fonts/Roboto-ThinItalic.ttf";
        default:
            return "fonts/Roboto-Regular.ttf";
    }
}

#endif