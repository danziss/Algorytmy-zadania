#include <cstdio>
#include <iostream>
#include <vector>

#define INF 99999

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
        void floydWarshall();
        void printFloyd(std::vector<std::vector<int>> dist);
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
            std::cout << " -> " << adjList[i][j] << " waga " << weights[i][j].second << "\n";
        }
        std::cout << "\n";
    }
}

void Graf::printFloyd (std::vector<std::vector<int>> dist){
    std::cout<<"Macierz najkrótszych ścieżek między wierzchołkami \n";  
    for (int i = 0; i < N; i++)  
    {  
        for (int j = 0; j < N; j++)  
        {  
            if (dist[i][j] == INF)  
                std::cout<<"INF"<<"     ";  
            else
                std::cout<<dist[i][j]<<"     ";  
        }  
        std::cout<<std::endl;  
    }  
}

void Graf::floydWarshall(){
    
    std::vector<std::vector<int>> dist;
    dist.resize(N);
    for (int i = 0; i < N; i++){
        dist[i].resize(N);
        std::fill(dist[i].begin(), dist[i].end(), INF);
        dist[i][i] = 0;
    }


    for (int i = 0; i < N; i++){
        for (int j = 0; j < weights[i].size(); j++){
            dist[i][weights[i][j].first] = weights[i][j].second;
        }
    }

    for (int k = 0; k < N; k++){
        for (int i = 0; i < N; i++){

            for (int j = 0; j < N; j++){
                if (dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    printFloyd(dist);
}

int main (){

    Graf g(true, 4);
 /*   g.addEdgeWithWeight(0, 1, 5);
    g.addEdgeWithWeight(0, 3, 10);
    g.addEdgeWithWeight(1, 2, 3);
    g.addEdgeWithWeight(2, 3, 1);
    g.floydWarshall(); */
    g.addEdgeWithWeight(0, 1, 3);
    g.addEdgeWithWeight(0, 3, 5);
    g.addEdgeWithWeight(1, 0, 2);
    g.addEdgeWithWeight(1, 3, 4);
    g.addEdgeWithWeight(2, 1, 1);
    g.addEdgeWithWeight(3, 2, 2);
    g.print();
    g.floydWarshall();

    return 0;
}