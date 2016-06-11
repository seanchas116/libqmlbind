// This is a port of the Qt quick controls2 gallery example found at
// https://doc-snapshots.qt.io/qt5-5.7/qtquickcontrols2-gallery-example.html
//
// It contains examples of each control as well as the usage of qrc resources.

#include <qmlbind.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // explicit const cast required because in plain C99, constness is only converted on the top level.
    qmlbind_application *app = qmlbind_application_new(argc, (const char* const *)argv);
    qmlbind_engine *engine = qmlbind_engine_new();
    qmlbind_component *component = qmlbind_component_new(engine);
    qmlbind_component_load_url(component, "qrc:/gallery.qml");

    qmlbind_string *errorString;
    if ((errorString = qmlbind_component_get_error_string(component)) != 0) {
        fprintf(stderr, "Error loading component: %s", qmlbind_string_get_chars(errorString));
        qmlbind_string_release(errorString);
        return 1;
    }

    qmlbind_value *instance = qmlbind_component_create(component);

    int exit_code = qmlbind_application_exec(app);

    qmlbind_value_release(instance);
    qmlbind_component_release(component);
    qmlbind_engine_release(engine);
    qmlbind_application_release(app);

    return exit_code;
}
