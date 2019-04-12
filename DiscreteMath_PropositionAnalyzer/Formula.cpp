#include "Formula.h"

const char* Formula::NOT = "~";
const char* Formula::AND = "/\\";
const char* Formula::OR = "\\/";
const char* Formula::CON = "->";
const char* Formula::BICON = "<->";

Tree * Formula::parse(string str)
{
	const unsigned int len = str.length();
	if (str[0] == OPEN_PAR)
	{
		// expression is compound
		if (str[1] == NOT[0])
		{
			//operator has one operand
			return new Tree(TreeNodeType::OPERATION, (VarName)TreeNodeOperation::NOT, parse(str.substr(2, len - 3)));
		}
		else
		{
			//operator has two operands
			Tree * rightOperand = nullptr;
			Tree * leftOperand = nullptr;

			unsigned short int leftOperandLen;
			unsigned short int rightOperandLen;


			if (str[1] == OPEN_PAR)
			{
				//first operand is compound
				unsigned short int openCount = 0;
				unsigned short int closeCount = 0;
				for (unsigned int i = 1; i < len-1; i++)
				{
					if (str[i] == OPEN_PAR)
					{
						openCount++;
					}
					else if (str[i] == CLOSE_PAR)
					{
						closeCount++;
						if (openCount == closeCount)
						{
							leftOperand = parse(str.substr(1, i));
							leftOperandLen = i;
							break;
						}
					}
				}
			}
			else
			{
				//left operand is Var
				leftOperand = parse(str.substr(1, 1));
				leftOperandLen = 1;
			}
			
			if (str[len - 2] == CLOSE_PAR)
			{
				//right operand is compound
				unsigned int openCount = 0;
				unsigned int closeCount = 0;

				for (unsigned int i = len-2; i >=1 ; --i)
				{
					if (str[i] == OPEN_PAR)
					{
						++openCount;
						if (closeCount == openCount)
						{
							rightOperand = parse(str.substr(i, len - i - 1));
							rightOperandLen = len - i - 1;
							break;
						}
					}
					else if(str[i] == CLOSE_PAR)
					{
						++closeCount;
					}
				}
			}
			else
			{
				//right operand is Var
				rightOperand = parse(str.substr(len - 2 , 1));
				rightOperandLen = 1;
			}

			//string opt = str.substr(1 + leftOperandLen, len - 1 - rightOperandLen - 1 - (1 + leftOperandLen) + 1);
			string optStr = str.substr(1 + leftOperandLen, len - rightOperandLen - leftOperandLen - 2);
			TreeNodeOperation optType = TreeNodeOperation::NONE;
			if (optStr == AND)
			{
				optType = TreeNodeOperation::AND;
			}
			else if (optStr == OR)
			{
				optType = TreeNodeOperation::OR;
			}
			else if (optStr == CON)
			{
				optType = TreeNodeOperation::CONDITIONAL;
			}
			else if (optStr == BICON)
			{
				optType = TreeNodeOperation::BICONDITIONAL;
			}
			
			return new Tree(TreeNodeType::OPERATION, (VarName)optType, leftOperand, rightOperand);
		}
	}
	else
	{
		// it is a variable
		// create tree and return
		return new Tree(TreeNodeType::VARIABLE, str[0]);
	}
	return nullptr;
}

Formula::Formula(const string & formula)
{
	this->str = formula;
	this->tree = parse(formula);

	getVariables(vars, this->tree);
	vars.erase(Formula::TRUE);
	vars.erase(Formula::FALSE);
}

Formula::~Formula()
{
	Tree::deleteTree(this->tree);
}

string Formula::getString()
{
	return this->str;
}

void Formula::getVariables(set<VarName> &vars , Tree * tree)
{
	if (tree == nullptr)		return;
	switch (tree->getType())
	{
		case TreeNodeType::OPERATION:
			getVariables(vars, tree->getLeft());
			getVariables(vars, tree->getRight());
			break;
		case TreeNodeType::VARIABLE:
			vars.insert(tree->getValue());
			break;
	default:
		break;
	}
}

bool Formula::assign(const map<VarName, VarType>& vars, Tree * tree)
{
	switch (tree->getType())
	{
	case TreeNodeType::OPERATION:
	{
		switch ((TreeNodeOperation)tree->getValue())
		{
		case TreeNodeOperation::AND:
			return assign(vars, tree->getLeft()) && assign(vars, tree->getRight());
			break;
		case TreeNodeOperation::OR:
			return assign(vars, tree->getLeft()) || assign(vars, tree->getRight());
			break;
		case TreeNodeOperation::NOT:
			return !assign(vars, tree->getLeft());
			break;
		case TreeNodeOperation::CONDITIONAL:
			return (!assign(vars, tree->getLeft())) || assign(vars, tree->getRight());
			break;
		case TreeNodeOperation::BICONDITIONAL:
			return (assign(vars, tree->getLeft()) == assign(vars, tree->getRight()));
			break;
		default:
			break;
		}
	}
	break;
	case TreeNodeType::VARIABLE:
		return vars.at(tree->getValue());
		break;
	default:
		return false;
		break;
	}
}

bool Formula::assign(map<VarName, VarType> vars)
{
	vars[TRUE] = true;
	vars[FALSE] = false;
	return assign(vars, this->tree);
}

//returns just parameters not T and F
set<VarName> Formula::getVariables()
{
	return vars;
}


map<VarName, VarType> Formula::binaryToMap(unsigned long long int binary)
{
	map<VarName, VarType> map;
	unsigned short cursor = vars.size()-1;
	for (auto it = vars.begin(); it != vars.end(); ++it , cursor--)
		map[*it] = (bool)(binary & (1 << (long long)cursor));

	return map;
}

bool Formula::iterateVarAssigns(const IteratorVarAssignsFunction & f)
{
	unsigned long long int count = (unsigned long long int)pow(2, vars.size());
	bool stop = false;
	bool res = true;
	for (unsigned long long int i = 0; (i < count) && !stop; i++)
	{
		auto map = binaryToMap(i);
		res = f(*this , map, assign(map) , stop);
	}
	return res;
}