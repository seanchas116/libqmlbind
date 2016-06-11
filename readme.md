# libqmlbind

libqmlbind is a C library for creating QML bindings for other languages easily through exporting objects and classes to QML.

* [Documentation](https://seanchas116.github.io/libqmlbind/)
* [Examples](https://github.com/seanchas116/libqmlbind/tree/master/examples)
* [Changelog](https://github.com/seanchas116/libqmlbind/tree/master/changelog.md)

[![Build Status](https://travis-ci.org/seanchas116/libqmlbind.svg?branch=master)](https://travis-ci.org/seanchas116/libqmlbind)

## Features

* Simple API to export objects / classes dynamically to QML
* Shared library with pure C interface
  * Decouple your language bindings from Qt itself
  * High portability
* Build with qmake
  * No need to configure compilation flags for Qt manually

## Code Structure
### Mapping of Classes to the C interface
* All classes are defined as opaque C structs in `include/qmlbind/qmlbind_global.h`
* For each class, there's a header file at `include/qmlbind/<classname>.h`
   which contains all methods defined on the class.

### Ownership Conventions used in libqmlbind:
* `const type*`-pointers never transfer ownership.
* Functions ending in `_new` are constructors, they transfer the ownership of the returned struct to the caller.
* Functions ending in `_release` are destructors, they take ownership of their first argument, called `self`.
* All remaining functions with `self` as first parameter are methods on `self`, they never take ownership of it.
* In all other cases, ownership of parameters and return value is explicitly stated in the comments.

## How to install
### Mac + Homebrew

You can install libqmlbind via [Homebrew](http://brew.sh/) on Mac.
(using [a custom tap](https://github.com/seanchas116/homebrew-libqmlbind))

```
> brew tap seanchas116/libqmlbind
> brew install libqmlbind
```

### Arch Linux via AUR

For Arch Linux, you can find the [latest release](https://aur.archlinux.org/packages/libqmlbind) and the
[git master](https://aur.archlinux.org/packages/libqmlbind-git/) version of libqmlbind in the AUR.

## How to build
### Requirements
* A C++11-capable compiler: libqmlbind is tested against `gcc 4.8.4`.
* Qt5: libqmlbind is tested against `Qt 5.6` and `Qt 5.2.1`.

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
> cd test
> ./test -platform offscreen
```

### Build the Documentation
Just run
```
> doxygen
```
from the project's main directory. You can then find the documentation in `doc/html/index.html`.


## Alternatives
If you're not happy with libqmlbind's interface or features, you might be interested in
[DOtherSide](https://github.com/filcuc/DOtherSide), an alternative C library for creating QML bindings.
While libqmlbind was designed with dynamic languages like ruby in mind, DOtherSide was designed for static languages
like D. (You can use libqmlbind for static languages, too, though, you just won't need some parts of the API).
