/*
 * StdTypes.h
 *
 *  Created on: Sep 10, 2023
 *      Author: ahmed
 */

#ifndef STDTYPES_H_
#define STDTYPES_H_



typedef unsigned char u8;
typedef signed char s8;
typedef char c8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long int u32;
typedef signed long int s32;

typedef unsigned long long u64;
typedef signed long long s64;

typedef float F32;

typedef enum {
	FALSE, 
	TRUE
} bool_t;

typedef enum {
	OK,
	NOT_OK,
	SUCCESS,
	FAILURE
} Error_t;

typedef enum {
	OUT_OF_RANGE_VALUE,
	NULL_POINTER,
	NO_ERROR
} Error_Status_t;

#define  NULL  (void*)0

#endif /* STDTYPES_H_ */
