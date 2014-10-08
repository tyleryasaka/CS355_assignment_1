//CS 355 Assignment 1 - BST.h
#include <iostream>
using namespace std;

template <class T>
class BNode{
	<T> data;
	BNode* left;
	BNode* right;
	BNode();
	BNode(T);
	BNode(T, BNode*, BNode*);	
	friend class BST;
public:
	int GetData()const;
};

template <class T>
class BST{
	BNode* root;
	BNode* cursor;
	bool InsertHelp(T e, BNode*&);
	void PrintInHelp(ostream& os, BNode* n);
	void PrintPreHelp(ostream& os, BNode* n);
	void PrintPostHelp(ostream& os, BNode* n);
	BNode* FindHelp(T e, BNode*n); 
	bool RemoveHelp(T e, BNode*&); 
	int FindMin(BNode* n)const;
	void GoToNextHelp(BNode* n,bool* flag);
	void GoToPrevHelp(BNode* n,bool* flag);
	void DeleteNode(BNode*& n);
	int GetHeightHelp(BNode* n)const;
	void PrintInfoHelp(ostream& os, BNode* n);
public:
	BST();
	BST(const BST&);
	~BST();
	BST& operator=(const BST&);
	bool Insert(T e);//cursor at insertion point
	bool Remove(T e);//cursor at parent of removed item or at root
	void PrintPre(ostream&);
	void PrintPost(ostream&);
	void PrintIn(ostream&);
	BNode* Find(T e);//cursor at located node or rightmost node	
	BNode* AtCursor()const;
	void GoToBeginning();
	void GoToEnd();
	void GoToNext();
	void GoToPrev();
	void ClearList();
	void CopyList(BNode*& cpy,BNode* src);// to be called by copy constructor and assignment
	bool Empty()const;
	int GetHeight()const; // return the height of the tree
	void PrintInfo(ostream&); //print the tree inorder, include value, status, child count for each node
};
