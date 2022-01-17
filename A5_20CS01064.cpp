#include <bits/stdc++.h>
using namespace std;
#define Node struct Node
Node {
    int val;
    Node* left;
    Node* right;
};
//for creating new node
Node* newnode(int k) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->val = k;
    temp->right = NULL;
    temp->left = NULL;
    return temp;
}

//for postorder travesal
void post(Node* root) {
    if (root == NULL) {
        return;
    }
    post(root->left);
    post(root->right);
    cout << root->val << " ";
}

//for buliding the tree
int indexI = 0;
Node* build_tree(int pre[], int in[], int lo, int hi) {
    if (lo > hi) return NULL;

    Node* temp = newnode(pre[indexI]);
    temp->right = NULL;
    temp->left = NULL;
    indexI++;

    if (lo == hi) return temp;

    int inindex;
    for (int i = lo; i <= hi; i++) {
        if (in[i] == temp->val) {
            inindex = i;
            break;
        }
    }

    temp->left = build_tree(in, pre, lo, inindex - 1);
    temp->right = build_tree(in, pre, inindex + 1, hi);

    return temp;
}

//merge
void merge(int arr[],int lo,int mid,int hi){
    int in[hi-lo+1];
    int i=lo,j=mid+1,ass=0;
    while(i<=mid && j<=hi){
        if(arr[i]<=arr[j]){
            in[ass++]=arr[i++];
        }
        else{
            in[ass++]=arr[j++];
        }
    }
    while(i<=mid){
        in[ass++]=arr[i++];
    }
    while(j<=hi){
        in[ass++]=arr[j++];
    }
    ass=0;
    for(int k=lo; k<=hi; k++){
        arr[k]=in[ass++];
    }
}

//mrege sort
void merge_sort(int arr[],int lo,int hi){
    if(lo>=hi)return;
    int mid=(lo+(hi-lo)/2);
    merge_sort(arr,lo,mid);
    merge_sort(arr,mid+1,hi);
    merge(arr,lo,mid,hi);
}

//q1
Node* q1() {
    int n;

    cout << "Size of tree\n";

    cin >> n;

    cout << "preorder\n";

    int pre[n];
    int in[n];

    for (int i = 0; i < n; i++) {
        cin >> pre[i];
        in[i] = pre[i];
    }

    merge_sort(in, 0, n - 1);
    Node* root = build_tree(pre, in, 0, n - 1);

    cout<<"postorder is \n";
    post(root);
    cout<<"\n";
    return root;
}

//lca
Node* lca(Node* root, int a, int b) {
    if (root == NULL) {
        return NULL;
    }

    if (root->val > a && root->val > b) {
        return lca(root->right, a, b);
    } else if (root->val < a && root->val < b) {
        return lca(root->left, a, b);
    }

    return root;
}

//q2
void q2(Node* root) {
    cout << "lowest common ansistor of a and b \n input a and b\n";
    int a, b;
    cin >> a >> b;

    Node* temp = lca(root, a, b);
    if (temp != NULL) {
        cout << "Found\n";
        cout << temp->val << "\n";
    } else {
        cout << "Not Found\n";
    }
}

//leaves printing
void print_leaves(Node* root) {
    if (root == NULL) return;

    print_leaves(root->left);

    if (!(root->left) && !(root->right)) cout << root->val << " ";

    print_leaves(root->right);
}

//left printing
void print_left(Node* root) {
    if (root == NULL) return;

    if (root->left) {
        cout << root->val << " ";
        print_left(root->left);
    } else if (root->right) {
        cout << root->val << " ";
        print_left(root->right);
    }
}

//right printing
void print_right(Node* root) {
    if (root == NULL) return;

    if (root->right) {
        print_right(root->right);
        cout << root->val << " ";
    } else if (root->left) {
        print_right(root->left);
        cout << root->val << " ";
    }
}

//q3
void q3(Node* root) {
    if (root == NULL) return;

    cout << root->val << " ";

    print_left(root->left);

    print_leaves(root->left);
    print_leaves(root->right);

    print_right(root->right);
    cout<<"\n";
}

//mirror the tree
void mirror(Node* root) {
    if (root == NULL)
        return;
    else {
        mirror(root->left);
        mirror(root->right);
        Node* temp;
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    return;
}

//q4
void q4(Node* root) { mirror(root); }

// merge
int merge2(int arr[], int lo, int mid, int hi) {
    int in[hi - lo + 1];
    int i = lo, j = mid + 1, ass = 0,inversion=0;
    while (i <= mid && j <= hi) {
        if (arr[i] <= arr[j]) {
            in[ass++] = arr[i++];
        } else {
            in[ass++] = arr[j++];
            inversion+=mid-i+1;
        }
    }
    while (i <= mid) {
        in[ass++] = arr[i++];
    }
    while (j <= hi) {
        in[ass++] = arr[j++];
    }
    ass = 0;
    for (int k = lo; k <= hi; k++) {
        arr[k] = in[ass++];
    }
    return inversion;
}

// mrege sort
int merge_sort2(int arr[], int lo, int hi) {
    int inversion=0;
    if (lo >= hi) return 0;
    int mid = (lo + (hi - lo) / 2);
    inversion+=merge_sort2(arr, lo, mid);
    inversion+=merge_sort2(arr, mid + 1, hi);
    inversion+=merge2(arr, lo, mid, hi);
    return inversion;
}

//q5
void q5() {
    int n;
    cout<<"Size of array\n";
    cin >> n;
    int arr[n];
    cout<<"Enter elements\n";
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    cout<<merge_sort2(arr,0,n-1);
}
// main function
int main() {
    Node* root;
    while (1) {
        cout << "Please Enter Question Number:\n";
        int i = 1;
        cin >> i;
        if (i == 1) {
            root = q1();
        } else if (i == 2) {
            q2(root);
        } else if (i == 3) {
            q3(root);
        } else if (i == 4) {
            q4(root);
        } else if (i == 5) {
            q5();
        } else if (i == -1) {
            exit(-1);
        }
    }
}