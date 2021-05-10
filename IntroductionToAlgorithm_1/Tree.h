#pragma once
#include <stdio.h>
#define RED 0
#define BLACK 1
namespace AllTrees {

	class Node
	{
	public:
		Node* LeftChild;
		Node* RightChild;
		int key;
		Node();
		~Node();
	};

	class AVLNode
	{
	public:
		int height;
		int CalculateBalance();
		void CalculateHeightFromLeaf();
		void print();
		AVLNode* LeftChild;
		AVLNode* RightChild;
		int key;
		bool add(AVLNode* node);
		AVLNode();
		AVLNode(int k);
		~AVLNode();
	};
	class RBNode
	{
	public: 
		void print();
		int key;
		bool flag;
		RBNode* LeftChild;
		RBNode* RightChild;
		RBNode* Parent;
		RBNode(int k);
		~RBNode();
	};

	class Red_Black_Tree
	{
	public:
		Red_Black_Tree();
		~Red_Black_Tree();
		bool Insert(int k);
		void print();
	private:
		bool Insert_Fix_Up(RBNode* violateNode);
		RBNode * root;
		RBNode * leaf;
	};

	class BinaryTree
	{
	public:
		BinaryTree();
		~BinaryTree();
	protected:
		Node * root;
	};


	class AVLTree
	{
	public:
		int size;
		AVLTree();
		~AVLTree();
		bool Insert(int k);
		void print();
	private:
		AVLNode * root;
		AVLNode * leaf;
	};
	int MaxHeight(AVLNode* a, AVLNode* b);
	AVLNode* LeftRotate(AVLNode* x);
	AVLNode* RightRotate(AVLNode* x);
	RBNode* LeftRotate(RBNode* x);
	RBNode* RightRotate(RBNode* x);
}