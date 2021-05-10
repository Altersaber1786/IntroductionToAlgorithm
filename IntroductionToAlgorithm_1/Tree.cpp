#include "Tree.h"

using namespace AllTrees;



BinaryTree::BinaryTree()
{
	root = nullptr;
}

BinaryTree::~BinaryTree()
{
}
AVLTree::AVLTree()
{
	size = 0;
	root = nullptr;
	leaf = nullptr;
}

void AVLNode::print()
{
	
	if (height == -1)
		return;
	printf("height[%d]: %d\tleft: %d, right: %d\n", height, key, LeftChild->key, RightChild->key);
	LeftChild->print();
	RightChild->print();
	return;

};

AVLNode::AVLNode()
{
	key = -1;
	LeftChild = nullptr;
	RightChild = nullptr;
	height = -1;
}

AVLNode::~AVLNode()
{
	if (height > 0) {
		delete LeftChild;
		delete RightChild;
	}
}

AVLNode::AVLNode(int k)
{
	key = k;
	LeftChild = nullptr;
	RightChild = nullptr;
	height = -1;
}

int AllTrees::MaxHeight(AVLNode* a, AVLNode* b)
{
	if (a->height > b->height)
		return a->height;
	return b->height;
};
void AVLNode::CalculateHeightFromLeaf()
{
	if (height == -1)
		return;
	LeftChild->CalculateHeightFromLeaf();
	RightChild->CalculateHeightFromLeaf();
	height = MaxHeight(LeftChild, RightChild) + 1;
	return;
};

int AVLNode::CalculateBalance()
{
	return LeftChild->height - RightChild->height;
}
bool AVLNode::add(AVLNode* node)
{

	if (node->key <= key) {
		if (LeftChild->height == -1)
		{
			LeftChild = node;
			LeftChild->height = 0;
			return true;
		}
		LeftChild->add(node);
		if (LeftChild->CalculateBalance() == 2) {
			if (LeftChild->LeftChild->CalculateBalance() == -1) {
				LeftChild->LeftChild = LeftRotate(LeftChild->LeftChild);
			}
			LeftChild = RightRotate(LeftChild);

		}
		else if (LeftChild->CalculateBalance() == -2) {
			if (LeftChild->RightChild->CalculateBalance() == 1) {
				
				LeftChild->RightChild = RightRotate(LeftChild->RightChild);
			}
			
			LeftChild = LeftRotate(LeftChild);

		}
	}
	else
	{
		if (RightChild->height == -1)
		{
			RightChild = node;
			RightChild->height = 0;
			return true;
		}
		RightChild->add(node);
		if (RightChild->CalculateBalance() == 2) {
			if (RightChild->LeftChild->CalculateBalance() == -1) {
				
				RightChild->LeftChild = LeftRotate(RightChild->LeftChild);
			}
			
			RightChild = RightRotate(RightChild);

		}
		else if (RightChild->CalculateBalance() == -2) {
			if (RightChild->RightChild->CalculateBalance() == 1) {
				
				RightChild->RightChild = RightRotate(RightChild->RightChild);
			}
			
			RightChild = LeftRotate(RightChild);

		}
	}
	CalculateHeightFromLeaf();
	
	return true;
}

bool AVLTree::Insert(int key)
{
	if (root == nullptr) {
		root = new AVLNode(key);
		root->height = 0;
		leaf = new AVLNode();
		root->LeftChild = leaf;
		root->RightChild = leaf;
		size++;
		return true;
	}
	AVLNode* temp = new AVLNode(key);
	size++;
	temp->LeftChild = leaf;
	temp->RightChild = leaf;
	root->add(temp);
	if (root->CalculateBalance() == 2) {
		if (root->LeftChild->CalculateBalance() == -1) {
			
			root->LeftChild = LeftRotate(root->LeftChild);
		}
		
		root = RightRotate(root);
	}
	else if (root->CalculateBalance() == -2) {
		if (root->RightChild->CalculateBalance() == 1) {
			
			root->RightChild = RightRotate(root->RightChild);
		}
		root = LeftRotate(root);

	}
	
	return true;
}

AVLTree::~AVLTree()
{
	if (root != nullptr) delete root;
	if (leaf != nullptr) delete leaf;
};
void AVLTree::print()
{
	root->print();
}
AVLNode* AllTrees::LeftRotate(AVLNode* x)
{
	AVLNode* Temp = x->RightChild;
	x->RightChild = Temp->LeftChild;
	Temp->LeftChild = x;
	return Temp;
};
AVLNode* AllTrees::RightRotate(AVLNode* x)
{
	AVLNode* Temp = x->LeftChild;
	x->LeftChild = Temp->RightChild;
	Temp->RightChild = x;
	return Temp;
};

RBNode::RBNode(int k)
{
	key = k;
	LeftChild = nullptr;
	RightChild = nullptr;
	Parent = nullptr;
	flag = RED;
}

