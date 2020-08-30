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
  Online Links :https://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data
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

    // Functions to check segmentation fault and access to illegal number
    // of bits  

    int len = 0;

    // Segmentation Faults Check
    if( (nbits/8) > size )
        return -1;

    // Illegal nbits
    if (nbits <= 0 ) {
        str[0] = '\0';
        return -1;
    }

    int temp = num;
    while (temp>0) { // Returns the modulo as binary of specified base
        temp /= base;
        len++;
    }
    
    // Seg Fault Check
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

    // Illegal setup
    if(num<0)
        return -1;

    // Seg faults and minimum size setup check
    if (check_legality(str, size, num, nbits, 2) == -1)
        return -1;

    // Function to convert the input "num" to Binary 
    dec_to_bin(str, size, num, nbits);

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
    
    // Valid Number of Bit Check 
    ret = uint_to_binstr(str, size, UINT8_MAX, 8);
        if(ret != -1) 
            return 0;
    // InValid Number of Bits as input 
    ret = uint_to_binstr(str, size, UINT8_MAX+1, 8);
        if(ret != -1) 
            return 0;

    // Valid Number of Bit Check
    ret = uint_to_binstr(str, size, INT16_MAX, 16);
        if(ret == -1) 
            return 0;

    // InValid Number of Bits as input
    ret = uint_to_binstr(str, size, UINT16_MAX+1, 8);
        if(ret != -1) 
            return 0;


    // Compiler interprets UINT32_MAX as -1 when assigned to uint32_t
    // which results in legality check to be as negative number 

    // InValid Number of Bits as input
    ret = uint_to_binstr(str, size, UINT32_MAX, 8);
        if(ret != 0) 
            return 0;

    // InValid Number of Bits as input
    ret = uint_to_binstr(str, size, UINT32_MAX, 16);
        if(ret != 0) 
            return 0;

    // Valid Input Check
    ret = uint_to_binstr(str, size, UINT32_MAX, 32);
        if(ret == 0) 
            return 0;

    return 1;

}
    


int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits) {

    // If Unsigned Integer uint_to_binstr() can be used
    if (num>0) 
        return uint_to_binstr(str, size, num, nbits);

    // Function to Check Segmentation Faults and Illegal Bit Access
    if (check_legality(str, size, num*-1, nbits, 2) == -1)
        return -1;

    num *= -1;
    int i =0,  c = 1;

    // Decimal to Binary Conversion
    dec_to_bin(str, size, num, nbits);

    // 1's compliment logic 
    for(i =2; str[i]!='\0'; i++) {
        if(str[i] == '1')
            str[i] = '0';

        else if(str[i] == '0')
            str[i] = '1';
    }
    int k = i-1;

    // 2's compliment logic 
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
    
    // Invalid number of bits as input Test
    ret = int_to_binstr(str, size, INT8_MIN*2, 8);
        if(ret != -1) 
            return 0;
    
    // Valid Input Test 
    ret = int_to_binstr(str, size, INT8_MIN, 8);
        if(ret == -1) 
            return 0;

    // Invalid number of bits as input Test
    ret = int_to_binstr(str, size, INT8_MAX*2+2, 8);
        if(ret != -1) 
            return 0;

    // Valid Input Test
    ret = int_to_binstr(str, size, INT8_MAX, 8);
        if(ret == -1) 
            return 0;


    // Invalid number of bits as input Test
    ret = int_to_binstr(str, size, INT16_MIN*2, 16);
        if(ret != -1) 
            return 0;
    
    // Valid Input Test
    ret = int_to_binstr(str, size, INT16_MIN, 16);
        if(ret == -1) 
            return 0;

    // Invalid number of bits as input Test
    ret = int_to_binstr(str, size, INT16_MAX*2+2, 16);
        if(ret != -1) 
            return 0;

    // Valid Input Test
    ret = int_to_binstr(str, size, INT16_MAX, 16);
        if(ret == -1) 
            return 0;


    // Compiler interprets UINT32_MAX as -1 when assigned to uint32_t
    // which results in legality check to be as negative number 

    // Invalid number of bits as input Test
    ret = int_to_binstr(str, size, INT32_MIN+1, 8);
        if(ret != -1) 
            return 0;

    // Invalid number of bits as input Test
    ret = int_to_binstr(str, size, INT32_MIN+1, 16);
        if(ret != -1) 
            return 0;

    // Valid Input test 
    ret = int_to_binstr(str, size, INT32_MIN+1, 32);
        if(ret == 0) 
            return 0;

    // Invalid number of bits as input Test
    ret = int_to_binstr(str, size, INT32_MAX-1, 8);
        if(ret != -1) 
            return 0;

    // Invalid Number of bits as input test
    ret = int_to_binstr(str, size, INT32_MAX-1, 16);
        if(ret != -1) 
            return 0;

    // Valid input test 
    ret = int_to_binstr(str, size, INT32_MAX-1, 32);
        if(ret == 0) 
            return 0;

    return 1;

}


