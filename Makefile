# -*- MakeFile -*-

bit_operations: bit_operations.h bit_operations.c
	gcc bit_operations.h bit_operations.c -o bit_operations