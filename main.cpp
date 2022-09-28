#include <bits/stdc++.h>

#define all(v) (v).begin(),(v).end()

using std::vector;

vector < int > order;
vector < bool > usd;
vector < vector < int > > graph, graphT;

void topsort(int v){
    usd[v] = true;
    for (int nxt: graph[v]){
        if (!usd[nxt]){
            topsort(nxt);
        }
    }
    order.push_back(v);
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int V;
    std::cin >> V;
    graph.resize(V);
    graphT.resize(V);
    usd.resize(V);
    fill(all(usd), false);
    int u, v;
    while(std::cin >> u >> v){
        graph[u].push_back(v);
        graphT[v].push_back(u);
    }
    for (int i=0; i<V; ++ i){
        if (!usd[i]){
            topsort(i);
        }
    }
    reverse(all(order));
    fill(all(usd), false);
    int numOfComps = 0;
    vector < int > comp(V, -1);
    for (int i: order){
        if (usd[i]) continue;
        comp[i] = numOfComps ++;
        std::queue < int > q;
        usd[i] = true;
        q.push(i);
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for (int nxt: graphT[cur]){
                if (usd[nxt]) continue;
                comp[nxt] = comp[cur];
                q.push(nxt);
                usd[nxt] = true;
            }
        }
    }
    vector < bool > hasIncomingEdge(numOfComps, false);
    for (int from=0; from<V; ++ from){
        for (int to: graph[from]){
            if (comp[to] != comp[from]) {
                hasIncomingEdge[comp[to]] = true;
            }
        }
    }
    int cntOfPossibleRoots = 0, rootComp = -1;
    for (int c=0; c<numOfComps; ++ c){
        if (!hasIncomingEdge[c]) ++ cntOfPossibleRoots, rootComp = c;
    }
    if (cntOfPossibleRoots > 1){
        std::cout << "-1\n";
    }else{
        for (int i=0; i<V; i++){
            if (comp[i] == rootComp){
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
