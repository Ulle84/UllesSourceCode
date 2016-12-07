#ifndef BITARRAY_H
#define BITARRAY_H

#include <iostream>
#include <string>

// Note: curently the indexes have 8 bit
//       if you have systems with more than 128 bit, this needs to be changed!

// http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c
// maybe use boos::dynamic_bitset - http://www.boost.org/doc/libs/1_36_0/libs/dynamic_bitset/dynamic_bitset.html

typedef unsigned char uint8;
typedef unsigned short uint16;

template<typename T>
class BitArray
{
public:
  BitArray(uint8 nUsedBits = 0);

  void setBit(uint8 index);
  void clearBit(uint8 index);
  bool isBitSet(uint8 index);
  void toggleBit(uint8 index);

  void setAllBits();
  void clearAllBits();

  void printAllBits();

private:
  T m_bitArray = 0;
  uint8 m_nUsedBits; // 0 means all available
};

template<typename T>
BitArray<T>::BitArray(uint8 nUsedBits) :
  m_nUsedBits(nUsedBits)
{

}

template<typename T>
void BitArray<T>::setBit(uint8 index)
{
  m_bitArray |= 1 << index;
}

template<typename T>
bool BitArray<T>::isBitSet(uint8 index)
{
  return (m_bitArray >> index) & 1;
}

template<typename T>
void BitArray<T>::toggleBit(uint8 index)
{
  m_bitArray ^= 1 << index;
}

template<typename T>
void BitArray<T>::clearBit(uint8 index)
{
  m_bitArray &= ~(1 << index);
}

template<typename T>
void BitArray<T>::setAllBits()
{
  if (m_nUsedBits == 0)
  {
    m_bitArray = -1;
  }
  else
  {
    for (uint8 i = 0; i < m_nUsedBits; ++i)
    {
      setBit(i);
    }
  }
}

template<typename T>
void BitArray<T>::clearAllBits()
{
  m_bitArray = 0;
}

template<typename T>
void BitArray<T>::printAllBits()
{
  std::string bits;
  for (uint8 i = m_nUsedBits - 1; i >= 0; --i)
  {
    if (isBitSet(i))
    {
      bits.push_back('X');
    }
    else
    {
      bits.push_back('.');
    }
  }
}

#endif // BITARRAY_H
