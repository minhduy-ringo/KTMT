
#include "Qint.h"

int main()
{
	QInt q1, q2, rs, rs1, rs2;

	string s = "7";
	string s2 = "-3";
	ScanQInt(q1, s);
	ScanQInt(q2, s2);

	PrintQInt(q1);
	PrintQInt(q2);
	
	rs = q1 - q2;

	cout << "____" << endl;
	PrintQInt(rs);

	int a;
	cin >> a;
}