#include"Qfloat.h"


// hàm khởi tạo  Qloat
void intItQfloat(QFloat &a)
{
	for (int i = 0; i < N; i++)
	{
		// khởi tạo  bằng không
		a.bigFloat[i] = 0;
	}
}
// hàm  đưa bit vào vùng nhớ
void setBit(QFloat &a, int i, int bit)
{
	
		int index = i / 32;
		int soBitDich = i % 32;
		a.bigFloat[index] = a.bigFloat[index] | (bit << (31 - soBitDich));
}

// hàm  nhập Qloat
void scanQFloat(QFloat &a, string s)
{
	intItQfloat(a);
	int check = 0;
	string bin = convertDecToBinary(s, check);
	cout << "bin:" << bin << endl;
	string IEE745 = convertIntoStandardIEEE754(bin, check);
	//cout << IEE745 << endl;
	string specialNumber[] = { "denormalized" ,"infinity" ,"NotaNumber" };
	for (int i = 0;i < 3; i++)
	{
		if (specialNumber[i] == IEE745)
		{
			cout << IEE745 << endl;
			return;
		}
	}

	int i = 127;
	int k = IEE745.length() - 1;
	while (k >= 0)
	{
		int  bit = int(IEE745[k] - '0');
		if (bit == 1)
		{
			setBit(a, i, bit);
		}
		i--;
		k--;
	}

}

// hàm  chia một số cho hai
string devi2(string s)
{
	// biến lưu kết quả 
	string result;
	int temp = 0;
	if (s.length() == 1 && (s[0] == '1' || s[0] == '0'))
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
		temp = temp % 2;
	}
	return  result;
}

// hàm chuyển đổi số nguyên thành  dạng nhi phân
string decIntoBin(string s)
{
	string  result;
	string  temp = s;

	while (temp != "0")
	{
		int bit = int(temp[temp.length() - 1] - '0') % 2;
		result.insert(result.begin(), bit + '0');
		temp = devi2(temp);
	}
	result.insert(result.begin(), 0 + '0');
	return result;
}

// hàm nhân một số cho 2
string muti2(string s)
{
	string result;
	int i = s.length() - 1;
	int miss = 0;
	while (i>=0)
	{
		int number = (s[i] - '0')*2+miss;
		if (number >= 10)
		{
			number = number % 10;
			miss = 1;
		}
		else
		{
			miss = 0;
		}
		result.insert(result.begin(), number + '0');
		i--;
	}
	return result;
}
// hàm kiểm tra bằng 1
bool check1(string s)
{
	if (s[0] !='1')
	{
		return false;
	}
	else
	{
		for (int i = 1; i < s.length(); i++)
		{
			if (s[i] != '0')
			{
				return false;
			}
		}
		return true;
	}
}
// hàm chuyển đổi  phần lẻ sang nhi phân
string convertFactionToBinary(string s,int &check)
{
	string result;
	int count = 0;
	string  temp = muti2(s);
	while (check1(temp) == false && count < 112)
	{
		count++;
		if (temp[0] == '0')
		{
			result += '0';
		}
		else
		{
			result += '1';
			temp[0] = '0';
		}
		temp = muti2(temp);
	}
	if (count < 112)
	{
		result += '1';
	}
	if (!check1(temp))
	{
		check = 0;
	}
	else
	{
		check = 1;
	}
	
	return result;
}
//  chuyển đổi số thực sang nhi phân
string convertDecToBinary(string s,int &check)
{
	// lưu kết quả
	string result;
	
	// xet dấu của số chấm động
	result = (s[0] == '-') ? '-' : '+';
	if (s[0] == '-'|| s[0] == '+')
	{
		s = s.erase(0, 1);
	}

	// tìm phần nguyên và phần  thập phân
	int index = s.find('.');
	if (index == -1)
	{
		index = s.length();
	}
	// tách lấy phần nguyên
	string n = s.substr(0, index);
	
	// chuyển phần nguyên thành nhi phân
	result+=decIntoBin(n);

	// tách lấy phần thập phân
	string temp = "0";
	temp += s.erase(0, index + 1);
	result += '.';
	
	result+= convertFactionToBinary(temp,check);
	return result;

}

