/*-------------------------------------------------------*/
//CS355 Assignment 1
//Dr. Janet Jenkins
//
//Binary Search Tree by Victor Rogers, Martin Tuck, Tyler Yasaka
/*-------------------------------------------------------*/

#include "BST.h"

/*---------------------------------------------*/
//BNode class
/*---------------------------------------------*/
template <class T>
BNode<T>::BNode():left(NULL),right(NULL){   
}

template <class T>
BNode<T>::BNode(T item):data(item),left(NULL),right(NULL){
}

template <class T>
BNode<T>::BNode(T item, BNode* l, BNode* r):data(item),left(l),right(r){
}

template <class T>
int BNode<T>::GetData()const{
		return data;
}

/*---------------------------------------------*/
//Insert Helper
/*---------------------------------------------*/
template <class T>
bool BST<T>::InsertHelp(T e, BNode<T>*& n){
    if(n==NULL){
        n=new BNode<T>(e);
        cursor=n;
        return true;
    }
    else if(e<n->data) {
        return InsertHelp(e,n->left);
    }
    else if(e>n->data) {
        return InsertHelp(e,n->right);
    }
    else{//if e==n->data
        cout << "No duplicates allowed. :(" << endl;
        return false;
    }
}

/*---------------------------------------------*/
//PrintIn Helper
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintInHelp(ostream& os, BNode<T>* n){
    if(n!=NULL){
        //Print Left Subtree
        if(n->left!=NULL)
            PrintInHelp(os,n->left);
        //Print Root
        if(n==cursor) os << "[" << n->data << "]";
        else os << n->data;
        os << "\t";
        //Print Right Subtree
        if(n->right!=NULL)
            PrintInHelp(os,n->right);
    }
}

/*---------------------------------------------*/
//PrintPre Helper
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintPreHelp(ostream& os, BNode<T>* n){
    if(n!=NULL){
        //Print Root
        if(n==cursor) os << "[" << n->data << "]";
        else os << n->data;
        os << "\t";
        //Print Left Subtree
        if(n->left!=NULL)
            PrintPreHelp(os,n->left);
        //Print Right Subtree
        if(n->right!=NULL)
            PrintPreHelp(os,n->right);
    }
}

/*---------------------------------------------*/
//PrintPost Helper
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintPostHelp(ostream& os, BNode<T>* n){
    if(n!=NULL){
        //Print Left Subtree
        if(n->left!=NULL)
            PrintPostHelp(os,n->left);
        //Print Right Subtree
        if(n->right!=NULL)
            PrintPostHelp(os,n->right);
        //Print Root
        if(n==cursor) os << "[" << n->data << "]";
        else os << n->data;
        os << "\t";
    }
}

/*---------------------------------------------*/
//Find Helper
/*---------------------------------------------*/
template <class T>
BNode<T>* BST<T>::FindHelp(T e, BNode<T>*n){
	if(n==NULL){
		//Moves cursor to end of list if not found
		GoToEnd();
		return NULL;
	}
	else if(n->data==e){
		cursor=n;
		return n;
	}
	else if(e<n->data)
		return FindHelp(e,n->left);
	else //if(e > n->data)
		return FindHelp(e,n->right);
}

/*---------------------------------------------*/
//Remove Helper
/*---------------------------------------------*/
template <class T>
bool BST<T>::RemoveHelp(T e, BNode<T>*& n, BNode<T>* parent){
	if(n==NULL){
		return false;
	}
	else if(e==n->data){
		//Scenario 1: no children
		if(n->left==NULL&&n->right==NULL){
		    delete n;
			n=NULL;
		}
		//Scenario 2: 1 child, left
		else if(n->right==NULL){
			BNode<T>* temp=n;
			n=n->left;
			delete temp;
		}
		//Scenario 3: 1 child, right
		else if(n->left==NULL){
			BNode<T>* temp=n;
			n=n->right;
			delete temp;
		}
		//Scenario 4: 2 children
		else{
			T minright=FindMin(n->right);
			RemoveHelp(minright,n->right,n);
			n->data=minright;
		}
		if(parent!=NULL) cursor=parent;
		else cursor=root;
		return true;
	}
	else if(e<n->data)
		return RemoveHelp(e,n->left,n);
	else
		return RemoveHelp(e,n->right,n);
}

