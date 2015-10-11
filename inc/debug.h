#pragma once

// uncomment to enable debug prints
//#define DEBUG
void debug_impl(char *format_str, ...);
#define DEBUG_PRINT(...) debug_impl(__VA_ARGS__);

// uncomment to enable debug2 prints
//#define DEBUG2
void debug2_impl(char *format_str, ...);
#define DEBUG2_PRINT(...) debug2_impl(__VA_ARGS__);
