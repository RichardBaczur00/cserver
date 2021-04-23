#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get.h"

void add_path(char* url) {
	struct get_request *new_path;
	strcpy(new_path->url, url);

	memcpy((struct get_request*) &paths[first_free_path++], new_path, sizeof(*new_path));
}

void set_callback(struct get_request *path, int(* callback)(char* data)) {
	path->callback = callback;
}

int exec(struct get_request path, char* data) {
	int status = path.callback(data);

	return status;
}
