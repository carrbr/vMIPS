//#define DEBUG
#ifdef DEBUG
extern int debug_var = 0;
#define DEBUG_PRINT(...) debug_var += printf("%s: ", __FUNCTION__);debug_var += printf(__VA_ARGS__)
#else
#define DEBUG_PRINT ;//
#endif

//#define DEBUG2
#ifdef DEBUG2
#define DEBUG2_PRINT(...) printf("%s: ", __FUNCTION__);printf(__VA_ARGS__)
#else
#define DEBUG2_PRINT ;//
#endif
