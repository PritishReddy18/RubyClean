# RubyClean

RubyClean is a simple disk cleanup utility written in C++.

I originally built this project to clean up build folders, cache files, logs, temporary files, and other junk that slowly accumulates while working on programming projects. It can also scan common Windows system locations and estimate how much storage can be recovered.

## What it can do

* Scan project directories for unnecessary files
* Detect common build folders
* Find cache, log, and temporary files
* Show recoverable storage space
* Display the largest folders in a project
* Support custom ignore rules using `.rubycleanignore`
* Scan common Windows junk locations
* Clean selected files and folders

## Supported Junk

### Folders

```text
build
cmake-build-debug
cmake-build-release
__pycache__
node_modules
dist
.next
out
bin
obj
```

### Files

```text
.log
.tmp
.temp
```

## Ignore Rules

Create a file called `.rubycleanignore` in your project directory.

Example:

```text
build
node_modules
test.log
```

Anything listed in this file will be skipped during scanning and cleanup.

## Building

```bash
g++ src/main.cpp ^
src/menu/Menu.cpp ^
src/menu/MenuRunner.cpp ^
src/system/SystemCleaner.cpp ^
src/cli/CommandParser.cpp ^
src/scanner/Scanner.cpp ^
-o RubyClean.exe
```

## Running

```bash
RubyClean.exe
```

Example menu:

```text
1. Project Scan
2. Project Clean
3. Largest Folders
4. Statistics
5. System Scan
6. System Clean
0. Exit
```

## Example Output

```text
System Junk Report

User Temp                25.6 MB
Thumbnail Cache           2.0 MB
Windows Update Cache      1.2 MB

Total Recoverable: 28.8 MB
```

## Installation

Download the latest installer from the Releases page and run:

```text
RubyCleanSetup.exe
```

A desktop shortcut and Start Menu entry will be created automatically.

## Technologies Used

```text
C++17
STL
std::filesystem
Inno Setup
```

## Future Plans

* Multi-threaded scanning
* Export scan reports
* Scheduled cleanup
* JSON output
* Better Windows integration
* Linux support
* macOS support