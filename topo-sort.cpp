#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

#define NOT_PROCESSED 0
#define BEING_PROCESSED 1
#define PROCESSED 2

void DFS(int u, int *state, std::stack<int> &topo, std::vector<int> *g) {
    state[u] = BEING_PROCESSED;
    for (int v : g[u]) {
        if (state[v] == BEING_PROCESSED) {
            std::cout << "Detected a cycle!" << std::endl;
            delete[] state;
            delete[] g;
            exit(1);
        }
        if (state[v] == NOT_PROCESSED)
            DFS(v, state, topo, g);
    }
    topo.push(u);
    state[u] = PROCESSED;
}

int main() {
    std::fstream input;
    input.open("input.in", std::ios::in);

    if (!input.is_open()) {
        std::cout << "Input not found!" << std::endl;
        return 1;
    }

    int nVertices, nEdges;
    input >> nVertices >> nEdges;

    int *STATE = new int[nVertices+1];
    std::vector<int> *G = new std::vector<int>[nVertices+1];
    for (int i = 0; i < nEdges; i++) {
        int u, v;
        input >> u >> v;
        G[u].push_back(v);
    }

    input.close();

    std::stack<int> TOPO;
    for (int u = 1; u <= nVertices; u++) STATE[u] = NOT_PROCESSED;

    for (int u = 1; u <= nVertices; u++)
        if (STATE[u] == NOT_PROCESSED)
            DFS(u, STATE, TOPO, G);

    // Print answer
    std::cout << "Topological order: ";
    while (!TOPO.empty()) {
        std::cout << TOPO.top() << " ";
        TOPO.pop();
    }
    std::cout << std::endl;

    delete[] STATE;
    delete[] G;

    return 0;
}