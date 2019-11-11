
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;
    if (sstring_new(&str, "你们好āa") != S_OK) {
        printf("Init failed\n");
        return 1;
    }
    s_assert_not_null(str);
    s_assert_equal(5, sstring_length(str));
    
    sstring_set_value(str, "");
    sstring_concat(str, "好");
    sstring_concat(str, "And");
    sstring_concat(str, "你们好āa");
    s_assert_chars_equal(sstring_get_value(str), "好And你们好āa");
    s_assert_equal(9, sstring_length(str));
    
    s_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}