#ifndef IMP_TYPE_MATRIX_H
#define IMP_TYPE_MATRIX_H

#include<map>

#include"imp_error.h"
#include"imp_data_types.h"
#include"imp_type_field.h"
#include"imp_type_func.h"

// REFERENCES //
class IMPMatrix;

// DEFINES //
#define impmx IMPMatrix

class IMPMatrix {
    DataTypes dataTypes;
    imperr::message _error_message;
public:
    IMPMatrix() {}
    IMPMatrix(int max_size) : _max_size(max_size) {}
    ~IMPMatrix() {}

    int _max_size;
    std::vector<IMPID> _idents;
    std::vector<IMPID> _args;
    std::vector<bool> _hide_fields;
    std::map<int,IMPFieldInt>   _fields_int;
    std::map<int,IMPFieldByte>  _fields_byte;
    std::map<int,IMPFieldWord>  _fields_word;
    std::map<int,IMPFieldDWord> _fields_dword;
    std::map<int,IMPFieldFloat> _fields_float;
    std::map<int,IMPFieldChar>  _fields_char;
    std::map<int,IMPFieldBool>  _fields_bool;
    std::map<int,IMPFunc>       _funcs;
    std::map<int,IMPMatrix>     _matrixes;

    int findId(std::string name) {
        for (int i = 0; i < _idents.size(); i++) {
            if (_idents[i].name == name) return i;
        }
        return nfind;
    }

    void add_field(IMPID field, bool hide_enable) {
        if (field.type == dataTypes.Int()) {
            _fields_int[_idents.size()] = IMPFieldInt();
            for (int i = 0; i < _max_size; i++) {
                _fields_int[_idents.size()].add(IMPEntityInt());
            }
        }
        else if (field.type == dataTypes.Byte()) {
            _fields_byte[_idents.size()] = IMPFieldByte();
            for (int i = 0; i < _max_size; i++) {
                _fields_byte[_idents.size()].add(IMPEntityByte());
            }
        }
        else if (field.type == dataTypes.Word()) {
            _fields_word[_idents.size()] = IMPFieldWord();
            for (int i = 0; i < _max_size; i++) {
                _fields_word[_idents.size()].add(IMPEntityWord());
            }
        }
        else if (field.type == dataTypes.DWord()) {
            _fields_dword[_idents.size()] = IMPFieldDWord();
            for (int i = 0; i < _max_size; i++) {
                _fields_dword[_idents.size()].add(IMPEntityDWord());
            }
        }
        else if (field.type == dataTypes.Float()) {
            _fields_float[_idents.size()] = IMPFieldFloat();
            for (int i = 0; i < _max_size; i++) {
                _fields_float[_idents.size()].add(IMPEntityFloat());
            }
        }
        else if (field.type == dataTypes.Char()) {
            _fields_char[_idents.size()] = IMPFieldChar();
            for (int i = 0; i < _max_size; i++) {
                _fields_char[_idents.size()].add(IMPEntityChar());
            }
        }
        else if (field.type == dataTypes.Bool()) {
            _fields_bool[_idents.size()] = IMPFieldBool();
            for (int i = 0; i < _max_size; i++) {
                _fields_bool[_idents.size()].add(IMPEntityBool());
            }
        }
        else {
            _error_message = imperr::message(imperr::semantic::data_type_not_allowed,"Data type is not allowed",field.type.name+" "+field.name);
        }
        _idents.push_back(field);
        _args.push_back(field);
        _hide_fields.push_back(hide_enable);
    }

    void add_func(IMPID fnc, IMPDataType result_type, std::vector<IMPID> args, IMPAstNode ret, bool hide_enable) {
        IMPFunc temp(result_type,ret);
        temp.args=args;
        _funcs[_idents.size()] = temp;
        _idents.push_back(fnc);
        _hide_fields.push_back(hide_enable);
    }

