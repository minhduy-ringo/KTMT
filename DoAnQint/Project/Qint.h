#pragma once

#include <iostream>
#include< string>
using namespace std;

#define N 4

struct QInt
{
	int bigInt[N];// int 4 byte x 4 byte =16 byte
	bool sign;
	short bitLength;

	// Operator
	bool operator>=(QInt const& a);
	void operator=(QInt const& a);
};

void InitQInt(QInt &a);
void ScanQInt(QInt& a, string s);
void PrintQInt(QInt a);
void SetBit(QInt &a, int i, int bit);
bool GetBit(QInt a, int i);
string Div2(string s);
char* DecToHex(QInt a);
