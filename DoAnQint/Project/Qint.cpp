#include"Qint.h"

// hàm khởi tạo kiểu dữ liệu Qint
//void InitQInt(QInt &a)
//{
//	for (int i = 0; i < N; i++)
//	{
//		a.bigInt[i] = 0;
//	}
//}

// đưa từng bit vào bộ nhớ
void SetBit(QInt &a, int i, int bit)
{
	int index = i / 32;
	int soBitDich = i % 32;
	a.bigInt[index] = a.bigInt[index] | (bit << (31 - soBitDich));
}

// Lấy bit tại ví trí thứ i
bool GetBit(QInt a, int i)
{
	int arr = i / 32;
	int index = i % 32;
	return (a.bigInt[arr] >> (31 - i)) & 1;
}

// Đọc chuỗi số lớn vào QInt
void ScanQInt(QInt &a, string s)
{
	int i = 127;

	if (s[0] == '-')
	{
		a.sign = 1;
		s[0] = '0';
	}
	else
		a.sign = 0;

	while (s != "0")
	{
		short lastNumber = s[s.length() - 1] - '0'; // Lấy chữ số cuối
		if (lastNumber < 0 || lastNumber > 9)
		{
			cout << "String number not valid" << endl;
			break;
		}
		SetBit(a, i, lastNumber % 2);
		s = Div2(s);	
		i--;
	}

	a.bitLength = 127 - i;
}

// hàm chia cho 2 lấy phần nguyên
string Div2(string s)
{
	string result;
	int temp = 0;
	if (s.length() == 1 && (s[0] == '1'||s[0]=='0'))
	{
		result.push_back('0');
	}
	
	for (int i = 0; i < s.length(); i++)
	{
		temp = temp * 10 + (int)s[i] - '0';
		if (i > 0 || (i == 0 && temp >= 2))
		{
			result.push_back(temp / 2 + '0');
		}
		temp = temp %2;
	}
	return result;
}

// hàm hiện thị dạng nhị phân của Qint
void PrintQInt(QInt a)
{
	for (int i = 0; i <= 127; i++)
	{
		cout << GetBit(a, i);
	}
	cout << endl;
}

// Hàm chuyển QInt thập phân (DEC) sang thập lục phân (HEX)
char* DecToHex(QInt a)
{
	short wordLength = 32;
	char* result = new char[wordLength + 1];
	memset(result, '0', wordLength);
	result[wordLength] = '\0';
	int bitLength = 127;
	short l = wordLength - 1;
	while (bitLength > 0)
	{
		short fourBit = 0;
		for (int i = 0; i < 4; i++)
		{
			bool bit = GetBit(a, bitLength - i);
			fourBit += (short)bit * pow(2,i);
		}
		switch (fourBit)
		{
		case 10:
			result[l] = 'A';
			break;
		case 11:
			result[l] = 'B';
			break;
		case 12:
			result[l] = 'C';
			break;
		case 13:
			result[l] = 'D';
			break;
		case 14:
			result[l] = 'E';
			break;
		case 15:
			result[l] = 'F';
			break;
		default:
			result[l] = fourBit + '0';
			break;
		}
		l--;
		bitLength -= 4;
	}
	for (int i = 0; i < 32; i++)
	{
		cout << result[i];
	}
	return result;
}

//Hệ nhị phân(BIN) sang Thập lục phân (HEX)
char* BINTOHEX(QInt a)
{
	
	char* result = new char[33]{ '0' };
	int bitLength = 127;
	short n = 32;
	while (bitLength > 0)
	{
		short fourBit = 0;
		for (int i = 0; i < 4; i++)
		{
			bool bit = GetBit(a, bitLength - i);
			fourBit += (short)bit * pow(2, i);
		}
		switch (fourBit)
		{
		case 10:
			result[n] = 'A';
			break;
		case 11:
			result[n] = 'B';
			break;
		case 12:
			result[n] = 'C';
			break;
		case 13:
			result[n] = 'D';
			break;
		case 14:
			result[n] = 'E';
			break;
		case 15:
			result[n] = 'F';
			break;
		default:
			result[n] = fourBit + '0';
			break;
		}
		n--;
		bitLength -= 4;
	}
	for (int i = 0; i < 32; i++)
	{
		cout << result[i];
	}
	return result;
}

