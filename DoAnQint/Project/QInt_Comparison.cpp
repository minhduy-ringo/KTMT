#include"Qint.h"

//operator ==
bool QInt::operator == (QInt const& a)
{
	int bitLength = 127;
	if (this->bitLength != a.bitLength)
		return false;
	int i = 127 - bitLength + 1;
	for (i; i <= 127; i++) {
		if (GetBit(*this, i) != GetBit(a, i))
			return false;
	}
	return true;
}


// Operator <=
bool QInt::operator <= (QInt const& b)
{
	//this -> a
	// a dương b âm
	if (this->sign == 0 && b.sign == 1)
		return false;
	// a âm b dương
	if (this->sign == 1 && b.sign == 0)
		return true;
	// a b cùng dấu
	// bit a dài hơn b
	if (this->bitLength > b.bitLength)
	{
		return false;
	}
	// bit b dài hơn a
	if (this->bitLength < b.bitLength)
	{
		return true;
	}
	// bit b b bằng nhbu
	int i = 127 - this->bitLength + 1;
	for (i; i <= 127; i++)
	{
		bool bita = GetBit(*this, i);
		bool bitb = GetBit(b, i);

		if (bita && bitb)
			continue;
		if (bita)
		{
			if (!bitb)
				return false;
		}
		if (!bita)
		{
			if (bitb)
				return true;
		}
	}
}

// Operator >=
bool QInt::operator >= (QInt const& a)
{
	// a dương b âm
	if (this->sign == 0 && a.sign == 1)
		return true;
	// a âm b dương
	if (this->sign == 1 && a.sign == 0)
		return false;
	// a b cùng dấu
	// bit a dài hơn b
	if (this->bitLength > a.bitLength)
	{
		return true;
	}
	// bit b dài hơn a
	if (this->bitLength < a.bitLength)
	{
		return false;
	}
	// bit a b bằng nhau
	int i = 127 - this->bitLength + 1;
	for (i; i <= 127; i++)
	{
		bool bit1 = GetBit(*this, i);
		bool bit2 = GetBit(a, i);

		if (bit1 && bit2)
			continue;
		if (bit1)
		{
			if (!bit2)
				return true;
		}
		if (!bit1)
		{
			if (bit2)
				return false;
		}
	}
}