int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits) {

    int base = 16, len = 0, i =0;
    int k = 2;

    // Illegal Num Bit setup
    if (nbits <= 0 ) {
        str[0] = '\0';
        return -1;
    } 

    // Illegal Length of bit setup
    int temp = num;
    while (temp>0) { // Returns the modulo as binary for base 
        temp /= base;
        len++;
    }

    if (len > nbits/4) {
        str[0] = '\0';
        return -1;
    }

    str[0] = '0';
    str[1] = 'x';

    // Initalizing with '0's for required nbits in hex
    for (i=0; i < nbits/4; i++) {
        str[k++] = '0';
        printf("i :%d\n", i);
    }

    // Marking Enf of string    
    str[k] = '\0';

    // Conversion of Decimal to Hex 
    while(num>0) {
        str[--k] = convert(num % base);
        num /= base;
        len++;
    }

    // Length Calculation
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

    // Invalid Check input 
    ret = uint_to_hexstr(str, size, INT8_MIN, 8);
        if(ret == -1) 
            return 0;

    // Valid Check Input
    ret = uint_to_hexstr(str, size, INT8_MAX, 8);
        if(ret != -1) 
            return 0;

    // Invalid Check input
    ret = uint_to_hexstr(str, size, INT16_MIN, 16);
        if(ret == -1) 
            return 0;

    // Valid Check Input
    ret = uint_to_hexstr(str, size, UINT16_MAX, 8);
        if(ret != -1) 
            return 0;


    // Compiler interprets UINT32_MAX as -1 when assigned to uint32_t
    // which results in legality check to be as negative number 

    // Invalid Check input
    ret = uint_to_hexstr(str, size, UINT32_MAX, 8);
        if(ret != -1) 
            return 0;

    // Invalid Check input
    ret = uint_to_hexstr(str, size, UINT32_MAX, 16);
        if(ret != -1) 
            return 0;

    // Valid Check Output
    ret = uint_to_hexstr(str, size, UINT32_MAX, 32);
        if(ret == -1) 
            return 0;

    return 1;

}


uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation) {

    // Invalid bit check
    if ( bit <0 || bit > 31)
        return 0xFFFFFFFF;

    // Function call to clear specific bit
    if (operation == CLEAR) {
        return clear_bit(input, bit);
    }
    // Function call to set specific bit
    else if (operation == SET) {
        return set_bit(input, bit);
    }
    // Function call to toggle specific bit
    else if (operation == TOGGLE) {
        return toggle_bit(input, bit);
    }
    else {
    // Invalid Operation
        return 0xFFFFFFFF;
    }

}

void test_twiggle_bit() {

    uint32_t input = UINT32_MAX-2;
    uint32_t output;

    // Validity Check to clear bit 0 
    if (twiggle_bit(input, 0, CLEAR) ==  0xFFFFFFFF )
        return 0;

    // Validity Check to set bit 0 
    if (twiggle_bit(input, 0, SET) ==  0xFFFFFFFF )
        return 0;

    // Validity Check to toggle bit 0 
    if (twiggle_bit(input, 0, TOGGLE) ==  0xFFFFFFFF )
        return 0;

    // bit size restricted 0 - 31
    if (twiggle_bit(input, 32, CLEAR) !=  0xFFFFFFFF )
        return 0;

    // bit size restricted 0 - 31
    if (twiggle_bit(input, 32, SET) !=  0xFFFFFFFF )
        return 0;

    // bit size restricted 0 - 31
    if (twiggle_bit(input, 32, TOGGLE) !=  0xFFFFFFFF )
        return 0;

    // Invalid Bit Test
    if (twiggle_bit(input, -1, CLEAR) !=  0xFFFFFFFF )
        return 0;

    // Invalid Bit Test
    if (twiggle_bit(input, -1, SET) !=  0xFFFFFFFF )
        return 0;

    // Invalid Bit Test
    if (twiggle_bit(input, -1, TOGGLE) !=  0xFFFFFFFF )
        return 0;

    return 1;


}


