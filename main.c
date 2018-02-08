#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sAsciiToBin(char *ascii, char *binString, long binLength)
{
    char *ptr,
         *temp;

    unsigned int ii,
	         bitset,
                 bitmask;

    /* Set the 8th bit of the bitmask. */
    bitmask = 1 << 7;

    /* Cycle through every character in the ASCII string. */
    while (*ascii)
    {
        /* The bitset is the 8 bits associated with this character. */
        bitset = (unsigned int) *ascii;

        for (ii = 1; ii <= 8; ii++)
        {
            /* Get the value of this bit. */
            char *bit = ((bitset & bitmask) == 0) ? "0" : "1";

            /* Add this bit to the result. */
            strcat(binString, bit);

            /* Shift the bitset one left. */
            bitset <<= 1;
        }

        /* Move on to the next character in the ASCII string. */
        ascii++;
    }

    /* Allocate space for our temporary buffer. */
    temp = malloc(binLength);
    if (!temp)
        exit(1);;

    /* Make a temporary copy of the binary string. */
    strcpy(temp, binString);

    /* Zero pad the binary string. */
    sprintf(temp, "%0*s", binLength - 1, binString);

    /* Copy the binary string back in for the caller. */
    strcpy(binString, temp);

    free(temp);
}

static void sBinToAscii(char *bin, char *ascii)
{
    char bitset[8];

    unsigned int value,
	         valuePos,
	         bitsetPos;

    /* Cycle through every character in the binary string. */
    while (*bin)
    {
	/* Make a copy of the next 8 bits of the binary string to work with. */
	memcpy(bitset, bin, 8);

	/* Reset the value, which represents the ascii value. */
        value = 0;

	/* Cycle through each of the 8 bits in the bitset. */
        for (valuePos = 7, bitsetPos = 0; 
	     bitsetPos <= 7; 
	     valuePos--,   bitsetPos++)
        {
	    /* Set the appropriate bit within the value. */
	    if (bitset[bitsetPos] == '1') 
	    {
	        value |= 1 << valuePos;
            }
        }

	/* Make a copy of this value for the caller. */
	if (value > 0)
	    *ascii++ = (char) value;

	/* Move on to the next 8 bits in the binary string. */
	bin += 8;
    }

    *ascii = '\0';
    
    return;
}


int main(int argc, char *argv[])
{
    char ascii[6],
         bin[49];

    memset(ascii, 0, sizeof ascii);
    memset(bin,   0, sizeof bin);

    strcpy(ascii, "1ABC9");
    printf(" ASCII: %s\n", ascii);

    sAsciiToBin(ascii, bin, sizeof(bin));
    printf("Binary: %s\n", bin);
 
    memset(ascii, 0, sizeof ascii);
    sBinToAscii(bin, ascii);
    printf(" ASCII: %s\n", ascii);

    memset(bin,   0, sizeof bin);
    sAsciiToBin(ascii, bin, sizeof(bin));
    printf("Binary: %s\n", bin);

    exit(0);
}
