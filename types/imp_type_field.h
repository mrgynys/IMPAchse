#ifndef IMP_TYPE_FIELD_H
#define IMP_TYPE_FIELD_H

#include<vector>

#include"imp_type_entity.h"
#include"imp_type_func.h"
#include"imp_error.h"

// REFERENCES //
class IMPFieldType;
class IMPFieldInt;
class IMPFieldByte;
class IMPFieldWord;
class IMPFieldDWord;
class IMPFieldFloat;
class IMPFieldChar;
class IMPFieldBool;
class IMPFieldNull;

// DEFINES //
#define field_null IMPFieldNull //IMP field null

#define fnull_show "FNULL"

// CORE FIELD TYPE //
class IMPFieldType {
protected:
    int _id=0;
    imperr::message _error_message;
public:
    virtual std::string show() = 0;
    virtual std::string show(int index) = 0;
    virtual std::string type() = 0;
    virtual int size() = 0;
    int id() { return _id; }
    void set_id(int new_id) { _id=new_id; }
    imperr::message geterr() { return _error_message; }
};

// FIELD TYPES //

class IMPFieldInt : public IMPFieldType {
    std::vector<IMPEntityInt> _values;
public:
    IMPFieldInt() { _values={}; }
    IMPFieldInt(std::vector<IMPEntityInt> values) { _values = values; }
    IMPFieldInt(const IMPFieldInt &field) { _values=field._values; }
    ~IMPFieldInt() { _values.clear(); }

    std::string show() {
        std::string temp = "";
        for (int i = 0; i<_values.size();i++) {
            temp += (i==0 ? "" : " ") + _values[i].show();
        }
        return temp;
    }

    std::string show(int index) {
        if (index<_values.size()) return _values[index].show();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return "";
    }
    
    std::string type() { return "FieldInt"; }
    int size() { return _values.size(); }

    void add(const int value) { this->_values.push_back(value); }
    void add(const IMPEntityInt value) { this->_values.push_back(value); }

    void pop() { this->_values.pop_back(); }

    void set(int index, const int value) { this->_values[index]=value; }
    void set(int index, const IMPEntityInt value) { this->_values[index]=value; }

    std::vector<IMPEntityInt> get() {return _values; }
    IMPEntityInt get(int index) {
        if (index<_values.size()) return _values[index].get();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return IMPEntityInt();
    }
};

class IMPFieldByte : public IMPFieldType {
    std::vector<IMPEntityByte> _values;
public:
    IMPFieldByte() { _values={}; }
    IMPFieldByte(std::vector<IMPEntityByte> values) { _values = values; }
    IMPFieldByte(const IMPFieldByte &field) { _values=field._values; }
    ~IMPFieldByte() { _values.clear(); }

    std::string show() {
        std::string temp = "";
        for (int i = 0; i<_values.size();i++) {
            temp += (i==0 ? "" : " ") + _values[i].show();
        }
        return temp;
    }

    std::string show(int index) {
        if (index<_values.size()) return _values[index].show();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return "";
    }
    
    std::string type() { return "FieldByte"; }
    int size() { return _values.size(); }

    void add(const uint8_t value) { this->_values.push_back(value); }
    void add(const IMPEntityByte value) { this->_values.push_back(value); }

    void pop() { this->_values.pop_back(); }

    void set(int index, const uint8_t value) { this->_values[index]=value; }
    void set(int index, const IMPEntityByte value) { this->_values[index]=value; }

    std::vector<IMPEntityByte> get() {return _values; }
    IMPEntityByte get(int index) {
        if (index<_values.size()) return _values[index].get();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return IMPEntityByte();
    }
};

class IMPFieldWord : public IMPFieldType {
    std::vector<IMPEntityWord> _values;
public:
    IMPFieldWord() { _values={}; }
    IMPFieldWord(std::vector<IMPEntityWord> values) { _values = values; }
    IMPFieldWord(const IMPFieldWord &field) { _values=field._values; }
    ~IMPFieldWord() { _values.clear(); }

    std::string show() {
        std::string temp = "";
        for (int i = 0; i<_values.size();i++) {
            temp += (i==0 ? "" : " ") + _values[i].show();
        }
        return temp;
    }

    std::string show(int index) {
        if (index<_values.size()) return _values[index].show();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return "";
    }
    
    std::string type() { return "FieldWord"; }
    int size() { return _values.size(); }

    void add(const uint16_t value) { this->_values.push_back(value); }
    void add(const IMPEntityWord value) { this->_values.push_back(value); }

    void pop() { this->_values.pop_back(); }

    void set(int index, const uint16_t value) { this->_values[index]=value; }
    void set(int index, const IMPEntityWord value) { this->_values[index]=value; }

    std::vector<IMPEntityWord> get() {return _values; }
    IMPEntityWord get(int index) {
        if (index<_values.size()) return _values[index].get();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return IMPEntityWord();
    }
};

class IMPFieldDWord : public IMPFieldType {
    std::vector<IMPEntityDWord> _values;
public:
    IMPFieldDWord() { _values={}; }
    IMPFieldDWord(std::vector<IMPEntityDWord> values) { _values = values; }
    IMPFieldDWord(const IMPFieldDWord &field) { _values=field._values; }
    ~IMPFieldDWord() { _values.clear(); }

