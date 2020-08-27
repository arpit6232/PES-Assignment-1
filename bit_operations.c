/* https://www.geeksforgeeks.org/program-to-reverse-a-string-using-pointers/

*/

#include "bit_operations.h"

#define MASK(x) (1UL << (x))

char rem(int num) 
{ 
    if (num >= 0 && num <= 9) 
        return (char)(num + '0'); 
    else
        return (char)(num - 10 + 'A'); 
} 

int uint_to_binstr(char *str, size_t size, uint32_t num, uint8_t nbits) {

    int base = 2, len = 0, i =0;
    char *p = str;
    *(p++) = '0';
    *(p++) = 'b';

    for (i =0; i < nbits; i++) 
        *(p++) = '0';
    *(p) = '\0';
    char *t = (--p);
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
    p = str;
    len=0;
    while (*(p++) != '\0')
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

    char *p = str;
    *(p++) = '0';
    *(p++) = 'b';

    for (i =0; i < nbits/4; i++) 
        *(p++) = '0';
    *(p) = '\0';
    char *t = (--p);
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
    p = str;
    len=0;
    while (*(p++) != '\0')
        len++;

    return len;

}

// Function to set nth bit of input 
int set_bit(uint32_t input, int bit) 
{ 
    return (input | (1 << (bit))); 
} 
  
// Function to clear nth bit of input 
int clear_bit(uint32_t input, int bit) 
{ 
    return (input & (~(1 << (bit)))); 
} 
  
// Function to toggle the nth bit of input 
int toggle_bit(uint32_t input, int bit) 
{ 
    return (input ^ (1 << (bit))); 
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

    char line[17];
    int i;
    char *counter = loc;
    char*p = str;
    int start = 0x0000;

    if(nbytes ==0 || nbytes <0)
        return -1;

    for (i=0; i<nbytes; i++) {
        if ((i % 16) == 0) {
            if (i != 0)
                *(p++) = '\n';

            *(p++) = start;
            start+=16;
            // printf ("  %04x ", i);
        }
        *(p++) = 0x00 + counter[i];
        // printf (" %02x", counter[i]);

    // And buffer a printable ASCII character for later.

    if ((counter[i] < 0x20) || (counter[i] > 0x7e)) 
        line[i % 16] = '.';
    else
        line[i % 16] = counter[i];
    line[(i % 16) + 1] = '\0';

    }

    while ((i % 16) != 0) {
        *(p++) = "   ";
        i++;
    }

    p = line;


}

int main(int argc, char** argv) {

    return 0;
}
