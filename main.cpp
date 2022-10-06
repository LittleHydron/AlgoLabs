#include <bits/stdc++.h>

#define all(v) (v).begin(),(v).end()

using namespace std;

int main(){
    freopen("gamsrv.in", "r", stdin);
    freopen("gamsrv.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    string line;
    getline(cin, line);
    getline(cin, line);
    vector < bool > isClient(n+1, false);
    line += ' ';
    int tmp = 0;
    for (char &c: line){
        if (c == ' '){
            if (tmp > 0) isClient[tmp] = true;
            tmp = 0;
        }else{
            tmp = tmp * 10 + (c - '0');
        }
    }
    vector < vector < tuple<int, int> > > g(n+1);
    int from, to, dist;
    while(m --){
        cin >> from >> to >> dist;
        g[from].push_back({to, dist});
        g[to].push_back({from, dist});
    }
    vector < bool > tmp_usd(n+1);
    long long ans = -1, max_min = -1;
    for (int i=1; i<=n; ++ i){
        if (isClient[i]) continue;
        fill(all(tmp_usd), false);
        priority_queue < tuple < long long, int > > q;
        q.push({0, i});
        while(!q.empty()){
            tie(dist, from) = q.top();
            q.pop();
            if (tmp_usd[from]) continue;
            tmp_usd[from] = true;
            dist *= -1;
            if (isClient[from]) max_min = dist;
            for (auto [to, latency]: g[from]){
                if (!tmp_usd[to]){
                    q.push({-(dist + latency), to});
                }
            }
        }
        if (ans == -1) ans = max_min;
        else ans = min(ans, max_min);
    }
    cout << ans << '\n';
    fclose(stdin);
    fclose(stdout);
    return 0;
}


/*
6
0 1
1 2
1 5
2 3
3 0
4 0

7
0 1
1 2
2 6
3 2
4 3
5 4
6 5

5
0 4
1 0
1 2
2 1
2 4
3 1
3 2
4 3

6
0 1
1 2
2 3
3 0
4 3
4 5
5 0
*/
