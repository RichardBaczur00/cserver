#ifndef COMMAND_UTILS_H_DEFINED
#define COMMAND_UTILS_H_DEFINED

#define GET_TYPE 1
#define POST_TYPE 2
#define DELETE_TYPE 3
#define PUT_TYPE 4
#define PATCH_TYPE 5


typedef struct command {
	int method_code;
	char* url;
	char* data_type;
	char* data;
};

void log_request(struct command);
int parse_command(char*);
int execute_command(struct command);

#endif
