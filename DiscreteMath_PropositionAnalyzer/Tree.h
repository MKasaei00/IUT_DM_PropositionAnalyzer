#pragma once

typedef char VarName;
typedef bool VarType;

enum class TreeNodeType { OPERATION, VARIABLE };
enum class TreeNodeOperation : VarName { AND, OR, NOT, CONDITIONAL, BICONDITIONAL  , NONE};

class Tree
{
private:
	TreeNodeType type;
	VarName value;	//operation type or var name
	Tree* right;
	Tree* left;

public:
	Tree();
	Tree(const TreeNodeType &type, const VarName &var, Tree * left = nullptr, Tree * right = nullptr);

	~Tree();

	TreeNodeType getType();
	VarName getValue();
	Tree * getRight();
	Tree * getLeft();
};

