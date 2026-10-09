# Inverted Search Engine 🔍

Welcome to **Inverted Search**, designed and implemented by [@Adhish-ece](https://github.com/Adhish-ece).

---

## 📋 Table of Contents
- [About](#-about)
- [Features](#-features)
- [Tech Stack](#-tech-stack)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Contributing](#-contributing)
- [License](#-license)
- [Contact](#-contact)

---

## 💡 About
Standard file searching algorithms scan entire documents sequentially, leading to high latency when parsing multiple files or large datasets.

**Inverted Search Engine** solves this efficiency challenge by parsing multiple text files and constructing an **Inverted Index database**. By mapping every unique word to a hash table with linked list nodes tracking file names and word frequencies, it achieves instant word lookups across multiple documents simultaneously.

---

## ✨ Features
- **Inverted Index Construction:** Fast parsing and indexing of input text files into an optimized hash database.
- **Core Operations:**
  - **Create Database:** Parse input files, tokenize words, and populate the hash table.
  - **Display Database:** Render the complete indexed database in a structured table format.
  - **Search Word:** Instantly locate a word across all indexed files along with exact occurrence counts.
  - **Save Database:** Persist the created index into an output file for future sessions.
  - **Update Database:** Load a previously saved index file back into memory without re-parsing files.
- **Dynamic Data Structures:** Combines array-based Hash Tables for fast indexing ($O(1)$ hashing) with Singly Linked Lists for dynamic node chaining and collision handling.
- **Input Validation:** File verification to ignore duplicate, empty, or non-existent files during initialization.

---

## 🛠️ Tech Stack
- **Language:** C
- **Data Structure:** Hash Tables & Singly Linked Lists
- **Build Tools:** GCC / GNU Make

---

## 🚀 Getting Started

### Prerequisites
Ensure you have a standard C compiler installed on your system:
- **GCC** or **Clang**
- **Make** (optional)

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Adhish-ece/Inverted-Search.git
   ```

2. **Navigate into the project directory:**
   ```bash
   cd Inverted-Search
   ```

3. **Compile the program:**
   ```bash
   make
   ```

---

## 💻 Usage

Run the compiled executable from your terminal by passing the target text files as command-line arguments:

```bash
./inverted_search file1.txt file2.txt file3.txt
```

---

## 📁 Project Structure

```text
Inverted-Search/
├── main.c            # Program entry point and menu driver
├── create_db.c       # Database creation and file parsing routines
├── display_db.c      # Functionality to print the index table
├── search_db.c       # Word search and occurrence lookup engine
├── save_db.c         # Database persistence and file export logic
├── update_db.c       # Loading previously saved database files
├── inverted_search.h # Header file with structs, prototypes & constants
├── Makefile          # Build automation script
└── README.md         # Project documentation
```

---

## 🤝 Contributing

Contributions, bug reports, and feature requests are welcome!

1. Fork the project repository.
2. Create your feature branch (`git checkout -b feature/NewFeature`)
3. Commit your changes (`git commit -m "Add NewFeature"`)
4. Push to the branch (`git push origin feature/NewFeature`)
5. Open a Pull Request.

---

## 📝 License

Distributed under the MIT License. See `LICENSE` for details.

---

## 📬 Contact

**Adhish** — [@Adhish-ece](https://github.com/Adhish-ece)

Project Link: [https://github.com/Adhish-ece/Inverted-Search](https://github.com/Adhish-ece/Inverted-Search)
