#pragma once
#include "Book.h"
#include <string>
#include <vector>

namespace Storage {
    bool loadBooks(const std::string& filename, std::vector<Book>& books,
                   std::string& error);
    bool saveBooks(const std::string& filename, const std::vector<Book>& books,
                   std::string& error);
}
