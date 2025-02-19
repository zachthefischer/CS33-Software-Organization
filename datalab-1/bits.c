/* 
 * CS:APP Data Lab 
 * 
 * Zachary Fischer 306195453
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Our checker requires that you do NOT define a variable after 
     a statement that does not define a variable.

     For example, this is NOT allowed:

     int illegal_function_for_this_lab(int x, int y) {
      // this statement doesn't define a variable
      x = x + y + 1;
      
      // The checker for this lab does NOT allow the following statement,
      // because this variable definition comes after a statement 
      // that doesn't define a variable
      int z;

      return 0;
     }
     
  2. VERY IMPORTANT: Use the dlc (data lab checker) compiler (described in the handout)
     to check the legality of your solutions.
  3. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  4. Use the btest to check your functions for correctness.
  5. The maximum number of ops for each function is given in the
     header comment for each function. 

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest to verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */


//1
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
       // 0 - false
       // nonzero - true
       // max is 0x7FFFFFFF
       // 0111 1111 1111 1111 1111 ...
       // 1000 0000 0000 000

       int result = !!~x & !(~(x ^ (x + 1)));  
       return result;
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  int result = 0x55;      // 0000 .... 1010 1010
  result = result << 8;   // 1010 1010 0000 0000
  result = result | 0x55; // 1010 1010 1010 1010

  // repeat process, shift again and add to itself
  result = result | (result << 16); 
  return  result;
}



//3
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  // xOr x and y
  // if they are equal, 
  int result = !(x ^ y);
  
  return result;
}


//4
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  // Number and the amt of bytes we're checking
  // -4, 3 - 110
  //  5, 3 - 011 (max positive, 3)

  // Make the max 000011
  // 0000011 ex
  //       1 make 1
  //     100 shift left n
  // 1111011 flip bits
  // 0110000 shift left 32-n
  // 0000011 shift right n

  // check 5 - 0000101
  //           0000011 max (rightmost 2)
  //           0000111 min (rightmost 3)
  //   0000101
  // & 

  int result = !(x >> (n + (~1+1))) | !(~x >> (n + (~1+1)));
  
  return result;
}



//5
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // if x != 0, return y
  // if x = 0, return z

  int condition  = ((!!x) << 31) >> 31; 
  // = 111... or 000... depending on the condition
  // and with x and y, one of them will be reduced to 0
  // return condition;
  return ((condition & y) | (~condition & z));
}




//6
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  // x - y > 0  --> return 1
  // x - y <= 0 --> return 0
  int diff = y + (~x + 1);
  int diffSign = diff >> 31; // 00..0 or 11..1
  int xSign = x >> 31;       // 00..0 or 11..1
  int ySign = y >> 31;       // 00..0 or 11..1  

  // edge case1: y < 0, x > 0 but d > 0 in this case return 1
  int over1 = (ySign & ~xSign & ~diffSign) & 1;
  
  // edge case2: y > 0, x < 0 but d < 0 in this case return 0
  int over2 = (~ySign & xSign & diffSign) & 1;

  int Tmin = 1 << 31;
  int isTmin = !(x ^ Tmin);
  //printf("IsTmin: %d\n", Tmin);

  // if sign of diff is 1, then x > y
  return (!over2) & (!isTmin) & (over1 | (diffSign & 1));
}




//7
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  int fivex = (x + x + x + x + x);
  int bias = (fivex >> 31) & 7;
  int result = (fivex + bias) >> 3;

  return result;
}



//8
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */


// negate --> make negative
// complement --> flip bits

int logicalNeg(int x) {
  // if the value is zero, return 1
  // if the value is nonzero, return 0
  // 000000100 --> 0
  // 000000000 --> 1
  // negated 0 = 0
  // negated x = -x

  int current = x >> 31;
  int negated = ((~x+1) >> 31);
  int mask = current | negated;
 
  return ((mask+1) & 1);
}





//9
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
  int signMask = x >> 31;
  int signBit = signMask << 31;

  int negX = ~x + 1;
  
  int absX = (x & ~signMask) + (negX & signMask);
    
  int result = absX + signBit;

  return result;
}





//10
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int xSign = x >> 31;

  int xIsZero = !(x ^ 0);
  int xIsOne = !(x + ~0); // if x is zero 
    
  // power of 2 if all numbers besides the leftmost bit are 0
  // EXCEPT FOR ONE OF THEM

  int oneBit = !((x + ~0) & x); 
  return (!xSign & !xIsZero & oneBit) | xIsOne;
}





