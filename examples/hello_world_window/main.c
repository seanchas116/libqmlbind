#include <qmlbind.h>
#include <stdio.h>

/*!
 * \file main.c
 * \brief This example shows the basics of how to load a qml file and display it with `libqmlbind`.
 */

int main(int argc, char *argv[]) {
    // explicit const cast required because in plain C99, constness is only converted on the top level.
    qmlbind_application *app = qmlbind_application_new(argc, (const char* const *)argv);
    qmlbind_engine *engine = qmlbind_engine_new();
    qmlbind_component *component = qmlbind_component_new(engine);
    qmlbind_component_load_path(component, "main.qml");

    qmlbind_string *errorString;
    if ((errorString = qmlbind_component_get_error_string(component)) != 0) {
        fprintf(stderr, "Error loading component: %s", qmlbind_string_get_chars(errorString));
        qmlbind_string_release(errorString);
        return 1;
    }

    qmlbind_value *instance = qmlbind_component_create(component);

    qmlbind_value *width_property = qmlbind_value_get_property(instance, "width");
    int width = (int) qmlbind_value_get_number(width_property);
    printf("width of the created component: %dpx\n", width);
    fflush(stdout);
    qmlbind_value_release(width_property);

    int exit_code = qmlbind_application_exec(app);

    qmlbind_value_release(instance);
    qmlbind_component_release(component);
    qmlbind_engine_release(engine);
    qmlbind_application_release(app);

    return exit_code;
}
