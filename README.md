# PES-Assignment-1
Author: Arpit Savarkar

## Repository Comments 
_Contains_
Code for Assignment 1 for PES, ECEN-5813, Fall 2020

Repository for PES-Assignment 1 

- <b>bit_operations.h - Header file which contains the function prototypes and enumerators needed for bit_operations.c
- <b>bit_operations.c - The main script for bit manipulation and data representation styles (decimal, binary and hexadecimal) and code for hexdump from a specific location</b>

Involves Six Functions and Unit Tests and helper functions for the following 
1) uint_to_binstr(char *str, size_t size, uint32_t num, uint8_t nbits)
 - Returns the binary representation of an unsigned integer, as a null-terminated string.  On input, str is a pointer to a char array of at least size bytes,numis the value to be converted,and nbitsis the number of bits in the input.If the operation was successful, the function returnsthe number of characters written to str, not including the terminal \0.

2) int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits)
 - Returns the binary representation of a signedinteger, as a null-terminated string. On input, stris a pointer to a char array of at least size bytes,num is the value to be converted,and nbitsis the number of bits in the input.If the operation was successful, the function returns the number of characters written to str, not including the terminal \0. In the case of an error, the function returns a negative value, and stris set to theempty string.

3) uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits)
 - Returns the hexadecimal representation of an unsigned integer, as a null-terminated string. On input, stris a pointer to a char array of at least size bytes, numis the value to be converted, and nbitsis the number of bits to be considered. If the operation was successful, the function returns the number of characters written to str, not including the terminal \0. In the case of an error, the function returns a negative value, and stris set to the empty string.

4) uint32_t twiggle_bit(uint32_t input, int bit, operation_toperation)
 - Changes a single bitof the input value, without changing the other bits. Upon invocation, bitis in the range 0 to 31, inclusive. Returns 0xFFFFFFFF in the case of an error

5) uint32_t grab_three_bits(uint32_t input, int start_bit)
 - Returns three bits from the input value, shifted down.This function’s outputis best shown graphically.
    ........ .XXX.... ........ ........ TO 00000000 00000000 00000000 00000XXX

6) char *hexdump(char *str, size_t size, const void*loc, size_t nbytes)
 - Returns a string representing a “dump” of the nbytesof memorystarting at loc.Bytes areprinted up to 16 bytes per line, separated by newlines

## Assignment Comments 
This assignment demonstrates C Programming from scratch for data representation conversion and basic bit manipulation, it also demonstrates a code for reading a hexdump from a address specified. 

## Execution 