    /*
    void add_element(std::vector<std::string> elements) {
        if (elements.size()!=_field_num) {
            _error_message = imperr::message(imperr::semantic::unable_to_create_an_instance,"Unable to create an instance in matrix","Invalid number of arguments");
            return;
        }
        for (int i = 0; i < _cur_index; i++) {
            if (_fields_int.find(i) != _fields_int.end()) {
                _fields_int[i].add(IMPEntityChar(elements[i]));
            }
            else if (_fields_float.find(i) != _fields_float.end()) {
                _fields_float[i].add(IMPEntityChar(elements[i]));
            }
            else if (_fields_char.find(i) != _fields_char.end()) {
                _fields_char[i].add(IMPEntityChar(elements[i]));
            }
            else if (_fields_bool.find(i) != _fields_bool.end()) {
                _fields_bool[i].add(IMPEntityChar(elements[i]));
            }
        }
    }

    void set_element(int element_index,std::vector<std::string> elements) {
        if (elements.size()!=_field_num) {
            _error_message = imperr::message(imperr::semantic::unable_to_create_an_instance,"Unable to create an instance in matrix","Invalid number of arguments");
            return;
        }
        for (int i = 0; i < _cur_index; i++) {
            if (_fields_int.find(i) != _fields_int.end()) {
                _fields_int[i].set(element_index, IMPEntityChar(elements[i]));
            }
            else if (_fields_float.find(i) != _fields_float.end()) {
                _fields_float[i].set(element_index, IMPEntityChar(elements[i]));
            }
            else if (_fields_char.find(i) != _fields_char.end()) {
                _fields_char[i].set(element_index, IMPEntityChar(elements[i]));
            }
            else if (_fields_bool.find(i) != _fields_bool.end()) {
                _fields_bool[i].set(element_index, IMPEntityChar(elements[i]));
            }
        }
    }
    */

    std::string show() {
        std::string temp="";        
        for (int i = 0; i < _idents.size(); i++) {
            if (_fields_int.find(i) != _fields_int.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _fields_int[i].show() + "\n";
            }
            else if (_fields_byte.find(i) != _fields_byte.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _fields_byte[i].show() + "\n";
            }
            else if (_fields_word.find(i) != _fields_word.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _fields_word[i].show() + "\n";
            }
            else if (_fields_dword.find(i) != _fields_dword.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _fields_dword[i].show() + "\n";
            }
            else if (_fields_float.find(i) != _fields_float.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _fields_float[i].show() + "\n";
            }
            else if (_fields_char.find(i) != _fields_char.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _fields_char[i].show() + "\n";
            }
            else if (_fields_bool.find(i) != _fields_bool.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _fields_bool[i].show() + "\n";
            }
            else if (_funcs.find(i) != _funcs.end()) {
                temp += (isHide(i)?"hide\t":"\t") + _idents[i].type.name + " " + _idents[i].name + "\t" + _funcs[i].show() + "\n";
            }
        }
        return temp;
    }

    std::string show(int index) {
        std::string temp="";
        for (int i = 0; i < _idents.size(); i++) {
            if (_fields_int.find(i) != _fields_int.end()) {
                temp += _idents[i].name + "\t" + _fields_int[i].show(index) + "\n";
            }
            else if (_fields_byte.find(i) != _fields_byte.end()) {
                temp += _idents[i].name + "\t" + _fields_byte[i].show(index) + "\n";
            }
            else if (_fields_word.find(i) != _fields_word.end()) {
                temp += _idents[i].name + "\t" + _fields_word[i].show(index) + "\n";
            }
            else if (_fields_dword.find(i) != _fields_dword.end()) {
                temp += _idents[i].name + "\t" + _fields_dword[i].show(index) + "\n";
            }
            else if (_fields_float.find(i) != _fields_float.end()) {
                temp += _idents[i].name + "\t" + _fields_float[i].show(index) + "\n";
            }
            else if (_fields_char.find(i) != _fields_char.end()) {
                temp += _idents[i].name + "\t" + _fields_char[i].show(index) + "\n";
            }
            else if (_fields_bool.find(i) != _fields_bool.end()) {
                temp += _idents[i].name + "\t" + _fields_bool[i].show(index) + "\n";
            }
        }
        return temp;
    }

    std::string type() {
        std::string temp="Matrix";
        for (int i = 0; i < _idents.size(); i++) {
            if (_fields_int.find(i) != _fields_int.end()) {
                temp += " " + _fields_int[i].type();
            }
            else if (_fields_byte.find(i) != _fields_byte.end()) {
                temp += " " + _fields_byte[i].type();
            }
            else if (_fields_word.find(i) != _fields_word.end()) {
                temp += " " + _fields_word[i].type();
            }
            else if (_fields_dword.find(i) != _fields_dword.end()) {
                temp += " " + _fields_dword[i].type();
            }
            else if (_fields_float.find(i) != _fields_float.end()) {
                temp += " " + _fields_float[i].type();
            }
            else if (_fields_char.find(i) != _fields_char.end()) {
                temp += " " + _fields_char[i].type();
            }
            else if (_fields_bool.find(i) != _fields_bool.end()) {
                temp += " " + _fields_bool[i].type();
            }
        }
        return temp;
    }

    int size() { return _idents.size(); }

    bool isHide(int field_index) { return _hide_fields[field_index]; }

    imperr::message geterr() { return _error_message; }
};

#endif //IMP_TYPE_MATRIX_H
