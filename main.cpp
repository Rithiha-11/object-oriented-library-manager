#include "Book.h"
#include "library.h"
#include "storage.h"
#include <iostream>
#include <limits>
#include <string>

namespace {
constexpr const char* DATA_FILE = "data/books.csv";

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        if (std::cin.eof()) return -1;
        std::cout << "Invalid input. Please enter a whole number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readText(const std::string& prompt) {
    std::string value;
    do {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (std::cin.eof()) return {};
        if (value.empty()) std::cout << "This field cannot be empty.\n";
    } while (value.empty());
    return value;
}

void showBooks(const Library& library) {
    if (library.books().empty()) {
        std::cout << "No books found.\n";
        return;
    }
    for (const auto& b : library.books()) {
        std::cout << "ID: " << b.id << " | Title: " << b.title
                  << " | Author: " << b.author << " | Status: "
                  << (b.borrowed ? "Borrowed" : "Available") << '\n';
    }
}

bool save(const Library& library) {
    std::string error;
    if (!Storage::saveBooks(DATA_FILE, library.books(), error)) {
        std::cerr << "Save failed: " << error << '\n';
        return false;
    }
    return true;
}
}

int main() {
    Library library;
    std::string error;
    std::vector<Book> loaded;
    if (Storage::loadBooks(DATA_FILE, loaded, error)) {
        for (const auto& book : loaded) library.addBook(book);
    } else {
        std::cerr << "Notice: " << error << "\nStarting with an empty library.\n";
    }

    while (true) {
        std::cout << "\n=== OBJECT-ORIENTED LIBRARY MANAGER ===\n"
                  << "1. Add book\n2. List books\n3. Search book\n4. Update book\n"
                  << "5. Borrow book\n6. Return book\n7. Library report\n8. Save and exit\n";
        int choice = readInt("Choose an option: ");
        if (choice == -1 || choice == 8) {
            if (save(library)) std::cout << "Data saved. Goodbye!\n";
            return 0;
        }
        if (choice == 1) {
            int id = readInt("Book ID (positive number): ");
            if (id <= 0) { std::cout << "ID must be positive.\n"; continue; }
            std::string title = readText("Title: ");
            std::string author = readText("Author: ");
            if (library.addBook(Book{id, title, author, false})) {
                if (save(library)) std::cout << "Book added.\n";
            } else std::cout << "Could not add book. Check fields and ensure the ID is unique.\n";
        } else if (choice == 2) {
            showBooks(library);
        } else if (choice == 3) {
            int id = readInt("Book ID to search: ");
            const Book* b = library.findBook(id);
            if (b) std::cout << b->id << " | " << b->title << " | " << b->author
                             << " | " << (b->borrowed ? "Borrowed" : "Available") << '\n';
            else std::cout << "Book not found.\n";
        } else if (choice == 4) {
            int id = readInt("Book ID to update: ");
            std::string title = readText("New title: ");
            std::string author = readText("New author: ");
            if (library.updateBook(id, title, author)) {
                if (save(library)) std::cout << "Book updated.\n";
            } else std::cout << "Update failed: book not found or fields invalid.\n";
        } else if (choice == 5 || choice == 6) {
            int id = readInt("Book ID: ");
            bool ok = choice == 5 ? library.borrowBook(id) : library.returnBook(id);
            if (ok) {
                if (save(library)) std::cout << (choice == 5 ? "Book borrowed.\n" : "Book returned.\n");
            } else std::cout << "Operation failed. Check the ID and current book status.\n";
        } else if (choice == 7) {
            std::cout << "\n--- Library Report ---\nTotal books: " << library.totalBooks()
                      << "\nBorrowed: " << library.borrowedCount()
                      << "\nAvailable: " << library.availableCount() << '\n';
        } else {
            std::cout << "Invalid option. Choose 1-8.\n";
        }
    }
}
