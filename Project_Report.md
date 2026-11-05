# C++ Application Capstone — Project Report

## 1. Overview
The Object-Oriented Library Manager is an offline command-line application for maintaining fictional library book records.

## 2. Requirements implemented
- Add, list, search, update, borrow, return, and persist book records.
- Reject invalid IDs, duplicate IDs, invalid menu input, and invalid borrow/return state changes.
- Separate data model, business rules, persistence, and user interface.
- Provide automated tests and a useful library analytics report.

## 3. Architecture
`Book` represents one record. `Library` owns records in `std::vector<Book>` and applies business rules. `Storage` loads and saves CSV data. `main.cpp` handles terminal input and output. Tests exercise the business rules separately from the user interface.

## 4. Ownership and resource management
Books are stored by value in a standard-library vector. File streams manage file resources through RAII. The program does not use owning raw pointers or manual memory allocation.

## 5. Validation and error handling
The application checks positive unique IDs, non-empty title/author fields, book existence, and borrow/return state. The CSV reader rejects malformed rows and duplicate IDs and reports missing-file errors.

## 6. Automated tests
`tests/test_library.cpp` covers an empty collection, successful add, duplicate and invalid IDs, search success/failure, update success/failure, borrow/return state checks, and analytics counts. Build and run it using the commands in `README.md`.

## 7. Complexity
With vector storage, lookup and mutation operations are O(n). Listing and persistence are O(n). Report counts are O(n), with O(1) auxiliary space.

## 8. Build environment
C++17 and GCC (`g++`) are required. A clean build can be performed using the commands in `README.md`. For second-environment verification, compile with another GCC installation or a second compiler such as Clang, if available, and record the compiler/version used.

## 9. Conclusion
The project demonstrates object-oriented design, standard-library containers, file persistence, validation, analytics, and automated testing in a maintainable C++ application.
