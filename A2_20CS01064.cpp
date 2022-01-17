#include <bits/stdc++.h>
using namespace std;
#define nax 10000
void ans1() {
    //number of guards
    int n;
    cin >> n;

    //heights of guards
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        v.push_back({temp, i});
    }

    //evaluating the answer using stack
    vector<int> ans(n, -1);
    stack<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && s.top().first < v[i].first) {
            ans[s.top().second] = v[i].second;
            s.pop();
        }
        s.push(v[i]);
    }

    while (!s.empty()) {
        ans[s.top().second] = -1;
        s.pop();
    }

    //printing the answer
    for (int i = 0; i < n; i++) {
        cout << i << "->" << ans[i] << " ";
    }
    cout << "\n";
}

//size of 2D matrix 
int n, m;

//moves
vector<pair<int, int>> moves = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

//visited array
bool isVisited[nax][nax];

//2D matrix
int arr[nax][nax];

//checking for valid move
bool isValid(int x, int y) {
    if (isVisited[x][y] || (x < 0 || y < 0 || x >= n || y >= m) ||
        (arr[x][y] == 0)) {
        return false;
    }
    return true;
}

void ans2() {
    memset(isVisited, false, sizeof(isVisited));
    cin >> n >> m;
    int i1, j1, i2, j2;
    cin >> i1 >> j1 >> i2 >> j2;

    //cosidering top to bottom row indexing (genral way to taking input for 2D matrix)
    for (int i = 0 ; i <n ; i++) {
        for (int j = 0 ; j <m ; j++) {
            cin >> arr[i][j];
        }
    }

    //if cosider bottom to top row indexing (as given in assignment example)
    /*for (int i = n; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }*/

    //stroing the parents
    pair<int, int> parent[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            parent[i][j] = {-1, -1};
        }
    }

    stack<pair<int, int>> s;
    s.push({i1, j1});
    parent[i1][j1]={-1,-1};
    int i = i1, j = j1;

    //moving in grid using stack
    while (!s.empty()) {
        pair<int, int> temp;
        temp = s.top();
        s.pop();
        if (!isVisited[temp.first][temp.second]) {
            isVisited[temp.first][temp.second] = true;
        }
        if(temp.first==i2&&temp.second==j2){
            break;
        }
        for (auto it : moves) {
            int x = temp.first+it.first;
            int y = temp.second+it.second;
            if (isValid(x, y)) {
                s.push({x, y});
                parent[x][y]={temp.first,temp.second};
            }
        }
    }

    //storing answer
    vector<pair<int, int>> ans;
    if (isVisited[i2][j2]) {
        ans.push_back({i2,j2});
        pair<int, int> p=parent[i2][j2];
        while (p.first != -1 || p.second != -1) {
            ans.push_back({p.first,p.second});
            p = parent[p.first][p.second];
        }
    }

    //printing the answer
    reverse(ans.begin(),ans.end());
    for(auto it:ans){
        cout<<"<"<<it.first<<","<<it.second<<">";
    }
    cout<<"\n";
}
signed main() {
    while (1) {
        cout << "Please Enter Question No: (Enter 0 to exit)"
             << "\n";
        int Q;
        cin >> Q;
        if (Q == 1) {
            ans1();
        } else if (Q == 2) {
            ans2();
        } else if (Q == 0) {
            exit(0);
        } else {
            cout << "Invalid output\n";
        }
    }

    return 0;
}