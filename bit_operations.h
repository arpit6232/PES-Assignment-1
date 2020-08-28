#ifndef BIT_OPERATIONS_
#define BIT_OPERATIONS_


#define CHAR_MIN 0
#define CHAR_MAX 255
#define UINT_MIN -32768

#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>
// UINT32_MAX


typedef enum {
CLEAR,
SET,
TOGGLE
} operation_t;

// Helper Functions 
void stringlen(char* str);
//  
int uint_to_binstr(char *str, size_t size, uint32_t num, uint8_t nbits);
int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits);
int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits);
uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation);
uint32_t grab_three_bits(uint32_t input, int start_bit);
char *hexdump(char *str, size_t size, const void *loc, size_t nbytes);
#endif