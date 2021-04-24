#ifndef COMMAND_UTILS_H_DEFINED
#define COMMAND_UTILS_H_DEFINED

#define GET_TYPE 1
#define POST_TYPE 2
#define DELETE_TYPE 3
#define PUT_TYPE 4
#define PATCH_TYPE 5
#define TEXT 0
#define APPLICATION_JSON 1
#define APPLICATION_XML 2


typedef struct _command {
	int method_code;
	char* url;
	int data_type;
	char* data;
} command;

void log_request(command);
int parse_command(char*, int);
int execute_command(command, int);

#endif
