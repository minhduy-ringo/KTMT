#include"Qint.h"

// Bù 2
QInt QInt::TwoComponent(string a)
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
	QInt result, Q, M;
	M = *this;
	bool C;
	int shift = 0;

	// Overflow
	int n = 2 * BitLength(a);
	if (n > 128)
	{
		throw "Overflow";
	}
	
	if (GetBit(*this, 0) && GetBit(a, 0)) // If QInt *this and QInt a are both negative
	{
		QInt one, nca;
		nca = a;
		ScanQInt(one, "1", "10");
		
		M = ~*this;
		M = M + one;
		Q = ~nca;
		Q = Q + one;

		result = Multiply(M, Q);
	}
	else if (GetBit(*this, 0) ^ GetBit(a, 0)) // If one of the two is negative
	{
		QInt one, nca;
		ScanQInt(one, "1", "10");
		if (GetBit(*this, 0))
		{
			M = ~*this;
			M = M + one;
			Q = a;
		}
		else
		{
			nca = a;
			Q = ~nca;
			Q = Q + one;
			M = *this;
		}
		result = Multiply(M, Q);
		result = ~result;
		result = result + one;
	}
	else if (GetBit(*this, 0) | GetBit(a, 0)) // If both are positive
	{
		result = Multiply(M, Q);
	}
	return result;
}

//
QInt Multiply(QInt M, QInt Q)
{
	QInt A, result;
	int k = BitLength(Q);
	int qbit = k;
	bool lastABit = 0;

	while(k > 0)
	{
		if (GetBit(Q, 127)) // If last bit of Q is 1 -> A + M
		{
			A = A + M;
		}
		lastABit = GetBit(A, 127);
		A >> 1;
		Q >> 1;
		SetBit(Q, 128 - qbit, lastABit);
		k--;
	}

	result = Q;
	// Combine A and Q bit string
	k = 128 - qbit - 1;
	for (int i = 127; i >= 128 - qbit; i--)
	{
		SetBit(result, k, GetBit(A, i));
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
