# 🌀 MiniGit – A Lightweight Git Clone in C++

A simple yet functional version control system built in **C++**, inspired by **Git**.  
It implements essential Git-like features including `init`, `add`, `commit`, `log`, and `revert`.

This project is ideal for understanding how Git works under the hood, while also showcasing key C++ programming concepts such as file handling, object-oriented design, and linked data structures.

---

## ✨ Features

### 📁 Repository Initialization
- **`./vcs.exe init`**  
  Initializes a `.git/` directory in the current folder with:
  - `staging_area/` – Temporary storage for files to be committed.
  - `commits/` – Stores all commit snapshots.

### ➕ File Staging
- **`./vcs.exe add .`**  
  Adds all files and folders in the current directory (excluding `.git`) to the staging area.

- **`./vcs.exe add <file1> <file2> ...`**  
  Selectively stages individual files or directories.

### 📝 Committing Changes
- **`./vcs.exe commit -m "message"`**  
  Creates a snapshot of the current staging area:
  - Stores files in a new commit folder under `.git/commits/`.
  - Saves a `commitInfo.txt` with metadata (ID, message, timestamp).
  - Assigns a unique 8-character commit hash.

### 🔁 Reverting Commits
- **`./vcs.exe revert HEAD`**  
  Reverts the project state to the most recent commit.

- **`./vcs.exe revert <commit_hash>`**  
  Reverts the project to the specified commit ID by creating a new commit snapshot of that previous state.

### 📜 Commit Log
- **`./vcs.exe log`**  
  Displays a list of all commits in chronological order:
  - ✅ Commit ID  
  - ✏️ Message  
  - 🕒 Timestamp  

---

## 🛠️ How It Works


Each commit folder holds:
- `commitInfo.txt` – Stores ID, message, and timestamp.
- `Data/` – The actual committed files (copied from staging).

---

## ⚙️ Internal Architecture

- **`commitNode`**  
  Represents a single commit node storing its ID, message, timestamp, and link to the next commit.

- **`commitNodeList`**  
  A linked list to manage all commits and handle:
  - Adding new commits.
  - Reverting to previous commits.
  - Printing logs.

- **`gitClass`**  
  Orchestrates Git-like operations such as:
  - Initializing the repository.
  - Staging files.
  - Committing.
  - Reverting.
  - Logging.

---

## 🧠 C++ Concepts Demonstrated

- 📦 **Object-Oriented Design**: Classes for modularity (`gitClass`, `commitNode`, `commitNodeList`).
- 📁 **Filesystem Manipulation**: Uses `std::filesystem` for copying and managing directories and files.
- 🔗 **Linked List Implementation**: For managing the chain of commits.
- 🧠 **Command-Line Argument Parsing**: Custom argument handling to mimic `git` commands.
- 🧪 **Random Commit Hashing**: Generates unique 8-character alphanumeric commit IDs.

---

## 🧪 Sample Usage

```bash
./vcs.exe init                    # Initialize repository
./vcs.exe add .                  # Stage all files
./vcs.exe commit -m "Initial commit"    # Commit staged files
./vcs.exe log                    # View commit history
./vcs.exe revert <commit_id>     # Revert to specific commit

