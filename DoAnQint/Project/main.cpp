
#include "Qint.h"

int main(int argc, char* argv[])
{
	// Uncomment this to debug
	/*argc = 3;
	argv[1] = "QInt_input.txt";*/

	// main
	if (argc != 3)
	{
		cout << "Command not valid" << endl << "<.exe><input.txt><output.txt>" << endl;
		return 0;
	}
	else
	{
		ifstream inFile;
		inFile.open(argv[1]);
		if (!inFile.is_open())
		{
			cout << "Could not open file" << endl;
			return 0;
		}
		else
		{
			list <vector<string>> list_command;
			list <vector<string>>::iterator list_it;
			list_command = Readfile(inFile);

			for (list_it = list_command.begin(); list_it != list_command.end(); ++list_it)
			{
				vector<string> token = *list_it;
				QInt q;
				switch (token.size())
				{
				case 3:
					if (token[0] == "2" && token[1] == "10")
					{
						//DecToBin
					}
					if (token[0] == "10" && token[1] == "2")
					{
						//BinToDec
					}
					if (token[0] == "2" && token[1] == "16")
					{
						BinToHex(q);
					}
					if (token[0] == "10" && token[1] == "16")
					{
						DecToHex(q);
					}
					break;
				case 4:
					if (token[2] == "+")
					{

					}
					if (token[2] == "-")
					{

					}
					if (token[2] == "*")
					{

					}
					if (token[2] == "/")
					{

					}
					if (token[2] == "<")
					{

					}
					if (token[2] == ">")
					{

					}
					if (token[2] == "<=")
					{

					}
					if (token[2] == ">=")
					{

					}
					if (token[2] == "==")
					{

					}
					if (token[2] == "&")
					{

					}
					if (token[2] == "|")
					{

					}
					if (token[2] == "^")
					{

					}
					if (token[2] == "~")
					{
						
					}
					if (token[2] == ">>")
					{

					}
					if (token[2] == "<<")
					{

					}
					if (token[2] == "ror")
					{

					}
					if (token[2] == "rol")
					{

					}
					break;
				default:
					break;
				}
			}
			
		}
	}

	/*QInt q1, q2, rs, rs1, rs2;

	string s = "10";
	string s2 = "7";
	ScanQInt(q1, s);
	ScanQInt(q2, s2);

	PrintQInt(q1);
	PrintQInt(q2);
	
	rs = q1 - q2;
	cout << "____" << endl;
	PrintQInt(rs);

	rs = q1 + q2;
	cout << "____" << endl;
	PrintQInt(rs);

	int a;
	cin >> a;*/
	return 0;
}