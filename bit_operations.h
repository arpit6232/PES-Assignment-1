#ifndef BIT_OPERATIONS_
#define BIT_OPERATIONS_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
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


/**
​ * ​ ​ @brief​ ​ Helper Function to check or prevent illegal access to memory out of scope 
​ *
​ * ​ ​ Returns a success or failure check over number of bytes before they are proceesed 
 *   for decimal to binary and decimal to hex conversion 
 *
​ * ​ ​ @param​ ​ str : ​ Pointer to a char​ data​ set where the hex dump would be stored
 *   @param  size : char array Instantiated of at 'size' bytes
 *   @param  num : Address in memory from where hex dump would be recorded
 *   @param nbits : Number of bits upto which string pointer would be manipulated in memory 
 *   @param base : Base for conversionDecimal -2 , Hexadecimal - 16
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0 = Failure )
​ */
int check_legality(char *str, size_t size, uint32_t num, uint8_t nbits, int base);


/**
​ * ​ ​ @brief​ ​ Helper Function to convert decimal number to binary representation 
​ *
​ * ​ ​ Returns a pointer to a string which represents the binary representation of the 
 *   decimal number.  
 * 
​ * ​ ​ @param​ ​ str : ​ Pointer to a char​ data​ set where the hex dump would be stored
 *   @param  size : char array Instantiated of at 'size' bytes
 *   @param  num : Address in memory from where hex dump would be recorded
 *   @param nbits : Number of bits upto which string pointer would be manipulated in memory 
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0 = Failure )
​ */
void dec_to_bin(char *str, size_t size, uint32_t num, uint8_t nbits);

/**
​ * ​ ​ @brief​ ​ Test function to test uint_to_binstr() function with test cases  
​ *
​ * ​ ​ Returns status as integer "1" if all test cases return successful, else "0" 
 *   Test Cases include 
 *   - Check on conversion of negative numbers
 *   - Check on convertion to binary numbers which require more than specified bytes
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0 = Failure )
​ */
int test_uint_to_binstr(int debug);

/**
​ * ​ ​ @brief​ ​ Test function to test int_to_binstr() function with test cases  
​ *
​ * ​ ​ Returns status as integer "1" if all test cases return successful, else "0" 
 *   Test Cases include 
 *   - Check on conversion to binary which require more than specified bytes 
 *   - Segmentation Faults Check 
 *   - Check on convertion to binary numbers which require more than specified bytes
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0 = Failure )
​ */
int test_int_to_binstr(int debug);


/**
​ * ​ ​ @brief​ ​ Test function to test uint_to_hexstr() function with test cases  
​ *
​ * ​ ​ Returns status as integer "1" if all test cases return successful, else "0" 
 *   Test Cases include 
 *   - Check on conversion to hexadecimal which require more than specified bytes 
 *   - Segmentation Faults Check 
 *   - Check on convertion to binary numbers which require more than specified bytes
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0 = Failure )
​ */
int test_uint_to_hexstr(int debug);

/**
​ * ​ ​ @brief​ ​ Test function to test twiggle_bit() function with test cases  
​ *
​ * ​ ​ Returns status as integer "1" if all test cases return successful, else "0" 
 *   Test Cases include 
 *   - Segmentation Faults Check 
 *   - Check on convertion to binary numbers which require more than specified bytes
 *   - Check which uses any other setups other than SET, TOGGLE, CLEAR
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0 = Failure )
​ */
int test_twiggle_bit(int debug);

/**
​ * ​ ​ @brief​ ​ Test function to test grab_three_bits() function with test cases  
​ *
​ * ​ ​ Returns status as integer "1" if all test cases return successful, else "0" 
 *   Test Cases include 
 *   - Segmentation Faults Check 
 *   - Check on bit manipulation over bits which access more than require more than specified bytes
 *   - Check to prevent access to bits which are negative and greater than 30
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0xFFFFFFFF = Failure )
​ */
int test_grab_three_bits(int debug);

/**
​ * ​ ​ @brief​ ​ Test function to test hexdump() function with test cases  
​ *
​ * ​ ​ Returns status as integer "1" if all test cases return successful, else "0" 
 *   Test Cases include 
 *   - Segmentation Faults Check 
 *   - Check to get the hexdump of a specified string upto the specific bytes
 * 
​ * ​ ​ @return​ ​ Integer ( 1 = Success, 0 = Failure )
​ */
int test_hexdump(int debug);


#endif /* BIT_OPERATIONS_ */