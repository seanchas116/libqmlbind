#include "test_helper.h"
#include "fixtures/emptyhandlers.h"
#include <qmlbind.h>

TEST_CASE("next_tick")
{
    static bool called;
    called = false;

    qmlbind_next_tick([] (void *data) {
        *((bool *)data) = true;
    }, &called);
    qmlbind_process_events();

    REQUIRE(called);
}
