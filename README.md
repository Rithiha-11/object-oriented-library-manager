# Object-Oriented Library Manager — Task 5

A small offline C++17 command-line library manager. It keeps the data model, library rules, CSV persistence, and terminal interface in separate files.

## Features
- Add, list, search, and update books.
- Borrow and return books with status validation.
- Save/load records using `data/books.csv`.
- Reject duplicate/non-positive IDs and invalid menu input.
- Report total, borrowed, and available books.
- Automated tests for empty collections, duplicate IDs, missing IDs, updates, borrowing, returning, and report counts.

## Project structure
- `include/Book.h` — book record.
- `include/library.h`, `src/Library.cpp` — business rules and analytics.
- `include/storage.h`, `src/storage.cpp` — CSV persistence and malformed-row checks.
- `main.cpp` — command-line interface.
- `tests/test_library.cpp` — automated unit tests.
- `data/books.csv` — sample data.

## Build and run (Windows PowerShell, from the project root)
```powershell
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude main.cpp src/Library.cpp src/storage.cpp -o library.exe
.\library.exe
```

## Run automated tests
```powershell
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_library.cpp src/Library.cpp -o library_tests.exe
.\library_tests.exe
```
Expected output: `All library tests passed.`

## Architecture and ownership
`Library` owns its `Book` records by value in a `std::vector<Book>`. No raw owning pointers or manual memory management are used. `Storage` receives references to vectors and does not retain them. The application uses stack objects and standard-library RAII for files and containers.

## Error handling
Invalid menu input is cleared and retried. IDs must be positive and unique. Borrowing an already borrowed book, returning an available book, or updating a missing ID is rejected. CSV loading reports missing files, malformed rows, invalid status fields, and duplicate IDs.

## Complexity note
Most book operations search the vector linearly, so lookup/update/borrow/return are O(n). Listing and saving are O(n). Analytics counts are O(n), with constant extra space.

## Clean-build test evidence
Build using the commands above, run the automated test executable, and capture a screenshot of the successful test output and the application report menu for your submission.
