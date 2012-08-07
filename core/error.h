/*
	M-Kernel - embedded RTOS
	Copyright (c) 2011-2012, Alexey Kramarenko
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
		list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
		this list of conditions and the following disclaimer in the documentation
		and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef ERROR_H
#define ERROR_H

/*
	error.h - error handling
*/

#include "kernel_config.h"
#include "dev.h"

#define ERROR_GROUP_SIZE				0x100

typedef enum {
	ERROR_GROUP_GENERAL = 0,
	ERROR_GROUP_MEMORY,
	ERROR_GROUP_DEVICE,
	ERROR_GROUP_THREAD,
	ERROR_GROUP_SYNC
} ERROR_GROUP;

typedef enum {
	ERROR_GENERAL = ERROR_GROUP_GENERAL * ERROR_GROUP_SIZE,
	ERROR_GENERAL_WRONG_CONTEXT,
	ERROR_GENERAL_UNDEFINED_INSTRUCTION,
	ERROR_GENERAL_INVALID_SYS_CALL,
	ERROR_GENERAL_OBJECT_NOT_FOUND,
	ERROR_GENERAL_INVALID_MAGIC,
	ERROR_GENERAL_VECTOR_TABLE_READ_FAULT,
	ERROR_GENERAL_HARD_FAULT,
	ERROR_GENERAL_STACKING_FAILED,
	ERROR_GENERAL_UNSTACKING_FAILED,
	ERROR_GENERAL_DATA_BUS_ERROR,
	ERROR_GENERAL_INSTRUCTION_BUS_ERROR,
	ERROR_GENERAL_DIVISION_BY_ZERO,
	ERROR_GENERAL_UNALIGNED_ACCESS,
	ERROR_GENERAL_NO_COPROCESSOR,
	ERROR_GENERAL_INVALID_STATE,

	ERROR_MEMORY = ERROR_GROUP_MEMORY * ERROR_GROUP_SIZE,
	ERROR_MEM_POOL_INVALID_PTR,
	ERROR_MEM_POOL_RANGE_CHECK_FAILED,
	ERROR_MEM_OUT_OF_SYSTEM_MEMORY,
	ERROR_MEM_OUT_OF_STACK_MEMORY,
	ERROR_MEM_OUT_OF_HEAP,
	ERROR_MEM_DATA_ACCESS_VIOLATION,
	ERROR_MEM_INSTRUCTION_ACCESS_VIOLATION,

	ERROR_DEVICE = ERROR_GROUP_DEVICE * ERROR_GROUP_SIZE,
	ERROR_DEVICE_INDEX_OUT_OF_RANGE,
	ERROR_DEVICE_NOT_PRESENT,
	ERROR_DEVICE_FAILED_TO_START,
	ERROR_DEVICE_NOT_ACTIVE,

	ERROR_THREAD = ERROR_GROUP_THREAD * ERROR_GROUP_SIZE,
	ERROR_THREAD_OUT_OF_CONTEXT,
	ERROR_THREAD_INVALID_CALL_IN_IDLE_THREAD,

	ERROR_SYNC = ERROR_GROUP_SYNC * ERROR_GROUP_SIZE,
	ERROR_SYNC_WRONG_UNLOCKER,
	ERROR_SYNC_ALREADY_OWNED,
	ERROR_SYNC_ALREADY_UNLOCKED
} ERROR_CODE;

//unrecovered fatal error. System will reboot
void fatal_error(ERROR_CODE ec, const char *name);
//same with memory address
void fatal_error_address(ERROR_CODE ec, unsigned int address);
//dump memory over serial
void dump(unsigned int addr, unsigned int size);

//error. kills current thread
void error(ERROR_CODE ec, const char *name);
//same with current thread name
void error_thread(ERROR_CODE ec);
//same with memory address
void error_address(ERROR_CODE ec, unsigned int address);
//same with immediate value
void error_value(ERROR_CODE ec, unsigned int value);
//same for device
void error_dev(ERROR_CODE ec, DEVICE_CLASS dev, int idx);

#endif // ERROR_H