#include <iostream>
#include <string>
#include <cstring>
#include <limits.h>
using namespace std;

int minDistance(int dist[], bool vertexSet[], int vertexNum)
{
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < vertexNum; v++)
    {
        if (vertexSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }
  
    return min_index;
}

int dijkstra(int **graph, int vertexNum, int targetSource, int targetDestination)
{
    // initialize
    int dist[vertexNum];
    bool vertexSet[vertexNum];
    for (int i = 0; i < vertexNum; i++)
        dist[i] = INT_MAX, vertexSet[i] = false;
    dist[targetSource] = 0;
  
    // Find shortest path for all vertices
    for (int count = 0; count < vertexNum - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, vertexSet, vertexNum);
        vertexSet[u] = true;
  
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < vertexNum; v++)
        {
            if (!vertexSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    return dist[targetDestination];
}

int main()
{
    int verticesNum = 0;
    cin >> verticesNum;
    cin.ignore();

    bool conti = true;
    while (conti == true)
    {
        //input
        int **adjacencyMatrix = new int *[verticesNum];
        for (int i = 0; i < verticesNum; ++i)
            adjacencyMatrix[i] = new int[verticesNum];

        string aString = "";
        while (getline(cin, aString))
        {
            if (aString == "#")
            {
                break;
            }
            else
            {
                int source = 0, destination = 0, distance = 0;
                char *token = strtok(const_cast<char *>(aString.c_str()), " ");
                while (token != nullptr)
                {
                    source = atoi(token);
                    token = strtok(nullptr, " ");
                    destination = atoi(token);
                    token = strtok(nullptr, " ");
                    distance = atoi(token);
                    token = strtok(nullptr, " ");
                }
                adjacencyMatrix[source][destination] = distance;
            }
        }

        //process
        int targetSource = 0, targetDestination = 0;
        conti = false;
        while (getline(cin, aString))
        {
            size_t found = aString.find(" ");
            if (found == std::string::npos)
            {
                verticesNum = stoi(aString);
                conti = true;
                break;
            }
            else
            {
                char *token = strtok(const_cast<char *>(aString.c_str()), " ");
                while (token != nullptr)
                {
                    targetSource = atoi(token);
                    token = strtok(nullptr, " ");
                    targetDestination = atoi(token);
                    token = strtok(nullptr, " ");
                }
                int minPath = dijkstra(adjacencyMatrix, verticesNum, targetSource, targetDestination);
                cout << minPath << endl;
            }
        }
    }

    return 0;
}