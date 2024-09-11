#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <queue>
 
using namespace std;

vector<vector<int>>g, gr;

vector<bool>used;
//first, we use used in dfs1 (to see if the current vertex was visited or not)
//then in dfs2 we equate used[v] to the csc number that vertex v belongs to
vector<int>topsort;
//stores our vertices in topological sorting (the vertices are arranged so that there is no path from the current vertex to the left)
//there may be several topological sorts for one set of vertices
void dfs1(int v) {
    used[v] = 0;
    for (auto to: g[v])
        if (used[to] == 1)
            dfs(to);
    topsort.push_back(v);
}

void dfs2(int v, int k) {
    used[v] = k;
    for (auto to: gr[v])
        if (used[to] == 0)
            dfs2(to, k);
}

int main() {
    int n, m; cin >> n >> m;
    g.resize(n);
    gr.resize(n);
    used.resize(n, 1);
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        g[--l].push_back(--r);
        gr[r].push_back(l);
    }
    
    for (int i = 0; i < n; i++)
        if (used[i] == 1)
            dfs(i);
    reverse(topsort.begin(), topsort.end());
    
    cout << "ok\n";
    
    int k = 1;
    for (int i = 0; i < topsort.size(); i++)
        if (used[topsort[i]] == 0)
            dfs2(topsort[i], k++);
    
    for (int i = 0; i < n; i++)
        cout << i + 1 << " : " << used[i] << endl;
}
