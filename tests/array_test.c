#include "array.c"
#include "snow/snow.h"

struct test_struct
{
    int i;
    char c;
};

static void set_test_struct(struct test_struct *p, int i, char c)
{
    p->i = i;
    p->c = c;
}

static bool test_checker(void *l, void *r)
{
    struct test_struct *le = l, *re = r;
    return le->i == re->i && le->c == re->c;
}

static struct test_struct *init_checker_test(size_t *len)
{
    const size_t arrlen = 5;
    struct test_struct *arr = malloc(sizeof(struct test_struct) * arrlen);
    set_test_struct(&arr[0], 1, 'a');
    set_test_struct(&arr[1], 3, 'b');
    set_test_struct(&arr[2], 5, 'c');
    set_test_struct(&arr[3], 7, 'd');
    set_test_struct(&arr[4], 9, 'e');
	*len = arrlen;
	return arr;
}

describe(array, {
    it("Search empty array", {
        struct test_struct *arr = NULL;
        struct test_struct m = {.i = 1, .c = 'a'};
        struct test_struct *res = array_search(arr, sizeof(struct test_struct), 0, test_checker, &m);
        asserteq(res, NULL);
    });

    it("Match at 0 index", {
		struct test_struct m = {.i = 1, .c = 'a'};
		size_t arrlen = 0;
		struct test_struct* arr = init_checker_test(&arrlen);
		defer(free(arr));
        struct test_struct *res = array_search(arr, sizeof(struct test_struct), arrlen, test_checker, &m);
        asserteq(res, &arr[0]);
    });

    it("Match in the middle", {
		struct test_struct m = {.i = 5, .c = 'c'};
		size_t arrlen = 0;
		struct test_struct* arr = init_checker_test(&arrlen);
		defer(free(arr));
        struct test_struct *res = array_search(arr, sizeof(struct test_struct), arrlen, test_checker, &m);
        asserteq(res, &arr[2]);
    });

    it("Match on the end", {
		struct test_struct m = {.i = 9, .c = 'e'};
		size_t arrlen = 0;
		struct test_struct* arr = init_checker_test(&arrlen);
		defer(free(arr));
        struct test_struct *res = array_search(arr, sizeof(struct test_struct), arrlen, test_checker, &m);
        asserteq(res, &arr[4]);
    });

	it("No match at all", {
		struct test_struct m = {.i = 10, .c = 'e'};
		size_t arrlen = 0;
		struct test_struct* arr = init_checker_test(&arrlen);
		defer(free(arr));
        struct test_struct *res = array_search(arr, sizeof(struct test_struct), arrlen, test_checker, &m);
        asserteq(res, NULL);
	});
});
