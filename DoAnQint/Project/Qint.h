﻿#pragma once

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
	int bigInt[N];// int 4 byte x 4 byte = 16 byte

	// Contructor
	QInt() 
	{
		for (int i = 0; i < N; i++)
		{
			this->bigInt[i] = 0;
		}
	}
	// Destructor
	~QInt() {}

	// Operator
	void operator=(QInt const& a);

	QInt TwoComponent(string a);

	QInt operator+(QInt const& a);
	QInt operator-(QInt const& a);
	QInt operator*(QInt const& a);

	QInt operator/(QInt const& a);

	bool operator==(QInt const& a);
	bool operator<=(QInt const& a);
	bool operator>=(QInt const& a);
	bool operator>(QInt const& a);
	bool operator<(QInt const& b);

	void operator>>(int n);
	void operator<<(int n);

	QInt operator &(QInt const& a);
	QInt operator |(QInt const& a);
	QInt operator ^(QInt const& a);
	QInt operator ~();
	string rol(int n);
	string ror(int n);

};

// void InitQInt(QInt &a);
void ScanQInt(QInt& a, string s, string base);
string QIntToString(QInt a);
bool GetBit(QInt a, int i);
void SetBit(QInt &a, int i, bool bit);
bool GetSign(QInt a);
int BitLength(QInt a);
string Div2(string s);
string HexToBin(string s);
string AddStr(string a, string b);
string SubStr(string a, string b);
string Multi(char base, int exp);
QInt Multiply(QInt M, QInt Q);

//
char* DecToHex(string s);
char* BinToHex(QInt a);
QInt DecToBin(string a);
string BinToDec(QInt a);
//
string Calculate(QInt q1, QInt q2, string op, string base);
list <vector<string>> Readfile(ifstream &file);
void WriteFile(ofstream &file, vector<string> v_result);
string TrimBit(string str);
string TrimBit(QInt q);