/*---------------------------------------------*/
//Destructor Helper
/*---------------------------------------------*/
template <class T>
void BST<T>::DeleteNode(BNode<T>*& n){
	if(n!=NULL){
		DeleteNode(n->left);
		DeleteNode(n->right);
	}
	delete n;
}

/*---------------------------------------------*/
//Find Minimum
/*---------------------------------------------*/
template <class T>
int BST<T>::FindMin(BNode<T>* n)const{
	if(n->left!=NULL)
		return FindMin(n->left);
	else
		return n->data;
}


/*---------------------------------------------*/
//GoToPrev Helper
/*---------------------------------------------*/
template <class T>
void BST<T>::GoToPrevHelp(BNode<T>*& n,BNode<T>*& pre, BNode<T>*& suc, T key){
	
	if(!n) return;
	
	if(n->data == key){
		if(n->left){
			BNode<T>* temp = n->left;
			while(temp->right)
				temp = temp->right;
			pre = temp;
		}
		
		if(n->right != NULL){
			BNode<T>* temp = n->right;
			while(temp->left)
				temp = temp->left;
		}
		return;
	}
	
	if(n->data > key){
		suc = n;
		GoToPrevHelp(n->left,pre,suc,key);
	}
	else{
		pre = n;
		GoToPrevHelp(n->right, pre, suc, key);
	}
	
}

/*---------------------------------------------*/
//GetHeight Helper
/*---------------------------------------------*/
template <class T>
int BST<T>::GetHeightHelp(BNode<T>* n)const{
	if(n!=NULL) {
		int left=GetHeightHelp(n->left);
		int right=GetHeightHelp(n->right);
		if(left>right)
			return left+1;
		else
			return right+1;
		}
	else
		return 0;
}

/*---------------------------------------------*/
//PrintInfo Helper
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintInfoHelp(ostream& os, BNode<T>* n){
    if(n!=NULL){
        //Print Left Subtree
        if(n->left!=NULL)
            PrintInfoHelp(os,n->left);
        //Print Root
        int children=0;
        if(n->left!=NULL)children++;
        if(n->right!=NULL) children++;
        os << n->data << "\t\t" << children;
        cout << "\t\t";
        if(n==root) cout << "X";
        else cout << "-";
        cout << "\t\t";
        if(n==cursor) cout << "X";
        else cout << "-";
        cout << endl;
        //Print Right Subtree
        if(n->right!=NULL)
            PrintInfoHelp(os,n->right);
    }
}

/*---------------------------------------------*/
//Constructor
/*---------------------------------------------*/
template <class T>
BST<T>::BST():root(NULL),cursor(NULL){
}

/*---------------------------------------------*/
//Copy Constructor
/*---------------------------------------------*/
template <class T>
BST<T>::BST(const BST<T>& sourcetree){
	CopyList(root,sourcetree.root);
	
	if(root)
		cursor = root;
}

/*---------------------------------------------*/
//Destructor
/*---------------------------------------------*/
template <class T>
BST<T>::~BST(){
	ClearList();
}

/*---------------------------------------------*/
//Assignment Operator
/*---------------------------------------------*/
template <class T>
BST<T>& BST<T>::operator=(const BST<T>& sourcetree){
	CopyList(root,sourcetree.root);
    return *this;
}

/*---------------------------------------------*/
//To be called by copy constructor & assignment
//
//I added 2 parameters to this, as I feel they are necessary.
//-Tyler
/*---------------------------------------------*/
template <class T>
void BST<T>::CopyList(BNode<T>*& cpy, BNode<T>* src){
	cpy = new BNode<T>;
	if(src!=NULL){
		cpy->data=src->data;
		CopyList(cpy->left,src->left);
		CopyList(cpy->right,src->right);
	}
	else cpy=NULL;
}

/*---------------------------------------------*/
//Insert
/*---------------------------------------------*/
template <class T>
bool BST<T>::Insert(T e){
    return InsertHelp(e,root);
}

