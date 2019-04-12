#pragma once
#include "Tree.h"
#include <string>
#include <map>
#include <set>

using std::string;
using std::set;
using std::map;


class Formula
{

	typedef	bool(*IteratorVarAssignsFunction)(const Formula& form,const map<VarName, VarType> &, const VarType &res , bool &stop);

private:
	static const char OPEN_PAR = '(';
	static const char CLOSE_PAR = ')';
	static const char TRUE = 'T';
	static const char FALSE = 'F';

	static const char* NOT;
	static const char* AND;
	static const char* OR;
	static const char* CON;
	static const char* BICON;

	Tree* tree;
	string str;
	set<VarName> vars;

	static Tree* parse(string);

	void getVariables(set<VarName> &vars, Tree * tree);
	bool assign(const map<VarName, VarType>& vars, Tree * tree);
	map<VarName, VarType> binaryToMap(unsigned long long int binary);
public:
	Formula(const string &formula);
	~Formula();

	string getString();

	bool Formula::assign(map<VarName, VarType> vars);
	set<VarName> getVariables();
	bool iterateVarAssigns(const IteratorVarAssignsFunction &iteratorFunction);
};