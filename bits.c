/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x){
        return !y;
    } else{
        if(!y){
            return 0;
        }
        else{
            return !(((x^y))>>31);
        }
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int shift;
    int r=0;

    shift = ((v>>16)>0)<<4;
    v = v>>shift;
    r = r|shift;

    shift = ((v>>8)>0)<<3;
    v = v>>shift;
    r = r|shift;

    shift = ((v>>4)>0)<<2;
    v = v>>shift;
    r = r|shift;

    shift = ((v>>2)>0)<<1;
    v = v>>shift;
    r = r|shift;

    shift = (v>>1)>0;
    r = r|shift;

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift = n<<3;//byte->位移量
    int mshift = m<<3;
    int nbyte =(x>>nshift)&0xFF;//取出两位
    int mbyte =(x>>mshift)&0xFF;
    int diff = nbyte ^ mbyte;//计算差异
    return x^((diff<<mshift)|(diff<<nshift));
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v>>1) & 0x55555555)|((v & 0x55555555)<<1);
    v = ((v>>2) & 0x33333333)|((v & 0x33333333)<<2);
    v = ((v>>4) & 0x0F0F0F0F)|((v & 0x0F0F0F0F)<<4);
    v = ((v>>8) & 0x00FF00FF)|((v & 0x00FF00FF)<<8);
    v = (v>>16)|(v<<16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x=x>>n;
    int mask = ~(((1<<31)>>n)<<1);
    return x&mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int v=~x;
    int isZero = !v;
    int shift;
    int r=0;

    shift = (!!(v>>16))<<4;
    v = v>>shift;
    r = r|shift;

    shift = (!!(v>>8))<<3;
    v = v>>shift;
    r = r|shift;

    shift = (!!(v>>4))<<2;
    v = v>>shift;
    r = r|shift;

    shift = (!!(v>>2))<<1;
    v = v>>shift;
    r = r|shift;

    shift = !!(v>>1);
    r = r|shift;

    int result = 32 + ~r;
    return (isZero << 5) | (result & (isZero + ~0));
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000;//取出最高位
    unsigned abs_x=x;
    unsigned exp, frac;
    int e=31;
    
    if(x==0) return 0;
    if(x<0) abs_x=-x;//取绝对值

    while(!(abs_x>>e)) e=e-1;//e=最高位1的位置
    exp=(e+127)<<23;//单精度指数偏移是127，e-1+127；右移23位至正确位置
    
    if(e<24){//所有有效位都能放进23位尾数
        frac=(abs_x<<(23-e)) & 0x7FFFFF;//直接左移对齐
    }else{//否则需要右移
        int shift = e-23;
        frac=(abs_x>>shift) & 0x7FFFFF;
        unsigned mask=(1<<shift)-1;
        unsigned remainder=abs_x&mask;//移出的位
        unsigned half=1<<(shift-1);

        if(remainder>half){//实现四舍六入
            frac=frac+1;
        }else{
            if(remainder==half){
                if(frac&1){//round to even
                    frac=frac+1;
                }
            }
        }
    }
    return sign+exp+frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign= uf&0x80000000;
    unsigned exp = (uf>>23)&0xFF;
    unsigned frac=uf&0x7FFFFF;

    if(exp==0xFF){
        return uf;
    }
    if(exp==0){
        if(frac==0)return uf;
        frac=frac<<1;
        if(frac&0x800000){
            exp=1;
            frac=frac&0x7FFFFF;
        }
        return sign|(exp<<23)|frac;
    }
    exp=exp+1;
    if(exp==0xFF){
        frac=0;
    }
    return sign|(exp<<23)|frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned s = uf2>>31;
    unsigned e=(uf2>>20) & 0x7FF;
    unsigned frac_high=uf2 & 0xFFFFF;
    unsigned frac_low=uf1;
    int exp;
    unsigned result;
    unsigned shift;
    unsigned frac_part;

    if(e>=0x7FF){
        return 0x80000000;
    }
    if(!e){
        return 0;
    }
    exp=e-1023;
    if(exp<0){
        return 0;
    }
    if(exp>=31){
        return 0x80000000;
    }
    shift=52-exp;
    if(shift>=32){
        frac_part = frac_high >>(shift-32);
    } else{
        frac_part = (frac_high<<(32-shift))|(frac_low>>shift);
    }
    result=(1<<exp)+frac_part;
    if(s){
        return -result;
    }else{
        return result;
    }
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127){
        return 0x7F800000;
    }else if(x>=-126){
        return (x+127)<<23;
    }else if(x>=-149){
        return 1<<(x+149);
    }else{
        return 0;
    }
}
