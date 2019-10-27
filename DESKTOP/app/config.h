#ifndef CONFIG_H
#define CONFIG_H

#include "include.h"

typedef QString T_Path;
typedef nlohmann::json T_JSON;
typedef std::ifstream T_IFStream;
typedef std::ofstream T_OFStream;

#define CONFIG_FILE_NAME "config.json"

class Config
{
    public:
        static Config& getInstance() {
            static Config instance;
            return instance;
        }

        Config * open() {
            if (!this->isOpened()) {
                if (FileSystem::isFile(this->getFilePath())) {
                    T_IFStream _handle(this->getFilePath().toStdString());
                    this->_data = T_JSON::parse(_handle);
                    this->_is_opened = true;
                }

                return this;
            }
        }
        T_JSON getData() {
            this->open();
            return this->_data;
        }
        Config * setData(T_JSON data) {
            this->_data = data;
            return this;
        }
        void save() {
             if (FileSystem::isFile(this->getFilePath())) {
                 T_OFStream _out(this->getFilePath().toStdString());
                 _out << this->_data.dump();
                 _out.close();
             }
        }
    private:
        Config() {
            this->_directory_path = FileSystem::getUserDirectory();
            this->_file_path = this->_directory_path + CONFIG_FILE_NAME;
            this->create();
        }
        Config(Config const&);
        void operator=(Config const&);
        T_JSON _data;
        T_Path _directory_path;
        T_Path _file_path;
        T_Bool _is_opened = false;
        T_Path getDirectoryPath() {
            return this->_directory_path;
        }
        T_Path getFilePath() {
            return this->_file_path;
        }
        T_Bool isOpened() {
            return this->_is_opened;
        }
        void create() {
            if (!FileSystem::isDirectory(this->getDirectoryPath())) {
                FileSystem::createDirectory(this->getDirectoryPath());
            }

            if (!FileSystem::isFile(this->getFilePath())) {
                T_JSON result;

                result["radio"]["leftX"]["middle"] = 1500;
                result["radio"]["leftX"]["min"] = 1100;
                result["radio"]["leftX"]["max"] = 1900;

                result["radio"]["leftY"]["middle"] = 1500;
                result["radio"]["leftY"]["min"] = 1100;
                result["radio"]["leftY"]["max"] = 1900;

                result["radio"]["rightX"]["middle"] = 1500;
                result["radio"]["rightX"]["min"] = 1100;
                result["radio"]["rightX"]["max"] = 1900;

                result["radio"]["rightY"]["middle"] = 1500;
                result["radio"]["rightY"]["min"] = 1100;
                result["radio"]["rightY"]["max"] = 1900;

                result["arming"]["leftX"] = 2000;
                result["arming"]["leftY"] = 1000;
                result["arming"]["rightX"] = 1500;
                result["arming"]["rightY"] = 1500;
                result["arming"]["time"] = 1000;

                result["disarming"]["leftX"] = 1000;
                result["disarming"]["leftY"] = 1000;
                result["disarming"]["rightX"] = 1500;
                result["disarming"]["rightY"] = 1500;
                result["disarming"]["time"] = 1000;

                result["throttleMode"]["step"] = 20;

                T_OFStream _out(this->getFilePath().toStdString());
                _out << result.dump();
                _out.close();
            }
        }
};

#endif // CONFIG_H
