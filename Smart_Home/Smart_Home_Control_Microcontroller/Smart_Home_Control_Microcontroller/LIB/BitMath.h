/*
 * BitMath.h
 *
 *  Created on: Sep 10, 2023
 *      Author: ahmed
 */

#ifndef BITMATH_H_
#define BITMATH_H_

#define SET_BIT(REG,BIT)           (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT)         (REG&=~(1<<BIT))
#define TOGGLE_BIT(REG,BIT)        (REG^=(1<<BIT))
#define WRITE_BIT(REG,BIT,VALUE)   (REG&=(VALUE<<BIT))
#define READ_BIT(REG,BIT)          ((REG>>BIT)&1)


#endif /* BITMATH_H_ */
