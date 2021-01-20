/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xdeque.h>
#include <exotic/xiterator.h>
#include <exotic/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XDEQUE_FOR(int)
    SETUP_XDEQUE_FOR(str)
    SETUP_XALGORITHM_SWAP_FOR(xdeque_str)
    SETUP_XALGORITHM_SWAP_FOR(char_array)
)

CESTER_TEST(xdeque_init, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_conf_init, _, {
    struct xcontainer_config config;
    xdeque(str) *fruits;
    enum x_stat status;

    config.memory_alloc   = malloc;
    config.memory_calloc  = calloc;
    config.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    status = xdeque_new_config(str)(&config, &fruits);
    cester_assert_uint_eq(status, X_OK);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_add_int, _, {
    xdeque(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xdeque_new(int)(&numbers);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xdeque_add(int)(numbers, index);
        cester_assert_uint_eq(status, X_OK);
    }
    cester_assert_uint_eq(xdeque_size(numbers), limit);

    xdeque_destroy(numbers);
})

CESTER_TEST(xdeque_add_str, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 0);

    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 1);

    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 2);

    status = xdeque_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 3);

    status = xdeque_add(str)(fruits, "Pawpaw");
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 4);

    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 5); 

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_add_at, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 0);

    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 1);
    cester_assert_str_equal(xget_at(fruits, 0), "Apple");

    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 2);
    cester_assert_str_equal(xget_at(fruits, 1), "Banana");

    status = xdeque_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, X_INDEX_OUT_OF_RANGE_ERR);

    status = xdeque_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 3);

    status = xdeque_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 4);

    cester_assert_str_equal(xget_at(fruits, 0), "Apple");
    cester_assert_str_equal(xget_at(fruits, 1), "Mango");
    cester_assert_str_equal(xget_at(fruits, 2), "Banana");
    cester_assert_str_equal(xget_at(fruits, 3), "Coconut");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_get_str, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, X_INDEX_OUT_OF_RANGE_ERR);
    status = xdeque_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, X_OK);

    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 0, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 3, &value), X_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 1, &value), X_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 2, &value), X_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 5, &value), X_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, -40, &value), X_INDEX_OUT_OF_RANGE_ERR);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_replace_at, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);

    cester_assert_str_equal(xget_at(fruits, 0), "Apple");
    cester_assert_str_equal(xget_at(fruits, 1), "Banana");
    cester_assert_str_equal(xget_at(fruits, 2), "Coconut");
    cester_assert_str_equal(xget_at(fruits, 3), "Mango");
    
    cester_assert_uint_eq(xdeque_replace_at(str)(fruits, 0, "Orange", NULL), X_OK);
    cester_assert_uint_eq(xdeque_replace_at(str)(fruits, 1, "Strawberry", NULL), X_OK);
    cester_assert_uint_eq(xdeque_replace_at(str)(fruits, 2, "Pineapple", NULL), X_OK);
    cester_assert_uint_eq(xdeque_replace_at(str)(fruits, 3, "Avocado", NULL), X_OK);

    cester_assert_str_equal(xget_at(fruits, 0), "Orange");
    cester_assert_str_equal(xget_at(fruits, 1), "Strawberry");
    cester_assert_str_equal(xget_at(fruits, 2), "Pineapple");
    cester_assert_str_equal(xget_at(fruits, 3), "Avocado");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_front_back, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);

    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Mango");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_front_back_2, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);

    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Apple");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_front_back_3, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);

    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_EMPTY_CONTAINER_ERR);
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_EMPTY_CONTAINER_ERR);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_capacity, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    
    cester_assert_false(xdeque_is_empty(fruits));
    cester_assert_uint_eq(xdeque_size(fruits), 4);
    cester_assert_uint_eq(xdeque_capacity(fruits), XDEFAULT_CONTAINER_CAPACITY);
    cester_assert_equal(xdeque_max_size(fruits), X_CONTAINER_MAX_CAPACITY);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_max_size_1, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new_max_size(str)(&fruits, 3);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_MAX_SIZE_ERR);
    status = xdeque_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, X_MAX_SIZE_ERR);
    
    cester_assert_false(xdeque_is_empty(fruits));
    cester_assert_uint_eq(xdeque_size(fruits), 3);
    cester_assert_uint_eq(xdeque_capacity(fruits), (xdeque_size(fruits)-1) << 1);
    cester_assert_llong_eq(xdeque_max_size(fruits), 3);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_max_size_2, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xdeque_new_max_size(str)(&fruits, max_size);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, X_MAX_SIZE_ERR);
    
    cester_assert_false(xdeque_is_empty(fruits));
    cester_assert_uint_eq(xdeque_size(fruits), max_size);
    cester_assert_llong_eq(xdeque_max_size(fruits), max_size);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_shrink_to_fit, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    cester_assert_false(xdeque_is_empty(fruits));
    cester_assert_uint_eq(xdeque_size(fruits), 5);
    cester_assert_uint_eq(xdeque_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    status = xdeque_shrink_to_fit(str)(fruits);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_capacity(fruits), (xdeque_size(fruits)-1) << 1);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_swap, _, {
    xdeque(str) *fruits;
    xdeque(str) *foods;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);

    status = xdeque_new(str)(&foods);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, X_OK);

    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xdeque_get_front(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xdeque_get_back(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(xdeque_str)(foods, fruits);

    cester_assert_uint_eq(xdeque_get_front(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_back(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Fufu");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_swap_buffer, _, {
    xdeque(str) *fruits;
    xdeque(str) *foods;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);

    status = xdeque_new(str)(&foods);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, X_OK);

    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xdeque_get_front(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xdeque_get_back(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(char_array)(&xget_buffer(foods), &xget_buffer(fruits));

    cester_assert_uint_eq(xdeque_get_front(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_back(str)(foods, &value), X_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Fufu");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_remove_front_and_back, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 1, &value), X_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xdeque_size(fruits), 3);
    
    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Apple");
    status = xdeque_remove_front(str)(fruits, &value);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xdeque_get_front(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xdeque_size(fruits), 2);
    
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Mango");
    status = xdeque_remove_back(str)(fruits, &value);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xdeque_get_back(str)(fruits, &value), X_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xdeque_size(fruits), 1);

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_remove_at, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    char *value;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 1, &value), X_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xdeque_size(fruits), 3);

    status = xdeque_remove_at(str)(fruits, 1, &value);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 1, &value), X_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xdeque_size(fruits), 2);

    status = xdeque_remove_at(str)(fruits, 0, NULL);
    cester_assert_uint_eq(status, X_OK);
    cester_assert_uint_eq(xdeque_get_at(str)(fruits, 1, &value), X_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xdeque_size(fruits), 1);


    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_clear, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    
    cester_assert_uint_eq(xdeque_size(fruits), 3);
    cester_assert_uint_eq(xdeque_clear(str)(fruits), X_OK);
    cester_assert_uint_eq(xdeque_size(fruits), 0);


    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_iterator, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    
    while (XITERATOR_HAS_NEXT(fruits)) {
        cester_assert_str_not_equal(XITERATOR_NEXT(fruits), NULL);
    }
    XITERATOR_RESET(fruits);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Apple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Banana");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Pineapple");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_iterator_reverse, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    
    while (XITERATOR_HAS_PREV(fruits)) {
        cester_assert_str_not_equal(XITERATOR_PREV(fruits), NULL);
    }
    XITERATOR_RESET(fruits);
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Banana");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Apple");

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    XFOREACH(const char *fruit, fruits, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach_reverse, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    XFOREACH_REVERSE(const char *fruit, fruits, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach_with_index, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    XFOREACH_INDEX(size_t index, const char *fruit, fruits, {
        if (index == 0) {
            cester_assert_str_equal(fruit, "Apple");
        } else if (index == 1) {
            cester_assert_str_equal(fruit, "Banana");
        } else if (index == 2) {
            cester_assert_str_equal(fruit, "Mango");
        } else if (index == 3) {
            cester_assert_str_equal(fruit, "Pineapple");
        }
    });

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach_reverse_with_index, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    XFOREACH_REVERSE_INDEX(size_t index, const char *fruit, fruits, {
        if (index == 3) {
            cester_assert_str_equal(fruit, "Pineapple");
        } else if (index == 2) {
            cester_assert_str_equal(fruit, "Mango");
        } else if (index == 1) {
            cester_assert_str_equal(fruit, "Banana");
        } else if (index == 0) {
            cester_assert_str_equal(fruit, "Apple");
        }
    });

    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_modify_in_loop, _, {
    xdeque(str) *fruits;
    enum x_stat status;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, X_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, X_OK);
    
    XFOREACH_INDEX(size_t index, const char *fruit, fruits, {
        if (xdeque_size(fruits) > 3) {
            status = xdeque_remove_at(str)(fruits, 3, NULL);
            cester_assert_uint_eq(status, X_OK);
        }
        if (xdeque_size(fruits) > 2) {
            status = xdeque_remove_at(str)(fruits, 1, NULL);
            cester_assert_uint_eq(status, X_OK);
        }
        cester_assert_str_not_equal(fruit, "Banana");
        cester_assert_str_not_equal(fruit, "Pineapple");
    });

    xdeque_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
