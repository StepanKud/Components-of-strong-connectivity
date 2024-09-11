#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <queue>
 
using namespace std;

vector<vector<int>>g, gr;
//g[i]- stores all vertices to which roads go from vertex i
//if you change the direction of all roads, then gr[i]-will store all vertices to which roads go from vertex i

vector<bool>used;
//first, we use used in dfs1 (to see if the current vertex was visited or not)
//then in dfs2 we equate used[v] to the csc number that vertex v belongs to
vector<int>topsort;
//stores our vertices in topological sorting (the vertices are arranged so that there is no path from the current vertex to the left)
//there may be several topological sorts for one set of vertices
void dfs1(int v) {//dfs 1 is needed to compile the topological sorting of our graph
    used[v] = 0;//let's mark that we entered this vertex
    for (auto to: g[v])//from the current vertex, we go along all roads that lead to unmarked vertices
        if (used[to] == 1)
            dfs(to);
    topsort.push_back(v);
}

void dfs2(int v, int k) {
    used[v] = k;//
    for (auto to: gr[v])
        if (used[to] == 0)
            dfs2(to, k);
}

int main() {
    int n, m; //n-vertices and m-roads
    cin >> n >> m;
    g.resize(n);
    gr.resize(n);
    used.resize(n, 1);
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        r--; l--
        g[l].push_back(r);
     
        gr[r].push_back(l);
    }
    
    for (int i = 0; i < n; i++)//let's go through all the vertices to make a topological sorting
        if (used[i] == 1)
            dfs(i);
    reverse(topsort.begin(), topsort.end());
    //let's reverse our topological sorting
    int k = 1;//we will number the csc from 1
    for (int i = 0; i < topsort.size(); i++)
        if (used[topsort[i]] == 0)
            dfs2(topsort[i], k++);
    
    for (int i = 0; i < n; i++)
        cout << i + 1 << " : " << used[i] << endl;
}
