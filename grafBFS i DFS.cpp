#include <cstdio>
#include <iostream>
#include <vector> 
#include <stack>
#include <queue>

//wersja nieskierowany
//wierzchołki to inty od 0 do N
class Graf{
    private:
        int N;
        std::vector<std::vector<int>> adjList;

    public:
        Graf(int maxSize){
            N = maxSize;
            adjList.resize(N);
        }
        void addEdge(int v1, int v2){
            adjList[v1].push_back(v2);
        }
        void print();
        void DFS(int s);
        void BFS(int s);
        void DFSRecursion(int s);
        void dfs(int s, bool visited[]);

};

void Graf::print(){
    std::cout << "Lista sąsiadów grafu: \n";
    for (int i = 0; i < adjList.size(); i++){
        std::cout << "Wierzchołek " << i << ":\n";
        for (int j = 0; j < adjList[i].size(); j++){
            std::cout << " -> " << adjList[i][j];
        }
        std::cout << "\n";
    }
}

void Graf::DFS(int s){
    std::stack<int> stack;
    std::vector<bool> visited(N, false);
    int check = 0;
    stack.push(s);

    std::cout << "DFS od wierzchołka " << s << ":\n";
    while (!stack.empty()){
        s = stack.top();
        stack.pop();

        if (!visited[s]){
            std::cout << s;
            visited[s] = true;
        }
        for (int i = 0; i < adjList[s].size(); i++){
            check = adjList[s][i];
            if (!visited[check])
                stack.push(adjList[s][i]);
        }
        if(!stack.empty())
            std::cout << "->";
    }
    std::cout << "\n";
}

void Graf::BFS(int s){
    std::cout << "BFS od wierzchołka " << s << ":\n";
    std::queue<int> que;
    std::vector<bool> visited(N, false);    
    que.push(s);
    int check = 0;

    while(!que.empty()){
        s = que.front();
        que.pop();
        
        if (!visited[s]){
            std::cout << s;
            visited[s] = true;
        }

        for (int i = 0; i < adjList[s].size(); i++){
            check = adjList[s][i];
            if (!visited[check])
                que.push(adjList[s][i]);
        }if(!que.empty())
            std::cout << "->";
    }
    std::cout << "\n";
}

void Graf::dfs(int s, bool visited[]){
    visited[s] = true;
    int check = 0;
    std::cout << s << "->";
    for (int i = 0; i < adjList[s].size(); i++){
        check = adjList[s][i];
        if (!visited[check])
            dfs(check, visited);
    }
}

void Graf::DFSRecursion(int s){
    std::cout<<"DFS Rekurencja od wierzcholka " << s <<":\n";
    bool *visited = new bool[N]; 
    for (int i = 0; i < N; i++){        
        visited[i] = false; 
    }
    dfs(s, visited);
    std::cout << "\n";
}

int main (){

    Graf g(6);
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 3); 
    g.addEdge(1, 4); 
    g.addEdge(2, 3); 
    g.addEdge(2, 5); 
    g.addEdge(3, 0); 
    g.addEdge(4, 3);  
    g.print();
    g.DFS(0);
    g.BFS(0);
    g.DFSRecursion(0);

    return 0;
}