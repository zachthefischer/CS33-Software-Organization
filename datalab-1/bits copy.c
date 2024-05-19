//1
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
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
  int bias  = (fivex >> 31) & 7;
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

! - logical neg, !000 = 0
                 !001 = 1   //any value with a 1 bit
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
