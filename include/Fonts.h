#ifndef FONTS_H
#define FONTS_H

#include <string>

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