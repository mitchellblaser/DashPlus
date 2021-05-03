/*
DashPlus
Mitchell Blaser 2021.
http://github.com/mitchellblaser/dashplus
*/

#include <raylib.h>

class Fonts {
    public:
        Fonts();
        void Load();
        void Unload();
        Font Body();
        Font Title();
    private:
        Font fontStore[1] = {0};
};