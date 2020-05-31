
#include <cstdio>
#include <iostream>
#include <vector> 
#include <limits.h> 
#include <set>
#include <algorithm>

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

        void dijkstraNew (int src);

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


void Graf::dijkstraNew(int src){
    int inf = 999;
    int node_count = N;
    std::vector<int> dist(node_count, inf);
    std::set<std::pair<int, int>> set_lenght_node;

    dist[src] = 0;
    set_lenght_node.insert(std::pair<int, int>(0, src));
    
    std::cout << "Od wierzchołka(" << src << ")" << std::endl;
    while (!set_lenght_node.empty()){


        std::pair<int, int> top = *set_lenght_node.begin();
        set_lenght_node.erase(set_lenght_node.begin());

        int src = top.second;

        for (auto &x : weights[src]){
            int adj_node = x.first;
            int lenght_to_adjNode = x.second;
            if (dist[adj_node] > lenght_to_adjNode + dist[src]) {
        //std::cout << "czy tu jest blad?" << std::endl;

                if (dist[adj_node] != inf) {
                    set_lenght_node.erase(set_lenght_node.find(std::pair<int, int>(dist[adj_node], adj_node)));
                }
                dist[adj_node] = lenght_to_adjNode + dist[src];
                set_lenght_node.insert(std::pair<int, int>(dist[adj_node], adj_node));
            }
        }
    }
    for (int i=0; i<node_count; i++)
        std::cout << "-> trasa do wierzchołka(" << i << ") : " << dist[i] << std::endl;
}


int main (){

    Graf g2(true, 5);
    g2.addEdgeWithWeight(0, 1, 5);
    g2.addEdgeWithWeight(0, 2, 1);
    g2.addEdgeWithWeight(0, 3, 4);
    g2.addEdgeWithWeight(1, 0, 2);
    g2.addEdgeWithWeight(1, 2, 3);
    g2.addEdgeWithWeight(1, 4, 8);
    g2.addEdgeWithWeight(2, 0, 1);
    g2.addEdgeWithWeight(2, 1, 3);
    g2.addEdgeWithWeight(2, 3, 2);
    g2.addEdgeWithWeight(2, 4, 1);
    g2.addEdgeWithWeight(3, 0, 4);
    g2.addEdgeWithWeight(3, 2, 2);
    g2.addEdgeWithWeight(3, 4, 2);
    g2.addEdgeWithWeight(3, 5, 1);
    g2.addEdgeWithWeight(4, 1, 8);
    g2.addEdgeWithWeight(4, 2, 1);
    g2.addEdgeWithWeight(4, 3, 2);
    g2.addEdgeWithWeight(4, 5, 3);
    g2.addEdgeWithWeight(5, 3, 1);
    g2.addEdgeWithWeight(5, 4, 3);
    g2.print();
    g2.dijkstraNew(0);

    return 0;
}