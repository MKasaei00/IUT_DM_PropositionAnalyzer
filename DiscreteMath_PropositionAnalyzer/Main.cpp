#include "Formula.h"
#include "CLI.h"

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <math.h>
#include <iomanip>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

using std::setfill;
using std::setw;

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

const char * FILE_NAME = "Proposition.txt";
const unsigned short int MAX_LENGTH = 10000;

string readDefaultFile()
{
	ifstream file(FILE_NAME);
	char temp[MAX_LENGTH];
	file.getline(temp, MAX_LENGTH);
	file.close();
	return string(temp);
}
bool cliHandler(const ArgCount &, const string*, string &, ostream&);
void cliHelper(void);

CLI cli("cmd", cin, cout, cliHandler, cliHelper, nullptr, 3);

bool cliHandler(const ArgCount &count, const string*words, string &message, ostream&out)
{
	if (count >= 1)
	{
		if (count >= 2)
		{
			if (words[0] == "table")
			{
				//read file , create formula , loop , draw table
			}
			else if (words[0] == "total")
			{
				//read file , create formula , loop , print the result
			}
			else if (words[0] == "contr")
			{
				//read file , create formula , loop , print the result
			}
			else if (words[0] == "satis")
			{
				//read file , create formula , loop , print the result
			}
			else if (words[0] == "equva")
			{
				//read file , create formula , loop , print the result
			}
			else if (words[0] == "infer")
			{
				//read file , create formulas , merge formulas , loop , print the result
			}
		}
		else if(words[0] == "help")			cli.help();
		else if (words[0] == "exit")		cli.stop();
		else								return false;
	}
	else return false;
}

void cliHelper(void)
{
	cli.printHelpStatement("table", "[input file name]");
	cli.printHelpStatement("total", "[input file name]");
	cli.printHelpStatement("contr", "[input file name]");
	cli.printHelpStatement("satis", "[input file name]");
	cli.printHelpStatement("equva", "[input file name (two first lines is read)]");
	cli.printHelpStatement("infer", "[input file name (has n line : n-1 lines premises the last is conclusion)]");
	cli.printEmptyLine();
	cli.printHelpStatement("help", "");
	cli.printHelpStatement("exit", "");
}

/*
void printTruthTable(Formula &form)
{
	const unsigned short COL_W = 7;
	const char HEADER_SEPERATOR = '-';

	set<VarName> vars = form.getVariables();
	unsigned short int size = (unsigned short int)vars.size();
	unsigned long long int count = (unsigned long long int)pow(2, size);

	//printHeader

	for (auto i = vars.begin(); i != vars.end(); ++i)
	{
		cout << setw(COL_W) << std::left << *i;
	}
	cout << form.getString();
	cout << endl;
	printLine(HEADER_SEPERATOR,(unsigned short int) (COL_W * (vars.size() + 1) + form.getString().length()));


	//print rows
	for (unsigned long long int i = 0; i < count; i++)
	{
		auto map = form.binaryToMap(i);
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			cout << std::left << setw(COL_W) << it->second;
		}
		cout << std::left << setw(COL_W) << form.assign(map) << endl;
	}
}

*/



int main()
{
	cli.maximizeWindow();
	cli.help();
	cli.start();

	/*
	string prp = readDefaultFile();
	cout << "reading file : " << FILE_NAME << endl;
	cout << "Proposition => " << prp << endl << endl;

	Formula form(prp);

	printTruthTable(form);

	*/

	_getch();

	return 0;
}