
#include "config.h"
#include "speedunit.h"

char* str = "Option=value";

void config_parse_line()
{
    config_value *setting = cv_parseLine(str);
    sp_assert(setting, "Setting was not made");
}

void config_fixture()
{
    sp_run_test(config_parse_line);
}
