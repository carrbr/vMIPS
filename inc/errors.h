#define ERR_CANT_OPEN_FILE 	-1
#define ERR_FILE_TOO_LARGE 	-2
#define ERR_INVALID_ARGS	-3
#define ERR_FILE_READ		-4

// special error print function
#define ERROR
#ifdef ERROR
#define ERR_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
#define ERR_PRINT(...) ; //
#endif