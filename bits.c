/* 
 * INF559 Data Lab 
 * 
 * Timothée Darcet timothee.darcet
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Run ./driver.pl on the lab machines before submitting.  
 *      If you don't, you are on your own.
 */

#endif

/* bit manipulation */

/*
 * func1 - returns 1 if x == 0, and 0 otherwise 
 *   Examples: func1(5) = 0, func1(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int func1(int x) {
  return !x;
}

/* 
 * func2 - ~(x|y) using only ~ and & 
 *   Example: func2(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int func2(int x, int y) {
  // That is the definition of the ! operator
  return (~x)&(~y);
}

/* 
 * func3 - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: func3(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int func3(int n) {
  /* 1 << 31 >> n is exactly what we need, but since n can be 32
  and >> 32 is an undefined behavior, we divide n by two using >> 1*/
  int tmp = n >> 1;
  return (1 << 31) >> tmp << !(n & 1) >> tmp;
}

/* 
 * func4 - set all bits of result to least significant bit of x
 *   Example: func4(5) = 0xFFFFFFFF, func4(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int func4(int x) {
  // replace most significant bit with least significant, then use arithmetic shift
  return x << 31 >> 31;
}

/* 
 * func5 - return 1 if all even-numbered bits in word set to 1
 *   Examples func5(0xFFFFFFFE) = 0, func5(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int func5(int x) {
  // Generate a mask with shifts, then test using the mask wether all even-number bits of ~x are set to 0
  int tmp0 = (0x55 << 8) + 0x55;
  int tmp = (tmp0 << 16) + tmp0;
  return !((~x) & tmp);
}

/* 
 * func6 - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: func6(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int func6(int x, int n) {
  // create a mask with zeros on the n first bits, then do an arithmetic shift and remove unwanted ones with the mask
  int tmp2 = ~(1 << 31);
  int mask = (tmp2 >> n << 1) + 1;
  return (x >> n) & mask;
}

/*
 * func7 - returns 1 if x contains an odd number of 0's
 *   Examples: func7(5) = 0, func7(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int func7(int x) {
  // Using shifts, progressively xor all bits of x to test for the parity of the number of 0's
  int tmp0 = x ^ (x >> 16);
  int tmp1 = tmp0 ^ (tmp0 >> 8);
  int tmp2 = tmp1 ^ (tmp1 >> 4);
  int tmp3 = tmp2 ^ (tmp2 >> 2);
  int res = tmp3 ^ (tmp3 >> 1);
  return res & 1;
}


/* 2's complement */

/* 
 * func8 - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int func8(void) {
  // The min number has a one for sign then only zeros
  return 1 << 31;
}

/*
 * func9 - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int func9(int x) {
  // Test wether x + 1 is the same as ~x, plus rule out the possibility of -1
  int p = x + 1;
  return !((p ^ (~x)) | !p);
}

/* 
 * func10 - return -x 
 *   Example: func10(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int func10(int x) {
  // Definition of -x in two's complement representation
  return ~x + 1;
}

/* 
 * func11 - Determine if can compute x+y without overflow
 *   Example: func11(0x80000000,0x80000000) = 0,
 *            func11(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int func11(int x, int y) {
  // Check wether x and y have same sign bit and wether x + y has a different sign bit.
  // Do calculations in the sign bit then right shift by 31 bits to bring it back 
  return !((~(x ^ y) & ((x + y) ^ x)) >> 31);
}

/* 
 * func12 - return 1 if x > 0, return 0 otherwise 
 *   Example: func12(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int func12(int x) {
  // Use the fact that x >> 31 depends only of the sign bit and is 0 if x >= 0
  // Do an extra check for 0
  return !(!x + (x >> 31));
}

/*
 * func13 - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: func13(0x40000000,0x40000000) = 0x7fffffff
 *             func13(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int func13(int x, int y) {
  // Use same method as func11 to calculate overflow, then use it as a mask to choose between the (max/min)int or the sum
  int s = x + y;
  int overflow = (~(x ^ y) & ((x + y) ^ x)) >> 31;
  return (overflow & (~(x >> 31) ^ (1 << 31))) + (~overflow & s);
}


