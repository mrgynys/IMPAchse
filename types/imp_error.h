#ifndef IMP_ERROR_H
#define IMP_ERROR_H

#include<string>

namespace imperr {

    // Syntax errors: 10XX
    enum syntax {
        unknown_token = 1001,
        multiline_string_is_illegal = 1002,
        unexpected_end_of_comment = 1003
    };

    // Semantic errors: 20XX
    enum semantic {
        unable_to_create_an_instance = 2001,
        expected_token_not_found = 2002,
        parse_crash = 2003,
        incorrect_math_expression = 2004,
        incorrect_string_expression = 2005,
        incorrect_logic_expression = 2006,
        invalid_expression = 2007,
        index_error = 2008,
        args_error = 2009,
        operator_error = 2010,
        out_of_env = 2011,
        unknown_instruction = 2012,
        statement_required = 2013,
        data_type_not_allowed = 2014
    };

    // Runtime errors: 30XX
    enum runtime {
        array_index_out_of_bounds = 3001
    };

    // Linker errors: 40XX
    enum link {
        file_link_crash = 4001
    };

    // Builder errors: 50XX
    enum build {
        unexpected = 5001,
        definition_error = 5002,
        overdefined_ident = 5003,
        unsuitable_datatype = 5004,
        incompatible_operands = 5005,
        unknown_definition = 5006
    };

    // Execute errors: 60XX
    enum exe {
        main_proc_not_found = 6001,
        unknown_procedure = 6002,
        incorrect_procedure_return_type = 6003,
        invalid_number_of_args = 6004,
        cant_assign_a_value_to_func = 6005
    };

    // Warnings: 11XX
    enum warning {
        implicit_conversion = 1101
    };

    // File errors: 22XX
    enum file {
        all_ok = 2200,
        read_file_error = 2201,
        write_file_error = 2202
    };

    class message {
        int _err_code;
        std::string _err_info;
        std::string _err_detail;
        int _err_row;
        int _err_col;
        std::string _err_filename;
    public:
        message() {
            _err_code=0;
            _err_info="Unknown error";
            _err_detail="";
            _err_row=-1;
            _err_col=-1;
            _err_filename="";
        }

        message(int err_code)
            : message() { _err_code=err_code; }
        
        message(int err_code, std::string err_info)
            : message(err_code) { _err_info=err_info; }
        
        message(int err_code, std::string err_info, std::string err_detail)
            : message(err_code, err_info) { _err_detail=err_detail; }
        
        message(int err_code, std::string err_info, std::string err_detail, int row, int col)
            : message(err_code, err_info, err_detail) { _err_row=row; _err_col=col; }
        
        message(int err_code, std::string err_info, std::string err_detail, int row, int col, std::string filename)
            : message(err_code, err_info, err_detail, row, col) { _err_filename=filename; }

        message(const message &MESSAGE) {
            _err_code=MESSAGE._err_code;
            _err_info=MESSAGE._err_info;
            _err_detail=MESSAGE._err_detail;
            _err_row=MESSAGE._err_row;
            _err_col=MESSAGE._err_col;
            _err_filename=MESSAGE._err_filename;
        }

        int code() { return this->_err_code; }
        std::string info() { return this->_err_info; }
        std::string detail() { return this->_err_detail; }
        int row() { return this->_err_row; }
        int col() { return this->_err_col; }
        std::string filename() { return this->_err_filename; }

        int code(int insert_code) { this->_err_code=insert_code; return _err_code; }
        std::string info(std::string insert_info) { this->_err_info=insert_info; return _err_info; }
        std::string detail(std::string insert_detail) { this->_err_detail=insert_detail; return _err_detail; }
        int row(int insert_row) { this->_err_row=insert_row; return _err_row; }
        int col(int insert_col) { this->_err_col=insert_col; return _err_col; }
        std::string filename(std::string insert_filename) { this->_err_filename=insert_filename; return _err_filename; }
        
        std::string show() {
            return (_err_filename!="" ? _err_filename+"::" : "")
                    +"IMP_ERROR_"+std::to_string(_err_code)
                    +"::row_"+std::to_string(_err_row)
                    +"::col_"+std::to_string(_err_col)
                    +"::"+_err_info
                    +(_err_detail!="" ? "::"+_err_detail : "");
        }

        message operator=(const message &MESSAGE) {
            _err_code=MESSAGE._err_code;
            _err_info=MESSAGE._err_info;
            _err_detail=MESSAGE._err_detail;
            _err_row=MESSAGE._err_row;
            _err_col=MESSAGE._err_col;
            _err_filename=MESSAGE._err_filename;
            return *this;
        }
    };
};

#endif //IMP_ERROR_H