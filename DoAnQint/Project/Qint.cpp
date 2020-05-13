#include"Qint.h"

// đưa từng bit vào bộ nhớ
void SetBit(QInt &a, int i, bool bit)
{
	int index = i / 32;
	int soBitDich = i % 32;
	a.bigInt[index] = a.bigInt[index] | (bit << (31 - soBitDich));
}

bool GetSign(QInt a)
{
	return GetBit(a, 0);
}

int BitLength(QInt a)
{
	int count = 128;
	for (int i = 0; i <= 127; i++)
	{
		if (GetBit(a, i))
			break;
		count--;
	}
	return count;
}

// Lấy bit tại ví trí thứ i
bool GetBit(QInt a, int i)
{
	int arr = i / 32;
	int index = i % 32;
	return (a.bigInt[arr] >> (31 - i)) & 1;
}

// Đọc chuỗi số lớn vào QInt
void ScanQInt(QInt &a, string s, string base)
{
	if (base == "10")
	{
		int i = 127;

		if (s[0] == '-')
		{
			s[0] = '0';
			a = a.SoDoi(s);
		}
		else
		{
			a = DecToBin(s);
		}
	}
	if (base == "2")
	{
		int bit = 127;
		for (int i = s.length() - 1; i >= 0; i--)
		{
			if (s[i] == '1')
				SetBit(a, bit, true);
			else
				SetBit(a, bit, false);
			bit--;
		}
	}
	if (base == "16")
	{
		s = HexToBin(s);
		ScanQInt(a, s, "2");
	}
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

// 
string QIntToString(QInt a)
{
	string str;
	for (int i = 0; i <= 127; i++)
	{
		if (GetBit(a, i))
		{
			str.push_back('1');
		}
		else
			str.push_back('0');
	}
	return str;
}

// Hàm chuyển QInt thập phân (DEC) sang thập lục phân (HEX)
char* DecToHex(string s)
{
	QInt a = DecToBin(s);
	char* result = new char[33]{ '0' };
	result = BinToHex(a);
	return result;
}

//Hệ nhị phân(BIN) sang Thập lục phân (HEX)
char* BinToHex(QInt a)
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
			fourBit += (short)bit * pow(2, i);
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

//dectobin
QInt DecToBin(string s)
{
	QInt a;
	int i = 127;
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
	
	return a;
}

//bintodec
string BinToDec(QInt a)
{
	string s = QIntToString(a);
	string result = "0";

	for (int i = s.length() - 1; i >= 0; i--) 
	{
		if (s[i] == '1') 
		{
			int j = 127 - i;
			string a = Multi('2', j);
			result = AddStr(result, a);
		}
	}
	return result;
}

string HexToBin(string s) 
{ 
	string result;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '0')
			result += "0000";
		if (s[i] == '1')
			result += "0001";
		if (s[i] == '2')
			result += "0010";
		if (s[i] == '3')
			result += "0011";
		if (s[i] == '4')
			result += "0100";
		if (s[i] == '5')
			result += "0101";
		if (s[i] == '6')
			result += "0110";
		if (s[i] == '7')
			result += "0111";
		if (s[i] == '8')
			result += "1000";
		if (s[i] == '9')
			result += "1001";
		if (s[i] == 'A' || s[i] == 'a')
			result += "1010";
		if (s[i] == 'B' || s[i] == 'b')
			result += "1011";
		if (s[i] == 'C' || s[i] == 'c')
			result += "1100";
		if (s[i] == 'D' || s[i] == 'd')
			result += "1101";
		if (s[i] == 'E' || s[i] == 'e')
			result += "1110";
		if (s[i] == 'F' || s[i] == 'f')
			result += "1111";
	}
	return result;
}

// Operator =
void QInt::operator = (QInt const& a)
{
	for (int i = 0; i < 4; i++)
		this->bigInt[i] = a.bigInt[i];
}

