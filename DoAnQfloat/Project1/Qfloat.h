#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define N 4

struct QFloat
{
	int bigFloat[N];
};
// hàm khởi tạo 
void intItQfloat(QFloat &a);
//hàm đưa bit vào  vùng nhớ
void setBit(QFloat &a, int i, int bit);
// hàm nhập 
void scanQFloat(QFloat &a, string s);
// hàm chia 2
string devi2(string s);
// hàm nhân 2
string muti2(string s);
// hàm chuyển phần thập phần thành  nhi phân
string convertFactionToBinary(string s, int &check);
// hàm chuyển cơ số 10 phân nguyên sang nhi phân
string decIntoBin(string s);
//hàm chuyển đổi số chấm động thành nhị phân
string convertDecToBinary(string s, int &check);
//hàm kiểm tra bằng 1 hay không
bool check1(string s);
// hàm chuyển đổi sang dạng chuẩn ieee754
string convertIntoStandardIEEE754(string s,int check);
// hàm  để hiển thị dãy bit trong vùng nhớ.
string displayBinaryOfinterger(QFloat a);
// hàm hiện thị số Qfloat
void PrintQfloat(QFloat x);
void add1(string &s);
void sub1(string &s);
//string decIntoBin(string s);
//string devi2(string s);
// hàm  kiểm tra bit  để in ra các dạng đặc biệt
bool checkBit0(string s);
bool checkBit1(string s);

string add(const string & n1, const string & n2);
string BinToDec(const string & bin);
string sub(const string &n1, const string &n2);
int compare(const string &n1, const string &n2);
string div10(const string &n);
string mul10(const string &n);
string mul(const string & n1, const string & n2);
string mul2(const string & n);
string div2(const string &n);
string calculate2power(const int exp);

// hàm chuyển đổi cơ số 10 sang 2;
string DecimaltoBinary(string s);
string BinaryToDecimal(string s);
// ham chay
void run(ifstream &input, ofstream &output);
