#pragma once
#include "include.h"

class FileSystem {
public:
#ifdef WIN32
    static void createDirectory(QString _path) {
        CreateDirectoryA(_path.toStdString().c_str(), NULL);
    }
    static T_Bool isDirectory(QString _path) {
        DWORD ftyp = GetFileAttributesA(_path.toStdString().c_str());

        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
    }
    static T_Bool isFile(QString _path) {
        std::ifstream f;
        f.open(_path.toStdString());

        if (f.is_open()) {
            f.close();
            return true;
        }

        return false;
    }
    static T_Bool createFile(QString _path) {
        HANDLE h = CreateFileA(_path.toStdString().c_str(),     // name of the file
                                  GENERIC_WRITE,                // open for writing
                                  0,                            // sharing mode, none in this case
                                  0,                            // use default security descriptor
                                  CREATE_ALWAYS,                // overwrite if exists
                                  FILE_ATTRIBUTE_NORMAL,
                                  0);
        if (h) {
           CloseHandle(h);
           return true;
        }

        return false;
    }
    static QString getUserDirectory() {
        char * _dir = getenv("APPDATA");
        return QString(_dir);
    }
#endif
#ifndef WIN32
    static void createDirectory(QString _path) {
        std::experimental::filesystem::create_directory(std::experimental::filesystem::path(_path.toStdString()));
    }
    static T_Bool isDirectory(QString _path) {
        return std::experimental::filesystem::is_directory(std::experimental::filesystem::path(_path.toStdString()));
    }
    static T_Bool isFile(QString _path) {
        return std::experimental::filesystem::exists(std::experimental::filesystem::path(_path.toStdString())) && !FileSystem::isDirectory(_path);
    }
    static T_Bool createFile(QString _path) {
        std::ofstream file(_path.toStdString());
        file << "";
        file.close();

        return FileSystem::isFile(_path);
    }
    static QString getUserDirectory() {
        return QString(getenv("HOME"));
    }
#endif
};
