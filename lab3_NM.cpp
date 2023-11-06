#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>

std::vector<std::vector<int>> ReadGraph(const std::string& graphFile) {
    std::ifstream file(graphFile);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the graph file.");
    }

    int numVertices;
    file >> numVertices;

    std::vector<std::vector<int>> graph(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            file >> graph[i][j];
        }
    }

    file.close();

    return graph;
}

int OutDegree(const std::vector<std::vector<int>>& graph, int vertex) {
    int outDegree = 0;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[vertex][i] == 1) {
            outDegree++;
        }
    }
    return outDegree;
}

std::vector<double> ComputePageRank(const std::vector<std::vector<int>>& graph, int numIterations, double dampingFactor) {
    int numVertices = graph.size();
    std::vector<double> ranks(numVertices, 1.0 / numVertices);

    for (int iteration = 0; iteration < numIterations; iteration++) {
        std::vector<double> newRanks(numVertices, 0.0);

        for (int i = 0; i < numVertices; i++) {
            double sum = 0.0;
            for (int j = 0; j < numVertices; j++) {
                if (graph[j][i] == 1) {
                    sum += ranks[j] / static_cast<double>(OutDegree(graph, j));
                }
            }
            newRanks[i] = (1.0 - dampingFactor) / numVertices + dampingFactor * sum;
        }

        ranks = newRanks;
    }

    return ranks;
}


void PrintRanks(const std::vector<double>& ranks) {
    int numVertices = ranks.size();
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Rank of vertex " << i << ": " << ranks[i] << std::endl;
    }
}

int main() {
   
     std::string graphFile = "Graph.txt";
     int numIterations = 100;
     double dampingFactor = 0.85;

     std::vector<std::vector<int>> graph = ReadGraph(graphFile);
     std::vector<double> ranks = ComputePageRank(graph, numIterations, dampingFactor);

     PrintRanks(ranks);
    
     return 0;
}
