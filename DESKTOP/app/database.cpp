#include "include.h"

using namespace std::experimental::filesystem::v1;

Database::Database() {
    this->_path = Path(QString(QString(getenv("HOME")) + QString("/.drone/")).toStdString());

    Path _path = this->_path;

    if (!exists(_path)) {
        create_directory(_path);

        _path += CONFIG_FILENAME;

        if (!exists(_path)) {
            this->_createFile(_path);
        }
    }
}
