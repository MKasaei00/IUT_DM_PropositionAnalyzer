#include "UI.h"

void fullScreen()
{
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

void printLine(const char &ch, const unsigned short int &count)
{
	for (unsigned short int i = 0; i < count; i++)
	{
		cout << ch;
	}
	cout << endl;
}
void printTitleLine(const string &title)
{
	cout <<"  "<< title << endl;
}
void printMessageLine(const string &message)
{
	cout << "\t" << message << endl;
}
void printActionStatement(const string &key , const string &value)
{
	cout << "\t" << key << "\t" << value << endl;
}