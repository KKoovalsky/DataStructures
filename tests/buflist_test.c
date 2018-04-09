#include <string.h>
#include "snow/snow.h"
#include "buflist.c"

describe(buflist, {
	it("Concatenate empty list of buffers", {
		struct doubly_linked_list bl;
		init_buflist(&bl);
		
		// Initialize len to a random value
		size_t len = 11;
		char *res = concat_buflist_and_rm(&bl, &len);
		asserteq(res, NULL);
		asserteq(len, 0);
	});

	it("One buffer in buflist", {
		struct doubly_linked_list bl;
		init_buflist(&bl);
		const char buf[] = "You filthy little bastard!"; 
		const size_t buflen = sizeof(buf);
		size_t len = 321312;
		char *res = NULL;
		defer(free(res));
		
		add_buf_to_buflist(&bl, buf, buflen);
		
		res = concat_buflist_and_rm(&bl, &len);
		
		// mortie/snow uses strcmp on strings, == operator otherwise
		asserteq(res, buf);
		asserteq(len, buflen);
	});

	it("Three buffers in buflist", {
		struct doubly_linked_list bl;
		init_buflist(&bl);
		const char buf1[] = "What do You think "; 
		const char buf2[] = "about Polish "; 
		const char buf3[] = "hospital business?";

		// Remember about null terminating character in every buffer but preserve one null terminating character
		const size_t totlen = sizeof(buf1) - 1 + sizeof(buf2) - 1 + sizeof(buf3) - 1 + 1;
		size_t len = 321312;
		char *res = NULL;
		defer(free(res));

		add_buf_to_buflist(&bl, buf1, sizeof(buf1) - 1);
		add_buf_to_buflist(&bl, buf2, sizeof(buf2) - 1);
		add_buf_to_buflist(&bl, buf3, sizeof(buf3));

		res = concat_buflist_and_rm(&bl, &len);
		
		asserteq(res, "What do You think about Polish hospital business?");
		asserteq(len, totlen);
	});
});
