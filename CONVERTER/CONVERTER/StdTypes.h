
#ifndef STDTYPES_H_
#define STDTYPES_H_

#define  NULL     0
#define  NULLPTR  ((void*)0)
#define  MAX_U16  (u16)65535
#define  MIN_U16  (u16)0
#define  MAX_S16  (s16)32767
#define  MIN_S16  (s16)-32768

typedef unsigned char  u8;
typedef signed char    s8;
typedef char           c8;

typedef unsigned short u16;
typedef signed short   s16;

typedef unsigned long int   u32;
typedef signed long int     s32;

typedef unsigned long long   u64;
typedef signed long long     s64;

typedef float   F32;

typedef enum{
	TRUE,
	FALSE
    }bool_t;




#endif /* STDTYPES_H_ */