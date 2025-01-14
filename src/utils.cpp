/**********************************************************
 * MIDI 2.0 Library 
 * Author: Andrew Mee
 * 
 * MIT License
 * Copyright 2021 Andrew Mee
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * ********************************************************/

#include <math.h>

#include "utils.h"


uint32_t scaleUp(uint32_t srcVal, uint8_t srcBits, uint8_t dstBits){
   // simple bit shift
    if(srcVal==0){
        return 0L;
    }
    if(srcBits==1){
        return pow(2,dstBits) - 1L;
    }

    // simple bit shift
	uint8_t scaleBits = (dstBits - srcBits);
	uint32_t bitShiftedValue = (srcVal + 0L) << scaleBits;
	uint32_t srcCenter = pow(2,(srcBits-1)) + 0L;
	if (srcVal <= srcCenter ) {
		return bitShiftedValue;
	}
	// expanded bit repeat scheme
	uint8_t repeatBits = srcBits - 1;
	unsigned int repeatMask = pow(2,repeatBits) - 1;
	uint32_t repeatValue = srcVal & repeatMask;
	if (scaleBits > repeatBits) {
		repeatValue <<= scaleBits - repeatBits;
	} else {
		repeatValue >>= repeatBits - scaleBits;
	}
	while (repeatValue != 0) {
		bitShiftedValue |= repeatValue;
		repeatValue >>= repeatBits;
	}
	return bitShiftedValue;
  
}

uint32_t scaleDown(uint32_t srcVal, uint8_t srcBits, uint8_t dstBits) {
	// simple bit shift
	uint8_t scaleBits = (srcBits - dstBits);
	return srcVal >> scaleBits;
}

long getNumberFromBytes(uint8_t* message, uint8_t offset, uint8_t amount){
     
    long num = 0;short upperOffset = offset+amount;
	for(short offsetC = offset; offsetC<upperOffset;offsetC++){
		num += (long)(message[offsetC] << (7* (offsetC-offset)));
	}
	return num;
}

void setBytesFromNumbers(uint8_t* message, long number, uint8_t start, uint8_t amount){
	for(int amountC = amount; amountC>0;amountC--){
		message[start++] = number & 127;
		number = number >> 7;
	}
};

void printUMP(uint32_t UMP){
/*	Serial.print(" ");
	Serial.print((UMP >> 24) & 255, BIN);
	Serial.print(" ");
	Serial.print((UMP >> 16) & 255, BIN);
	Serial.print(" ");
	Serial.print((UMP >> 8) & 255, BIN);
	Serial.print(" ");
	Serial.print(UMP & 255, BIN); */
}
