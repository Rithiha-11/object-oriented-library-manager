#pragma once
#include "Book.h"
#include <cstddef>
#include <string>
#include <vector>

class Library {
public:
    bool addBook(const Book& book);
    bool updateBook(int id, const std::string& title, const std::string& author);
    bool borrowBook(int id);
    bool returnBook(int id);
    const Book* findBook(int id) const;
    const std::vector<Book>& books() const noexcept;
    std::size_t totalBooks() const noexcept;
    std::size_t borrowedCount() const noexcept;
    std::size_t availableCount() const noexcept;

private:
    std::vector<Book> books_;
};
