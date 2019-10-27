#ifndef STORAGE_H
#define STORAGE_H

class Storage
{
    public:
        static Storage& getInstance() {
            static Storage instance;
            return instance;
        }
        void create() {
            std::experimental::filesystem::path path = this->path;

            if (!exists(path)) {
                create_directory(path);
            }

            path += "config.json";

            if (!exists(path)) {
                nlohmann::json result;

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

                result["throttleMode"]["step"] = 25;

                std::ofstream out(path);
                out << result.dump();
                out.close();
            }
        }
        Storage * open() {
            if (!this->isOpened) {
                std::experimental::filesystem::path path = this->path;
                path += "config.json";

                if (exists(path)) {
                    std::ifstream ifs(path);
                    this->data = nlohmann::json::parse(ifs);
                    this->isOpened = true;
                }

                return this;
            }
        }
        nlohmann::json getData() {
            this->open();
            return this->data;
        }
        Storage * setData(nlohmann::json data) {
            this->data = data;
            return this;
        }
        void save() {
             std::experimental::filesystem::path path = this->path;
             path += "config.json";

             if (exists(path)) {
                 std::ofstream out(path);
                 out << this->data.dump();
                 out.close();
             }
        }
    private:
        Storage() {
            this->path = std::experimental::filesystem::path(QString(QString(getenv("HOME")) + QString("/.drone/")).toStdString());
        }
        Storage(Storage const&);
        void operator=(Storage const&);
        nlohmann::json data;
        std::experimental::filesystem::path path;
        bool isOpened = false;
};

#endif // STORAGE_H
