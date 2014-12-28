#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <qmlbind.h>

int main(int argc, char **argv)
{
    auto app = qmlbind_application_new(argc, argv);
    auto result = Catch::Session().run();
    qmlbind_application_delete(app);
    return result;
}
