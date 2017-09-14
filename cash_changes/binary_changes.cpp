/*
 需求：
   小Q十分富有 拥有非常多的硬币，小Q拥有的硬币是有规律的， 对于所有的非负整数k, 小Q恰好有2个面值为2^k的硬币，
   所以小Q拥有的硬币就是: 1,1, 2,2, 4,4, 8,8, 16,16, ..., 那么小Q需要付N元来买件喜欢的东西，小Q总共可以有多少种付钱方式。
   从他拥有的硬币中拼凑出N元。

 解答：
   对于任意的非负整数都可以转化为其二进制的多项式表示，如果限定多项式系数也是二进制(系数只能为，0，1)的话，那么这个多项式表示是唯一的。
   按题目要求，现在多项式系数可以为(0, 1, 2). 多项是中的任意非零项，可以用其2个后续邻居项相加表示（2^k+1 = 2 * 2^k）

   将N转化为二进制后，其可以被'0'分割为形如这样的group，1000 | 1110 | 100 | 1
   因为， 2^k > 2×(2^k-2 +... 2^0), 所以被'0'分割的group，低位的group无论如何变化，其都不会产生二次进位，
   一次进位又会导致不相等，这样group间可以独立组合。问题题变成一个乘法组合问题.

   对于 111000 这样的数字，显而易见，这样的数可以分为两种拼凑方案：
   1. 拼凑中出现且仅出现一个最低位1的硬币，那么方案有且仅有一种
   2. 拼凑中出现0个或2个最低位1的硬币. 这两种也构成一个独立拼凑方案. 想象成一个填字模型，首先填入0个或2个最低位1，那么最低位1必变为0，
      这个0又将10序列分为全1或全0group，那么剩下的填字分成两步，
      第一步，用低位0拼凑出这个隔断0原来的1，也即1000的拼凑总数，等于bit-0的数目；
      第二步，拼凑出比隔断位高的全1，也即110的拼凑总数，等于bit-1的数目；
*/

#include <stdlib.h>
#include <stdint.h>

uint64_t num_changes(uint64_t n) {
    if ( n < 1 )
        return 0;

    unsigned bitmap[64][2] = {0};

    uint64_t pre_bit=0, cur_bit;
    unsigned idx = 0;

    while ( n ) {
        cur_bit = n & 0x01;
        if ( pre_bit == 1 && cur_bit == 0 ) {
            idx++;
        }
        bitmap[idx][cur_bit]++;

        pre_bit = cur_bit;
        n = n >> 1;
    }
    unsigned num_group = idx+1;

    uint64_t num_result = 1;
    for ( unsigned i=0; i<=idx; ++i ) {
        num_result *= (1 + bitmap[i][0] * bitmap[i][1]);
    }

    return num_result;
}

int main(int argc, char* argv[])
{
    for ( uint64_t n = 0; n<=32; ++n ) {
        printf("num changes of %llu: %llu\n", n, num_changes(n));
    }
    return 0;
}
