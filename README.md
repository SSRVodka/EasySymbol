## Easy Symbol

✨ Easy access to Symbols & Emoji ✨

<a href="README_zh_CN.md">中文</a>

## Introduction

Have you ever had the frustration that when you want to input some special symbols (math symbols, Greek letters, etc. that you often encountered when writing scientific and technical articles) or emoji expressions when writing a document, you often spend a long time looking for specific symbols or emoji expressions due to the ineffective input method? 

While this experience is annoying, the most troublesome thing is that the phrase customization feature of many input methods is not so good, or the various plug-ins are very bloated.

Easy Symbol was born out of this need.

The structure of this program is very simple, you can customize the relationship between some symbols (called `target`) and hints (called `hint`). This way, in the program, you can just import your customized dictionary and do a search to quickly find the symbol you need and double-click to copy it to the clipboard.

You can simply bind the program startup to a system shortcut for quick and easy access to the symbols.

## Advantages

- Small system overhead;

- Shortcut key launch, symbols find quickly;

- Easy copying to speed up your symbol editing;

- Self-customized dictionary mapping.

## Quick Start

You can download the binary program for your operating system from Release. After that, you can set up a shortcut to start the program as follows:

### Windows

Create a shortcut to an executable program (exe) by right clicking on it. Right click on the shortcut, "shortcut" -> "shortcut key".

### Linux

For Ubuntu 22, open Settings -> Keyboard -> Keyboard Shortcuts -> View and Customize Shortcuts -> Custom Shortcuts.

### Source code compilation

Alternatively, you can compile the source code yourself. Here is the development environment:

- Qt 5.x (and C++ dev kits)

- GNU make, cmake

Run the following commands (Linux for example):

```bash
cmake -B build
cd build
make
```

The debugging flag can be enabled with `-Ddebug=1`:

```bash
cmake -B build -Ddebug=1
```
