#include"Qint.h"

// RotateLeft
QInt QInt:: RotateLeft()
{
	QInt result;

	bool arr[128];
	int index = 127;
	while (index >= 0)
	{
		if(index == 127){
			arr[index] = GetBit(*this, 0);
		}
		else 
			arr[index] = GetBit(*this, index + 1);
		index--;
	}

	index = 127;
	while (index >= 0) {
		SetBit(result, index, arr[index]);
		index--;
	}
	return result;
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
	int shiftPos = 127 - this->bitLength + n + 1;
	if (shiftPos > 127)
	{
		return;
	}
	else
	{
		int i = 127 - this->bitLength + 1;

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