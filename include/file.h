/*
DashPlus
Mitchell Blaser 2021.
http://github.com/mitchellblaser/dashplus
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

#ifndef DP_FILE
#define DP_FILE

class File {
    public:
        enum FileType {
            tFile,
            tFolder,
            tNotExist
        };

        File();
        bool FolderExists(string filePath);
        bool IsFile(string filePath);
        bool IsFolder(string filePath);
        bool MakeFolder(string filePath);
        void WriteFile(string filePath, string fileData);
    private:
        bool _PathExists(string filePath);
        FileType _CheckFile(string filePath);
};

#endif