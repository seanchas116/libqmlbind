#include "test_helper.h"
#include "fixtures/emptyhandlers.h"
#include <qmlbind.h>

TEST_CASE("next_tick")
{
    static bool called;
    auto interface = qmlbind_interface_new(emptyHandlers());

    called = false;

    qmlbind_next_tick(interface, [](qmlbind_backref) {
        called = true;
    }, nullptr);
    qmlbind_process_events();

    REQUIRE(called);
}