// hàm chuyển đổi nhi phân sang  nhi phân tiêu chuẩn ieee754
string convertIntoStandardIEEE754(string s,int check)
{
	//biến để lưu kết quả
	string result;
	// xét dấu
	string sign = (s[0] == '-') ? "1" : "0";
	// xóa dấu đi
	s = s.erase(0, 1);

	string exp;
	string fraction;
	// tinh exponent
	int indexPoint = s.find('.');
	int index1 = s.find('1');
	int E;
	// chuẩn hóa số 0
	if (index1 == -1)
	{
		E = 0;

	}
	else if (indexPoint > index1)
	{
		 E = (int)pow(2, 15 - 1) - 1 + indexPoint - index1 - 1;
	}
	else
	{
		 E = (int)pow(2, 15 - 1) - 1 + indexPoint - index1 ;
	}
	
	// chuyển đổi sang dạng nhi phân
	int i = 1;
	while (i<=15) {

		
		exp.insert(exp.begin(),E%2+'0');
		E = E / 2;
		i++;
	}
	// tách lấy phần fraction
	string temp = s.erase(0, index1+1);
	int point = temp.find('.');
	if (point != -1)
	{
		temp = temp.erase(point, 1);
	}
	fraction = temp;
	if (fraction.length() < 112)
	{
		string b;
		int a = 112 - fraction.length();
		for (int i = 1; i <= a; i++)
		{
			b += '0';
		}
		fraction += b;
	}
	else if(fraction.length() > 112)
	{
		fraction = fraction.erase(112, fraction.length() - 112);
		
	}
	// dạng các số đặc biệt 
	// số 0
	// số không thể chuẩn hóa
	// số vô cùng
	//số báo lỗi


	// số o và số không thể chuẩn hóa
	if (checkBit0(exp) )
	{
		if (checkBit0(fraction))
		{
			result = sign + exp + fraction;
			return result;
		}
		else
		{
			result = "denormalized";
			return result;
		}
	}

	 // số vô cùng  và số báo lỗi
	if (checkBit1(exp))
	{
		if (checkBit0(fraction))
		{
			result = "infinity";
			return result;
		}
		else
		{
			result = "NotaNumber";
			return result;
		}
	}
	
	// làm tròn số
	if (check == 0)
	{

		if (sign == "0")
		{
			add1(fraction);
		}
		else
		{
			sub1(fraction);
		}

	}

	result = sign + exp + fraction;
	return result;


}
// hàm cộng thêm 1 để làm tròn
void add1(string &s)
{
	int i = s.length() - 1;

	int miss = 0;
	int bitAdd = 1;

	while (i >= 0)
	{
		int bit = (int)(s[i] - '0') + bitAdd + miss;
		if (bit == 2)
		{
			s[i] = '0';
			miss = 1;
		}
		else if (bit == 1)
		{
			s[i] = '1';
			miss = 0;
		}
		else
		{
			s[i] = '0';
			miss = 0;
		}
		bitAdd = 0;
		i--;
	}
}


// hàm trừ 1 để làm tròn số.
void sub1(string &s)
{
	
	int i = s.length() - 1;

	int miss = 0;
	int bitSub = 1;

	while (i >= 0)
	{
		int bit = (int)(s[i] - '0') - bitSub + miss;
		if (bit == -2)
		{
			s[i] = '0';
			miss = -1;
		}
		else if (bit == -1)
		{
			s[i] = '1';
			miss = -1;
		}
		else if(bit==0)
		{
			s[i] = '0';
			miss = 0;
		}
		else if (bit == 1)
		{
			s[i] = '1';
			miss = 0;
		}
		bitSub = 0;
		i--;
	}
}


bool checkBit0(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != '0')
		{
			return false;
		}
	}
	return true;
}

bool checkBit1(string s)
{

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != '1')
		{
			return false;
		}
	}
	return true;

}



string BinToDec(const string & bin)
{
	string result = "0";

	int len = bin.length();

	int pointPosition = bin.find('.');
	if (pointPosition == -1)
		pointPosition = len;

	for (int i = pointPosition - 1; i >= 0; i--) {
		if (bin[i] == '1')
			result = add(result, calculate2power(pointPosition - 1 - i));
	}

	for (int i = pointPosition + 1; i < len; i++) {
		if (bin[i] == '1')
			result = add(result, calculate2power(pointPosition - i));
	}

	return result;
}


