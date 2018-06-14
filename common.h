

#ifndef COMMON_H_
#define COMMON_H_

#define Set_Bit(X,Bit_Num) X|=1<<Bit_Num
#define Clear_Bit(X,Bit_Num) X&=~(1<<Bit_Num)
#define Toggle_Bit(X,Bit_Num) X^=1<<Bit_Num
#define Get_Bit(X,Bit_Num) (X&(1<<Bit_Num))>>Bit_Num
#define Clear_Nibble(X,Index)  X&=~(15<<Index*4)
#define Set_Nibble(X,Index)   X|=15<<(Index*4)





#endif /* COMMON_H_ */