/*---------------------------------------------*/
//Remove
/*---------------------------------------------*/
template <class T>
bool BST<T>::Remove(T e){
	return RemoveHelp(e,root,NULL);
}

/*---------------------------------------------*/
//Find
/*---------------------------------------------*/
template <class T>
BNode<T>* BST<T>::Find(T e){
    return FindHelp(e,root);//Note: this returns NULL if not found
}

/*---------------------------------------------*/
//Pre-order
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintPre(ostream& os){
	PrintPreHelp(os,root);
}

/*---------------------------------------------*/
//In-order
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintIn(ostream& os){
    PrintInHelp(os,root);
}

/*---------------------------------------------*/
//Post-order
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintPost(ostream& os){
	PrintPostHelp(os,root);
}

/*---------------------------------------------*/
//Returns the cursor
/*---------------------------------------------*/
template <class T>
BNode<T>* BST<T>::AtCursor()const {
	return cursor;
}

/*---------------------------------------------*/
//Moves Cursor to beginning of list (smallest item)
/*---------------------------------------------*/
template <class T>
void BST<T>::GoToBeginning(){
	if(root!=NULL){
		cursor=root;
		while(cursor->left!=NULL){
			cursor=cursor->left;
		}
	}
}

/*---------------------------------------------*/
//Moves Cursor to end of list (largest item)
/*---------------------------------------------*/
template <class T>
void BST<T>::GoToEnd(){
	if(root!=NULL){
		cursor=root;
		while(cursor->right!=NULL){
			cursor=cursor->right;
		}
	}
}

/*---------------------------------------------*/
//Moves Cursor to next largest item
/*---------------------------------------------*/
template <class T>
void BST<T>::GoToNext(){
	if( !root || !cursor){
		cursor = 0;
		return;
	}
	BNode<T>* newCur = 0;
	BNode<T> * c = root;
	BNode<T> * p = root;
	bool flag = false;
	//if cursor has right child;
	if(cursor->right){
		newCur = cursor->right;
		while(newCur->left)
			newCur = newCur->left;
		flag = true;
	}
	//if no right children
	else{
		while(c){
			if(c->data>cursor->data){
				p = c;
				flag = true;
				c= c->left;
			}
			else if(c->data<cursor->data){
				c = c->right;
			}
			else{
				
				newCur = p;
				c = 0;
			} 
		}
	}
	
	
	if(flag)
		cursor = newCur;
	//cursor is at largest number
	else{
		newCur = root;
		while(newCur->left)
			newCur = newCur->left;
		cursor = newCur;
	}
		
		

}

/*---------------------------------------------*/
//Moves Cursor to next smallest item
/*---------------------------------------------*/
template <class T>
void BST<T>::GoToPrev(){
	if(root && cursor){
		BNode<T> * pre = 0;
		BNode<T> * suc = 0;
		GoToPrevHelp(root,pre,suc,cursor->data);
		if(!pre){
			if(root->right){
				pre=root->right;
				while(pre->right)
					pre = pre->right;
			}
			else
				pre = root;
		}
		cursor = pre;
		
	}
	else
		cursor = 0;
}

/*---------------------------------------------*/
//Clears the list
/*---------------------------------------------*/
template <class T>
void BST<T>::ClearList(){
	DeleteNode(root);
	root=NULL;
	cursor=NULL;
}

/*---------------------------------------------*/
//Checks for empty list
/*---------------------------------------------*/
template <class T>
bool BST<T>::Empty()const{
	if(root==NULL) return true;
	else return false;
}

/*---------------------------------------------*/
//Returns height of tree.
//My interpretation of height is the number of
//rows it would have if drawn on a whiteboard
/*---------------------------------------------*/
template <class T>
int BST<T>::GetHeight()const{
	return GetHeightHelp(root);
}

/*---------------------------------------------*/
//Print info
/*---------------------------------------------*/
template <class T>
void BST<T>::PrintInfo(ostream& os){
	cout << endl << "Tree nodes:" << endl;
	cout << "Value" << "\t\t" << "Children" << "\t"
	<< "Root" << "\t\t" << "Cursor" << endl;
    PrintInfoHelp(os,root);
    cout << endl;
}
