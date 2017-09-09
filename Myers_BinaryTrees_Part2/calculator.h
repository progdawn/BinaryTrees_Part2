//Programmer: Dawn Myers
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <fstream>
using namespace std;

#define OPERATOR 0
#define DATA 1
#define FAIL 1
#define SUCCEED 0

typedef
struct
{
	int data;
	int dataType;
} DataNode;

typedef
struct node
{
	DataNode *nodeData;
	struct node *leftChild;
	struct node *rightChild;
} TreeNode;

int printNode(TreeNode *currentTreeNode, int leftData, int rightData);
int evaluate(TreeNode *currentTreeNode, int leftData, int rightData);
int destroyNode(TreeNode *currentTreeNode, int leftData, int rightData);

class calculator
{
public:
	calculator();
	~calculator();
	void mainMethod();
private:
	int scan(DataNode *data, FILE *fptr);
	TreeNode *makeTreeNode(DataNode *data);
	void insertTreeNode(TreeNode *newTreeNode, TreeNode **root);
	int inOrder(TreeNode *currentTreeNode, int(*pVisit)(TreeNode *, int, int));
	int preOrder(TreeNode *currentTreeNode, int(*pVisit)(TreeNode *, int, int));
	int postOrder(TreeNode *currentTreeNode, int(*pVisit)(TreeNode *, int, int));
	int postOrderCalc(TreeNode *currentTreeNode);
	void postOrderDelete(TreeNode *currentTreeNode);
};
#endif

