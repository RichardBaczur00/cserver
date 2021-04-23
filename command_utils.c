#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "command_utils.h"

void log_request(struct command request) {
	printf("Request received: \nMethod: \t %d\nData type: \t %s\nData: \t %s", request.method_code, request.data_type, request.data);
}

int parse_command(char *raw_request) {
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

	log_request(request);

	return 0;
}

int execute_command(struct command request) {
	
}
