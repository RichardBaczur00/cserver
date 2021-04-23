#ifndef GET_H_INCLUDED
#define GET_H_INCLUDED

#define NUMBER_OF_UNIQUE_PATHS 255

typedef struct get_request {
	char* url;
	int (* callback)(char* data, int file_descriptor);
};

int find_request_index(char*);
struct get_request find_request(char*);
void add_path(char*);
void set_callback(char*, int(* callback)(char*, int));
int get(struct get_request, char* data, int file_descriptor);

#endif
