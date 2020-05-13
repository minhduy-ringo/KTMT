#include"Qint.h"

// Tìm số đối
QInt QInt::SoDoi(string a)
{
	QInt temp = DecToBin(a);
	QInt bu1 = ~temp;
	QInt mot = DecToBin("1");
	QInt kq = bu1 + mot;
	return kq;
}
// operator +
QInt QInt::operator+(QInt const& a)
{
	int bitLength = 127;
	bool bitNho = 0;
	QInt kq;
	for (int i = bitLength; i >= 0; i--)
	{

		bool temp1 = GetBit(*this, i);
		bool temp2 = GetBit(a, i);
		
		if ((temp1 == temp2) && (temp1 == 0))
		{
			if (bitNho == 1)
			{
				SetBit(kq, i, 1);
				bitNho = 0;
			}
			else {
				SetBit(kq, i, temp1);
				bitNho = 0;
			}
		}
		else if ((temp1 == temp2) && (temp1 == 1))
		{
			if (bitNho == 1)
			{
				SetBit(kq, i, 1);
				bitNho = 1;
			}
			else {
				SetBit(kq, i, 0);
				bitNho = 1;
			}
		}
		else {
			if (bitNho == 1)
			{
				SetBit(kq, i, 0);
				bitNho = 1;
			}
			else {
				SetBit(kq, i, 1);
				bitNho = 0;
			}
		}
	}
	return kq;
}

//operator -
QInt QInt::operator- (QInt const& a)
{
	QInt result;

	bool arrA[128], arrB[128];
	int index = 127;
	while (index >= 0)
	{
		arrA[index] = GetBit(*this, index);

		arrB[index] = GetBit(a, index);
		if (arrB[index] == 0) arrB[index] = 1;
		else arrB[index] = 0;
		index--;
	}

	cout << endl;
	index = 127;
	bool memoAdd1 = 0;
	bool memoAdd = 0;
	while (index >= 0)
	{
		if (index == 127){
			if (arrB[index] == 1) {
				memoAdd1 = 1;
				arrB[index] = 0;
			}
			else
			{
				arrB[index] = 1;
				break;
			}
		}
		else 
		{
			if (memoAdd1 == 1)
			{
				if (arrB[index] == 1) {
					arrB[index] = 0;
				}
				else
				{
					arrB[index] = 1;
					memoAdd1 = 0;
					break;
				}
			}
		}
		index--;
	}

	index = 127;
	while (index >= 0)
	{
		if (memoAdd == 0) {
			if (arrA[index] == 0 && arrB[index] == 1) {
				arrA[index] = 1;
			}
			else if (arrA[index] == 1 && arrB[index] == 1) {
				arrA[index] = 0;
				memoAdd = 1;
			}
		}
		else {
			if (arrA[index] == 1 && arrB[index] == 0)
				arrA[index] = 0;
			else if (arrA[index] == 0 && arrB[index] == 0) {
				arrA[index] = 1;
				memoAdd = 0;
			}
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

// Operator *
QInt QInt::operator* (QInt const& a)
{
	// *this = M
	short k =  BitLength(a);
	QInt result, Q;
	Q = a;
	bool qBit = 0;

	while (k > 0)
	{
		bool lastBit = GetBit(Q, 127);
		if (lastBit == 1 && qBit == 0)
		{
			result = result - *this;
		}
		else if (lastBit == 0 && qBit == 1)
		{
			result = result + *this;
		}
		qBit = GetBit(Q, 127);
		Q >> 1;
		result >> 1;
		k--;
	}
	return result;
}
void ShiftLeft(QInt& a, QInt& q) {
	a << 1;
	SetBit(a, 127, GetBit(q, 0));
	cout << "a sau khi dich bit la: ";

	q << 1;
	SetBit(q, 127, 0);
	cout << "q sau khi dich la: ";
}

//operator /
QInt QInt::operator/ (QInt const&b)
{
	QInt m = *this;
	cout << "m = ";
	QInt a;
	QInt q = b;
	int n, k;
	cout << "b = ";
	if (GetSign(q))
	{
		//khởi tạo a = 1, q<0
		if (BitLength(*this) > BitLength(q))
		{
			n = BitLength(*this);
			for (int j = 127; j >= 0; j--)
			{
				SetBit(a, j, 1);

			}
			k = n;
		}
		else {
			n = BitLength(q);
			for (int j = 127; j >= 0; j--)
			{
				SetBit(a, j, 1);
			}
			k = n;
		}
	}
	else 
	{
		if (BitLength(*this) > BitLength(q))
		{
			n = BitLength(*this);
			for (int j = 127; j >= 0; j--)
			{
				SetBit(a, j, 0);
			}
			k = n;
		}
		else {
			n = BitLength(q);
			for (int j = 127; j >= 0; j--)
			{
				SetBit(a, j, 0);
			}
			k = n;
		}
	}
	cout << "a = ";

	cout << "q = ";
	while (k > 0) {
		
		cout << " lan thu " << k << endl;
		ShiftLeft(a, q);
		a = a - m;
		cout << "a-m = ";
		//cout << BinToDec(a) << endl;
		if (a < DecToBin("0"))
		{
			SetBit(q, 0, 0);
			a = a + m;
		}
		else {
			SetBit(q, 0, 1);
		}
		k--;
	}
	cout << "thuong la: ";
	cout << "so du: ";

	return m;
}
