#include<bits/stdc++.h>
using namespace std;
//struct for HashTable
struct HashTable{
    vector<pair<string,double>>arr;
    int s;
    int n;
    int d;
    double lamda;
    double delta;
};
//for checking prime
bool IsPrime(int number) {
    if (number == 2 || number == 3) return true;

    if (number % 2 == 0 || number % 3 == 0) return false;

    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number) {
        if (number % (divisor - 1) == 0) return false;

        if (number % (divisor + 1) == 0) return false;

        divisor += 6;
    }

    return true;
}
//for next prime
int nextPrime(int a) {
    while (!IsPrime(++a)) {
    }
    return a;
}
//Department array
string DEPT[23] = {"AE", "AG", "AR", "BT", "CE", "CH", "CS", "CY", "EC", "EE", "EX",
"GG", "HS", "IE", "IM", "MA", "ME", "MF", "MI", "MT", "NA", "PH", "QD" };
int bs(string dept){
    int lo=0;
    int hi=22;
    while(lo<hi){
        int mid=lo+(hi-lo)/2;
        if(DEPT[mid]==dept){
            return mid;
        }
        else if(DEPT[mid]<dept){
            lo=mid+1;
        }
        else{
            hi=mid-1;
        }
    }
    return 0;
}
//Custom hash function 
int custom_hash(string rollno,int s,int i=0){
    string r;
    r+=rollno[0];
    r+=rollno[1];
    for(int j=4; j<9; j++){
        r+=rollno[j];
    }
    string dept;
    dept+=rollno[2];
    dept+=rollno[3];
    int index=0;
    index=bs(dept);
    int h = (stoi(r)+index+(i*i))%s;
    return h;
}
//creating hash table
struct HashTable* CreateEmptyHashTable(int k){
    int next = nextPrime(2*k);
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    table->arr.resize(next);
    table->s=table->arr.size();
    table->n=0;
    for(int i=0; i<table->s; i++){
        table->arr[i].second=-1;
    }
    return table;
}
//searching
int srch(struct HashTable* table,string r){
    // //int ind = custom_hash(r, table->s);
    // cout<<"s is "<<table->s<<" \n";
    int i=0;
    while (table->arr[custom_hash(r, table->s, i)].second != -2 &&
           table->arr[custom_hash(r, table->s, i)].second != -1 && table->arr[custom_hash(r,table->s,i)].first!=r) {
        // cout << custom_hash(r, table->s, i)<<"\n";
        i++;
    }
    if((table->arr[custom_hash(r,table->s,i)].second==-1 || table->arr[custom_hash(r,table->s,i)].second==-2)){
        //cout<<"Not Found\n";
        return -1;
    }
    // cout << "Custum hash " << custom_hash(r, table->s, i) << "\n";
    return custom_hash(r,table->s,i);
}
//inserting
void insert(struct HashTable* table, string r,double cgpa) ;
//reshash
void rehash(struct HashTable* table, int k) {
    cout<<"Rehasing please wait\n";
    vector<pair<string,double>>temp=table->arr;
    table->arr.resize(0);
    table->arr.resize(k);
    for(int i=0; i<table->arr.size(); i++){
        table->arr[i].second=-1;
    }
    table->s=k;
    table->d = 0;
    table->n=0;
    table->delta = 0;
    for(int i=0; i<temp.size(); i++){
        if(!(temp[i].second==-1 || temp[i].second==-2)){
            insert(table,temp[i].first,temp[i].second);
        }
    }
    table->lamda = (double)(table->n) / (double)(table->s);
}
//inserting
void insert(struct HashTable* table,string r,double cgpa){
    int i=0;
    while (table->arr[custom_hash(r, table->s, i)].second != -2 && table->arr[custom_hash(r, table->s, i)].second != -1){
        i++;
    }
    //return;
    // cout<<"Inserting at index "<<custom_hash(r,table->s,i)<<" \n";
    // cout<<"S is "<<table->s<<" \n";
    table->arr[custom_hash(r,table->s,i)]={r,cgpa};
    (table->n)=(table->n)+1;
    (table->lamda)=(double)(table->n)/(double)(table->s);
    if(table->lamda>0.5){
        rehash(table,nextPrime(2*table->n));
    }
}
//delete 
void del(struct HashTable* table,string r){
    int t=srch(table,r);
    if(t==-1){
        cout<<"Roll No does not exist \n";
        return ;
    }
    (table->arr)[t].second=-2;
    (table->d)=(table->d)+1;
    (table->delta)=(double)(table->d)/(double)(table->s);
    if(table->delta>0.2){
        rehash(table,table->s);
    }
}
//printing table
void print(struct HashTable* table){
    cout<<"~~~~~~~~~  Printing Table ~~~~~\n";
    for(auto it:table->arr){
        cout<<it.first<<" "<<it.second<<"\n";
    }
    cout<<"s: "<<table->s<<", ";
    cout<<"n: "<<table->n<<" \n";
    cout<<"delat: "<<table->delta<<", ";
    cout<<"lamda: "<<table->lamda<<" \n";
    cout<<"~~~~~~~~~  End of Table ~~~~~~~\n";
}
int main(){
    cout<< "Enter value of K\n";
    int k;
    cin >> k;
    struct HashTable* table=CreateEmptyHashTable(k);
    print(table);
    for(int i=0; i<k; i++){
        string s;
        double c;
        cin >> s;
        cin >> c;
        insert(table,s,c);
        print(table);
    }
    cout<<"1. for search , 2. for insert , 3. for delete , 4. for exit\n";
    int input=0;
    while(1){
        cout << "input \n";
        cin >> input;
        //search
        if(input==1){
            string s;
            cin >> s;
            int i=srch(table,s);
            if(i==-1){
                cout<<"Not found\n";
            }
            else{
                cout<<"index "<<i<<" \n";
                cout<<"Cgpa of "<<table->arr[i].first<<" is "<<table->arr[i].second<<"\n";
            }
            //print(table);
        }
        else if(input==2){
            //insert
            string s;
            cin >> s;
            double c;
            cin >> c;
            insert(table,s,c);
            print(table);
        }
        else if(input==3){
            //delete
            string s;
            cin >> s;
            del(table,s);
            print(table);
        }
        else{
            exit(0);
        }
    }
    return 0;
}