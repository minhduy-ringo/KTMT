
#include "Qint.h"

int main(int argc, char* argv[])
{
	// Uncomment this to debug
	/*argc = 3;
	argv[1] = "QInt_input.txt";
	argv[2] = "QInt_output.txt";*/
	//"test abc"

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

			string result;
			vector<string> v_result;

			list_command = Readfile(inFile);

			int count = 1;

			for (list_it = list_command.begin(); list_it != list_command.end(); ++list_it)
			{
				cout << "Lenh: " << count << endl;
				count++;
				vector<string> token = *list_it;
				QInt q1,q2,qr;
				switch (token.size())
				{
				case 3:
					ScanQInt(qr, token[2], token[0]);
					if (token[0] == "2" && token[1] == "10")
					{
						result = BinToDec(qr);
					}
					else if (token[0] == "10" && token[1] == "2")
					{
						result = QIntToString(qr);
					}
					else if (token[0] == "2" && token[1] == "16")
					{
						result = TrimBit(BinToHex(qr));
					}
					else if (token[0] == "10" && token[1] == "16")
					{
						result = TrimBit(DecToHex(token[2]));
					}
					else if (token[1] == "~")
					{
						qr = ~ qr;
						result = TrimBit(QIntToString(qr));
					}
					v_result.push_back(result);
					break;
				case 4:
					ScanQInt(q1, token[1], token[0]);
					if (token[2] == ">>" || token[2] == "<<" || token[2] == "ror" || token[2] == "rol")
						ScanQInt(q2, token[3], "10");
					else
						ScanQInt(q2, token[3], token[0]);
					result = Calculate(q1, q2, token[2], token[0]);
					v_result.push_back(result);
					break;
				}
			}
			
			ofstream outFile;
			outFile.open(argv[2], ios::out);
			WriteFile(outFile, v_result);

			inFile.close();
			outFile.close();

			return 1;
		}
	}
}