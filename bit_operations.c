/******************************************************************************
*​​Copyright​​ (C) ​​2020 ​​by ​​Arpit Savarkar
*​​Redistribution,​​ modification ​​or ​​use ​​of ​​this ​​software ​​in​​source​ ​or ​​binary
*​​forms​​ is​​ permitted​​ as​​ long​​ as​​ the​​ files​​ maintain​​ this​​ copyright.​​ Users​​ are
*​​permitted​​ to ​​modify ​​this ​​and ​​use ​​it ​​to ​​learn ​​about ​​the ​​field​​ of ​​embedded
*​​software. ​​Arpit Savarkar ​​and​ ​the ​​University ​​of ​​Colorado ​​are ​​not​ ​liable ​​for
*​​any ​​misuse ​​of ​​this ​​material.
*
******************************************************************************/ 
/**
 * @file bit_operations.c
 * @brief An abstraction for bit manipulation operations and 
 * hexdump from a specific location 
 * 
 * This file provides functions and abstractions for bit manipulation 
 * decimal to binary, decimal to hex, clearing, Setting and toggling 
 * a bit and printing a hex dump from a specific location
 * 
 * @author Arpit Savarkar
 * @date August 27 2020
 * @version 1.0

https://www.geeksforgeeks.org/program-to-reverse-a-string-using-pointers/


*/

#include "bit_operations.h"

#define MASK(x) (1UL << (x))
#define hex_asc_lo(x)	hex_asc[((x) & 0x0f)]
#define hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]

// Helper Functions to convert to Hexadecimal
char rem(int num) 
{ 
    if (num >= 0 && num <= 9) 
        return (char)(num + '0'); 
    else
        return (char)(num - 10 + 'A'); 
} 

// Helper Function to set nth bit of input 
int set_bit(uint32_t input, int bit) 
{ 
    return (input | (1 << (bit))); 
} 
  
// Helper Function to clear nth bit of input 
int clear_bit(uint32_t input, int bit) 
{ 
    return (input & (~(1 << (bit)))); 
} 
  
// Helper Function to toggle the nth bit of input 
int toggle_bit(uint32_t input, int bit) 
{ 
    return (input ^ (1 << (bit))); 
}

int uint_to_binstr(char *str, size_t size, uint32_t num, uint8_t nbits) {

    int base = 2, len = 0, i =0;
    str[0] = '0';
    str[1] = 'b';
    
    for (i =2; i < nbits+2; i++) {
        str[i] = '0';
    }
    str[i] = '\0';

    for (i =2; i < nbits+2; i++) {
        str[i] = '0';
    }
    str[i] = '\0';
    while (num>0) {
        str[--i] = rem(num % base);
        num /= base;
        len ++;
    }
    if (nbits ==0 ) {
        printf("Illegal bits");
        *str = NULL;
        return -1;
    } 
    if (len > nbits) {
        printf("num too large");
        *str = NULL;
        return -1;
    }
    len=0;
    for (i =0 ; str[i]!= '\0'; i++)
        len++;  

    return len;
}

int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits) {

    char *start = str;
    if (num>0) 
        return uint_to_binstr(str, size, num, nbits);

    int base = 2;
    int i =0,  c = 1;
    char *p = str;
    *(p++) = '0';
    *(p++) = 'b';
    char *shifted_p;
    shifted_p = p;

    for (int i =0; i < nbits; i++) 
        *(p++) = '0';
    *(p) = '\0';
    char *t = (--p);
    int temp, len=0;
    num*=-1;
    while(num>0) {
        *t = rem(num % base);
        t--;
        num /= base;
        len++;
    }

    if (nbits ==0 ) {
        printf("Illegal bits");
        *str = NULL;
        return -1;
    } 
    if (len > nbits) {
        printf("num too large");
        *str = NULL;
        return -1;
    }

    // 1's complement logic
    p = shifted_p;
    while(*p != '\0') {
        if(*p == '1')
            *(p++) = '0';

        else if(*p == '0')
            *(p++) = '1';
    }
    *(p--) = '\0';
    
    while( (nbits--) != 1 ) {
        if(*p == '1' && c == 1)
        {
            *(p--) = '0';
        }
        else if(*p == '0' && c == 1)
        {
            *(p--) = '1';
            c = 0;
        }
    }

    p = str;
    len=0;
    while (*(p++) != '\0')
        len++;

    return len;
}

int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits) {

    int base = 16, len = 0, i =0;
    int k = 0;
    // char *p = str;
    str[k++] = '0';
    str[k++] = 'x';

    for (i=0; i < (nbits+2)/4; i++) 
        str[k++] = '0';
    str[k] = '\0';
    char *t ;
    t = &str[--k];
    while(num>0) {
        *t = rem(num % base);
        t--;
        num /= base;
        len++;
    }
    if (nbits /4 != 0 ) {
        printf("Illegal bit size");
        *str = NULL;
        return -1;
    } 
    if (len > nbits) {
        printf("num too large");
        *str = NULL;
        return -1;
    }

    len = 0;
    for(i =0; str[i]!='\0'; i++) {
        len++;
    }

    return len;
} 

typedef enum {
CLEAR,
SET,
TOGGLE
} operation_t;
uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation) {

    if ( bit <0 || bit > 31)
        return -1;

    if (operation == CLEAR) {
        return clear_bit(input, bit);
    }
    else if (operation == SET) {
        return set_bit(input, bit);
    }
    else if (operation == TOGGLE) {
        return toggle_bit(input, bit);
    }
    else {
        return 0xFFFFFFFF;
    }

}

uint32_t grab_three_bits(uint32_t input, int start_bit) {

    uint32_t output;
    int num_elem = 3;
    int output = (((1 << num_elem) - 1) & (input >> (start_bit))); 
    if (output < 0)
        return 0xFFFFFFFF;
    else 
        return output;

}

char *hexdump(char *str, size_t size, const void *loc, size_t nbytes) {


    if (nbytes > size) {
        str = '\0';
        return str;
    }
        
    int i;
    unsigned char buff[17];
    const unsigned char * pc = (const unsigned char *)loc;
    int k = 0;

    // Length checks.

    if (nbytes == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    else if (nbytes < 0) {
        printf("  NEGATIVE LENGTH: %d\n", nbytes);
        return;
    }

    // Process every byte in the data.

    for (i = 0; i < nbytes; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Don't print ASCII buffer for the "zeroth" line.

            if (i != 0) {
                str[k++] = '\n';
            }

            // Output the offset.
            str[k++] = '0';
            str[k++] = 'x';
            if(i == 0)
                str[k++] = '0';
            
            str[k++] = i;
            for (int s =0; s<2; s++)
                str[k++] = ' ';
        }

        // Now the hex code for the specific character.
        str[k++] = pc[i];
        str[k++] = ' ';

        // And buffer a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) 
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.

    while ((i % 16) != 0) {
        str[k++] = 0x20;
        i++;
    }

}

int main(int argc, char** argv) {

    return 0;
}
