#ifndef ARCHIVARIUS_H
#define ARCHIVARIUS_H

#include"filesystem.h"
#include<vector>
#include<sstream>
#include<string>
#include<fstream>
#include<locale>
#include<clocale>
#include<codecvt>
#include<cstring>

#include"../types/imp_error.h"

#define imp_code_extension ".imp"
#define imp_proj_extension ".impctrl"

namespace archivarius {
    class file {
    private:
        std::vector<std::string> _code;
        std::string _path;
        std::string _filename;
        std::string _extension;

        imperr::message _error_message;
    public:
        file() {
            _path = "";
            _filename = "untitled";
            _extension = imp_code_extension;
            _error_message = imperr::message(imperr::file::all_ok,"All ok",_path);
        }

        file(std::string path) {
            filesystem::path p(path);
            _path = p.parent_path();
            _filename = p.stem();
            _extension = p.extension();
            _error_message = imperr::message(imperr::file::all_ok,"All ok",_path);
        }

        file(const archivarius::file& _file_) {
            this->_code = _file_._code;
            this->_path = _file_._path;
            this->_filename = _file_._filename;
            this->_extension = _file_._extension;
            this->_error_message = _file_._error_message;
        }

        ~file() {}

        std::string fpath()     { return _path+(_path!="" ? "/" : "")+_filename+_extension; }
        std::string path()      { return _path; }
        std::string filename()  { return _filename; }
        std::string ext()       { return _extension; }

        void setExtension(std::string exxt) {
            this->_extension = exxt;
        }

        std::vector<std::string> read() {
            _code.clear();
            std::stringstream ss;
            ss << std::ifstream(fpath()).rdbuf();
            std::string line = ss.str();
            std::string row_str = "";
            for (char c : line) {
                if (c == '\n') {
                    _code.push_back(row_str);
                    row_str="";
                }
                else {
                    row_str+=c;
                }
            }
            _code.push_back(row_str);
            return _code;
        }

        bool write(std::vector<std::string> output_code) {
            setlocale(LC_ALL,"ru");
            std::ofstream f(path());
            f.open(fpath());
            if (f.is_open()) {
                for (std::string line : output_code) {
                    f<< line.c_str() <<std::endl;
                }
            }
            else {
                _error_message = imperr::message(imperr::file::write_file_error,"Write file error",fpath());
                f.close();
                return false;
            }
            f.close();
            return true;
        }

        imperr::message geterr() { return _error_message; }
        archivarius::file& operator=(const archivarius::file& _file_) {
            this->_code = _file_._code;
            this->_path = _file_._path;
            this->_filename = _file_._filename;
            this->_extension = _file_._extension;
            this->_error_message = _file_._error_message;
            return *this;
        }
    };
};

#endif // ARCHIVARIUS_H
