# Terminal-Based Notepad with Autocorrect (C++ & Ncurses)

A Linux-terminal based notepad application written in C++, featuring:

- Real-time text input
  
- Autocorrect suggestions
  
- File saving and loading
  
- Backspace enabled
  
- Dictionary-backed word checking using an AVL tree
  
- Custom implementations of:
  - Circular queue
  - Linked list for character tracking
  - AVL tree for dictionary lookup

## 🧠 Key Features

- **Autocorrect**: When you press space after typing a word, the system checks it against a dictionary (stored as an AVL tree). If not found, it suggests close alternatives (via insertion, deletion, substitution, and reversal).

<img width="1284" height="672" alt="autocorrect_1" src="https://github.com/user-attachments/assets/12f406b6-43be-426d-980c-4bdc954f208f" />
<img width="1284" height="672" alt="autocorrect_2" src="https://github.com/user-attachments/assets/75cba05c-a61f-43f0-a55a-816f47b56801" />

- **Backspace behavior**: Maintains a state of typed characters to handle undo-like word recovery.
  
- **File handling**:
  - `Ctrl + S`: Save current screen content to a file.
  - `Ctrl + L`: Load a file into the screen.
    
- **Escape key**: Exit the application.

## 🚧 Requirements

- Linux (Ubuntu recommended)
  
- `g++` (GNU Compiler)
  
- `ncurses` library

## 🔧 How to Build

### 1. Clone the Repository

git clone https://github.com/RJ601/Text-Editor.git

cd Text-Editor

### 2. Install Dependencies (if not already installed)

sudo apt update

sudo apt install libncurses5-dev libncursesw5-dev

### 3. Compile

g++ main.cpp -o notepad -lncurses

### 4. Disable XON/XOFF software flow control (to allow file saving and loading with ctrl+s and ctrl+l respectively)

stty -ixon

### 5. Run

./notepad

## 📁 Files

main.cpp: The main source file containing all implementations.

dictionary.txt: Word list used for spell-checking/autocorrect. This file must be in the same directory as the executable.

Saved files: Will be created and loaded using terminal prompts during runtime (with .txt extension).

## ⚠️ Notes

This program is Linux-only, due to its use of ncurses for terminal UI.

ncurses handles input/output in a terminal-safe way but is not compatible with Windows without WSL or a terminal emulator like Cygwin.

## 📝 Controls Summary

Any key	Type characters

Space	Check and suggest autocorrect

Backspace	Remove previous letter or re-queue last word

Ctrl + S	Save screen to file

Ctrl + L	Load file to screen

Esc	Exit the application
