
# Library Management System (C-Based)

A lightweight, console-based application designed to manage a library's book inventory and student borrowing records. This project demonstrates fundamental programming concepts in C, specifically focusing on data organization and procedural logic.

## Language & Technical Concepts

The system is built using the C programming language, and it utilizes several core concepts to manage data efficiently:

### 1. Data Structures (`struct`)
The foundation of the system rests on two custom data types:
* `books`: Stores the unique ID, title, author, and current stock (copy number).
* `student`: Stores student identification, class details, and tracking for issued books including `time_t` variables for date management.

### 2. Pointers and Memory
The `issue()` and `re()` (return) functions use **pointers** (`books *bk`, `student *st`) to point directly to the memory address of a specific record within the global arrays. This allows the system to update book counts and student status in real-time without creating redundant copies of the data.

### 3. Time Management
By including `<time.h>`, the system captures the exact moment a book is issued or returned. It uses `difftime()` to calculate the interval between these two points, allowing for automated late fee calculations.

### 4. String & Buffer Handling
The code utilizes `scanf(" %[^\n]", ...)` to handle strings. This is a crucial "regex-style" format specifier in C that allows the program to read full titles (like "The Great Gatsby") including spaces, which a standard `%s` would truncate.

---

## System Workflow

The application follows a linear, menu-driven lifecycle:

### Phase 1: Initialization
Upon launching, the user defines the `max` capacity of the library. This sets the boundary for how many books the system can track before triggering a "Library FULL!" warning.

### Phase 2: Inventory & Member Setup
* **Add Books:** Users populate the `b[]` array with book details.
* **Add Students:** Users populate the `s[]` array. The system checks for duplicate Student IDs before allowing a new entry.

### Phase 3: Transactional Logic
1.  **Issue:** The system validates that both the Student ID and Book ID exist. It then checks if `copyno > 0`. If successful, it decrements the book stock and timestamps the start of the loan.
2.  **Return:** The system calculates the time elapsed. If the duration exceeds the 7-day limit, it applies a fine (100 units per day) based on the `difftime` result.

### Phase 4: Data Visualization
Users can view the current state of the library through:
* **Inventory:** Displays all books and their current stock levels.
* **Student Database:** Shows which students have active loans and which are clear ("N/A").

---

## How to Run
1.  Ensure you have a C compiler installed (like `gcc`).
2.  Compile the code:
    ```bash
    gcc library_system.c -o library_system
    ```
3.  Run the executable:
    ```bash
    ./library_system
    ```
