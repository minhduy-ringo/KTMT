#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
using namespace std;

#define N 4

struct QInt
{
	int bigInt[N];// int 4 byte x 4 byte =16 byte
	bool sign;
	short bitLength;

	// Contructor
	QInt() 
	{
		for (int i = 0; i < N; i++)
		{
			this->bigInt[i] = 0;
		}
		this->sign = 0;
		this->bitLength = 0;
	}
	// Destructor
	~QInt() {}

	// Operator
	void operator=(QInt const& a);

	QInt operator+(QInt const& a);
	QInt operator-(QInt const& a);
	QInt operator*(QInt const& a);

	bool operator==(QInt const& a);
	bool operator<=(QInt const& a);
	bool operator>=(QInt const& a);

	void operator>>(int n);
	void operator<<(int n);

	QInt operator &(QInt const& a);
	QInt operator ~();
};

// void InitQInt(QInt &a);
void ScanQInt(QInt& a, string s, string base);
void PrintQInt(QInt a);
void SetBit(QInt &a, int i, int bit);
bool GetBit(QInt a, int i);
string Div2(string s);

//
char* DecToHex(QInt a);
char* BinToHex(QInt a);

//
string Calculate(QInt q1, QInt q2, string op, string base);
list <vector<string>> Readfile(ifstream &file);
void WriteFile(ofstream &file, vector<string> v_result);
string TrimBit(string str);
string TrimBit(QInt q);