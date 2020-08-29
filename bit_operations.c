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
 * 
 * 

  Sources of Reference :
  Links :https://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers 

  I would like to thank the SA's for the course Rakesh Kumar, Saket Penurkar for their 
  support. 

*/

#include "bit_operations.h"


// ************************ Helper Functions  ************************************

char convert(int num)  { 
    /*
    Conversion Table for reference
    Decimal:	0	1	2	3	4	5	6	7
    Hex	        0	1	2	3	4	5	6	7
    Decimal:	8	9	10	11	12	13	14	15
    Hex      	8	9	A	B	C	D	E	F
    */ 
    if (num >= 0 && num <= 9) 
        return (char)(num + '0'); 
    else
        return (char)(num - 10 + 'A'); 
} 

int set_bit(uint32_t input, int bit)  { 
    // Returns Input manipulated to set a bit
    //  "|" is Bitwise OR
    return (input | (1U << (bit))); 
} 
  

int clear_bit(uint32_t input, int bit)  {
    // Returns Input manipulated to clear a bit 
    //  "&" is Bitwise AND
    return (input & (~(1U << (bit)))); 
} 
  

int toggle_bit(uint32_t input, int bit)  { 
    // Returns Input manipulated to toggle a bit 
    // "^" is Bitwise AND
    return (input ^ (1U << (bit))); 
}

int check_legality(char *str, size_t size, uint32_t num, uint8_t nbits, 
                   int base) {

    // Function to prevent segmentation fault to acess 

    int len = 0;

    if( (nbits/8) > size )
        return -1;

    // Illegal nbits
    if (nbits == 0 ) {
        str[0] = '\0';
        return -1;
    }

    int temp = num;
    while (temp>0) { // Returns the modulo as binary for base 2
        temp /= base;
        len++;
    }

    if (len > nbits) {
        str[0] = '\0';
        return -1;
    }
}

void dec_to_bin(char *str, size_t size, uint32_t num, uint8_t nbits) {

    int base = 2, i =0, len = 0;

    // To specify the 0bxxxxxx for the binary 
    str[0] = '0';  
    str[1] = 'b';
    
    // Instantiating string with '0's upto nbytes
    for (i =2; i < nbits+2; i++) {
        str[i] = '0';
    }
    //Demarkating End of string
    str[i] = '\0';

    // Need to be stored backwards for correctness
    while (num>0) {
        str[--i] = convert(num % base); // Returns the modulo as binary for base 2
        num /= base;
        len++;
    }

    // To prevent Segmentation faults restricted to nbits 
    if (len > nbits) {
        str[0] = '\0';
    }

}


int uint_to_binstr(char *str, size_t size, uint32_t num, uint8_t nbits) {


    int len = 0;

    if(num<0)
        return -1;
    if (check_legality(str, size, num, nbits, 2) == -1)
        return -1;
    dec_to_bin(str, size, num, nbits);

    // To prevent Segmentation faults restricted to nbits 
    if (len > nbits) {
        str[0] = '\0';
        return -1;
    }
    len = 0;
    for (int i =0; str[i]!='\0'; i++)
        len++;

    return (len);
}


void test_uint_to_binstr() {
    size_t size = 1024;
    char str[size];
    int k =0;
    int ret,i;
        
    ret = uint_to_binstr(str, size, INT8_MIN, 8);
        if(ret == -1) 
            return 0;

    ret = uint_to_binstr(str, size, INT8_MAX, 8);
        if(ret != -1) 
            return 0;

    ret = uint_to_binstr(str, size, 0, 16);
        if(ret == -1) 
            return 0;

    ret = uint_to_binstr(str, size, UINT16_MAX+1, 8);
        if(ret != -1) 
            return 0;


    // Compiler interprets UINT32_MAX as -1 when assigned to uint32_t
    // which results in legality check to be as negative number 

    ret = uint_to_binstr(str, size, UINT32_MAX, 8);
        if(ret != 0) 
            return 0;

    ret = uint_to_binstr(str, size, UINT32_MAX, 16);
        if(ret != 0) 
            return 0;

    ret = uint_to_binstr(str, size, UINT32_MAX, 32);
        if(ret == 0) 
            return 0;

    return 1;

}
    


