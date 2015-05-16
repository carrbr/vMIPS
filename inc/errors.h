#define ERR_CANT_OPEN_FILE 	-1
#define ERR_FILE_TOO_LARGE 	-2
#define ERR_INVALID_ARGS	-3
#define ERR_FILE_READ		-4

// special error print function
#define ERROR
#ifdef ERROR
#define ERR_PRINT(...) fprintf(stderr, "ERROR %s", __FUNCTION__);fprintf(stderr, __VA_ARGS__)
#else
#define ERR_PRINT(...) ; //
#endif

// special warning print function
#define WARN
#ifdef WARN
#define WARN_PRINT(...) fprintf(stderr, "WARNING %s", __FUNCTION__);fprintf(stderr, __VA_ARGS__)
#else
#define WARN_PRINT(...) ; //
#endif