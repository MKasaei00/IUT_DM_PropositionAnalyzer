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

TreeNodeType Tree::getType() const
{
	return type;
}

VarName Tree::getValue() const
{
	return value;
}

Tree * Tree::getRight() const
{
	return this->right;
}

Tree * Tree::getLeft() const
{
	return this->left;
}

void Tree::deleteTree(Tree * tree)
{
	if (tree == nullptr)		return;
	deleteTree(tree->getRight());
	deleteTree(tree->getLeft());
	delete tree;
}
