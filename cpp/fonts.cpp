#include "fonts.h"

Fonts::Fonts() {}

void Fonts::Load() {
    fontStore[0] = LoadFontEx("resources/fonts/Livvic-Light.ttf", 32, 0, 250);
    fontStore[1] = LoadFontEx("resources/fonts/LEMONMILK-Bold.otf", 80, 0, 250);
}

void Fonts::Unload() {
    for (int i = 0; i > sizeof(fontStore); i++) {
        UnloadFont(fontStore[i]);
    }
}

Font Fonts::Body() {
    return fontStore[0];
}

Font Fonts::Title() {
    return fontStore[1];
}