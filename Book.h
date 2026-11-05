#pragma once
#include <string>

struct Book {
    int id{};
    std::string title;
    std::string author;
    bool borrowed{false};
};
