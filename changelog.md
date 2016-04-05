# Change Log #
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [0.2.0] - Unreleased ##
### Added ###
- Add `qmlbind_exporter_into_metaobject()` function transform an exporter directly into a metaobject.

### Changed ###
- Rename `qmlbind_value_get_backref()` to `qmlbind_value_unwrap()`, as it's the opposite operation of
  `qmlbind_engine_new_wrapper()`.
- `qmlbind_backref` is removed and replaced with two more specific types:
  `qmlbind_client_object` and `qmlbind_client_class`. `qmlbind_client_object` is used for references exposed to the
  metaobject system located in the client code, and `qmlbind_client_class` is used for references to class objects
  located in the client code.

### Deprecated ###

### Removed ###
- Remove `qmlbind_interface` from public api. You can now directly hand `qmlbind_interface_handlers` to
  `qmlbind_exporter`.
- Interface and its atomic reference counting mechanism is also removed from the internals, which might speed
  things up a little as no synchronization is needed anymore.
- Remove `qmlbind_exporter_release()` and `qmlbind_metaobject_new()`. Use `qmlbind_exporter_into_metaobject()` instead,
  which take ownership of the exporter.

### Fixed ###

### Security ###

## 0.1.0 - 2016-04-05 ##
### Main Features ###
- Simple API to export objects / classes dynamically to QML
- Shared library with pure C interface
  - Decouple your language bindings from Qt itself
  - High portability
- Build with qmake
  - No need to configure compilation flags for Qt manually


This uses [Keep a CHANGELOG](http://keepachangelog.com/) as a template.


[0.2.0]: https://github.com/alacarte-maps/alacarte/compare/v0.1.0...HEAD
