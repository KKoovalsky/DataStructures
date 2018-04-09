#include <stdio.h>
#include <stdbool.h>
#include "snow/snow.h"
#include "doubly_linked_list.c"

#define create_test_elem(_name, _i, _p, _c)	\
	struct test_elem _name;						\
	_name.i = _i;								\
	_name.cp = _p;								\
	_name.c = _c								

struct test_elem
{
	int i;
	char *cp;
	char c;
};

static bool compare_test_elem(struct test_elem *l, struct test_elem *r)
{
	return l->i == r->i && l->cp == r->cp && l->c == r->c;
}

describe(doubly_linked_list, {
	it("Remove from an empty list", {
		struct doubly_linked_list l;
		dl_list_init(&l, sizeof(struct test_elem));
		defer(dl_list_delete(&l));
		asserteq(l.head, NULL);
		asserteq(l.tail, NULL);

		// Remove from empty list
		dl_list_remove_node(&l, NULL);
		asserteq(l.head, NULL);
	});

	it("Add an element and remove it", {
		struct doubly_linked_list l;
		dl_list_init(&l, sizeof(struct test_elem));
		defer(dl_list_delete(&l));
		
		// Add a node
		create_test_elem(elem1, 312, "MAKAKA", 'c');
		dl_list_insert_at_tail(&l, &elem1);
		// l.head + 1 is same as l.head->elem
		assert(compare_test_elem((struct test_elem *) (l.head + 1), &elem1));
		assert(compare_test_elem(l.head->elem, &elem1));
		assert(compare_test_elem((struct test_elem *) (l.tail + 1), &elem1));

		// And remove it
		dl_list_remove_node(&l, l.head);
		asserteq(l.head, NULL);
		asserteq(l.tail, NULL);
	});

	it("Add two and delete first and then add two", {
		struct doubly_linked_list l;
		dl_list_init(&l, sizeof(struct test_elem));
		defer(dl_list_delete(&l));
	
		// Add two
		create_test_elem(elem1, 500, "MASTA", 'm');
		dl_list_insert_at_tail(&l, &elem1);
		create_test_elem(elem2, 100, "HIPOCAMP", 'i');
		dl_list_insert_at_tail(&l, &elem2);

		// Delete the last one
		dl_list_remove_node(&l, l.tail);
		assert(compare_test_elem((struct test_elem *) (l.head + 1), &elem1));
		assert(compare_test_elem(l.head->elem, &elem1));
		// One element on the list so the head must be the same as the tail
		asserteq(l.head, l.tail);

		// Add two more
		create_test_elem(elem3, 1000, "GARGAMELLO", 's');
		dl_list_insert_at_tail(&l, &elem3);
		create_test_elem(elem4, 1001, "BONZORNO", 'p');
		dl_list_insert_at_tail(&l, &elem4);

		assert(compare_test_elem(l.tail->prev->elem, &elem3));
		assert(compare_test_elem(l.tail->elem, &elem4));
	});

	it("Add some elements and remove first", {
		struct doubly_linked_list l;
		dl_list_init(&l, sizeof(struct test_elem));
		defer(dl_list_delete(&l));

		// Add three
		create_test_elem(elem1, 511, "KASTA", 'z');
		dl_list_insert_at_tail(&l, &elem1);
		create_test_elem(elem2, 109, "RADAGASTA", 'o');
		dl_list_insert_at_tail(&l, &elem2);
		create_test_elem(elem3, 127, "GOLUMMOIS", 'g');
		dl_list_insert_at_tail(&l, &elem3);

		// Remove the first
		dl_list_remove_node(&l, l.head);
		assert(compare_test_elem(l.head->elem, &elem2));
		assert(compare_test_elem(l.tail->elem, &elem3));
	});

	it("Add some elements and remove from the middle", {
		struct doubly_linked_list l;
		dl_list_init(&l, sizeof(struct test_elem));
		defer(dl_list_delete(&l));

		// Add three
		create_test_elem(elem1, 999999, "AUROBERIALIS", '0');
		dl_list_insert_at_tail(&l, &elem1);
		create_test_elem(elem2, 3166, "NASTURTIO", '1');
		struct dll_node *node = dl_list_insert_at_tail(&l, &elem2);
		create_test_elem(elem3, 11, "PROMUNDIS", '2');
		dl_list_insert_at_tail(&l, &elem3);

		// Remove from the middle
		dl_list_remove_node(&l, node);
		assert(compare_test_elem(l.head->next->elem, l.tail->elem));
		assert(compare_test_elem(l.head->next->elem, &elem3));
		asserteq(l.head, l.tail->prev);
	});
});

