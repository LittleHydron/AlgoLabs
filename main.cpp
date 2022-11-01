#include <bits/stdc++.h>

#define all(v) (v).begin(),(v).end()

using namespace std;

int main(){
    freopen("wchain.in", "r", stdin);
    freopen("wchain.out", "w", stdout);

    int n;
    cin >> n;
    unordered_map < string, int > maxChainLength;
    vector < string > dictionary(n);
    for (int i=0; i<n; ++ i){
        cin >> dictionary[i];
        maxChainLength[dictionary[i]] = 1;
    }

    sort(all(dictionary), [](string &a, string &b) -> bool {
        return a.length() < b.length();
    });

    string pref, tmp;
    int ans = 0;
    for (string &s: dictionary){
        pref = "";
        for (int i=0; i<s.length(); ++ i){
            tmp = pref;
            for (int j=i+1; j<s.length(); ++ j){
                tmp += s[j];
            }
            if (maxChainLength[tmp] > 0) maxChainLength[s] = max(maxChainLength[s], maxChainLength[tmp] + 1);
            pref += s[i];
        }
        ans = max(ans, maxChainLength[s]);
    }
    cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

/*
10
crates
car
cats
crate
rate
at
ate
tea
rat
a

5
b
bcad
bca
bad
bd

3
word
anotherword
yetanotherword
*/
