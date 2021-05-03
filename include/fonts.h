/*
DashPlus
Mitchell Blaser 2021.
http://github.com/mitchellblaser/dashplus
*/

#include <raylib.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Fonts {
    public:
        Fonts();
        void Load(string dataPath);
        void Unload();
        Font Body();
        Font Title();
    private:
        Font fontStore[1] = {0};
};