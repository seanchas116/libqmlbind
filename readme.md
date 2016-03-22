# libqmlbind

libqmlbind is a C library for creating QML bindings for other languages easily through exporting objects and classes to QML.

[![Build Status](https://travis-ci.org/seanchas116/libqmlbind.svg?branch=master)](https://travis-ci.org/seanchas116/libqmlbind)

## Features

* Simple API to export objects / classes dynamically to QML
* Shared library with pure C interface
  * Decouple your language bindings from Qt itself
  * High portability
* Build with qmake
  * No need to configure compilation flags for Qt manually

## How to build
### Requirements
* A C++11-capable compiler: libqmlbind is tested against `clang 3.4`.
* Qt5: libqmlbind is tested against `Qt 5.5.1`. Everything `>= 5.2` might work, too.

libqmlbind uses Qt's private headers. To quote the qmake warning:

> This project is using private headers and will therefore be tied to this specific Qt module build version.
> Running this project against other versions of the Qt modules may crash at any arbitrary point.
> This is not a bug, but a result of using Qt internals. You have been warned!


### Build the Code
First, clone the repository with all its submodules:
```
> git clone --recursive git@github.com:seanchas116/libqmlbind.git
```

Alternatively, if you already cloned but forgot `--recursive`, use this inside `libqmlbind`:
```
> git submodule update --init --recursive
```

Use qmake to generate the `Makefile`:
```
# if you want to use your default compiler:
> qmake -r
# if you want to use clang:
> qmake -r QMAKE_CC=clang QMAKE_CXX=clang
```

and then build it:
```
> make
```

### Run the Tests

From the main directory:

```
> ./test/test -platform offscreen
```
