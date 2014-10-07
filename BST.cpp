/*---------------------------------------------*/
//BNode class
/*---------------------------------------------*/
BNode::BNode():left(NULL),right(NULL){
}
BNode::BNode(int item):data(item),left(NULL),right(NULL){
}
BNode::BNode(int item, BNode* l, BNode* r):data(item),left(l),right(r){
}
int BNode::GetData()const{
return data;
}
/*---------------------------------------------*/
//Insert Helper
/*---------------------------------------------*/
bool BST::InsertHelp(int e, BNode*& n){
if(n==NULL){
n=new BNode(e);
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
void BST::PrintInHelp(ostream& os, BNode* n){
if(n!=NULL){
//Print Left Subtree
if(n->left!=NULL)
PrintInHelp(os,n->left);
//Print Root
os << n->data << " ";
//Print Right Subtree
if(n->right!=NULL)
PrintInHelp(os,n->right);
}
}
/*---------------------------------------------*/
//PrintPre Helper
/*---------------------------------------------*/
void BST::PrintPreHelp(ostream& os, BNode* n){
if(n!=NULL){
//Print Root
os << n->data << " ";
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
void BST::PrintPostHelp(ostream& os, BNode* n){
if(n!=NULL){
//Print Left Subtree
if(n->left!=NULL)
PrintPostHelp(os,n->left);
//Print Right Subtree
if(n->right!=NULL)
PrintPostHelp(os,n->right);
//Print Root
os << n->data << " ";
}
}
/*---------------------------------------------*/
//Find Helper
/*---------------------------------------------*/
BNode* BST::FindHelp(int e, BNode*n){
if(n==NULL)
return NULL;
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
bool BST::RemoveHelp(int e, BNode*& n){
if(n==NULL)
return false;
else if(e==n->data){
//Scenario 1: no children
if(n->left==NULL&&n->right==NULL){
delete n;
n=NULL;
}
//Scenario 2: 1 child, left
else if(n->right==NULL){
BNode* temp=n;
n=n->left;
delete temp;
}
//Scenario 3: 1 child, right
else if(n->left==NULL){
BNode* temp=n;
n=n->right;
delete temp;
}
//Scenario 4: 2 children
else{
int minright=FindMin(n->right);
RemoveHelp(minright,n);
n->data=minright;
}
cursor=root;
return true;
}
else if(e<n->data)
return RemoveHelp(e,n->left);
else
return RemoveHelp(e,n->right);
}
/*---------------------------------------------*/
//Destructor Helper
/*---------------------------------------------*/
void BST::DeleteNode(BNode*& n){
if(n!=NULL){
DeleteNode(n->left);
DeleteNode(n->right);
}
delete n;
}
/*---------------------------------------------*/
//Find Minimum
/*---------------------------------------------*/
int BST::FindMin(BNode* n)const{
if(n->left!=NULL)
return FindMin(n->left);
else
return n->data;
}
/*---------------------------------------------*/
//GoToNext Helper
/*---------------------------------------------*/
void BST::GoToNextHelp(BNode* n,bool* flag){
if(n!=NULL){
//Traverse left subtree
if(n->left!=NULL)
GoToNextHelp(n->left,flag);
//Check n
if(*flag) {
cursor=n;
*flag=false;
return;
}
if(n==cursor)
*flag=true;
//Traverse Right Subtree
if(n->right!=NULL)
GoToNextHelp(n->right,flag);
}
}
/*---------------------------------------------*/
//GoToPrev Helper
/*---------------------------------------------*/
void BST::GoToPrevHelp(BNode* n,bool* flag){
if(n!=NULL){
//Traverse Right Subtree
if(n->right!=NULL)
GoToPrevHelp(n->right,flag);
//Check n
if(*flag) {
cursor=n;
*flag=false;
return;
}
if(n==cursor)
*flag=true;
//Traverse left subtree
if(n->left!=NULL)
GoToPrevHelp(n->left,flag);
}
}
/*---------------------------------------------*/
//GetHeight Helper
/*---------------------------------------------*/
int BST::GetHeightHelp(BNode* n)const{
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
void BST::PrintInfoHelp(ostream& os, BNode* n){
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
BST::BST():root(NULL),cursor(NULL){
}
/*---------------------------------------------*/
//Copy Constructor
/*---------------------------------------------*/
BST::BST(const BST& sourcetree){
CopyList(root,sourcetree.root);
}
/*---------------------------------------------*/
//Destructor
/*---------------------------------------------*/
BST::~BST(){
DeleteNode(root);
}
/*---------------------------------------------*/
//Assignment Operator
/*---------------------------------------------*/
BST& BST::operator=(const BST& sourcetree){
CopyList(root,sourcetree.root);
}
/*---------------------------------------------*/
//To be called by copy constructor & assignment
//
//I added 2 parameters to this, as I feel they are necessary.
//-Tyler
/*---------------------------------------------*/
void BST::CopyList(BNode*& cpy,BNode* src){
cpy = new BNode;
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
bool BST::Insert(int e){
return InsertHelp(e,root);
}
/*---------------------------------------------*/
//Remove
/*---------------------------------------------*/
bool BST::Remove(int e){
return RemoveHelp(e,root);
}
/*---------------------------------------------*/
//Find
/*---------------------------------------------*/
BNode* BST::Find(int e){
return FindHelp(e,root);//Note: this returns NULL if not found
}
/*---------------------------------------------*/
//Pre-order
/*---------------------------------------------*/
void BST::PrintPre(ostream& os){
PrintPreHelp(os,root);
}
/*---------------------------------------------*/
//In-order
/*---------------------------------------------*/
void BST::PrintIn(ostream& os){
PrintInHelp(os,root);
}
/*---------------------------------------------*/
//Post-order
/*---------------------------------------------*/
void BST::PrintPost(ostream& os){
PrintPostHelp(os,root);
}
/*---------------------------------------------*/
//Returns the cursor
/*---------------------------------------------*/
BNode* BST::AtCursor()const {
return cursor;
}
/*---------------------------------------------*/
//Moves Cursor to beginning of list (smallest item)
/*---------------------------------------------*/
void BST::GoToBeginning(){
cursor=root;
while(cursor->left!=NULL){
cursor=cursor->left;
}
}
/*---------------------------------------------*/
//Moves Cursor to end of list (largest item)
/*---------------------------------------------*/
void BST::GoToEnd(){
cursor=root;
while(cursor->right!=NULL){
cursor=cursor->right;
}
}
/*---------------------------------------------*/
//Moves Cursor to next largest item
/*---------------------------------------------*/
void BST::GoToNext(){
bool* flag=new bool;
GoToNextHelp(root,flag);
}
/*---------------------------------------------*/
//Moves Cursor to next smallest item
/*---------------------------------------------*/
void BST::GoToPrev(){
bool* flag=new bool;
GoToPrevHelp(root,flag);
}
/*---------------------------------------------*/
//Clears the list
/*---------------------------------------------*/
void BST::ClearList(){
DeleteNode(root);
root=NULL;
}
/*---------------------------------------------*/
//Checks for empty list
/*---------------------------------------------*/
bool BST::Empty()const{
if(root==NULL) return true;
else return false;
}
/*---------------------------------------------*/
//Returns height of tree.
//My interpretation of height is the number of
//rows it would have if drawn on a whiteboard
/*---------------------------------------------*/
int BST::GetHeight()const{
return GetHeightHelp(root);
}
/*---------------------------------------------*/
//Print info
/*---------------------------------------------*/
void BST::PrintInfo(ostream& os){
cout << endl << "Tree nodes:" << endl;
cout << "Value" << "\t\t" << "Children" << "\t"
<< "Root" << "\t\t" << "Cursor" << endl;
PrintInfoHelp(os,root);
cout << endl;
}
