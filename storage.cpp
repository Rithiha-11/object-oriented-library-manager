#include "storage.h"
#include <fstream>
#include <sstream>

namespace {
std::string csvEscape(const std::string& value) {
    std::string out = "\"";
    for (char c : value) {
        if (c == '"') out += "\"\"";
        else out += c;
    }
    out += '"';
    return out;
}

bool parseCsvRow(const std::string& line, Book& book) {
    std::vector<std::string> fields;
    std::string field;
    bool quoted = false;
    for (std::size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (quoted && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                ++i;
            } else quoted = !quoted;
        } else if (c == ',' && !quoted) {
            fields.push_back(field);
            field.clear();
        } else field += c;
    }
    if (quoted) return false;
    fields.push_back(field);
    if (fields.size() != 4) return false;
    try {
        std::size_t used = 0;
        int id = std::stoi(fields[0], &used);
        if (used != fields[0].size() || id <= 0) return false;
        if (fields[3] != "0" && fields[3] != "1") return false;
        if (fields[1].empty() || fields[2].empty()) return false;
        book = Book{id, fields[1], fields[2], fields[3] == "1"};
        return true;
    } catch (...) {
        return false;
    }
}
}

namespace Storage {
bool loadBooks(const std::string& filename, std::vector<Book>& books, std::string& error) {
    std::ifstream input(filename);
    if (!input) {
        error = "Could not open data file: " + filename;
        return false;
    }
    std::vector<Book> loaded;
    std::string line;
    std::size_t lineNumber = 0;
    while (std::getline(input, line)) {
        ++lineNumber;
        if (line.empty()) continue;
        if (lineNumber == 1 && line == "id,title,author,borrowed") continue;
        Book book;
        if (!parseCsvRow(line, book)) {
            error = "Malformed CSV row at line " + std::to_string(lineNumber);
            return false;
        }
        for (const auto& existing : loaded) {
            if (existing.id == book.id) {
                error = "Duplicate book ID at line " + std::to_string(lineNumber);
                return false;
            }
        }
        loaded.push_back(book);
    }
    if (input.bad()) {
        error = "Error while reading data file.";
        return false;
    }
    books = std::move(loaded);
    error.clear();
    return true;
}

bool saveBooks(const std::string& filename, const std::vector<Book>& books, std::string& error) {
    std::ofstream output(filename, std::ios::trunc);
    if (!output) {
        error = "Could not write data file: " + filename;
        return false;
    }
    output << "id,title,author,borrowed\n";
    for (const auto& book : books) {
        output << book.id << ',' << csvEscape(book.title) << ','
               << csvEscape(book.author) << ',' << (book.borrowed ? 1 : 0) << '\n';
    }
    if (!output) {
        error = "A write error occurred while saving data.";
        return false;
    }
    error.clear();
    return true;
}
}
