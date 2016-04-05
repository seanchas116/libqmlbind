#include <qmlbind.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \file main.c
 * \brief This example shows how to wrap fizzbuzz into a metaclass with `libqmlbind`.
 */

#define UNUSED(x) (void)(x)

#define MIN_RESULT_LEN 9 // len("FizzBuzz") + 1


typedef struct fizzbuzz
{
    int input;
    char *result;
    int result_len;
    qmlbind_signal_emitter *signalEmitter;
} fizzbuzz_t;


void on_changed(fizzbuzz_t *fb, const qmlbind_value *input)
{
    input_str_len++; // take '\0' into account
    if (input_str_len > fb->result_len) {
        fb->result_len =
            input_str_len > MIN_RESULT_LEN ? input_str_len : MIN_RESULT_LEN;
        fb->result = realloc(fb->result, sizeof(char) * fb->result_len);
        if (fb->result == NULL) {
            printf("Error reallocating memory");
            qmlbind_application_exit(0);
            return;
        }
    }

    int i = (int) qmlbind_value_get_number(input);
    if (i % 15 == 0) {
        qmlbind_signal_emitter_emit(fb->signalEmitter, "inputWasFizzBuzz",
                                    0, NULL);
        strcpy(fb->result, "FizzBuzz");
    } else if (i % 3 == 0) {
        strcpy(fb->result, "Fizz");
    } else if (i % 5 == 0) {
        strcpy(fb->result, "Buzz");
    } else {
        sprintf(fb->result, "%d", i);
    }

    qmlbind_value *params[1] = {
        qmlbind_value_new_string_cstr(fb->result)
    };
    qmlbind_signal_emitter_emit(fb->signalEmitter, "resultChanged", 1,
                                (const qmlbind_value * const*) params);
    qmlbind_value_release(params[0]);
}


qmlbind_client_object *
fizzbuzz_new_object_cb(qmlbind_client_class *classRef,
                       qmlbind_signal_emitter *signalEmitter)
{
    UNUSED(classRef);

    fizzbuzz_t *fb = malloc(sizeof(fizzbuzz_t));
    fb->input = 0;
    fb->result = malloc(sizeof(char) * MIN_RESULT_LEN);
    fb->result_len = MIN_RESULT_LEN;
    strcpy(fb->result, "");
    fb->signalEmitter = signalEmitter;

    return (qmlbind_client_object *) fb;
}


void fizzbuzz_delete_object_cb(qmlbind_client_object *obj)
{
    fizzbuzz_t *fb = (fizzbuzz_t *) obj;
    free(fb->result);
    qmlbind_signal_emitter_release(fb->signalEmitter);
    free(fb);
}


qmlbind_value *fizzbuzz_call_method_cb(qmlbind_engine *engine,
                                       qmlbind_client_object *obj,
                                       const char *name,
                                       int argc,
                                       const qmlbind_value *const *argv)
{
    UNUSED(engine);
    UNUSED(argc);
    UNUSED(argv);

    fizzbuzz_t *fb = (fizzbuzz_t *) obj;

    if (strcmp(name, "quit") == 0) {
        printf("Quitting… Last result was: %s\n", fb->result);
        qmlbind_application_exit(0);
    }

    return qmlbind_value_new_undefined();
}


qmlbind_value *fizzbuzz_get_property_cb(qmlbind_engine *engine,
                                        qmlbind_client_object *obj,
                                        const char *name)
{
    UNUSED(engine);

    fizzbuzz_t *fb = (fizzbuzz_t *) obj;

    if (strcmp(name, "input") == 0) {
        return qmlbind_value_new_number(fb->input);
    } else if (strcmp(name, "result") == 0) {
        return qmlbind_value_new_string_cstr(fb->result);
    } else {
        return qmlbind_value_new_undefined();
    }
}


void fizzbuzz_set_property_cb(qmlbind_engine *engine,
                              qmlbind_client_object *obj,
                              const char *name,
                              const qmlbind_value *value)
{
    UNUSED(engine);

    fizzbuzz_t *fb = (fizzbuzz_t *) obj;

    if (strcmp(name, "input") == 0) {
        fb->input = (int) qmlbind_value_get_number(value);

        on_changed(fb, value);

        qmlbind_value *params[1] = {
            qmlbind_value_new_number(fb->input)
        };
        qmlbind_signal_emitter_emit(fb->signalEmitter, "inputChanged", 1,
                                    (const qmlbind_value * const*) params);
        qmlbind_value_release(params[0]);
    } else if (strcmp(name, "result") == 0) {
        qmlbind_string *qstr = qmlbind_value_get_string(value);
        const char *str = qmlbind_string_get_chars(qstr);
        strcpy(fb->result, str);

        qmlbind_value *params[1] = {
            qmlbind_value_new_string_cstr(fb->result)
        };
        qmlbind_signal_emitter_emit(fb->signalEmitter, "resultChanged", 1,
                                    (const qmlbind_value * const*) params);
        qmlbind_value_release(params[0]);
    }
}


void create_fizzbuzz_metaclass()
{
    qmlbind_client_class *classRef = NULL;
    qmlbind_client_callbacks callbacks;
    callbacks.new_object = fizzbuzz_new_object_cb;
    callbacks.delete_object = fizzbuzz_delete_object_cb;
    callbacks.call_method = fizzbuzz_call_method_cb;
    callbacks.get_property = fizzbuzz_get_property_cb;
    callbacks.set_property = fizzbuzz_set_property_cb;

    qmlbind_metaclass *metaclass =
        qmlbind_metaclass_new(classRef, "FizzBuzz", callbacks);

    const char *params1[] = { "input" };
    qmlbind_metaclass_add_signal(metaclass, "inputChanged", 1, params1);
    qmlbind_metaclass_add_property(metaclass, "input", "inputChanged");

    const char *params2[] = { "result" };
    qmlbind_metaclass_add_signal(metaclass, "resultChanged", 1, params2);
    qmlbind_metaclass_add_property(metaclass, "result", "resultChanged");

    qmlbind_metaclass_add_signal(metaclass, "inputWasFizzBuzz", 0, NULL);

    qmlbind_metaclass_add_method(metaclass, "quit", 0);

    qmlbind_metaclass_register(metaclass, "Examples.FizzBuzz", 0, 1, "FizzBuzz");

    qmlbind_metaclass_release(metaclass);
}


int main(int argc, char *argv[])
{
    // explicit const cast required because in plain C99,
    // constness is only converted on the top level.
    qmlbind_application *app =
        qmlbind_application_new(argc, (const char* const*) argv);
    qmlbind_engine *engine = qmlbind_engine_new();

    create_fizzbuzz_metaclass();

    qmlbind_component *component = qmlbind_component_new(engine);
    qmlbind_component_load_path(component, "main.qml");

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
