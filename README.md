# RubyClean

A C++ utility for finding and cleaning junk files, build folders, and temporary system files.

## Features

* Scan project directories for junk files
* Clean detected junk files and folders
* Largest junk analysis
* Project statistics
* Export reports
* `.rubycleanignore` support
* Interactive desktop menu
* System temporary file cleaner

## Supported Junk Folders

* build
* cmake-build-debug
* cmake-build-release
* **pycache**
* node_modules
* dist
* .next
* out
* bin
* obj

## Supported Junk Files

* .log
* .tmp
* .temp

## Build

```bash
g++ src/main.cpp src/menu/Menu.cpp src/menu/MenuRunner.cpp src/system/SystemCleaner.cpp src/cli/CommandParser.cpp src/scanner/Scanner.cpp -o RubyClean.exe
```

## CLI Usage

### Scan

```bash
RubyClean.exe scan .
```

### Clean

```bash
RubyClean.exe clean .
```

### Largest Junk

```bash
RubyClean.exe largest .
```

### Statistics

```bash
RubyClean.exe stats .
```

### Export Report

```bash
RubyClean.exe scan . export
```

## Ignore Rules

Create a file named:

```text
.rubycleanignore
```

Example:

```text
test.log
node_modules
cache
```

Ignored files and folders will be skipped during scans and cleanup.

## Desktop Mode

Launch directly:

```text
RubyClean.exe
```

Menu:

```text
1. Project Scan
2. Project Clean
3. Largest Junk
4. Statistics
5. System Clean
6. Exit
```

## Example Output

```text
=========================================
           RubyClean Report
=========================================

Type      Path                     Size
-----------------------------------------------------
FILE      .\test\test.temp         520 KB

-----------------------------------------------------
Files   : 1
Recover : 520 KB
```

## Current Version

```text
v1.4.0
```

Have any doubts join discord : https://discord.gg/upzqsFHzzx