string add(const string & n1, const string & n2)
{
	if (n1[0] == '-' && n2[0] != '-')
		return sub(n2, n1.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return sub(n1, n2.c_str() + 1);
	if (n1[0] == '-' && n2[0] == '-')
		return '-' + add(n1.c_str() + 1, n2.c_str() + 1);

	string result;
	string number1 = n1;
	string number2 = n2;

	int len1 = n1.length();
	int len2 = n2.length();

	// find the point position in n1
	int point_position1 = n1.find('.');
	if (point_position1 == -1)
		point_position1 = len1;

	// find the point position in n2
	int point_position2 = n2.find('.');
	if (point_position2 == -1)
		point_position2 = len2;

	if (point_position1 != len1 || point_position2 != len2)
	{
		int digitsAfterPoint1 = len1 - point_position1 - 1;
		int digitsAfterPoint2 = len2 - point_position2 - 1;
		// find the point position after calculation 
		int point_position = (digitsAfterPoint1 > digitsAfterPoint2) ? digitsAfterPoint1 : digitsAfterPoint2;
		for (int i = 0; i < point_position; i++)
		{
			number1 = mul10(number1);
			number2 = mul10(number2);
		}
		result = add(number1, number2);
		for (int i = 0; i < point_position; i++)
			result = div10(result);
		return result;
	}

	int carry = 0;
	int sum;

	while (true) {
		if (len1 > 0 && len2 > 0)
			sum = (n1[len1-- - 1] - '0') + (n2[len2-- - 1] - '0') + carry;
		else if (len1 > 0 && len2 <= 0)
			sum = (n1[len1-- - 1] - '0') + carry;
		else if (len1 <= 0 && len2 > 0)
			sum = (n2[len2-- - 1] - '0') + carry;
		else
			break;

		carry = (sum >= 10) ? 1 : 0;
		sum -= carry * 10;

		result = (char)(sum + '0') + result;
	}
	if (carry != 0)
		result = (char)(carry + '0') + result;

	return result;
}


string sub(const string &n1, const string &n2)
{
	if (n1[0] == '-' && n2[0] == '-')
		return sub(n2.c_str() + 1, n1.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return add(n1, n2.c_str() + 1);
	if (n1[0] == '-' && n2[0] != '-')
		return add(n1, '-' + n2);
	if (compare(n1, n2) < 0)
		return '-' + sub(n2, n1);
	string result;
	string number1 = n1;
	string number2 = n2;

	int len1 = n1.length();
	int len2 = n2.length();

	// find the point position in n1
	int point_position1 = n1.find('.');
	if (point_position1 == -1)
		point_position1 = len1;

	// find the point position in n2
	int point_position2 = n2.find('.');
	if (point_position2 == -1)
		point_position2 = len2;

	if (point_position1 != len1 || point_position2 != len2)
	{
		int digitsAfterPoint1 = len1 - point_position1 - 1;
		int digitsAfterPoint2 = len2 - point_position2 - 1;
		// find the point position after calculation 
		int point_position = (digitsAfterPoint1 > digitsAfterPoint2) ? digitsAfterPoint1 : digitsAfterPoint2;
		for (int i = 0; i < point_position; i++)
		{
			number1 = mul10(number1);
			number2 = mul10(number2);
		}
		result = sub(number1, number2);
		for (int i = 0; i < point_position; i++)
			result = div10(result);
		return result;
	}

	int diff;
	int carry = 0;

	while (true) {
		if (len1 > 0 && len2 > 0)
			diff = (n1[len1-- - 1] - '0') - (n2[len2-- - 1] - '0') - carry + 10;
		else if (len1 > 0 && len2 <= 0)
			diff = (n1[len1-- - 1] - '0') - carry + 10;
		else if (len1 <= 0 && len2 > 0)
			diff = (n2[len2-- - 1] - '0') - carry + 10;
		else
			break;

		carry = (diff < 10) ? 1 : 0;
		diff %= 10;

		result = (char)(diff + '0') + result;
	}

	return result;
}

int compare(const string &n1, const string &n2)
{
	if (n1 == n2)
		return 0;
	if (n1[0] == '-' && n2[0] == '-')
		return compare(n2.c_str() + 1, n1.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return 1;
	if (n1[0] == '-' && n2[0] != '-')
		return -1;

	int len1 = n1.length();
	int len2 = n2.length();

	if (len1 > len2)
		return 1;
	if (len1 < len2)
		return -1;
	for (int i = 0; i < len1; i++)
	{
		if (n1[i] > n2[i])
			return 1;
		if (n1[i] < n2[i])
			return -1;
	}
	return 0;
}
string div10(const string &n)
{
	if (n == "0")
		return n;
	if (n[0] == '-')
		return '-' + div10(n.c_str() + 1);

	string result = n;

	int len = n.length();
	int i = len - 1;
	for (; i >= 0; i--) {
		if (n[i] == '.') {
			swap(result[i], result[i - 1]);
			break;
		}
	}
	if (i == -1)
	{
		result += '.';
		swap(result[len], result[len - 1]);
	}
	if (result[0] == '.')
		result = '0' + result;
	if (result[len] == '0')
		result = result.substr(0, len - 1);

	return result;
}

string mul10(const string &n)
{
	if (n[0] == '-')
		return '-' + mul10(n.c_str() + 1);

	string result = n;

	int len = n.length();
	int i = len - 1;
	for (; i >= 0; i--) {
		if (n[i] == '.') {
			swap(result[i], result[i + 1]);
			break;
		}
	}
	if (i == -1)
		result += '0';
	if (result[len - 1] == '.')
		result = result.substr(0, len - 1);
	if (result[0] == '0')
		result = result.c_str() + 1;
	return result;
}
string calculate2power(const int exp) // return 2^exp (string)
{
	if (exp == 0)
		return "1";
	if (exp == 1)
		return "2";
	if (exp == -1)
		return "0.5";

	string temp = calculate2power(exp / 2);
	if (exp % 2 == 0)
		return mul(temp, temp);
	else {
		if (exp > 0)
			return mul2(mul(temp, temp));
		return div2(mul(temp, temp));
	}
}

string mul(const string & n1, const string & n2)
{
	if (n1[0] == '-' && n2[0] == '-')
		return mul(n1.c_str() + 1, n2.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return '-' + mul(n1, n2.c_str() + 1);
	if (n1[0] == '-' && n2[0] != '-')
		return '-' + mul(n2, n1.c_str() + 1);

	int len1 = n1.length();
	int len2 = n2.length();

	int pointPosition1 = n1.find(".");
	if (pointPosition1 == -1)
		pointPosition1 = len1;

	int pointPosition2 = n2.find(".");
	if (pointPosition2 == -1)
		pointPosition2 = len2;

	string number1 = n1;
	string number2 = n2;
	string result;

	if (pointPosition1 != len1 || pointPosition2 != len2)
	{
		// point position after calculation
		int pointPosition = 0;

		if (pointPosition1 != len1) {
			for (int i = len1 - 1 - pointPosition1; i > 0; i--)
				number1 = mul10(number1);
			pointPosition += len1 - 1 - pointPosition1;
		}

		if (pointPosition2 != len2) {
			for (int i = len2 - 1 - pointPosition2; i > 0; i--)
				number2 = mul10(number2);
			pointPosition += len2 - 1 - pointPosition2;
		}

		result = mul(number1, number2);

		for (int i = 0; i < pointPosition; i++)
			result = div10(result);

		return result;
	}

	result = "0";
	for (int i = len2 - 1; i >= 0; i--)
	{
		int product;
		int carry = 0;

		string sum;
		for (int j = len1 - 1; j >= 0; j--)
		{
			product = (n1[j] - '0') * (n2[i] - '0') + carry;
			carry = (product >= 10) ? product / 10 : 0;
			product %= 10;
			sum = (char)(product + '0') + sum;
		}
		if (carry != 0)
			sum = (char)(carry + '0') + sum;
		for (int k = len2 - 1; k > i; k--)
			sum += '0';
		result = add(result, sum);
	}

	return result;
}

string mul2(const string & n)
{
	return mul("2", n);
}

string div2(const string &n)
{
	if (n[0] == '-')
		return '-' + div2(n.c_str() + 1);

	int len = n.length();

	string result = n;

	// find the point position in n
	int point_position = n.find('.');

	// erase the point from n
	if (point_position != -1)
		result.erase(result.begin() + point_position);

	// find the point position after calculation 
	point_position = (point_position == -1) ? 1 : len - point_position;

	// n/2 == (n*5)/10
	if (result[0] == '0')
		result = result.c_str() + 1;
	result = mul(result, "5");
	for (int i = 0; i < point_position; i++)
		result = div10(result);

	return result;
}


string displayBinaryOfinterger(QFloat a)
{
	int i = 127;
	string  result;
	while (i >= 0)
	{
		int index = i / 32;
		int soBitDich = i % 32;
		int bit = (a.bigFloat[index] >> (31 - soBitDich)) & 1;
		result.insert(result.begin(), bit + '0');
		i--;
	}
	return result;
}
void PrintQfloat(QFloat x)
{
	
	string bin = displayBinaryOfinterger(x);
	string resuslt;
	string sign = (bin[0] == '1') ? "-" : "+";
	// tinh exponent
	string binary;
	int exp=0;
	int k = 14;
	for (int i = 1; i <= 15;i++)
	{
		if (bin[i] == '1')
		{
			exp += (int)pow(2, k);
	   }
		k--;
	}
	exp -= pow(2, 14) - 1;
	cout << "exp:" << exp << endl;
	string fraction = bin.erase(0, 16);
	cout << "Fraction:" << fraction << endl;
	if (exp > 0)
	{
		binary = "1" + fraction.insert(exp, ".");
		cout << "bin cahuyen" << binary << endl;
	}
	else
	{
		string temp = "1" + fraction;
		for (int i = 1;i <= abs(exp)-1; i++)
		{
			temp = temp.insert(0, "0");
		}
		temp = temp.insert(0, ".");
		temp = temp.insert(0, "0");
		binary = temp;
		cout << "binary:" << binary << endl;
	}
	resuslt = sign+BinToDec(binary);
	cout << "result "<<resuslt << endl;
}

// hàm chuyển đổi cơ số 10 sang cơ số 2
string DecimaltoBinary(string s)
{
	int check = 0;
	string bin = convertDecToBinary(s, check);
	//cout << "He co so 2 :" << bin << endl;
	string IEE745 = convertIntoStandardIEEE754(bin, check);
	
	string specialNumber[] = { "denormalized" ,"infinity" ,"NotaNumber" };
	for (int i = 0;i < 3; i++)
	{
		if (specialNumber[i] == IEE745)
		{
			cout << IEE745 << endl;
			return specialNumber[i];
		}
	}
	return IEE745;
}

string BinaryToDecimal(string s)
{

	
	string resuslt;
	string sign = (s[0] == '1') ? "-" : "+";
	// tinh exponent
	string binary;
	int exp = 0;
	int k = 14;
	for (int i = 1; i <= 15;i++)
	{
		if (s[i] == '1')
		{
			exp += (int)pow(2, k);
		}
		k--;
	}
	exp -= pow(2, 14) - 1;
	//cout << "exp:" << exp << endl;
	string fraction = s.erase(0, 16);
	//cout << "Fraction:" << fraction << endl;

	if (exp == -16383 && !checkBit0(fraction))
	{
		resuslt = "denormalized";
		return resuslt;
	}
	if (exp == -16383 && checkBit0(fraction))
	{
		resuslt = sign+"0.0";
		return resuslt;
	}
	if (exp == 16384 && checkBit0(fraction))
	{
		resuslt = "infinity";
		return resuslt;
	}
	if(exp == 16384 && !checkBit0(fraction))
	{
		resuslt = "NotaNumber";
		return resuslt;
	}





	if (exp > 0)
	{
		binary = "1" + fraction.insert(exp, ".");
		//cout << "bin can chuyen" << binary << endl;
	}
	else
	{
		string temp = "1" + fraction;
		for (int i = 1;i <= abs(exp) - 1; i++)
		{
			temp = temp.insert(0, "0");
		}
		temp = temp.insert(0, ".");
		temp = temp.insert(0, "0");
		binary = temp;
		//cout << "binary:" << binary << endl;
	}
	resuslt = sign + BinToDec(binary);
	//cout << "result " << resuslt << endl;
	return resuslt;
}


// ham run 
void run(ifstream &input, ofstream &output)
{
	
	while (!input.eof())
	{
		int  a, b;
		string s;
		input >> a >> b >> s;
		if (a==2 && b==10)
		{
			string result = BinaryToDecimal(s);
			output << result << endl;
		}
		if (a == 10 && b == 2)
		{
			string result = DecimaltoBinary(s);
			output << result << endl;
		}

	}

}