void RBNode::print()
{
	printf("color: %s", (flag== RED)? "Red ":"Back.");
	printf("Key = [%d], left child [%d], rightChild [%d]\n", key, LeftChild->key, RightChild->key);
	if(LeftChild->LeftChild != nullptr)
	LeftChild->print();
	if(RightChild->LeftChild != nullptr)
	RightChild->print();
}

RBNode::~RBNode()
{
	if(RightChild != nullptr)
	if(RightChild->LeftChild != nullptr)
	delete RightChild;
	if(LeftChild != nullptr)
	if(LeftChild->LeftChild != nullptr)
	delete LeftChild;
}

Red_Black_Tree::Red_Black_Tree()
{
	root = nullptr;
	leaf = nullptr;
}

bool Red_Black_Tree::Insert(int key)
{
	if (root == nullptr)
	{
		leaf = new RBNode(-1);
		leaf->flag = BLACK;
		root = new RBNode(key);
		root->flag = BLACK;
		root->LeftChild = leaf;
		root->RightChild = leaf;
		leaf->Parent = root;
		return true;
	}
	RBNode* temp = root;
	while (true)
	{
		if (key <= temp->key) {
			if (temp->LeftChild == leaf)
			{
				temp->LeftChild = new RBNode(key);
				temp->LeftChild->LeftChild = leaf;
				temp->LeftChild->RightChild = leaf;
				temp->LeftChild->Parent = temp;
				break;
			}
			temp = temp->LeftChild;
		}
		else
		{
			if (temp->RightChild == leaf)
			{
				temp->RightChild = new RBNode(key);
				temp->RightChild->LeftChild = leaf;
				temp->RightChild->RightChild = leaf;
				temp->RightChild->Parent = temp;
				break;
			}
			temp = temp->RightChild;
		}
	}
	if (temp->flag == RED)
		Insert_Fix_Up(temp);
	return true;
}

bool Red_Black_Tree::Insert_Fix_Up(RBNode* violateNode)
{	
	if (violateNode == violateNode->Parent->LeftChild)
	{
		if (violateNode->Parent->RightChild->flag == RED)
		{
			violateNode->flag = BLACK;
			violateNode->Parent->flag = RED;
			violateNode->Parent->RightChild->flag = BLACK;
			if (violateNode->Parent == root)
			{
				root->flag = BLACK;
				return true;
			}
			if (violateNode->Parent->Parent->flag == RED)
			{
				Insert_Fix_Up(violateNode->Parent->Parent);
			}
		}
		else
		{
			if (violateNode->RightChild->flag == RED)
				violateNode = LeftRotate(violateNode);
			violateNode = RightRotate(violateNode->Parent);
			if (violateNode->RightChild == root)
				root = violateNode;
			violateNode->flag = BLACK;
			violateNode->RightChild->flag = RED;
			return true;
		}
	}
	else
	{
		if (violateNode->Parent->LeftChild->flag == RED)
		{
			violateNode->flag = BLACK;
			violateNode->Parent->flag = RED;
			violateNode->Parent->LeftChild->flag = BLACK;
			if (violateNode->Parent == root)
			{
				root->flag = BLACK;
				return true;
			}
			if (violateNode->Parent->Parent->flag == RED)
			{
				Insert_Fix_Up(violateNode->Parent->Parent);
			}
		}
		else
		{
			if (violateNode->LeftChild->flag == RED)
				violateNode = RightRotate(violateNode);
		
			violateNode = LeftRotate(violateNode->Parent);
			if (violateNode->LeftChild == root)
				root = violateNode;
			violateNode->flag = BLACK;
			violateNode->LeftChild->flag = RED;
			return true;
		}
	}
	return true;
}

RBNode* AllTrees::LeftRotate(RBNode* x)
{
	RBNode* temp = x->RightChild;
	if (x->Parent != nullptr) {
		x->RightChild->Parent = x->Parent;
		if (temp->Parent->LeftChild == x)
			temp->Parent->LeftChild = temp;
		else
			temp->Parent->RightChild = temp;
		
	}
	else x->RightChild->Parent = nullptr;
	x->Parent = x->RightChild;
	x->RightChild = temp->LeftChild;
	temp->LeftChild = x;
	
	return temp;
}
RBNode* AllTrees::RightRotate(RBNode* x)
{
	RBNode* temp = x->LeftChild;
	if(x->Parent != nullptr){
		x->LeftChild->Parent = x->Parent;
		if (temp->Parent->LeftChild == x)
			temp->Parent->LeftChild = temp;
		else
			temp->Parent->RightChild = temp;
	
	}
	x->Parent = x->LeftChild;
	x->LeftChild = temp->RightChild;
	temp->RightChild = x;
	
	return temp;
}

void Red_Black_Tree::print()
{

	if(root != nullptr) root->print();
	return;

};

Red_Black_Tree::~Red_Black_Tree()
{
	if (root != nullptr) delete root;
	if (leaf != nullptr) delete leaf;
}