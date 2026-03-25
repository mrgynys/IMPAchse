#ifndef IMP_TYPE_ENTITY_H
#define IMP_TYPE_ENTITY_H

#include<stdint.h>
#include<string>

#include"imp_error.h"

// REFERENCES //
class IMPEntityType;
class IMPEntityInt;
class IMPEntityByte;
class IMPEntityWord;
class IMPEntityDWord;
class IMPEntityFloat;
class IMPEntityChar;
class IMPEntityBool;
class IMPEntityNull;

// DEFINES //
#define entity_null IMPEntityNull // IMP entity null

#define enull_show "ENULL"

// CORE ENTITY TYPE //
class IMPEntityType {
    imperr::message _error_message;
public:
    virtual std::string show() = 0;
    virtual std::string type() = 0;
    imperr::message geterr() { return _error_message; }
};

// ENTITY TYPES //

class IMPEntityInt : public IMPEntityType {
    int _value;
public:
    IMPEntityInt() { _value=0; }
    IMPEntityInt(int value) { _value=value; }
    IMPEntityInt(const IMPEntityInt &entity) { _value=entity._value; }
    ~IMPEntityInt() {}

    std::string show() { return std::to_string(_value); }
    std::string type() { return "EntityInt"; }
    
    int set(const int value) { _value=value; return 0; }
    int get() { return _value; }

    operator int()              const { return _value; }
    operator uint8_t()          const { return _value; }
    operator uint16_t()         const { return _value; }
    operator uint32_t()         const { return _value; }
    operator double()           const { return _value; }
    operator std::string()      const { return std::to_string(_value); }
    operator bool()             const { return _value>0; }
};

class IMPEntityByte : public IMPEntityType {
    uint8_t _value;
public:
    IMPEntityByte() { _value=0; }
    IMPEntityByte(uint8_t value) { _value=value; }
    IMPEntityByte(const IMPEntityByte &entity) { _value=entity._value; }
    ~IMPEntityByte() {}

    std::string show() { return std::to_string(_value); }
    std::string type() { return "EntityByte"; }
    
    uint8_t set(const uint8_t value) { _value=value; return 0; }
    uint8_t get() { return _value; }

    operator int()              const { return _value; }
    operator uint8_t()          const { return _value; }
    operator uint16_t()         const { return _value; }
    operator uint32_t()         const { return _value; }
    operator double()           const { return _value; }
    operator std::string()      const { return std::to_string(_value); }
    operator bool()             const { return _value>0; }
};

class IMPEntityWord : public IMPEntityType {
    uint16_t _value;
public:
    IMPEntityWord() { _value=0; }
    IMPEntityWord(uint16_t value) { _value=value; }
    IMPEntityWord(const IMPEntityWord &entity) { _value=entity._value; }
    ~IMPEntityWord() {}

    std::string show() { return std::to_string(_value); }
    std::string type() { return "EntityWord"; }
    
    uint16_t set(const uint16_t value) { _value=value; return 0; }
    uint16_t get() { return _value; }

    operator int()              const { return _value; }
    operator uint8_t()          const { return _value; }
    operator uint16_t()         const { return _value; }
    operator uint32_t()         const { return _value; }
    operator double()           const { return _value; }
    operator std::string()      const { return std::to_string(_value); }
    operator bool()             const { return _value>0; }
};

class IMPEntityDWord : public IMPEntityType {
    uint32_t _value;
public:
    IMPEntityDWord() { _value=0; }
    IMPEntityDWord(uint32_t value) { _value=value; }
    IMPEntityDWord(const IMPEntityDWord &entity) { _value=entity._value; }
    ~IMPEntityDWord() {}

    std::string show() { return std::to_string(_value); }
    std::string type() { return "EntityDWord"; }
    
    uint32_t set(const uint32_t value) { _value=value; return 0; }
    uint32_t get() { return _value; }

    operator int()              const { return _value; }
    operator uint8_t()          const { return _value; }
    operator uint16_t()         const { return _value; }
    operator uint32_t()         const { return _value; }
    operator double()           const { return _value; }
    operator std::string()      const { return std::to_string(_value); }
    operator bool()             const { return _value>0; }
};

class IMPEntityFloat : public IMPEntityType {
    double _value;
public:
    IMPEntityFloat() { _value=0; }
    IMPEntityFloat(double value) { _value=value; }
    IMPEntityFloat(const IMPEntityFloat &entity) { _value=entity._value; }
    ~IMPEntityFloat() {}

    std::string show() { return std::to_string(_value); }
    std::string type() { return "EntityFloat"; }

    int set(const double value) { _value=value; return 0; }
    double get() { return _value; }

    operator int()              const { return _value; }
    operator uint8_t()          const { return _value; }
    operator uint16_t()         const { return _value; }
    operator uint32_t()         const { return _value; }
    operator double()           const { return _value; }
    operator std::string()      const { return std::to_string(_value); }
    operator bool()             const { return _value>0; }
};

class IMPEntityChar : public IMPEntityType {
    std::string _value;
public:
    IMPEntityChar() { _value=""; }
    IMPEntityChar(std::string value) { _value=value; }
    IMPEntityChar(const char* value) { _value=value; }
    IMPEntityChar(const IMPEntityChar &entity) { _value=entity._value; }
    ~IMPEntityChar() {}

    std::string show() { return _value; }
    std::string type() { return "EntityChar"; }

    int set(const char value) { _value=value; return 0; }
    std::string get() { return _value; }

    operator int()              const { return std::stoi(_value); }
    operator uint8_t()          const { return std::stoi(_value); }
    operator uint16_t()         const { return std::stoi(_value); }
    operator uint32_t()         const { return std::stoi(_value); }
    operator double()           const { return std::stod(_value); }
    operator std::string()      const { return _value; }
    operator bool()             const {
        std::string temp = "";
        for (char c : _value)
            if (std::isupper(c))
                temp += std::toupper(c);
            else temp += c;
        if (temp=="T"||temp=="TRUE")
            return true;
        else if (temp=="F"||temp=="FALSE")
            return false;
        //_error_message = imperr::message(imperr::warning::implicit_conversion,"Implicit conversation",this->type());
        return false;
    }
};

class IMPEntityBool : public IMPEntityType {
    bool _value;
public:
    IMPEntityBool() { _value=false; }
    IMPEntityBool(bool value) { _value=value; }
    IMPEntityBool(const IMPEntityBool &entity) { _value=entity._value; }
    ~IMPEntityBool() {}
    
    std::string show() { return _value ? "T" : "F"; }
    std::string type() { return "EntityBool"; }

    int set(const bool value) { _value=value; return 0; }
    bool get() { return _value; }

    operator int()              const { return _value; }
    operator uint8_t()          const { return _value; }
    operator uint16_t()         const { return _value; }
    operator uint32_t()         const { return _value; }
    operator double()           const { return _value; }
    operator std::string()      const { return _value ? "T" : "F"; }
    operator bool()             const { return _value; }
};

class IMPEntityNull : public IMPEntityType {
public:
    IMPEntityNull() {}
    IMPEntityNull(const IMPEntityNull &entity) {}
    ~IMPEntityNull() {}
    
    std::string show() { return enull_show; }
    std::string type() { return "EntityNULL"; }
};

#endif //IMP_TYPE_ENTITY_H
