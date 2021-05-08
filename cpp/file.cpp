#include "file.h"

File::File() {}

bool File::FolderExists(string filePath) {
    if (_CheckFile(filePath) != File::tNotExist) {
        return true;
    }
    else {
        return false;
    }
}

bool File::IsFile(string filePath) {
    if (_CheckFile(filePath) != File::tFile) {
        return false;
    }
    else {
        return true;
    }
}

bool File::IsFolder(string filePath) {
    if (_CheckFile(filePath) != File::tFolder) {
        return false;
    }
    else {
        return true;
    }
}

File::FileType File::_CheckFile(string filePath) {
    struct stat info;
    if (stat(filePath.c_str(), &info) == 0) {
        if (info.st_mode & S_IFDIR) {
            return File::tFolder;
        }
        else {
            return File::tFile;
        }
    }
    else {
        return File::tNotExist;
    }
}

bool File::MakeFolder(string filePath) {
    mkdir(filePath.c_str(), 0777);
    if (FolderExists(filePath)) {
        return true;
    } else {
        return false;
    }
}

void File::WriteFile(string filePath, string fileData) {
    ofstream f;
    f.open(filePath);
    f << fileData;
    f.close();
}

string File::ReadFile(string filePath) { //TODO: Implement this function
    return "";
}