// Operator =
void QInt::operator= (QInt const& a)
{
	for (int i = 0; i < 4; i++)
		this->bigInt[i] = a.bigInt[i];
	this->sign = a.sign;
	this->bitLength = a.bitLength;
}

//operator ==
bool QInt::operator == (QInt const& a)
{
	int bitLength = 127;
	if (this->bitLength != a.bitLength)
		return false;
	int i = 127 - bitLength + 1;
	for ( i; i <= 127 ; i++) {
		if (GetBit(*this, i) != GetBit(a, i))
			return false;
	}
	return true;
}

// operator +
QInt QInt::operator+(QInt const& a) 
{
	int bitLength = 127;
	int bitNho = 0;
	QInt kq;
	for (int i = bitLength; i >= 0; i--) 
	{
		
		int temp1 = GetBit(*this, i);
		int temp2 = GetBit(a, i);
		if ((temp1 == temp2) && (temp1 = temp2 = 0))
		{
			if (bitNho == 1)
			{
				SetBit(kq, i, 1);
				bitNho = 0;
			}
			SetBit(kq, i, temp1);
			bitNho = 0;
		}
		else if ((temp1 == temp2) && (temp1 = temp2 = 1))
		{
			if (bitNho == 1)
			{
				SetBit(kq, i, 0);
				bitNho = 1;
			}
			SetBit(kq, i, 1);
			bitNho = 1;
		}
		else {
			SetBit(kq, i, 1);
			bitNho = 0;
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
		if (memoAdd1 == 0)
			if (arrB[index] == 1) {
				memoAdd1 = 1;
				arrB[index] = 0;
			}
			else {
				arrB[index] = 1;
				memoAdd1 = 0;
			}

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
	short k = a.bitLength;
	QInt result, Q;
	Q = a;
	bool qBit = 0;

	while (k > 0)
	{
		bool lastBit = GetBit(Q, 127);
		if (lastBit == 1 && qBit == 0)
		{
			result = result - *this;
			PrintQInt(result);
		}
		else if (lastBit == 0 && qBit == 1)
		{
			result = result + *this;
			PrintQInt(result);
		}
		qBit = GetBit(Q, 127);
		Q >> 1;
		result >> 1;
		k--;
	}
	PrintQInt(result);
	PrintQInt(Q);
	return result;
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

//NOT
QInt NOTQInt(QInt a) {
	QInt kq;
	for (int i = 127; i >= a.bitLength; i--)
	{
		if (GetBit(a, i))
			SetBit(kq, i, 0);
		else
			SetBit(kq, i, 1);
	}

	return kq;
}

//operator AND
QInt operator& (QInt const& qiA, QInt const& qiB)
{
	QInt result;

	bool arrA[128], arrB[128];
	int index = 127;
	while (index >= 0)
	{
		arrA[index] = GetBit(qiA, index);
		arrB[index] = GetBit(qiB, index);
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

// RotateLeft
QInt RotateLeft (QInt const& qi)
{
	QInt result;

	bool arr[128];
	int index = 127;
	while (index > 0)
	{
		arr[index - 1] = GetBit(qi, index);
		index--;
	}
	bool leftmost;
	leftmost = (qi.bigInt[0] >> 0) & 1;
	arr[127] = leftmost;

	index = 127;
	while (index >= 0) {
		SetBit(result, index, arr[index]);
		index--;
	}
	return result;
}

// operator Shift right
//QInt QInt::operator >> (int n)
//{
//	QInt result;
//	InitQInt(result);
//
//	bool arr[128];
//	int index = 127;
//	while (index >= 0)
//	{
//		if (index >= n) 
//			arr[index] = 0;
//		else
//			arr[index] = GetBit(*this, index - n);
//		index--;
//	}
//
//	index = 127;
//	while (index >= 0) {
//		SetBit(result, index, arr[index]);
//		index--;
//	}
//	return result;
//}

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

// Trim all not needed 0 bit
string TrimBit(QInt qi)
{
	return string();
}