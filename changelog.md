# Change Log #
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [0.2.0] - Unreleased ##
### Added ###
- Add `qmlbind_signal_emitter_new(wrapper)` to create new signal emitters for wrappers created via
  `qmlbind_engine_new_wrapper()`. Previously, such wrappers could not emit signals.

### Changed ###
- Rename `qmlbind_value_get_backref()` to `qmlbind_value_unwrap()`, as it's the opposite operation of
  `qmlbind_engine_new_wrapper()`.
- `qmlbind_backref` is removed and replaced with two more specific types:
  `qmlbind_client_object` and `qmlbind_client_class`. `qmlbind_client_object` is used for references exposed to the
  metaobject system located in the client code, and `qmlbind_client_class` is used for references to class objects
  located in the client code.
- Rename `qmlbind_interface_handlers` to `qmlbind_client_callbacks` because there is no `qmlbind_interface` anymore
  and to reflect it is implemented by the user of libqmlbind. This fits the theme that all client-defined types are
  called `qmlbind_client_*` now (namely `qmlbind_client_object` and `qmlbind_client_class`).
- Rename `qmlbind_exporter` to `qmlbind_metaclass` to make its intent more obvious.
- Change `qmlbind_register_type()` to `qmlbind_metaclass_register()`.

### Deprecated ###

### Removed ###
- Remove `qmlbind_metaobject` from public api. The metaobjects are now automatically created in `qmlbind_metaclass_register()` and `qmlbind_engine_new_wrapper()`.
- Remove `qmlbind_interface` from public api. You can now directly hand `qmlbind_interface_handlers` to
  `qmlbind_exporter`.
- Interface and its atomic reference counting mechanism is also removed from the internals, which might speed
  things up a little as no synchronization is needed anymore.

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
