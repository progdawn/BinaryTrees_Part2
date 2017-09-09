//Programmer: Dawn Myers
#include "calculator.h"
#include <iostream>
#include <stdio.h>
using namespace std;

calculator::calculator()
{
}


calculator::~calculator()
{
}

void calculator::mainMethod()
{
	DataNode *node = NULL;
	TreeNode *newTreeNode = NULL;
	TreeNode *root = NULL;

	int resultCode;

	cout << "Enter a mathematical expression using single digit integers." << endl;
	cout << "Use only the common operators (+, -, /, *)." << endl;
	cout << "An example would be 3 + 2 / 5 * 2" << endl;
	cout << "Enter your expression here >> ";

	node = (DataNode*)malloc(sizeof(DataNode)); //allocate memory for data node

	while (resultCode = scan(node, stdin) != EOF)
	{
		newTreeNode = makeTreeNode(node);
		insertTreeNode(newTreeNode, &root);
		node = (DataNode*)malloc(sizeof(DataNode));
	}

	cout << endl;

	cout << "In Order traversal: ";
	inOrder(root, printNode);
	cout << endl;
	cout << "In Order result: " << inOrder(root, evaluate) << endl << endl;

	cout << "Pre Order traversal: ";
	preOrder(root, printNode);
	cout << endl;
	cout << "Pre Order result: " << preOrder(root, evaluate) << endl << endl;

	cout << "Post Order traversal: ";
	postOrder(root, printNode);
	cout << endl;
	cout << "Post Order result: " << postOrder(root, evaluate) << endl << endl;

	cout << "Post Order Calculation: " << postOrderCalc(root) << endl;	

	postOrderDelete(root);

	cin.ignore();
}

TreeNode* calculator::makeTreeNode(DataNode *data)
{
	TreeNode *newptr = NULL;

	if ((newptr = (TreeNode *)malloc(sizeof(TreeNode))) != (TreeNode *)NULL)
	{
		newptr->nodeData = data;
		newptr->leftChild = (TreeNode *)NULL;
		newptr->rightChild = (TreeNode *)NULL;
	}

	return (newptr);
}

int printNode(TreeNode *currentTreeNode, int leftData, int rightData)
{
	leftData = 0;
	rightData = 0;
	
	if (currentTreeNode->nodeData->dataType == OPERATOR)
		cout << (char)currentTreeNode->nodeData->data;
	else
		cout << currentTreeNode->nodeData->data;
	return 0;
}

void calculator::insertTreeNode(TreeNode *newTreeNode, TreeNode **root)
{
	if (*root == (TreeNode*)NULL)
		*root = newTreeNode;
	else
	{
		switch (newTreeNode->nodeData->dataType)
		{
			case OPERATOR:
				newTreeNode->leftChild = *root;
				*root = newTreeNode;
				break;
			case DATA:
				(*root)->rightChild = newTreeNode;
				break;
			default:
				break;
		}
	}
	return;
}

int evaluate(TreeNode *currentTreeNode, int leftValue, int rightValue)
{
	int nodeValue = 0;

	switch (currentTreeNode->nodeData->data)
	{
	case '+':
		nodeValue = leftValue + rightValue;
		break;
	case '-':
		nodeValue = leftValue - rightValue;
		break;
	case '*':
		nodeValue = leftValue * rightValue;
		break;
	case '/':
		if (rightValue != 0)
			nodeValue = leftValue / rightValue;
		else
		{
			cout << "Cannot divide by zero." << endl;
		}
		break;
	default:
		nodeValue = currentTreeNode->nodeData->data;
		break;
	}
	return nodeValue;
}

int destroyNode(TreeNode *currentTreeNode, int leftData, int rightData)
{
	leftData = 0;
	rightData = 0;

	free(currentTreeNode->nodeData);
	free(currentTreeNode);

	return 0;
}

int calculator::inOrder(TreeNode *currentTreeNode, int(*pVisit)(TreeNode *, int, int))
{
	int nodeValue = 0;
	int leftValue = 0;
	int rightValue = 0;

	if (currentTreeNode != NULL)
	{
		leftValue = inOrder(currentTreeNode->leftChild, (*pVisit));
		nodeValue = (*pVisit)(currentTreeNode, leftValue, rightValue);
		rightValue = inOrder(currentTreeNode->rightChild, (*pVisit));
	}

	return nodeValue;
}

int calculator::preOrder(TreeNode *currentTreeNode, int(*pVisit)(TreeNode *, int, int))
{
	int nodeValue = 0;
	int leftValue = 0;
	int rightValue = 0;

	if (currentTreeNode != NULL)
	{
		nodeValue = (*pVisit)(currentTreeNode, leftValue, rightValue);
		leftValue = preOrder(currentTreeNode->leftChild, (*pVisit));
		rightValue = preOrder(currentTreeNode->rightChild, (*pVisit));
	}

	return 0;
}

int calculator::postOrder(TreeNode *currentTreeNode, int(*pVisit)(TreeNode *, int, int))
{
	int nodeValue = 0;
	int leftValue = 0;
	int rightValue = 0;

	if (currentTreeNode != NULL)
	{
		leftValue = preOrder(currentTreeNode->leftChild, (*pVisit));
		rightValue = preOrder(currentTreeNode->rightChild, (*pVisit));
		nodeValue = (*pVisit)(currentTreeNode, leftValue, rightValue);
	}

	return 0;

}

int calculator::postOrderCalc(TreeNode *currentTreeNode)
{
	int nodeValue = 0;
	int leftData = 0;
	int rightData = 0;

	if (currentTreeNode != (TreeNode *)NULL)
	{
		leftData = postOrderCalc(currentTreeNode->leftChild);
		rightData = postOrderCalc(currentTreeNode->rightChild);
		nodeValue = evaluate(currentTreeNode, leftData, rightData);
	}

	return nodeValue;
}

void calculator::postOrderDelete(TreeNode *currentTreeNode)
{
	int rightValue = 0;
	int leftValue = 0;

	if (currentTreeNode != (TreeNode *)NULL)
	{
		postOrderDelete(currentTreeNode->leftChild);
		postOrderDelete(currentTreeNode->rightChild);
		destroyNode(currentTreeNode, leftValue, rightValue);
	}
}


int calculator::scan(DataNode *node, FILE *fptr)
{
	char c = 0;
	int resultCode = SUCCEED;
	
	while (isspace(c = (char)fgetc(fptr)) && (c != '\n')); //eat the whitespace

	switch (c)
	{
	case '+': case '-':
	case '*': case '/':
		(*node).dataType = OPERATOR;
		(*node).data = c; //resultCode = SUCCEED as it is initialized
		break;

	case '0': case '1':
	case '2': case '3':
	case '4': case '5':
	case '6': case '7':
	case '8': case '9':
		(*node).dataType = DATA;
		(*node).data = c - '0'; //resultCode = SUCCEED as it is initialized
		break;

	case '\n':
	case EOF:
		(*node).data = 0;
		resultCode = EOF;
		break;

	default:
		(*node).data = c;
		resultCode = FAIL;
		break;
	}

	return resultCode;
}
