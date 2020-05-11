#include"Qint.h"

//NOT
QInt QInt::operator ~()
{
	QInt kq;
	for (int i = 127; i >= this->bitLength; i--)
	{
		if (GetBit(*this, i))
			SetBit(kq, i, 0);
		else
			SetBit(kq, i, 1);
	}
	return kq;
}

//operator AND
QInt QInt::operator &(QInt const& qi)
{
	QInt result;

	bool arrA[128], arrB[128];
	int index = 127;
	while (index >= 0)
	{
		arrA[index] = GetBit(*this, index);
		arrB[index] = GetBit(qi, index);
		if (arrA[index] == 1) {
			if (arrB[index] == 1) arrA[index] = 1;
			else arrA[index] = 0;
		}
		index--;
	}
	index = 127;
	while (index >= 0) {
		SetBit(result, index, arrA[index]);
		index--;
	}
	return result;
}