#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "SUBLW.h"

unsigned char FSR[0x1000];

void sublw(Bytecode *code){
	FSR[STATUS] = 0;

	if(code->operand1 >= 0 && code->operand1 <= 0xFF && code->operand2 == -1 && code->operand3 == -1){
		if(code->operand1 > FSR[WREG]){
			FSR[WREG] = code->operand1 - FSR[WREG];
			FSR[STATUS] = FSR[STATUS] | 0x01;
			code->absoluteAddress++;
		}
		
		else if(FSR[WREG] > code->operand1){
			FSR[WREG] = code->operand1 - FSR[WREG];
			FSR[STATUS] = FSR[STATUS] | 0x10;
			code->absoluteAddress++;
		}
		
		else if(FSR[WREG] == code->operand1){
			FSR[WREG] = code->operand1 - FSR[WREG];
			FSR[STATUS] = 0x05;
			code->absoluteAddress++;
		}
		
		else 
			Throw(ERR_INVALID_OPERAND);
	}
	
	else 
		Throw(ERR_INVALID_OPERAND);
}

