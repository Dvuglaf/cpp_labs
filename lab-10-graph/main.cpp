#include "Graph.h"
#include <string>
#include <iostream>
#include "Locality.h"

using namespace std;
int main() {
    Graph<Locality*, float> graph;

    try {
        graph.AddVertex(new Locality("Samara", 2000000));
        graph.AddVertex(new Locality("St.Petersburg", 5000000));
        graph.AddVertex(new Locality("Moscow", 12000000));

        graph.AddEdge(graph.GetVertex(0), graph.GetVertex(1), 1769);
        graph.AddEdge(graph.GetVertex(0), graph.GetVertex(2), 1000);
        graph.AddEdge(graph.GetVertex(1), graph.GetVertex(0), 1769);
        graph.AddEdge(graph.GetVertex(1), graph.GetVertex(2), 705);
        graph.AddEdge(graph.GetVertex(2), graph.GetVertex(0), 1000);
        graph.AddEdge(graph.GetVertex(2), graph.GetVertex(1), 705);

        graph.Print();

        {
            std::cout<<"\nrRDepthFirstSearch:\n";
            auto visited = new bool[graph.GetVertexCount()]{false};
            RDepthFirstSearch(graph, graph.GetVertex(0), [](auto vertex) { std::cout << vertex << ' '; }, visited);
            std::cout << std::endl;
            delete[] visited;
        }
        std::cout << "\nEdit vertex (Moscow; 12000000) to (Moscow-city; 11000000)\n\n";
        graph.EditVertex(graph.GetVertex(2), new Locality("Moscow-city",11000000));
        graph.Print();
        {
            std::cout<<"\nBreadthFirstSearch:\n";
            BreadthFirstSearch(graph, graph.GetVertex(0), [](auto vertex) { std::cout << vertex << ' '; });
            std::cout << std::endl;
        }
        {
            std::cout << "\nDijkstra:\n";
            auto path = new Locality*[graph.GetVertexCount()];
            size_t length = 0;
            cout << Dijkstra(graph, graph.GetVertex(0), graph.GetVertex(1), path, &length) << ": ";
            for (size_t i = 0; i < length ; ++i) {
                cout << path[i]->getCity();
                if (i != length - 1)
                    cout << " -> ";

            }
            std::cout << std::endl;

            delete [] path;
        }
        std::cout << "\nErase edge from Samara to Moscow-city.\n";
        graph.EraseEdge(graph.GetVertex(0), graph.GetVertex(2));
        {
            std::cout << "\nBellmanFord:\n";
            auto path = new Locality*[graph.GetVertexCount()];
            size_t length = 0;
            cout << BellmanFord(graph, graph.GetVertex(0), graph.GetVertex(1), path, &length) << ": ";
            for (size_t i = 0; i < length ; ++i) {
                cout << path[i]->getCity();
                if (i != length - 1)
                    cout << " -> ";

            }
            std::cout << std::endl;

            delete [] path;
        }
        std::cout << "\nClear graph and add vertex Final:\n\n";
        graph.Clear();
        graph.AddVertex(new Locality("Final",1));
        graph.Print();
        return 0;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

}