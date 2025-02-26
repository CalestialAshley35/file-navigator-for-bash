# File Navigator for Bash

## Overview

File Navigator for Bash is a command-line tool designed to help you navigate, manage, and manipulate files and directories efficiently in a Unix-based system. It provides several useful commands such as file listing, file deletion, permissions management, file compression, and more. This tool is ideal for users who want to streamline their interaction with files via a terminal interface.

## Features

- **File Management**:
  - List files in the current directory
  - Delete files
  - Check file extensions and types
  - Search for files
  - View file contents
  - Show file sizes
  - Change file permissions
  - Rename files
  - Copy and move files
  
- **Directory Management**:
  - Create and remove directories
  - Change directories

- **Search and Content Management**:
  - Search for a word within a file using `grep`
  - Search for a word in all files within the directory
  - Compress and extract files (supports `.zip` files)

- **Command History**:
  - View the history of commands executed within the session

## Prerequisites

Before using this tool, ensure that you have the following installed:

- A **Unix-based system** (Linux, macOS, etc.)
- A **C++ compiler** that supports C++17 or later (e.g., `g++` version 7+)
- **libzip** library for file compression and extraction (`-lz` flag)
- **Filesystem library** support in `g++` (use `-lstdc++fs` flag)

## Installation

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/CalestialAshley35/file-navigator-for-bash.git

2. Navigate to the project directory:

```bash
cd file-navigator-for-bash
```

3. Compile the code using g++:

```bash
g++ -o file-navigator main.cpp -lstdc++fs -lz
```


4. Run the program:

```bash
./file-navigator
```

## Usage

Once the program is running, you can enter various commands to interact with files and directories. Below are the available commands:

Available Commands:

- `help`: Displays a list of all available commands.
- `files`: Lists all files in the current directory.
- `delete <file>` Deletes the specified file.
- `file <file>`: Checks the extension of the specified file and identifies its type.
- `search <file>`: Searches for a file by name.
- `size <file>`: Displays the size of the specified file.
- `view <file>`: Views the contents of the specified file.
- `permission <perm> <file>`: Changes the permissions of the specified file (<perm> should be in octal format, e.g., 755).
- `grep <word> <file>`: Searches for the specified word in a file using grep.
- `mkdir <dir>`: Creates a new directory with the given name.
- `rmdir <dir>`: Removes an empty directory.
- `cd <dir>`: Changes the current directory to the specified one.
- `copy <source> <destination>`: Copies a file from the source path to the destination path.
- `move <source> <destination>`: Moves a file from the source path to the destination path.
- `rename <old> <new>`: Renames a file from <old> name to <new> name.
- `history`: Displays the history of commands executed during the session.
- `searchcontent <word>`: Searches for the specified word in all files within the current directory.
- `compress <file>`: Compresses the specified file into a .zip archive.
- `extract <archive>`: Extracts the contents of a .zip archive.

Example Commands:

1. **To list all files in the current directory:**
   `files`

2. **To delete a file named `example.txt`:**
   `delete example.txt`

3. **To check the type of a file `script.py`:**
   `file script.py`

4. **To search for a file called `index.html`:**
   `search index.html`

5. **To change the permissions of a file `script.sh` to `755`:**
   `permission 755 script.sh`

6. **To compress a file `document.txt` into a `.zip` archive:**
   `compress document.txt`

7. **To extract a `.zip` archive `document.zip`:**
   `extract document.zip`

---

### Command History

The tool maintains a history of up to the last 20 commands entered. To view your command history, simply use:

`history`

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Feel free to fork the repository and contribute by opening issues or submitting pull requests. All contributions are welcome!

## Contact

For any questions or support, you can reach out via email or open an issue on the GitHub repository.