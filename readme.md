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
