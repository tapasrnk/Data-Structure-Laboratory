/*
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include<stdio.h>
#include<stdlib.h>
#define rt return
//Tree Node
struct TreeNode{
    int freq;
    char character;
    struct TreeNode* left;
    struct TreeNode* right;
};
//Heap 
struct MinHeap{
    int size;
    int MAX_SIZE;
    struct TreeNode** array;
};
//creating new node
struct TreeNode* newNode(int f,char c){
    struct TreeNode* temp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    temp->freq=f;
    temp->character=c;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
//creating min heap
struct MinHeap* createMinHeap(int size){
    struct MinHeap* minheap=(struct MinHeap*)malloc(sizeof(struct MinHeap));
    minheap->size=0;
    minheap->MAX_SIZE=size;
    minheap->array=(struct TreeNode**)malloc(minheap->MAX_SIZE*sizeof(struct TreeNode*));
    //printf("fff");
    return minheap;
}
//swap
void swap(struct MinHeap* heap,int i,int j){
    struct TreeNode* temp=heap->array[i];
    heap->array[i]=heap->array[j];
    heap->array[j]=temp;
}
//movedown
void movedown(struct MinHeap* heap, int i) {
    // printf("%d  fff \n",i);
    int n=heap->size;
    int min = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && heap->array[l]->freq < heap->array[min]->freq) min = l;
    if (r < n && heap->array[r]->freq < heap->array[min]->freq) min = r;
    if (min != i) {
        // printf("ttt\n");
        swap(heap, i, min);
        movedown(heap, min);
    }
}
//Extract Minimum
struct TreeNode* extractMinimum(struct MinHeap* heap) {
    int n=heap->size;
    if (n <= 0) {
        printf("\nBinary Heap is empty.\n");
        return NULL;
    }
    // int min = heap->array[0]->freq;
    struct TreeNode* min = heap->array[0];
    heap->array[0]= heap->array[(n) - 1];
    heap->size=n-1;
    movedown(heap, 0);
    return min;
}
//moveup
void moveup(struct MinHeap* heap, int i) {
    int p = (i - 1) / 2;
    if (p >= 0 && heap->array[i]->freq < heap->array[p]->freq) {
        swap(heap, i, p);
        moveup(heap, p);
    }
}
//insert into binary heap
void insertBinaryHeap(struct MinHeap* heap,struct TreeNode* x) {
    int n=heap->size;
    if ((n) == heap->MAX_SIZE) {
        printf("\nBinary Heap is full.\n");
        return;
    }
    (heap->size)=n+1;
    //(*n)++;
    heap->array[n] = x;
    // a[(*n) - 1] = x;
    moveup(heap, (n));
}
//build heap
void buildBinaryHeap(struct MinHeap* heap,struct TreeNode* a[], int n) {
    heap->array=a;
    heap->size=n;
    int i, start;
    start = (n - 2) / 2;
    for (i = start; i >= 0; i--) movedown(heap, i);
}
//printing the array for debug
void print(struct MinHeap* heap){
    int n=heap->size;
    for(int i=0; i<n; i++){
        printf("%d ",heap->array[i]->freq);
    }
}
void print2(struct MinHeap* heap) {
    int n = heap->size;
    for (int i = 0; i < n-1; i++) {
        printf("%d ", heap->array[i]->freq);
    }
}
//dfs for priting
void dfs(struct TreeNode* root,int p[],int k,int n){
    if(!root)return;
    if(root->left==NULL && root->right==NULL){
        printf("%c ",root->character);
        for(int i=0; i<k; i++)
            printf("%d ",p[i]);
        printf("\n");
        p[k]=-1;
        return;
    }
    p[k]=1;
    dfs(root->left,p,k+1,n);
    p[k]=0;
    dfs(root->right,p,k+1,n);
}
int main(){
    //return 0;
    //we can create an array from a text file and run the algorithm accordingly 
    char str[]="adkjigjijiigh";
    int frq[26];
    for(int i=0; i<26; i++){
        frq[i]=0;
    }
    int n=(sizeof(str)/sizeof(str[0]));
    for(int i=0; i<n; i++){
        frq[(int)(str[i]-'a')]++;
    }
    //return 0;
    int size=0;
    for(int i=0; i<n; i++)
        if(frq[i]!=0)
            size++;
    struct TreeNode* arr[size];
    int asg=0;
    for(int i=0; i<26 && asg<size; i++){
        if(frq[i]!=0)
            arr[asg++]=newNode(frq[i],(char)('a'+i));
    }
    struct MinHeap* heap=createMinHeap(30);
    // for(int i=0; i<size; i++){
    //     printf("%d ",arr[i]->freq);
    // }
    // printf("ffff\n");
    buildBinaryHeap(heap,arr,size);
    // printf("fffff\n");
    // insertBinaryHeap(heap,newNode(1,'r'));
    // insertBinaryHeap(heap,newNode(0,'t'));
    // print(heap);
    // printf("\n");
    // extractMinimum(heap);
    // print(heap);
    // printf("\n");
    // extractMinimum(heap);
    // print(heap);
    // printf("\n");
    // extractMinimum(heap);
    // printf("%d \n", heap->size);
    // print(heap);
    // printf("\n");
    while(heap->size>1){
        // print(heap);
        // printf("\n");
        struct TreeNode* m1 = extractMinimum(heap);
        struct TreeNode* m2 = extractMinimum(heap);
        struct TreeNode* temp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        temp->freq=m1->freq+m2->freq;
        temp->character='$';
        temp->left=m1;
        temp->right=m2;
        insertBinaryHeap(heap,temp);
    }
    struct TreeNode* root = extractMinimum(heap);
    int p[30];
    for(int i=0; i<30; i++)p[i]=-1;
    dfs(root,p,0,30);

    return 0;
}