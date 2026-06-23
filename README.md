# RubyClean

A simple C++ CLI tool that scans projects for common development junk folders and helps clean them up.

## Features

- Scan project directories
- Detect common junk folders
- Calculate recoverable storage size
- Sort results by size
- Remove detected junk folders

### Supported Folders

- build
- cmake-build-debug
- cmake-build-release
- __pycache__
- node_modules
- dist
- .next
- out
- bin
- obj

---

## Build

```bash
g++ src/main.cpp src/cli/CommandParser.cpp src/scanner/Scanner.cpp -o RubyClean.exe
```

## Usage

### Scan

```bash
RubyClean.exe scan .
```

### Clean

```bash
RubyClean.exe clean .
```

---

## Example Output

```text
=====================================
        RubyClean Report
=====================================

Path                                    Size
----------------------------------------------------------
.\test\cmake-build-debug                3.13 KB
----------------------------------------------------------

Total Recoverable: 3.13 KB
```

### Cleaning

```text
Delete all junk folders? (y/n): y

Cleanup completed.
```

---

## Future Improvements

- Detect log files
- Detect temporary files
- Export scan reports
- Ignore file support
- Largest folder analysis

---

Built while learning C++ and CLI application development.
