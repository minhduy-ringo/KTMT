#include"Qint.h"

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
	return result;
}

//Hệ nhị phân(BIN) sang Thập lục phân (HEX)
char* BinToHex(QInt a)
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

list <vector<string>> Readfile(ifstream &file)
{
	string line, med;
	vector<string> token;
	list <vector<string>> list_command;

	while (!file.eof())
	{
		getline(file, line);
		stringstream tokenize(line);
		while (getline(tokenize, med, ' '))
		{
			token.push_back(med);
		}
		list_command.push_back(token);
		token.clear();
	}
	return list_command;
}

// Trim all not needed 0 bit
string TrimBit(QInt qi)
{
	return string();
}
