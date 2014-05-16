//
//  BitArray.cpp
//  CS587_ShuaiSong
//
//  Created by shuai song on 3/17/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "BitArray.h"
BitArray::BitArray()
{
    _length = 0 ;
    _bArray = NULL;
    Reserve( 32 );
}
BitArray::BitArray(int length)
{
    _bArray = NULL;
    _length =length;
}

BitArray::~BitArray()
{
    if (_bArray!=NULL)
    {
        delete _bArray;
    }
}

void BitArray::Reserve(int newCapacity)
{
    if (newCapacity == 0||newCapacity <= _length)
    {
        return ;
    }
    
    newCapacity= (newCapacity -1)/32+1;
    unsigned long int * newArray = new unsigned long int [newCapacity];
    
    if (newArray==NULL)
    {
        return;
    }
    
    for (int i = 0;i < _length;i ++)
    {
        newArray [i]=_bArray[i];
    }
    
    _length = newCapacity;
    
    if (_bArray != NULL)
    {
        
        delete _bArray;
    }
    _bArray = newArray;
    Reset();
}
bool BitArray::operator [](int index)
{
    
    if (index > _length *32 + _length%32)
    {
        Reserve(index);
    }
    int bin =  index / 32;
    int bit =  index % 32;
    return (_bArray[bin] & (1<<bit)) >> bit;
}
void BitArray::Set(int index ,bool value)
{
    int bin =  index / 32;
    int bit =  index % 32;

    if ((index -1)/32+1 > _length )
    {
        Reserve(index);
    }
    
    if (value ==true)
    {
        _bArray[bin] = (_bArray[bin]|(1 << bit));
    }
    else
    {
        _bArray[bin] = (_bArray[bin] & (~(1<<bit)));
    }
    
}
void BitArray::Reset()
{
    for (int i = 0; i < _length; i++)
    {
        _bArray[i]=0;
        
    }
}
void BitArray::SetBit(int bit)
{
    _bArray[0]|= bit;
}




