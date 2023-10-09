// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
unsigned int bitsInElem = sizeof(TELEM) * 8;


TBitField::TBitField(int len)
{
    if (len < 0)
        throw("Negative length");
    else if (len == 0)
    {
        BitLen = len;
        pMem = nullptr;
        MemLen = 0;
    }
    else {
        BitLen = len;
        MemLen = len / bitsInElem + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
    }
   // memset(pMem, 0, MemLen * sizeof(TELEM));
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/bitsInElem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n & (bitsInElem));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen)
        throw out_of_range("bit pos is out of range");
    else if (n < 0)
        throw ("Negative length");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen)
        throw out_of_range("bit pos is out of range");
    else if (n < 0)
        throw ("Negative length");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen)
        throw out_of_range("bit pos is out of range");
    else if (n < 0)
        throw ("Negative length");
    return pMem[GetMemIndex(n)] &= GetMemMask(n);

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        if (pMem!=nullptr) delete[] pMem;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
        //TBitField tmp(bf);
        //swap(*this, tmp);
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
            return 0;
 return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return ~(*this==bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
        TBitField tmp(max((*this).BitLen, bf.BitLen));
        for (int i = 0; i < MemLen; i++)
            tmp.pMem[i] = bf.pMem[i] | (*this).pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField tmp(max((*this).BitLen, bf.BitLen));
    for (int i = 0; i < MemLen; i++)
        tmp.pMem[i] &= pMem[i];
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(BitLen);
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = ~pMem[i];
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    istr >> bf.BitLen;
    TELEM tel;
    TBitField tf(bf.BitLen);
    for (int i = 0; i < tf.BitLen; i++)
    {
        istr >> tel;
        if (tel == 1)
            tf.SetBit(i);
    }
    bf = tf;
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        if (bf.GetBit(i))
            ostr << '1';
        else
            ostr << '0';
    return ostr;
}
