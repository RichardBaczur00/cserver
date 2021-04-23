#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get.h"

struct get_request get_paths[NUMBER_OF_UNIQUE_PATHS];
int first_free_get = 0;

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
	printf("new_path.url <- %s\n", url); 
	new_path->url = (char*) calloc(30, sizeof(char));
	strcpy(new_path->url, url);
	get_paths[first_free_get++] = *new_path;
}

void set_callback(char *path, int(* callback)(char*, int)) {
	int path_index = find_request_index(path);
	get_paths[path_index].callback = callback;
	fprintf(stdout, "in set: callback address: %p \n", get_paths[path_index].callback);
	fflush(stdout);
}

int get(struct get_request path, char* data, int file_descriptor) {
	
	fprintf(stdout, "callback address: %p \n", path.callback);
	fflush(stdout);

	int status = path.callback(data, file_descriptor);

	return status;
}
