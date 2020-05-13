#include"Qint.h"

// Rotate Left
string QInt::rol(int n)
{
	string s = QIntToString(*this);
	string temp;
	temp = s;
	int len = temp.size();
	char t = temp[0];
	for (int i = 0; i < len - 1; i++)
	{
		temp[i] = temp[i + 1];
	}
	temp[len - 1] = t;

	while (temp[0] == '0')
		temp.erase(0, 1);

	return temp;
}

// Rotate Right
string QInt::ror(int n) 
{
	string s = QIntToString(*this);
	string temp;
	temp = s;
	int len = temp.size();
	char t = temp[len - 1];
	for (int i = len - 1; i > 0; i--)
	{
		temp[i] = temp[i - 1];
	}
	temp[0] = t;

	while (temp[0] == '0')
		temp.erase(0, 1);

	return temp;
}

// Operator Shift right
void QInt::operator>> (int n)
{
	QInt temp;
	temp = *this;

	// Tạo lại QInt
	for (int i = 0; i < N; i++)
	{
		this->bigInt[i] = 0;
	}

	// Xác định vị trí bit sẽ dịch
	int shiftPos = 127 -  BitLength(temp) + n + 1;
	if (shiftPos > 127)
	{
		return;
	}
	else
	{
		int i = 127 - BitLength(temp) + 1;

		for (shiftPos; shiftPos <= 127; shiftPos++)
		{
			bool bit = GetBit(temp, i);
			SetBit(*this, shiftPos, GetBit(temp, i));
			i++;
		}
	}
}

// Operator Shift left
void QInt::operator<< (int n)
{
	QInt temp;
	temp = *this;

	// Xác định vị trí bit sẽ dịch
	int shiftPos = 127 - n;
	if (shiftPos < 0)
	{
		return;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			this->bigInt[i] = 0;
		}

		int i = 127;

		for (shiftPos; shiftPos > 0; shiftPos--)
		{
			SetBit(*this, shiftPos, GetBit(temp, i));
			i--;
		}
	}
}