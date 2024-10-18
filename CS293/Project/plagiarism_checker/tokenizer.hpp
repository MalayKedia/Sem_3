#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#pragma once
#include <clang-c/Index.h>

// You should NOT modify ANYTHING in this file.

class tokenizer_t {
public:
    tokenizer_t(std::string __file_name);
    ~tokenizer_t(void);
    std::vector<int> get_tokens(void);

protected:
    std::string file_name;
    CXTranslationUnit unit;
    CXIndex index;
    bool is_from_main_file(CXCursor __cursor);
    struct tokenizer_data_t {
        std::vector<int> tokens;
        tokenizer_t* tokenizer;
    };
};

std::string get_cursor_kind_spelling(int kind);
