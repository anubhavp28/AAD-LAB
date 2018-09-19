#include <bits/stdc++.h>

using namespace std;

pair<int, int> lcs(int i, int j, string &a, string &b, vector< vector<int> > &dp) {
    if (a.at(i - 1) == b.at(j - 1))
        return make_pair(1, dp.at(i - 1).at(j - 1) + 1);
    else {
        if (dp.at(i - 1).at(j) > dp.at(i).at(j - 1))
            return make_pair(2, dp.at(i - 1).at(j));
        else
            return make_pair(3, dp.at(i).at(j - 1));
    }
}

int main() {
    string a;
    string b;
    cin>>a>>b;
    int lenA, lenB;
    lenA = a.length();
    lenB = b.length();
    vector< vector<int> > dp(lenA + 1);
    vector< vector<int> > B(lenA + 1);
    for (vector<int> &row : dp) {
        row.resize(lenB + 1);
    }
    for (vector<int> &row : B) {
        row.resize(lenB + 1);
    }    
    vector< int >::iterator iter_j;
    for (iter_j = dp.at(0).begin(); iter_j < dp.at(0).end(); iter_j++) {
        *iter_j = 0;
    }
    
    vector< vector<int> >::iterator iter_i;
    for (iter_i = dp.begin(); iter_i < dp.end(); iter_i++) {
        (*iter_i).at(0) = 0;
    }
    
    int i,j;
    for (i=1, iter_i = ++dp.begin();iter_i < dp.end(); iter_i++, i++) {
        for (j=1, iter_j = ++iter_i->begin(); iter_j < iter_i->end(); iter_j++, j++) {
            pair<int, int> p = lcs(i, j, a, b, dp);
            *iter_j = p.second;
            B.at(i).at(j) = p.first;
        }
    }
    
    string ans = "";
    i = lenA, j = lenB;
    while (i > 0 and j > 0) {
        if (B.at(i).at(j) == 1) {
            ans = a.at(i - 1) + ans;
            i--, j--;
        }
        else if (B.at(i).at(j) == 2)
            i--;
        else 
            j--;
    }
    cout<<dp.at(lenA).at(lenB)<<" "<<ans;    
}
