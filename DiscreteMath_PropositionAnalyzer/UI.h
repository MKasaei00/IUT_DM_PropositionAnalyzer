#pragma once
#include <iostream>
#include <string>
#include <windows.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

void fullScreen();

void printLine(const char & ch, const unsigned short int & count);

void printTitleLine(const string & title);

void printMessageLine(const string & message);

void printActionStatement(const string & key, const string & value);