uint32_t grab_three_bits(uint32_t input, int start_bit) {

    uint32_t output;
    int num_elem = 3;
    if (start_bit < 0 || start_bit >= 30)
        return 0xFFFFFFFF;
    // Logic to set the 3 bits from start_bit left to right direction
    output = (((1 << num_elem) - 1) & (input >> (start_bit))); 
    
        return output;
}

void test_grab_three_bits() {

    uint32_t input = UINT32_MAX-2;
    uint32_t output;
    // Valid Bit Test
    if (grab_three_bits(input, 0) ==  0xFFFFFFFF )
        return 0;

    // Invalid Bit Test
    if (grab_three_bits(input, 30) !=  0xFFFFFFFF )
        return 0;

    // Illegal Bit Test
    if (grab_three_bits(input, -1)  !=  0xFFFFFFFF )
        return 0;

    return 1;
}


char *hexdump(char *str, size_t size, const void *loc, size_t nbytes) {
    
    // Segmentation Fault Check
    if (nbytes > size) {
        str = '\0';
        return str;
    }

    // Length checks.

    if (nbytes <= 0) {
        str[0]='\0';
        return str;
    }

    int i, j;
    char temp[3];  // Required to restrict compiler from using 2 bytes for special characters
    uint8_t rem = 0, num, rem = 0;
    unsigned char buff[17]; // String of 17 
    const unsigned char * pc = (const unsigned char *)loc;
    int k = 0;

    for (i = 0; i < nbytes; i++) {
        // Newline after 16 bytes check with necessary space/offset.

        if ((i % 16) == 0) {
            
            // Preventing newline before "zeroth" line buffer.
            if (i != 0) {
                str[k++] = '\n';
            }

            // Output the offset.
            str[k++] = '0';
            str[k++] = 'x';

            // 0x0_"0"_ requires an extra character zero 
            if(i == 0)
                str[k++] = '0';
            
            // Initial Delta from location Decimal to Hex Manipulation
            num = i;
            do 
            { 
                rem = num % 16; 
                str[k++] = (rem > 9)? rem -10 + 'A' : rem + '0'; 
                num = num/16; 
            } while (num != 0);
            
            // 2 Spaces between Address and Buffer Values
            for (int s =0; s<2; s++)
                str[k++] = ' ';
        }

        // Now the hex code for the specific character.
        str[k++] = '0';
        str[k++] = '0';

        // Hexadecimal equivalent of buffer
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

        // Manipulation Reversing the hex string to get the right order
        j = 0;
        for(j = 0; j<=1; j++)
            str[--k] = temp[j];
        k+=2;

        // Space after the hexdump of memory after every address read 
        str[k++] = ' ';

        if ((pc[i] > 0x20) || (pc[i] < 0x7e)) 
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\n';
    }

    // Padding out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        str[k++] = ' ';
        i++;
    }
    return str;
}


void test_hexdump() {

    const char *buf= "To achieve great things, two things are needed:\n a plan, and not quite enough time.";
    size_t size = 1024;
    char str[size];

    // Valid Input Test
    hexdump(str, size, buf, strlen(buf)+1);
    if (str[0] == '\0')
        return 0;
    
    // Invalid Input Test
    size = 0;
    hexdump(str, size, buf, strlen(buf)+1);
    if (str[0] != '\0')
        return 0;
    
    return 1;

}


int main(int argc, char** argv) {

    void test_uint_to_binstr();
    void test_int_to_binstr();
    void test_uint_to_hexstr();
    void test_twiggle_bit();
    void test_grab_three_bits();
    void test_hexdump();

    return 0;
}
