#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get.h"

struct get_request get_paths[NUMBER_OF_UNIQUE_PATHS];

int find_request_index(char* path) {
	for (int i = 0; i < first_free_get; ++i) {
		if (strcmp(path, get_paths[i].url) == 0) {
			return i;
		}
	}
}

struct get_request find_request(char* path) {
	for (int i = 0; i < first_free_get; ++i) {
		if (strcmp(path, get_paths[i].url) == 0) {
			return get_paths[i];
		}
	}
}

void add_path(char* url) {
	struct get_request *new_path;
	strcpy(new_path->url, url);
	get_paths[first_free_get++] = *new_path;
}

void set_callback(char *path, int(* callback)(char*, int)) {
	int path_index = find_request_index(path);
	get_paths[path_index].callback = callback;
}

int get(struct get_request path, char* data, int file_descriptor) {
	int status = path.callback(data, file_descriptor);

	return status;
}
