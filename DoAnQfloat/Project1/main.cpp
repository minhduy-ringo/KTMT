
#include"Qfloat.h"

int main(int argc, char* argv[])
{
	ifstream input(argv[1], ios_base::in);
	ofstream output(argv[2], ios_base::out);
	if (input.fail() || output.fail())
	{
		cout << "can not opend file";
		system("pause");
		return 1;
	}

	run(input, output);
	cout << "conpletely" << endl;
	system("pause");
	return 1 ;
}