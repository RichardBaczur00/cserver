#ifndef GET_H_INCLUDED
#define GET_H_INCLUDED

#define NUMBER_OF_UNIQUE_REQUESTS 255

typedef struct get_request {
	char* url;
	int (* callback)(char* data);
} paths[NUMBER_OF_UNIQUE_REQUESTS];

int first_free_path = 0;

void add_path(char* url);
void set_callback(struct get_request*, int(* callback)(char* data));
int exec(struct get_request, char* data);

#endif