string Calculate(QInt q1, QInt q2, string op, string base)
{
	bool rs = 0;
	QInt qr;
	string result;
	// Operation
	if (op == "+")
	{
		qr = q1 + q2;
	}
	else if (op == "-")
	{
		qr = q1 - q2;
	}
	else if (op == "*")
	{
		// qr = q1 * q2;
	}
	else if (op == "/")
	{
		// qr = q1 / q2;
	}
	// Comparison
	else if (op == "<")
	{
		// rs = q1 < q2;
		return rs ? "True" : "False";
	}
	else if (op == ">")
	{
		// rs = q1 > q2;
		return rs ? "True" : "False";
	}
	else if (op == "<=")
	{
		rs = q1 <= q2;
		return rs ? "True" : "False";
	}
	else if (op == ">=")
	{
		rs = q1 >= q2;
		return rs ? "True" : "False";
	}
	else if (op == "==")
	{
		rs = q1 == q2;
		return rs ? "True" : "False";
	}
	// BitWise
	else if (op == "&")
	{
		qr = q1 & q2;
	}
	else if (op == "|")
	{
		qr = q1 | q2;
	}
	else if (op == "^")
	{
		qr = q1 ^ q2;
	}
	// BitShift
	else if (op == ">>")
	{
		int bitShift = stoi(BinToDec(q2));
		qr = q1;
		qr >> bitShift;
	}
	else if (op == "<<")
	{
		int bitShift = stoi(BinToDec(q2));
		qr = q1;
		qr << bitShift;
	}
	else if (op == "ror")
	{
		int bitShift = stoi(BinToDec(q2));
		string s = q1.ror(bitShift);
		ScanQInt(qr, s, "2");
	}
	else if (op == "rol")
	{
		int bitShift = stoi(BinToDec(q2));
		string s = q1.rol(bitShift);
		ScanQInt(qr, s, "2");
	}

	// Convert to input base before return
	if (base == "2")
	{
		return TrimBit(qr);
	}
	else if (base == "10")
	{
		return TrimBit(BinToDec(qr));
	}
	else if (base == "16")
	{
		return TrimBit(BinToHex(qr));
	}
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

void WriteFile(ofstream& file, vector<string> v_result)
{
	vector<string>::iterator it;
	for (it = v_result.begin(); it != v_result.end(); ++it) 
	{
		file << *it << endl;
	}
}

// Trim all not needed 0 bit
string TrimBit(string str)
{
	string trimedStr;
	
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '0')
			continue;
		else
		{
			for (int j = i; j < str.length(); j++)
			{
				trimedStr.push_back(str[j]);
			}
			break;
		}
	}
	return trimedStr;
}

string TrimBit(QInt q)
{
	string trimedStr;

	for (int i = 0; i <= 127; i++)
	{
		if (GetBit(q, i) == '0')
			continue;
		else
		{
			for (int j = i; j <= 127; j++)
			{
				trimedStr.push_back((char)GetBit(q,i));
			}
			break;
		}
	}
	return trimedStr;
}

string AddStr(string a, string b) 
{ 
	string result = "0";
	bool flag = false;
	int max;
	int x, y, temp;

	if (a.length() > b.length())
		max = a.length();
	else
		max = b.length();

	for (int i = 0; i < max; i++) 
	{
		if (i == result.length())
			result += "0";

		if (i > a.length() - 1)
			x = 0;
		else
			x = a[a.length() - 1 - i] - '0';

		if (i > b.length() - 1)
			y = 0;
		else
			y = b[b.length() - 1 - i] - '0';

		temp = x + y;

		if (flag == true) 
		{
			temp = temp + 1;
			flag = false;
		}

		if (temp > 9) 
		{
			result[i] = (temp - 10) + '0';

			if (i == result.length() - 1)
				result += "1";

			flag = true;
		}
		else
			result[i] = temp + '0';
	}

	reverse(result.begin(), result.end());
	return result;
}

string SubStr(string a, string b) { // tru 2 chuoi string
	if (a == b)
		return "0";

	int sign = 0;

	while (a.length() < b.length())
		a = "0" + a;

	if (a < b) {
		string temp = a;
		a = b;
		b = temp;
		sign = 1;
	}

	string result = "0";
	bool flag = false;
	int x, y, temp;

	for (int i = 0; i < a.length(); i++) {
		if (i == result.length())
			result += "0";

		if (i > a.length() - 1)
			x = 0;
		else
			x = a[a.length() - 1 - i] - '0';

		if (i > b.length() - 1)
			y = 0;
		else
			y = b[b.length() - 1 - i] - '0';

		if (flag == true) {
			y = y + 1;
			flag = false;
		}

		temp = x - y;

		if (temp < 0) {
			flag = true;
			result[i] = (temp + 10) + '0';
		}
		else
			result[i] = temp + '0';
	}

	reverse(result.begin(), result.end());
	while (result[0] == '0')
		result.erase(0, 1);

	if (sign == 1)
		result = "-" + result;

	return result;
}

string Multi(char base, int exp) // base ^ exp
{	
	string result = "1";

	for (int i = 1; i <= exp; i++)
		result = AddStr(result, result);

	return result;
}