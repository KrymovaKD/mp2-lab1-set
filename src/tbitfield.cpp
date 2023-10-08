// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)//инициализация
{
	if (len <= 0) { throw "wrong length"; }
	else {
		MemLen = (len / 32) + 1;//количество интовских чисел(0,1,2) в массиве
		pMem = new TELEM[MemLen];//выделение памяти для массива беззнаковых интов заданной длины мемлен
		BitLen = len;//ограничитель в массиве битов 
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n//побитовая длинна n
{
	return (n/32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t = 1;//беззнаковая единица , биты которой мы будем двигать для работы с числами с массиве
	char shift = n % 32;//находим нужный нам сдвиг
	TELEM result = t << shift;//сдвигаем разряд и получаем битовую маску
	return result;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) {
		throw "wrong bit";
}
	TELEM mask = GetMemMask(n);
	int idx = GetMemIndex(n);//ячейка
	pMem[idx] = pMem[idx]|mask;//складывакем двоичные числа
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) {
		throw "wrong bit";
	}
	TELEM mask = GetMemMask(n);//получаем маску для бита
	int idx = GetMemIndex(n);//ячейка
	pMem[idx] = pMem[idx] & mask;//умножаем двоичные числа
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) {
		throw "wrong bit";
	}
	TELEM mask = GetMemMask(n);//создаем маску 00001000..
	int idx = GetMemIndex(n);//получаем номер ячейки
	TELEM res = mask & pMem[idx];//умножая, получаем бит
  return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf.MemLen != MemLen) {
		delete[]pMem;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;
	for (int i = 0; i < MemLen - 1; i++)//минус один потому что не учитываем последнюю,её отдельно ниже
	{
		if (pMem[i] != bf.pMem[i])
			return false;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)//в хвосте может быть что-угодно,поэтому проверяем побитово
	{
		if (GetBit(i) != bf.GetBit(i))//сравниваем побитово с помощью функции получения значение данного бита
			return false;
	}
  return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this==bf);//зыс приходит ссылкой,чтобы получить его нужно разоименовать 
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	return*this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return* this;
}

TBitField TBitField::operator~(void) // отрицание
{
	return*this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;

}
