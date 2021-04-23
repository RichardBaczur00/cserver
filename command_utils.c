#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "command_utils.h"
#include "requests/get.h"

void log_request(struct command request) {
	printf("Request received: \nMethod: \t %d\nURL: \t %s\nData type: \t %s\nData: \t %s\n",
		       	request.method_code, request.url, request.data_type, request.data);
}

int parse_command(char *raw_request, int file_descriptor) {
	char *token;
	int line = 0;
	struct command request;

	printf("%s", raw_request);

	// Allocations only for testing
	// Dinamic allocations will soon be added
	request.data_type = (char*) calloc(20, sizeof(char));
	request.url = (char*) calloc(30, sizeof(char));
	request.data = (char*) calloc(100, sizeof(char));

	token = strtok(raw_request, ";");

	while (token != NULL) {
		if (line == 0) {
			// deal with method
			if (strcmp(token, "GET") == 0) {
				request.method_code = GET_TYPE;	
			} else if (strcmp(token, "POST") == 0) {
				request.method_code = POST_TYPE;
			} else if (strcmp(token, "DELETE") == 0) {
				request.method_code = DELETE_TYPE;
			} else if (strcmp(token, "PUT") == 0) {
				request.method_code = PUT_TYPE;
			} else if (strcmp(token, "PATCH") == 0) {
				request.method_code = PATCH_TYPE;
			} else {
				// handle error
			}
		} else if (line == 1) {
			strcpy(request.url, token);
		} else if (line == 2) {
			// deal with content type
			strcpy(request.data_type, token);
			//TODO: Add checking for certain types (for now text will do it)
		} else {
			// deal with data itself
			strcat(request.data, token);
			//TODO: Check whether the data matches the type declared above
		}

		++line;

		token = strtok(NULL, ";");
	}

	free(token);

	log_request(request);

	execute_command(request, file_descriptor);

	return 0;
}

int dummy_callback(char* incoming, int file_descriptor) {
	printf("Inside handler\n");
	incoming[strlen(incoming) - 2] = '\0';
	printf("Data received: %s\n", incoming);
	printf("Data expected: %s\n", "ping");
	printf("Comparison: %d\n", strcmp(incoming, "ping"));
	if (strcmp(incoming, "ping") == 0) {
		send(file_descriptor, "pong", strlen("pong"), 0);
	}
	else {
		send(file_descriptor, "pingme", strlen("pingme"), 0);
	}
}

void add_dummy_get() {
	printf("Adding the dummy path\n");
	add_path("http://localhost:8080/ping");
	set_callback("http://localhost:8080/ping", &dummy_callback);
	printf("Added the dummy path\n");
}

int execute_command(struct command request, int file_descriptor) {
	char *url = (char*) calloc(30, sizeof(char));
	char *data = (char*) calloc(100, sizeof(char));
	add_dummy_get();

	switch (request.method_code) {
		case 1:

			strcpy(url, request.url);
			strcpy(data, request.data);

			struct get_request new_request = find_request(url);
			get(new_request, data, file_descriptor);

			free(url);
			free(data);

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			// handle error
			break;
	}
}







