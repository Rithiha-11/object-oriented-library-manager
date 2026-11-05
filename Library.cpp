#include "library.h"
#include <algorithm>

bool Library::addBook(const Book& book) {
    if (book.id <= 0 || book.title.empty() || book.author.empty() || findBook(book.id))
        return false;
    books_.push_back(book);
    return true;
}

bool Library::updateBook(int id, const std::string& title, const std::string& author) {
    auto it = std::find_if(books_.begin(), books_.end(),
        [id](const Book& b) { return b.id == id; });
    if (it == books_.end() || title.empty() || author.empty()) return false;
    it->title = title;
    it->author = author;
    return true;
}

bool Library::borrowBook(int id) {
    auto it = std::find_if(books_.begin(), books_.end(),
        [id](const Book& b) { return b.id == id; });
    if (it == books_.end() || it->borrowed) return false;
    it->borrowed = true;
    return true;
}

bool Library::returnBook(int id) {
    auto it = std::find_if(books_.begin(), books_.end(),
        [id](const Book& b) { return b.id == id; });
    if (it == books_.end() || !it->borrowed) return false;
    it->borrowed = false;
    return true;
}

const Book* Library::findBook(int id) const {
    auto it = std::find_if(books_.begin(), books_.end(),
        [id](const Book& b) { return b.id == id; });
    return it == books_.end() ? nullptr : &*it;
}

const std::vector<Book>& Library::books() const noexcept { return books_; }
std::size_t Library::totalBooks() const noexcept { return books_.size(); }
std::size_t Library::borrowedCount() const noexcept {
    return static_cast<std::size_t>(std::count_if(books_.begin(), books_.end(),
        [](const Book& b) { return b.borrowed; }));
}
std::size_t Library::availableCount() const noexcept { return totalBooks() - borrowedCount(); }
