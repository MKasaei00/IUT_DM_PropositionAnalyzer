#pragma once
#include <windows.h>

#include<istream>
using std::istream;

#include<ostream>
using std::ostream;

#include<sstream>
using std::stringstream;

#include<string>
using std::string;

typedef unsigned char ArgCount;

class CLI
{
	typedef bool(*HandlerFunction)(const ArgCount &, const string*, string & , ostream&);
	typedef	void(*HelpFunction)(void);
	typedef void(*ErrorFunction)(const string & message);


	static const size_t DEF_MAX_WORDS = 10;

	static const char QUATATION = '"';

private:
	bool active = false;

	string name;
	istream& in;
	ostream& out;
	HandlerFunction handler;			//not null
	HelpFunction helper;
	ErrorFunction errorHandler;
	const size_t MAX_WORDS;

public:
	CLI(
		const string &name,
		istream &input,
		ostream &out,
		HandlerFunction handler,
		HelpFunction helper,
		ErrorFunction errorHandler = nullptr,
		const size_t &MAX_WORDS = DEF_MAX_WORDS
	);
	~CLI();

	void start();
	void stop();
	void help();

	void maximizeWindow();

	void printHelpStatement(const char * statement, const char *desc);
	void printEmptyLine();
	void clearScreen();
};


/// CLI.cpp	******************************************************************



//init and start the CLI
CLI::CLI(const string &name , istream &inputStream, ostream&out, HandlerFunction handler, HelpFunction helper, ErrorFunction errorHandler, const size_t& INPUT_MAX_WORDS)
	: name(name) , in(inputStream), out(out), MAX_WORDS(INPUT_MAX_WORDS)
{
	//assert(handler!= null)
	//assert(helper!= null)
	this->handler = handler;
	this->helper = helper;
	this->errorHandler = errorHandler;
}


CLI::~CLI()
{
}


void CLI::start()
{
	if (!active)
	{
		active = true;
		while (active)
		{
			string line;
			out << name << " : ";
			while (std::getline(in, line), line.length() == 0);
			stringstream stream;
			stream << line;

			//process line and convert to array of args
			string* words = new string[this->MAX_WORDS];
			ArgCount count = 0;
			string word;
			bool readingString = false;
			size_t len;
			while (stream >> word && count < MAX_WORDS)
			{
				if (len = word.length())
				{
					if (readingString)
					{
						words[count] += " ";
						if (word[len - 1] == QUATATION)		//end of string
						{
							words[count] += word.substr(0, len - 1);
							readingString = false;
							++count;
						}
						else //still in the string
						{
							words[count] += word;
						}
					}
					else if (word[0] == QUATATION)
					{
						//start string from here
						if (word[len - 1] == QUATATION)
						{
							words[count++] = word.substr(1, len - 2);
						}
						else
						{
							words[count] = word.substr(1);
							readingString = true;
						}
					}
					else  //normal : no string just one words
					{
						words[count++] = word;
					}
				}
			}
			string message;
			if (!handler(count, words, message , out))
			{
				//error
				if (errorHandler)
				{
					errorHandler(message);
				}
				else
				{	//def error
					out << "Invalid statement\n";
					if (message.length())
						out << "message : " << message << '\n';
					out << '\n';
				}
				help();
			}
			else if (message.length())
			{
				out << message << '\n';
			}
		}
	}
}

void CLI::stop()
{
	if (active)
	{
		active = false;
	}
}

void CLI::help()
{
	out << "\tCommands : \n";
	helper();
}

void CLI::maximizeWindow()
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

void CLI::printHelpStatement(const char * statement, const char * desc)
{
	out << "\t\t" << statement << "\t" << desc << '\n';
}

void CLI::printEmptyLine()
{
	out << '\n';
}

void CLI::clearScreen()
{
	system("cls");
}