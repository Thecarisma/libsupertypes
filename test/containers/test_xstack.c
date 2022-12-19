/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstack.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/algorithm/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XDEQUE_FOR(str)
    SETUP_ONLY_XSTACK_FOR(str)
    SETUP_XALGORITHM_SWAP_FOR(xstack_str)
    SETUP_XALGORITHM_SWAP_FOR(char_array)
)

CESTER_TEST(xstack_init, _, {
    xstack(str) *fruits;
    enum x_stat status;

    status = xstack_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_conf_init, _, {
    struct xcontainer_config config;
    xstack(str) *fruits;
    enum x_stat status;

    config.allocator.memory_malloc   = malloc;
    config.allocator.memory_calloc  = calloc;
    config.allocator.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    config.max_size       = 5000;
    status = xstack_new_config(str)(&config, &fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_push, _, {
    xstack(str) *fruits;
    enum x_stat status;
    
    status = xstack_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_true(xstack_is_empty(fruits));
    cester_assert_uint_eq(xstack_size(fruits), 0);

    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xstack_push(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_false(xstack_is_empty(fruits));
    cester_assert_uint_eq(xstack_size(fruits), 4);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_peek, _, {
    xstack(str) *fruits;
    enum x_stat status;
    char *value;

    status = xstack_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    
    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xstack_size(fruits), 1);

    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xstack_size(fruits), 2);

    status =xstack_push(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xstack_size(fruits), 3);

    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xstack_size(fruits), 4);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_pop, _, {
    xstack(str) *fruits;
    enum x_stat status;
    char *value;

    status = xstack_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xstack_push(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xstack_size(fruits), 3);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xstack_size(fruits), 2);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xstack_size(fruits), 1);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xstack_size(fruits), 0);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_pop_underflow, _, {
    xstack(str) *fruits;
    enum x_stat status;
    char *value;

    status = xstack_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xstack_push(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xstack_size(fruits), 3);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xstack_size(fruits), 2);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xstack_size(fruits), 1);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xstack_size(fruits), 0);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_STACK_UNDERFLOW_ERR);

    status = xstack_pop(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_STACK_UNDERFLOW_ERR);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_capacity, _, {
    xstack(str) *fruits;
    enum x_stat status;

    status = xstack_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_false(xstack_is_empty(fruits));
    cester_assert_uint_eq(xstack_size(fruits), 4);
    cester_assert_uint_eq(xstack_capacity(fruits), XDEFAULT_CONTAINER_CAPACITY);
    cester_assert_equal(xstack_max_size(fruits), XTD_CONTAINER_MAX_CAPACITY);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_max_size_1, _, {
    xstack(str) *fruits;
    enum x_stat status;

    status = xstack_new_max_size(str)(&fruits, 3);
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_STACK_OVERFLOW_ERR);
    status = xstack_push(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_STACK_OVERFLOW_ERR);
    
    cester_assert_false(xstack_is_empty(fruits));
    cester_assert_uint_eq(xstack_size(fruits), 3);
    cester_assert_uint_eq(xstack_capacity(fruits), 4);
    cester_assert_llong_eq(xstack_max_size(fruits), 3);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_max_size_2, _, {
    xstack(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xstack_new_max_size(str)(&fruits, max_size);
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Carrot");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_STACK_OVERFLOW_ERR);
    status = xstack_push(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, XTD_STACK_OVERFLOW_ERR);
    
    cester_assert_false(xstack_is_empty(fruits));
    cester_assert_uint_eq(xstack_size(fruits), max_size);
    cester_assert_uint_eq(xstack_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    cester_assert_llong_eq(xstack_max_size(fruits), max_size);

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_swap, _, {
    xstack(str) *fruits;
    xstack(str) *foods;
    enum x_stat status;
    char *value;

    status = xstack_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xstack_new(str)(&foods);
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xstack_push(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xstack_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xstack_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(xstack_str)(foods, fruits);

    cester_assert_uint_eq(xstack_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");
    cester_assert_uint_eq(xstack_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");

    xstack_destroy(fruits);
})

CESTER_TEST(xstack_swap_buffer, _, {
    printf("NEVER EVER SWAP BUFFER OF XSTACK\n");
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

