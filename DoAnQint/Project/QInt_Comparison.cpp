#include"Qint.h"

//operator ==
bool QInt::operator == (QInt const &a)
{
	int bitLength = 127;
	if (BitLength(*this) != BitLength(a))
		return false;
	int i = 127 - bitLength + 1;
	for (i; i <= 127; i++) {
		if (GetBit(*this, i) != GetBit(a, i))
			return false;
	}
	return true;
}

// Operator =
void QInt::operator = (QInt const& a)
{
	for (int i = 0; i < 4; i++)
		this->bigInt[i] = a.bigInt[i];
}
// Operator <=
bool QInt::operator <= (QInt const& b)
{
	//this -> a
	// a dương b âm
	if (GetSign(*this) == 0 && GetSign(b) == 1)
		return false;
	// a âm b dương
	if (GetSign(*this) == 1 && GetSign(b) == 0)
		return true;
	// a b cùng dấu
	// bit a dài hơn b
	if (BitLength(*this) > BitLength(b))
	{
		return false;
	}
	// bit b dài hơn a
	if (BitLength(*this) < BitLength(b))
	{
		return true;
	}
	// bit b b bằng nhbu
	int i = 127 - BitLength(*this) + 1;
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
	if (GetSign(*this) == 0 && GetSign(a) == 1)
		return true;
	// a âm b dương
	if (GetSign(*this) == 1 && GetSign(a) == 0)
		return false;
	// a b cùng dấu
	// bit a dài hơn b
	if (BitLength(*this) >  BitLength(a))
	{
		return true;
	}
	// bit b dài hơn a
	if (BitLength(*this) <  BitLength(a))
	{
		return false;
	}
	// bit a b bằng nhau
	int i = 127 - BitLength(*this) + 1;
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
//operator >
bool QInt::operator > (QInt const& b)
{
	//this -> a
	// a dương b âm
	if (GetSign(*this) == 0 && GetSign(b) == 1)
		return true;
	// a âm b dương
	if (GetSign(*this) == 1 && GetSign(b) == 0)
		return false;
	// a b cùng dấu
	// bit a dài hơn b
	if (BitLength(*this) > BitLength(b))
	{
		return true;
	}
	// bit b dài hơn a
	if (BitLength(*this) < BitLength(b))
	{
		return false;
	}
	// bit a b bằng nhau
	int i = 127 - BitLength(*this) + 1;
	for (i; i <= 127; i++)
	{
		bool bita = GetBit(*this, i);
		bool bitb = GetBit(b, i);

		if (bita && bitb)
			return false;
		if (bita)
		{
			if (!bitb)
				return true;
		}
		if (!bita)
		{
			if (bitb)
				return false;
		}
	}
}
//operator <
bool QInt::operator < (QInt const& b)
{
	//this -> a
	// a dương b âm
	if (GetSign(*this) == 0 && GetSign(b) == 1)
		return false;
	// a âm b dương
	if (GetSign(*this) == 1 && GetSign(b) == 0)
		return true;
	// a b cùng dấu
	// bit a dài hơn b
	if (BitLength(*this) > BitLength(b))
	{
		return false;
	}
	// bit b dài hơn a
	if (BitLength(*this) < BitLength(b))
	{
		return true;
	}
	// bit a b bằng nhau
	int i = 127 - BitLength(*this) + 1;
	for (i; i <= 127; i++)
	{
		bool bita = GetBit(*this, i);
		bool bitb = GetBit(b, i);

		if (bita && bitb)
			return false;
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