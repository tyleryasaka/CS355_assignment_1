#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

template <class T>
class BST;
template <class T>
class BNode;

template <class T>
class BNode{
	T data;
	BNode<T>* left;
	BNode<T>* right;
	BNode();
	BNode(T);
	BNode(T, BNode*, BNode*);	
	friend class BST<T>;
public:
	int GetData()const;
};

template <class T>
class BST{
	BNode<T>* root;
	BNode<T>* cursor;
	bool InsertHelp(T e, BNode<T>*&);
	void PrintInHelp(ostream& os, BNode<T>* n);
	void PrintPreHelp(ostream& os, BNode<T>* n);
	void PrintPostHelp(ostream& os, BNode<T>* n);
	BNode<T>* FindHelp(T e, BNode<T>*n); 
	bool RemoveHelp(T e, BNode<T>*&, BNode<T>* parent); 
	int FindMin(BNode<T>* n)const;
	void GoToNextHelp(BNode<T>* n,bool* flag);
	void GoToPrevHelp(BNode<T>*& n,BNode<T>*& pre, BNode<T>*& suc, T key);
	void DeleteNode(BNode<T>*& n);
	int GetHeightHelp(BNode<T>* n)const;
	void PrintInfoHelp(ostream& os, BNode<T>* n);
public:
	BST();
	BST(const BST<T>&);
	~BST();
	BST& operator=(const BST<T>&);
	bool Insert(T e);//cursor at insertion point
	bool Remove(T e);//cursor at parent of removed item or at root
	void PrintPre(ostream&);
	void PrintPost(ostream&);
	void PrintIn(ostream&);
	BNode<T>* Find(T e);//cursor at located node or rightmost node	
	BNode<T>* AtCursor()const;
	void GoToBeginning();
	void GoToEnd();
	void GoToNext();
	void GoToPrev();
	void ClearList();
	void CopyList(BNode<T>*& cpy,BNode<T>* src);// to be called by copy constructor and assignment
	bool Empty()const;
	int GetHeight()const; // return the height of the tree
	void PrintInfo(ostream&); //print the tree inorder, include value, status, child count for each node
};

#include "BST.cpp"
#endif

