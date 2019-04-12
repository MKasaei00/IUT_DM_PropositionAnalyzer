#include "Formula.h"
#include "CLI.h"
#include "FileHelper.h"

#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

using std::setfill;
using std::setw;
using std::to_string;

bool cliHandler(const ArgCount &, const string*, string &, ostream&);
void cliHelper(void);

const char COL_W = 10;

CLI cli("cmd", cin, cout, cliHandler, cliHelper, nullptr, 3);

//void tableIterator(const map<VarName, VarType> &, const VarType &res, bool & stop)

bool tableIterator(const Formula& form , const map<VarName, VarType> &map, const VarType &res , bool & stop)
{
	//print every row
	for (auto v : map)
		cout << setw(COL_W) << v.second;
	cout << setw(COL_W) << res << '\n';
	return true;
}


bool totalIterator(const Formula& form, const map<VarName, VarType> &map, const VarType &res, bool & stop)
{
	if (!res)
	{
		cout << "Counter example : \n";
		for (auto v : map)
			cout << '\t' << (v.first) << " = " << (v.second) << '\n';
		cout << '\n';
		stop = true;
		return false;
	}
	else
		return true;
}

bool contrIterator(const Formula& form, const map<VarName, VarType> &map, const VarType &res, bool & stop)
{
	if (res)
	{
		cout << "Counter example : \n";
		for (auto v : map)
			cout << '\t' << (v.first) << " = " << (v.second) << '\n';
		cout << '\n';
		stop = true;
		return false;
	}
	else
		return true;
}

bool satisIterator(const Formula& form, const map<VarName, VarType> &map, const VarType &res, bool & stop)
{
	if (res)
	{
		cout << "Assignment : \n";
		for (auto v : map)
			cout << '\t' << (v.first) << " = " << (v.second) << '\n';
		cout << '\n';
		stop = true;
		return true;
	}else return false;
}

bool cliHandler(const ArgCount &count, const string*words, string &message, ostream&out)
{
	if (count >= 1)
	{
		if (count >= 2)
		{
			if (words[0] == "table")
			{
				//read file , create formula , print header , loop
				unsigned short int size = 0;
				string * formStr = readFile(size, words[1], 1);
				if (size)
				{
					Formula f(formStr[0]);
					//print table header
					auto vars = f.getVariables();
					for (auto it = vars.begin(); it != vars.end(); it++)
					{
						out << setw(COL_W) << std::left << *it;
					}
					out << setw(COL_W) << std::left << formStr[0] << '\n';
					for (size_t i = 0; i < COL_W * (vars.size() + 1); i++)
						out << '-';
					out << '\n';

					f.iterateVarAssigns(tableIterator);
				}
				else		message = "File reading error";
				delete[] formStr;
			}
			else if (words[0] == "total")
			{
				//read file , create formula , loop , print the result
				unsigned short int size = 0;
				string * formStr = readFile(size, words[1], 1);
				if (size)
				{
					Formula f(formStr[0]);
					
					cout << "Input : " << formStr[0] << '\n';
					if (f.iterateVarAssigns(totalIterator))
						cout << "Proposition is Taotology" << '\n';
					else
						cout << "Proposition is NOT Taotology" << '\n';
				}
				else		message = "File reading error";
				delete[] formStr;
			}
			else if (words[0] == "contr")
			{
				//read file , create formula , loop , print the result
				unsigned short int size = 0;
				string * formStr = readFile(size, words[1], 1);
				if (size)
				{
					Formula f(formStr[0]);

					cout << "Input : " << formStr[0] << '\n';
					if (f.iterateVarAssigns(contrIterator))
						cout << "Proposition is Contradiction" << '\n';
					else
						cout << "Proposition is NOT Contradiction" << '\n';
				}
				else		message = "File reading error";
				delete[] formStr;
			}
			else if (words[0] == "satis")
			{
				//read file , create formula , loop , print the result
				unsigned short int size = 0;
				string * formStr = readFile(size, words[1], 1);
				if (size)
				{
					Formula f(formStr[0]);

					cout << "Input : " << formStr[0] << '\n';
					if (f.iterateVarAssigns(satisIterator))
						cout << "Proposition is Satisfiable" << '\n';
					else
						cout << "Proposition is NOT Satisfiable" << '\n';
				}
				else		message = "File reading error";
				delete[] formStr;
			}
			/*
			else if (words[0] == "equva")
			{
				//read file , create formula , loop , print the result
			}
			else if (words[0] == "infer")
			{
				//read file , create formulas , merge formulas , loop , print the result
			}
			*/
			else return false;
		}
		else if(words[0] == "help")			cli.help();
		else if (words[0] == "exit")		cli.stop();
		else if (words[0] == "cls")			cli.clearScreen();
		else if (words[0] == "clear")		cli.clearScreen();
		else if (words[0] == "exit")		cli.stop();
		else								return false;
	}
	else return false;

	return true;
}

void cliHelper(void)
{
	cli.printHelpStatement("table", "[input file name]");
	cli.printHelpStatement("total", "[input file name]");
	cli.printHelpStatement("contr", "[input file name]");
	cli.printHelpStatement("satis", "[input file name]");
	/*
	cli.printHelpStatement("equva", "[input file name (two first lines is read)]");
	cli.printHelpStatement("infer", "[input file name (has n line : n-1 lines premises the last is conclusion)]");
	*/
	cli.printEmptyLine();
	cli.printHelpStatement("cls", "");
	cli.printHelpStatement("help", "");
	cli.printHelpStatement("exit", "");
	cli.printEmptyLine();
}


int main()
{
	cli.maximizeWindow();
	cli.help();
	cli.start();

	return 0;
}