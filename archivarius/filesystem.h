#include<iostream>
#include<string>

// parent_path()    : returns the path to the current file
// stem()           : returns the filename (without extension)
// extension()      : returns the file extension

namespace filesystem {
    class path {
    private:
        std::string _filepath;
        std::string _parent_path;
        std::string _stem;
        std::string _extension;

    public:
        path(std::string filepath) {
            _filepath = filepath;
            _parent_path = "";
            _stem = "";
            _extension = "";
            std::string gstack = filepath;
            std::string fstack = "";
            while (gstack.size() > 0) {
                char curc = gstack.back();
                if (curc == '/' or curc == '\\') {
                    gstack.pop_back();
                    _parent_path = gstack;
                    std::string fnamestack = "";
                    bool write_extension = false;
                    while (fstack.size() > 0) {
                        char cc = fstack.back();
                        if (write_extension) {
                            _extension.push_back(fstack.back());
                            fstack.pop_back();
                        }
                        else if (cc == '.') {
                            _stem = fnamestack;
                            _extension.push_back(fstack.back());
                            fstack.pop_back();
                            write_extension = true;
                        }
                        else {
                            fnamestack.push_back(cc);
                            fstack.pop_back();
                        }
                    }
                    break;
                }
                else {
                    fstack.push_back(curc);
                    gstack.pop_back();
                }
            }
        }
        ~path() {}

        std::string parent_path() { return _parent_path; }

        std::string stem() { return _stem; }

        std::string extension() { return _extension; }
    };
};