
#include <cstdio>
#include <iostream>
#include <vector> 
#include <stack>


//Klasa grafu na którym wykonuję wszystkie zadania

class Graf{
    private:
        int N;
        bool directed;
        std::vector<std::vector<int>> adjList;
        std::vector<std::vector<std::pair<int, int>>> weights;

    public:
        Graf( bool isDirected, int maxSize){
            N = maxSize;
            directed = isDirected;
            adjList.resize(N);
            weights.resize(N);
        }
        void addEdge(int v1, int v2){
            adjList[v1].push_back(v2);
            if(!directed){
                adjList[v2].push_back(v1);                
            }
        }
        void addEdgeWithWeight(int v1, int v2, int weight);
        void print();

        std::vector<bool> DFS(int s);
        bool GraphConsistency();
        bool isDirected(){return directed;}
        void topSort(int v, bool visited[], std::stack<int> &stos);
        void topologicalSort();

};
void Graf::addEdgeWithWeight(int v1, int v2, int weight){
    adjList[v1].push_back(v2);
    if(!directed){
        adjList[v2].push_back(v1);
        weights[v2].push_back(std::pair<int, int>(v2, weight));                
    }
    weights[v1].push_back(std::pair<int, int>(v2, weight));
}

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

std::vector<bool> Graf::DFS(int s){
    std::stack<int> stack;
    std::vector<bool> visited(N, false);
    int check = 0;
    stack.push(s);
    int consHelp = s;

    //std::cout << "DFS od wierzchołka " << s << ":\n";
    while (!stack.empty()){
        s = stack.top();
        stack.pop();

        if (!visited[s]){
            //std::cout << s;
            visited[s] = true;
        }
        for (int i = 0; i < adjList[s].size(); i++){
            check = adjList[s][i];
            if (!visited[check])
                stack.push(adjList[s][i]);
        }
        //if(!stack.empty())
            //std::cout << "->";
    }
    //std::cout << "\n";
    //if(directed)visited[consHelp] = false;    linijka dla po prostu spojnego grafu
    return visited;
}

bool Graf::GraphConsistency(){
    std::vector<bool> visited;
    if(directed){
        std::vector<bool> help(N, false);
        for (int i=0; i < N; i++){
            visited = this->DFS(i);
            /*for (int j = 0; j < visited.size(); j++){   dla Grafu skierowanego spójnego
                if (visited[j] == true){
                    help[j] = true;
                }
            }*/

            for (int i = 0; i < visited.size(); i++){
                if (!visited[i])return false;
            }
        }

        /*for (int i = 0; i < help.size(); i++){
            if(!help[i])return false;
        }*/
        return true;
    }else{
        visited = this->DFS(0);
        for (int i = 0; i < visited.size(); i++){
            if (!visited[i])return false;
        }
        return true;
    }
}

void Graf::topSort(int v, bool visited[], std::stack<int> &stos){
    visited[v] = true;

    for (int i = 0; i < adjList[v].size(); i++){
        if(!visited[adjList[v][i]]){
            topSort(adjList[v][i], visited, stos);
        }
    }
    stos.push(v);
}

void Graf::topologicalSort(){

    std::stack<int> stos;
    
    bool *visited = new bool[N]; 
    for (int i = 0; i < N; i++) 
        visited[i] = false; 

    for (int i = 0; i < N; i++) 
      if (visited[i] == false) 
        topSort(i, visited, stos); 

    while (stos.empty() == false) 
    { 
        std::cout << stos.top() << " "; 
        stos.pop(); 
    } 
}


int main (){

    Graf g(true, 6);
    g.addEdge(0, 1); 
    g.addEdge(0, 4); 
    g.addEdge(1, 2); 
    g.addEdge(1, 4); 
    g.addEdge(2, 3); 
    g.addEdge(3, 4); 
    g.addEdge(3, 5); 
    g.addEdge(3, 0); 
    g.print();
    std::cout <<"Czy graf spójny " << g.GraphConsistency() << "\n";
    std::cout << std::endl;

    Graf g1(true, 6);
    g1.addEdge(0, 1); 
    g1.addEdge(0, 3); 
    g1.addEdge(1, 2); 
    g1.addEdge(1, 3); 
    g1.addEdge(2, 5); 
    g1.addEdge(2, 4); 
    g1.addEdge(2, 3); 
    g1.addEdge(3, 4); 
    g1.addEdge(3, 5); 

    g1.print();
    std::cout << "Po posortowaniu topologicznym g1 to: ";
    g1.topologicalSort(); 
    std::cout << std::endl;

    return 0;
}