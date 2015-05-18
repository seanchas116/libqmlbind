#include "test_helper.h"
#include "fixtures/emptyhandlers.h"
#include <qmlbind.h>

TEST_CASE("set_tick_callback")
{
    static bool called;
    called = false;

    qmlbind_set_tick_callback([] {
        called = true;
    });
    qmlbind_process_events();

    REQUIRE(called);
}
