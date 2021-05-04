#include "fonts.h"

Fonts::Fonts() {}

void Fonts::Load(string dataPath) {
    cout << "DPENV: " << dataPath << endl;

    string PATH0 = dataPath + "resources/fonts/Livvic-Light.ttf";
    string PATH1 = dataPath + "resources/fonts/LEMONMILK-Bold.otf";
    string PATH2 = dataPath + "resources/fonts/Livvic-Light.ttf";

    fontStore[0] = LoadFontEx(PATH0.c_str(), 32, 0, 250);
    fontStore[1] = LoadFontEx(PATH1.c_str(), 80, 0, 250);
    fontStore[2] = LoadFontEx(PATH2.c_str(), 16, 0, 250);
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

Font Fonts::BodySmall() {
    return fontStore[2];
}