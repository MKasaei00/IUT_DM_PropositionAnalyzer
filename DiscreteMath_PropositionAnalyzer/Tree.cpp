#include "Tree.h"

Tree::Tree()
{
	right = nullptr;
	left = nullptr;
}

Tree::Tree(const TreeNodeType & type, const VarName & var , Tree * left, Tree * right)
{
	this->type = type;
	this->value = var;
	this->left = left;
	this->right = right;
}


Tree::~Tree()
{
}

TreeNodeType Tree::getType()
{
	return type;
}

VarName Tree::getValue()
{
	return value;
}

Tree * Tree::getRight()
{
	return this->right;
}

Tree * Tree::getLeft()
{
	return this->left;
}