int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits) {

    // If Unsigned Integer uint_to_binstr() can be used
    if (num>0) 
        return uint_to_binstr(str, size, num, nbits);

    if (check_legality(str, size, num*-1, nbits, 2) == -1)
        return -1;

    num *= -1;
    int i =0,  c = 1;

    dec_to_bin(str, size, num, nbits);

    for(i =2; str[i]!='\0'; i++) {
        if(str[i] == '1')
            str[i] = '0';

        else if(str[i] == '0')
            str[i] = '1';
    }
    int k = i-1;
    for (i = k; i>=0; i--) {
        if(str[i] == '1' && c == 1) {
            str[i] = '0';
        }
        else if(str[i] == '0' && c == 1) {
            str[i] = '1';
            c = 0;
        }
    }

    int len = 0;
    for (int i =0; str[i]!='\0'; i++)
        len++;

    return (len);
}

void test_int_to_binstr() {
    size_t size = 1024;
    char str[size];
    uint8_t nbits = 16;
    int k =0;
    int ret,i;
        
    ret = int_to_binstr(str, size, INT8_MIN*2, 8);
        if(ret != -1) 
            return 0;
    
    ret = int_to_binstr(str, size, INT8_MIN, 8);
        if(ret == -1) 
            return 0;

    ret = int_to_binstr(str, size, INT8_MAX*2+2, 8);
        if(ret != -1) 
            return 0;

    ret = int_to_binstr(str, size, INT8_MAX, 8);
        if(ret == -1) 
            return 0;



    ret = int_to_binstr(str, size, INT16_MIN*2, 16);
        if(ret != -1) 
            return 0;
    
    ret = int_to_binstr(str, size, INT16_MIN, 16);
        if(ret == -1) 
            return 0;

    ret = int_to_binstr(str, size, INT16_MAX*2+2, 16);
        if(ret != -1) 
            return 0;

    ret = int_to_binstr(str, size, INT16_MAX, 16);
        if(ret == -1) 
            return 0;


    // Compiler interprets UINT32_MAX as -1 when assigned to uint32_t
    // which results in legality check to be as negative number 

    ret = int_to_binstr(str, size, INT32_MIN+1, 8);
        if(ret != -1) 
            return 0;

    ret = int_to_binstr(str, size, INT32_MIN+1, 16);
        if(ret != -1) 
            return 0;

    ret = int_to_binstr(str, size, INT32_MIN+1, 32);
        if(ret == 0) 
            return 0;

    ret = int_to_binstr(str, size, INT32_MAX-1, 8);
        if(ret != -1) 
            return 0;

    ret = int_to_binstr(str, size, INT32_MAX-1, 16);
        if(ret != -1) 
            return 0;

    ret = int_to_binstr(str, size, INT32_MAX-1, 32);
        if(ret == 0) 
            return 0;

    return 1;

}


int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits) {

    int base = 16, len = 0, i =0;
    int k = 2;

    if (check_legality(str, size, num, nbits, base) == -1)
        return -1;

    if (nbits/4 == 0 ) {
        str[0] = '\0';
        return -1;
    } 

    int temp = num;
    while (temp>0) { // Returns the modulo as binary for base 2
        temp /= base;
        len++;
    }

    if (len > nbits/4) {
        str[0] = '\0';
        return -1;
    }

    str[0] = '0';
    str[1] = 'x';

    for (i=0; i < nbits/4; i++) {
        str[k++] = '0';
        printf("i :%d\n", i);
    }
    str[k] = '\0';
    while(num>0) {
        char rem = convert(num % base);
        // printf("%c", rem);
        str[--k] = convert(num % base);
        num /= base;
        len++;
    }
    // str[++k] = '\0';

    len = 0;
    for(i =0; str[i]!='\0'; i++) {
        printf("%c", str[i]);
        len++;
    }

    return len;
}

