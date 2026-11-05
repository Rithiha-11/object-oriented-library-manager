#include "library.h"
#include <cassert>
#include <iostream>

int main() {
    Library library;
    assert(library.totalBooks() == 0);
    assert(library.addBook(Book{1, "The C++ Book", "A. Writer", false}));
    assert(!library.addBook(Book{1, "Duplicate", "B. Writer", false}));
    assert(!library.addBook(Book{0, "Invalid ID", "C. Writer", false}));
    assert(library.findBook(1) != nullptr);
    assert(library.findBook(99) == nullptr);
    assert(library.updateBook(1, "Modern C++", "A. Writer"));
    assert(library.findBook(1)->title == "Modern C++");
    assert(library.borrowBook(1));
    assert(!library.borrowBook(1));
    assert(library.borrowedCount() == 1);
    assert(library.availableCount() == 0);
    assert(library.returnBook(1));
    assert(!library.returnBook(1));
    assert(library.availableCount() == 1);
    assert(!library.updateBook(99, "Missing", "Nobody"));
    std::cout << "All library tests passed.\n";
}
