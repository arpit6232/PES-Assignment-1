#ifndef BIT_OPERATIONS_
#define BIT_OPERATIONS_

#include <stdint.h>
#include <stddef.h>

// #define INT_MIN -2147483648
// #define INT_MAX +2147483647
// #define UINT_MAX 4294967295


typedef enum {
CLEAR,
SET,
TOGGLE
} operation_t;

/**
​ * ​ ​ @brief​ ​ Returns a character corresponding to hex table for decimal equivalent
​ *
​ * ​ ​ Given​ ​ a ​ ​ integer ​ to​ ​ a ​ ​ char​ ​ data​ ​ set,​ ​ this​ ​ will​ ​ return​ ​ a char 
​ * ​ equivalent in hex
​ *
​ * ​ ​ @param​ ​ num ​ Integer ​ to​ ​ a ​ ​ data​ ​ item
​ *
​ * ​ ​ @return​ ​ char.
​ */
char convert(int num); 

/**
​ * ​ ​ @brief​ ​ Returns a integer set with a specific bit
​ *
​ * ​ ​ Given​ ​ a ​ ​ integer ​and a bit location,​ ​ this​ ​ will​ ​ return​ ​ a uint32_t
 *   Set to a specified bit location
 *
​ * ​ ​ @param​ ​ num : ​ Integer ​ to​ ​ a ​ ​ data​ ​ item
 *   @param  bit : Location of a specific bit on the register corresponding to num
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
int set_bit(uint32_t input, int bit);

/**
​ * ​ ​ @brief​ ​ Returns a integer set with a specific bit
​ *
​ * ​ ​ Given​ ​a integer ​and a bit location,​ this​ ​ will​ ​ return​ ​ a uint32_t
 *   cleared to a specified bit location
 *
​ * ​ ​ @param​ ​ num : ​ Integer ​ to​ ​ a ​ ​ data​ ​ item
 *   @param  bit : Location of a specific bit on the register corresponding to num
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
int clear_bit(uint32_t input, int bit) ;

/**
​ * ​ ​ @brief​ ​ Returns a integer set with a specific bit
​ *
​ * ​ ​ Given​ ​a integer ​and a bit location,​ this​ ​ will​ ​ return​ ​ a uint32_t
 *   Toggled to a specified bit location
 *
​ * ​ ​ @param​ ​ num : ​ Integer ​ to​ ​ a ​ ​ data​ ​ item
 *   @param  bit : Location of a specific bit on the register corresponding to num
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
int toggle_bit(uint32_t input, int bit);

/**
​ * ​ ​ @brief​ ​ Returns a pointer to a string corresponding to binary representation of 
 *           unsigned uint32_t integer
​ *
​ * ​ ​ Given​ ​a pointer to string instantiated with a specified size, function returns the 
 *   length of the binary equivalent of a number (argument) upto a specified number of 
 *   bits (argument)
 *
​ * ​ ​ @param​ ​ str : ​ Pointer to a char​ ​ data​ ​ set 
 *   @param  size : char array Instantiated of at 'size' bytes
 *   @param  num : Integer to be converted to binary 
 *   @param nbits : It is the number of bits of the input
​ *
​ * ​ ​ @return​ ​ int
​ */

int uint_to_binstr(char *str, size_t size, uint32_t num, uint8_t nbits);

/**
​ * ​ ​ @brief​ ​ Returns a pointer to a string corresponding to binary representation of 
 *           signed uint32_t integer
​ *
​ * ​ ​ Given​ ​a pointer to string instantiated with a specified size, function returns the 
 *   length of the binary equivalent of a number (argument) upto a specified number of 
 *   bits (argument)
 *
​ * ​ ​ @param​ ​ str : ​ Pointer to a char​ ​ data​ ​ set 
 *   @param  size : char array Instantiated of at 'size' bytes
 *   @param  num : Integer to be converted to binary 
 *   @param nbits : It is the number of bits of the input
​ *
​ * ​ ​ @return​ ​ int
​ */

int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits);


/**
​ * ​ ​ @brief​ ​ Returns a pointer to a string corresponding to hexadecimal representation of 
 *           unsigned uint32_t integer
​ *
​ * ​ ​ Given​ ​a pointer to string instantiated with a specified size, function returns the 
 *   length of the hex equivalent of a number (argument) upto a specified number of 
 *   bits (argument)
 *
​ * ​ ​ @param​ ​ str : ​ Pointer to a char​ ​ data​ ​ set 
 *   @param  size : char array Instantiated of at 'size' bytes
 *   @param  num : Integer to be converted to binary 
 *   @param nbits : It is the number of bits of the input
​ *
​ * ​ ​ @return​ ​ int
​ */

int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits);

/**
​ * ​ ​ @brief​ ​ Bit Manipulation to set/clear/toggle a but at a specified bit location
​ *
​ * ​ ​ Changes a single bit of the input value, without changing the other bits. Upon invocation, bit is in
*    the range 0 to 31, inclusive. Returns 0xFFFFFFFF in the case of an error.
 *
​ * ​ ​ @param​ ​ input : Integer data of whose bits are to be manipulated 
 *   @param  bit : Specific location upon which bit manipulation is to be carried out
​ *   @param  operation : Object to Enum Operation_t
​ * ​ ​ @return​ ​ uint32_t
​ */
typedef enum {
CLEAR,
SET,
TOGGLE
} operation_t;
uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation);

/**
​ * ​ ​ @brief​ ​ Bit Manipulation to return three bits from the input value, shifted down. 
 *
​ * ​ ​ @param​ ​ input : ​ Pointer to a integer data​ ​over which bits values are to be extracted 
 *   @param  start_bit : Starting bit location from which next 3 bits would be extracted
​ *
​ * ​ ​ @return​ ​ uint32_t 
​ */

uint32_t grab_three_bits(uint32_t input, int start_bit);
/**
​ * ​ ​ @brief​ ​ Hex Dump of a memory location upto a selected number of bytes at a specified memory 
 *           location
​ *
​ * ​ ​ Returns a string pointer representing a “dump” of the nbytes of memory starting at loc. Bytes are
 *    printed up to 16 bytes per line, separated by newlines. The function returns the pointer str, which 
 *   facilitates daisy-chaining this function into other
 *   string-manipulation functions such as puts.
 *
​ * ​ ​ @param​ ​ str : ​ Pointer to a char​ data​ set where the hex dump would be stored
 *   @param  size : char array Instantiated of at 'size' bytes
 *   @param  num : Address in memory from where hex dump would be recorded
 *   @param nbytes : Number of bytes upto which the hex values of the memory would be stored
 * 
​ * ​ ​ @return​ ​ Character Pointer
​ */

char *hexdump(char *str, size_t size, const void *loc, size_t nbytes);

#endif /* BIT_OPERATIONS_ */