void test_uint_to_hexstr() {
    size_t size = 1024;
    char str[size];
    int ret;
        
    ret = uint_to_hexstr(str, size, INT8_MIN, 8);
        if(ret == -1) 
            return 0;

    ret = uint_to_hexstr(str, size, INT8_MAX, 8);
        if(ret != -1) 
            return 0;

    ret = uint_to_hexstr(str, size, 0, 16);
        if(ret == -1) 
            return 0;

    ret = uint_to_hexstr(str, size, UINT16_MAX, 8);
        if(ret != -1) 
            return 0;


    // Compiler interprets UINT32_MAX as -1 when assigned to uint32_t
    // which results in legality check to be as negative number 

    ret = uint_to_hexstr(str, size, UINT32_MAX, 8);
        if(ret != -1) 
            return 0;

    ret = uint_to_hexstr(str, size, UINT32_MAX, 16);
        if(ret != -1) 
            return 0;

    ret = uint_to_hexstr(str, size, UINT32_MAX, 32);
        if(ret == -1) 
            return 0;

    return 1;

}


uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation) {

    if ( bit <0 || bit > 31)
        return 0xFFFFFFFF;

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

void test_twiggle_bit() {

    uint32_t input = UINT32_MAX-2;
    uint32_t output;
    if (twiggle_bit(input, 0, CLEAR) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, 0, SET) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, 0, TOGGLE) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, 32, CLEAR) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, 32, SET) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, 32, TOGGLE) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, -1, CLEAR) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, -1, SET) ==  0xFFFFFFFF )
        return 0;

    if (twiggle_bit(input, -1, TOGGLE) ==  0xFFFFFFFF )
        return 0;

    return 1;


}


uint32_t grab_three_bits(uint32_t input, int start_bit) {

    uint32_t output;
    int num_elem = 3;
    if (start_bit < 0 || start_bit >= 30)
        return 0xFFFFFFFF;
    output = (((1 << num_elem) - 1) & (input >> (start_bit))); 
    
        return output;
}

void test_grab_three_bits() {

    uint32_t input = UINT32_MAX-2;
    uint32_t output;
    if (grab_three_bits(input, 0) ==  0xFFFFFFFF )
        return 0;

    if (grab_three_bits(input, 30) !=  0xFFFFFFFF )
        return 0;

    if (grab_three_bits(input, -1)  !=  0xFFFFFFFF )
        return 0;

    return 1;
}


char *hexdump(char *str, size_t size, const void *loc, size_t nbytes) {

    if (nbytes > size) {
        str = '\0';
        return str;
    }

    // Length checks.

    if (nbytes <= 0) {
        printf("  ZERO LENGTH\n");
        str[0]='\0';
        return -1;
    }

    int i, j;
    char temp[3];  // Required to restrict compiler from using 2 bytes for special characters
    uint8_t rem = 0, num;
    unsigned char buff[17]; // String of 17 
    const unsigned char * pc = (const unsigned char *)loc;
    int k = 0;

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
            
            num = i;
            do 
            { 
                int rem = num % 16; 
                str[k++] = (rem > 9)? rem -10 + 'A' : rem + '0'; 
                num = num/16; 
            } while (num != 0);
            
            for (int s =0; s<2; s++)
                str[k++] = ' ';
        }

        // Now the hex code for the specific character.
        str[k++] = '0';
        str[k++] = '0';
        // k+=;
        num = pc[i];
        for(j=0; temp[j]!='\0'; j++)
            temp[j] = '0';
        j = 0;
        while (num != 0)
        {   
            rem = num % 16;
            temp[j++] =  (rem > 9)? (rem-10) + 'A' : rem + '0' ; 
            num = num/16; 
        }
        j = 0;
        // temp[j] = '\0';
        for(j = 0; j<=1; j++)
            str[--k] = temp[j];
        k+=2;
        str[k++] = ' ';
        // And buffer a printable ASCII character for later.

        if ((pc[i] > 0x20) || (pc[i] < 0x7e)) 
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\n';
    }

    // Pad out last line if not exactly 16 characters.

    while ((i % 16) != 0) {
        str[k++] = ' ';
        i++;
    }
    return str;
}


void test_hexdump() {

}



int main(int argc, char** argv) {

    return 0;
}
