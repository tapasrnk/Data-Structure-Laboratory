#include<bits/stdc++.h>
using namespace std;
#define Node struct Node
//Node struct
Node{
    int val;
    Node* left;
    Node* right;
};
//Function for newnode
Node* newnode(int k){
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->val=k;
    temp->right=NULL;
    temp->left=NULL;
    return temp;
}
//search for index of a given value in inorder 
int found(vector<int>&in,int start,int end,int to_found){
    for(int i=start; i<=end; i++){
        if(in[i]==to_found){
            return i;
        }
    }
    return 0;
}
//building the tree
Node* buildtree(vector<int>&post,vector<int>&in,int start,int end,int* index){
    if(start>end){
        return NULL;
    }
    Node* temp=newnode(post[*index]);
    (*index)--;
    if(start==end){
        return temp;
    }
    //searching for index in inorder
    int next_index=found(in,start,end,temp->val);
    //building the right
    temp->right =buildtree(post, in, next_index+1, end, index);
    //building the left
    temp->left=buildtree(post,in,start,next_index-1,index);
    return temp;
}
//Q2
void q2(Node* root) {
    cout << "Printing the inordered of tree\n";
    //if tree is null 
    if (root == NULL) {
        cout << "NULL Tree\n";
        return;
    }
    Node* cur = root;
    stack<Node*> s;
    while (cur != NULL || !s.empty()) {
        while (cur != NULL) {
            s.push(cur);
            cur = cur->left;
        }
        cur= s.top();
        s.pop();
        cout << cur->val << " ";
        cur = cur->right;
    }
    cout<<"\n";
}
//Q3
void q3(Node* root) {
    cout << "Printing the levelorder of tree\n";
    //if tree is null
    if (root == NULL) {
        cout << "NULL Tree\n";
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        cout << temp->val << " ";
        //check for left child
        if (temp->left != NULL) 
            q.push(temp->left);
        //check for right child
        if (temp->right != NULL) 
            q.push(temp->right);
    }
    cout << "\n";
}
//Q1
void q1(){
    int n;
    cout<<"n\n";
    cin >> n;
    cout<<"Enter postorder\n";
    vector<int>post(n);
    vector<int>in(n);
    //input for postorder
    for(int i=0; i<n; i++){
        cin >> post[i];
    }
    cout<<"Enter Inorder\n";
    //input for inorder
    for(int i=0; i<n; i++){
        cin >> in[i];
    }
    int index=n-1;
    //building the tree
    Node* out=buildtree(post,in,0,n-1,&index);
    //printing the inorder
    q2(out);
    //printing the levelorder
    q3(out);

}
//main function
int main(){
    cout<<"Please Enter Question Number:\n";
    while(1){
        int i=1;
        cin >> i;
        if(i==1){
            q1();
        }
        else if(i==2){
            cout<<"Question 2 should be called in Question 1 after cereating a tree\n";
        }
        else if(i==3){
            cout<<"Question 3 should be called in Question 1 after cereating a tree\n";
        }
        else if(i==-1){
            exit(-1);
        }
    }
}