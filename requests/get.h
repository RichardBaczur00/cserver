#ifndef GET_H_INCLUDED
#define GET_H_INCLUDED

#define NUMBER_OF_UNIQUE_PATHS 255

typedef struct _get_request {
	char* url;
	int (* callback)(char* data, int file_descriptor);
} get_request;

int find_request_index(char*);
get_request find_request(char*);
void add_path(char*);
void set_callback(char*, int(* callback)(char*, int));
int get(get_request, char* data, int file_descriptor);

#endif
