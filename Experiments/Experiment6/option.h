#ifndef __OPTION_H
#define __OPTION_H

#include <stdbool.h>

typedef enum {
	SOME,
	NONE,
} option_tag;

typedef struct {
	option_tag t;
	void *data;
} option;

option some(void *data);
option none(void);
bool is_some(option o);
bool is_none(option o);

#ifdef OPTION_IMPL

option some(void *data) {
	return (option) {
		.t = SOME,
		.data = data,
	};
}

option none(void) {
	return (option) {
		.t = NONE,
		.data = NULL,
	};
}

bool is_some(option o) {
	return o.t == SOME;
}

bool is_none(option o) {
	return o.t == NONE;
}

#endif // OPTION_IMPL
#endif // !__OPTION_H
