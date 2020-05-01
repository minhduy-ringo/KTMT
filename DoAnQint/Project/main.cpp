
#include "Qint.h"

int main()
{
	QInt qI, q2;
	InitQInt(qI);
	InitQInt(q2);

	string s = "234534256234523";
	string s2 = "400";
	ScanQInt(qI, s);
	ScanQInt(q2, s2);
	PrintQInt(qI);
	PrintQInt(q2);
	
	if (qI >= q2)
	{
		cout << "true" << endl;
	}
	else
		cout << "false" << endl;
}