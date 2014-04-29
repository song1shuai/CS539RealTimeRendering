//
//  BitArray.h
//  CS587_ShuaiSong
//
//  Created by shuai song on 3/17/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS587_ShuaiSong_BitArray_h
#define CS587_ShuaiSong_BitArray_h
#include <iostream>
class BitArray
{
protected :
    

    
public:
    int _length;
    unsigned long int * _bArray;
    BitArray();
    void Reserve(int newCapacity);          //Reserve the capacity of the array
    BitArray(int length);                   //init the bitarray length
    bool operator [](int index);
    void Set(int index ,bool value);        //Set the bit to 1
    void SetBit(int bit);
    void Reset();                           //Reset all the bit to 0
    ~BitArray();
};


#endif
