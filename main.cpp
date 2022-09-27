#include <bits/stdc++.h>

#define all(v) (v).begin(),(v).end()

using std::vector;

int numOfComps;
vector < int > comp, order;
vector < bool > usd;
vector < vector < int > > g, gT;

void topsort(int v){
    usd[v] = true;
    for (int to: g[v]){
        if (!usd[to]){
            topsort(to);
        }
    }
    order.push_back(v);
}

int main(){
    int V, E;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::cin >> V >> E;
    g.resize(V);
    gT.resize(V);
    usd.resize(V);
    comp.resize(V);
    fill(all(comp), -1);
    fill(all(usd), false);
    while(E --){
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        gT[v].push_back(u);
    }
    for (int i=0; i<V; ++ i){
        if (!usd[i]){
            topsort(i);
        }
    }
    reverse(all(order));
    fill(all(usd), false);
    for (int i: order){
        if (usd[i]) continue;
        comp[i] = numOfComps ++;
        std::queue < int > q;
        usd[i] = true;
        q.push(i);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for (int to: gT[v]){
                if (usd[to]) continue;
                comp[to] = comp[v];
                q.push(to);
                usd[to] = true;
            }
        }
    }
    vector < bool > hasIncomingEdge(numOfComps, false);
    for (int i=0; i<V; ++ i){
        for (int to: g[i]){
            if (comp[to] != comp[i]) {
                hasIncomingEdge[comp[to]] = true;
            }
        }
    }
    int cntOfPossibleRoots = 0, root = -1;
    for (int i=0; i<numOfComps; ++ i){
        if (!hasIncomingEdge[i]) ++ cntOfPossibleRoots, root = i;
    }
    if (cntOfPossibleRoots > 1){
        std::cout << "-1\n";
    }else{
        for (int i=0; i<V; i++){
            if (comp[i] == root){
                std::cout << i << '\n';
                break;
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}


/*
7 7
0 1
1 2
2 6
3 2
4 3
5 4
6 5

5 8
0 4
1 0
1 2
2 1
2 4
3 1
3 2
4 3

6 7
0 1
1 2
2 3
3 0
4 3
4 5
5 0
*/