    std::string show() {
        std::string temp = "";
        for (int i = 0; i<_values.size();i++) {
            temp += (i==0 ? "" : " ") + _values[i].show();
        }
        return temp;
    }

    std::string show(int index) {
        if (index<_values.size()) return _values[index].show();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return "";
    }
    
    std::string type() { return "FieldDWord"; }
    int size() { return _values.size(); }

    void add(const uint32_t value) { this->_values.push_back(value); }
    void add(const IMPEntityDWord value) { this->_values.push_back(value); }

    void pop() { this->_values.pop_back(); }

    void set(int index, const uint32_t value) { this->_values[index]=value; }
    void set(int index, const IMPEntityDWord value) { this->_values[index]=value; }

    std::vector<IMPEntityDWord> get() {return _values; }
    IMPEntityDWord get(int index) {
        if (index<_values.size()) return _values[index].get();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return IMPEntityDWord();
    }
};

class IMPFieldFloat : public IMPFieldType {
    std::vector<IMPEntityFloat> _values;
public:
    IMPFieldFloat() { _values={}; }
    IMPFieldFloat(std::vector<IMPEntityFloat> values) { _values = values; }
    IMPFieldFloat(const IMPFieldFloat &field) { _values=field._values; }
    ~IMPFieldFloat() { _values.clear(); }

    std::string show() {
        std::string temp = "";
        for (int i = 0; i<_values.size();i++) {
            temp += (i==0 ? "" : " ") + _values[i].show();
        }
        return temp;
    }

    std::string show(int index) {
        if (index<_values.size()) return _values[index].show();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return "";
    }
    
    std::string type() { return "FieldFloat"; }
    int size() { return _values.size(); }

    void add(const double value) { this->_values.push_back(value); }
    void add(const IMPEntityFloat value) { this->_values.push_back(value); }

    void pop() { this->_values.pop_back(); }

    void set(int index, const double value) { this->_values[index]=value; }
    void set(int index, const IMPEntityFloat value) { this->_values[index]=value; }

    std::vector<IMPEntityFloat> get() {return _values; }
    IMPEntityFloat get(int index) {
        if (index<_values.size()) return _values[index].get();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return IMPEntityFloat();
    }
};

class IMPFieldChar : public IMPFieldType {
    std::vector<IMPEntityChar> _values;
public:
    IMPFieldChar() { _values={}; }
    IMPFieldChar(std::vector<IMPEntityChar> values) { _values = values; }
    IMPFieldChar(const IMPFieldChar &field) { _values=field._values; }
    ~IMPFieldChar() { _values.clear(); }

    std::string show() {
        std::string temp = "";
        for (int i = 0; i<_values.size();i++) {
            temp += (i==0 ? "" : " ") + _values[i].show();
        }
        return temp;
    }

    std::string show(int index) {
        if (index<_values.size()) return _values[index].show();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return "";
    }
    
    std::string type() { return "FieldChar"; }
    int size() { return _values.size(); }

    void add(const std::string value) { this->_values.push_back(value); }
    void add(const IMPEntityChar value) { this->_values.push_back(value); }

    void pop() { this->_values.pop_back(); }

    void set(int index, const std::string value) { this->_values[index]=value; }
    void set(int index, const IMPEntityChar value) { this->_values[index]=value; }

    std::vector<IMPEntityChar> get() {return _values; }
    IMPEntityChar get(int index) {
        if (index<_values.size()) return _values[index].get();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return IMPEntityChar();
    }
};

class IMPFieldBool : public IMPFieldType {
    std::vector<IMPEntityBool> _values;
public:
    IMPFieldBool() { _values={}; }
    IMPFieldBool(std::vector<IMPEntityBool> values) { _values = values; }
    IMPFieldBool(const IMPFieldBool &field) { _values=field._values; }
    ~IMPFieldBool() { _values.clear(); }

    std::string show() {
        std::string temp = "";
        for (int i = 0; i<_values.size();i++) {
            temp += (i==0 ? "" : " ") + _values[i].show();
        }
        return temp;
    }

    std::string show(int index) {
        if (index<_values.size()) return _values[index].show();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return "";
    }
    
    std::string type() { return "FieldBool"; }
    int size() { return _values.size(); }

    void add(const bool value) { this->_values.push_back(value); }
    void add(const IMPEntityBool value) { this->_values.push_back(value); }

    void pop() { this->_values.pop_back(); }

    void set(int index, const bool value) { this->_values[index]=value; }
    void set(int index, const IMPEntityBool value) { this->_values[index]=value; }

    std::vector<IMPEntityBool> get() {return _values; }
    IMPEntityBool get(int index) {
        if (index<_values.size()) return _values[index].get();
        _error_message = imperr::message(imperr::runtime::array_index_out_of_bounds,"Out of bounds",this->type());
        return IMPEntityBool();
    }
};

class IMPFieldNull : public IMPFieldType {
public:
    IMPFieldNull() {}
    IMPFieldNull(const IMPFieldNull &field) {}
    ~IMPFieldNull() {}
    
    std::string show() { return fnull_show; }
    std::string show(int index) { return fnull_show; }
    std::string type() { return "FieldNULL"; }
    int size() { return 0; }
};

#endif //IMP_TYPE_FIELD_H
