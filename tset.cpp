// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) :MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
    TBitField tmp(BitField);
    return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem > MaxPower)
        throw out_of_range("bit pos is out of range");
    else if (Elem < 0)
        throw ("Negative length");
    if (BitField.GetBit(Elem)==1)
        return 1;
    else return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem > MaxPower)
        throw out_of_range("bit pos is out of range");
    else if (Elem < 0)
        throw ("Negative length");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem > MaxPower)
        throw out_of_range("bit pos is out of range");
    else if (Elem < 0)
        throw ("Negative length");
        BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{

    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return (*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if ((BitField == s.BitField) && (MaxPower == s.MaxPower)) return 1;
    else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if ((BitField != s.BitField) || (MaxPower != s.MaxPower)) return 1;
    else return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    
    TSet tmp(max((*this).MaxPower, s.MaxPower));
        tmp.BitField = (*this).BitField | s.BitField;

    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem >= MaxPower)
        throw out_of_range("bit pos is out of range");
    else if (Elem < 0)
        throw ("Negative length");
    TSet tmp(BitField);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem >= MaxPower)
        throw out_of_range("bit pos is out of range");
    else if (Elem < 0)
        throw ("Negative length");
    TSet tmp(BitField);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{

    TSet tmp(max((*this).MaxPower, s.MaxPower));
    tmp.BitField = (*this).BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(MaxPower);
    tmp.BitField = ~((*this).BitField);
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.MaxPower;
    TELEM tel;
    TBitField tf(s.MaxPower);
    for (int i = 0; i < tf.GetLength(); i++)
    {
        istr >> tel;
        if (tel == 1)
            tf.SetBit(i);
    }
    s.BitField = tf;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    int i, n;
    char ch = '{';
    n = s.GetMaxPower();
    for (i = 0; i < n; i++)
    {
        if (s.IsMember(i))
        {
            ostr << ch << ' ' << i;
            ch = ',';
        }
    }
    ostr << '}';
    return ostr;
}
