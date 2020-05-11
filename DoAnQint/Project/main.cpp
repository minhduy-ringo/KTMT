
#include "Qint.h"

int main(int argc, char* argv[])
{
	// Uncomment this to debug
	argc = 3;
	argv[1] = "QInt_input.txt";
	//"test abc"

	//if (argc != 3)
	//{
	//	cout << "Command not valid" << endl << "<.exe><input.txt><output.txt>" << endl;
	//	return 0;
	//}
	//else
	//{
	//	ifstream inFile;
	//	inFile.open(argv[1]);
	//	if (!inFile.is_open())
	//	{
	//		cout << "Could not open file" << endl;
	//		return 0;
	//	}
	//	else
	//	{
	//		list <vector<string>> list_command;
	//		list <vector<string>>::iterator list_it;

	//		string result;
	//		vector<string> v_result;

	//		list_command = Readfile(inFile);

	//		for (list_it = list_command.begin(); list_it != list_command.end(); ++list_it)
	//		{
	//			vector<string> token = *list_it;
	//			QInt q1,q2,qr;
	//			switch (token.size())
	//			{
	//			case 3:
	//				ScanQInt(qr, token[2], token[0]);
	//				if (token[0] == "2" && token[1] == "10")
	//				{
	//					//DecToBin(q)
	//				}
	//				if (token[0] == "10" && token[1] == "2")
	//				{
	//					//BinToDec(q)
	//				}
	//				if (token[0] == "2" && token[1] == "16")
	//				{
	//					BinToHex(qr);
	//					
	//				}
	//				if (token[0] == "10" && token[1] == "16")
	//				{
	//					DecToHex(qr);
	//				}
	//				if (token[1] == "~")
	//				{
	//					qr = ~ qr;
	//				}
	//				v_result.push_back(result);
	//				break;
	//			case 4:
	//				ScanQInt(q1, token[1], token[0]);
	//				ScanQInt(q2, token[3], token[0]);
	//				result = Calculate(q1, q2, token[2], token[0]);
	//				v_result.push_back(result);
	//				break;
	//			}
	//		}
	//		
	//		ofstream outFile;
	//		outFile.open(argv[2], ios::out);
	//		WriteFile(outFile, v_result);

	//		inFile.close();
	//		outFile.close();

	//		return 1;
	//	}
	//}


	QInt q1, q2, rs, rs1, rs2;

	string s = "100000";
	string s2 = "100000";
	ScanQInt(q1, s, "10");
	ScanQInt(q2, s2, "10");

	rs = q1 + q2;
	PrintQInt(rs);

	int a;
	cin >> a;
	return 0;
}