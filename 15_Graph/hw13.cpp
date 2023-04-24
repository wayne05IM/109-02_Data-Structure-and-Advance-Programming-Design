#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int shortestPath(int **adjMatrix, int vertexNum, int source, int destination);
bool inSetFunc(int j, int vertexSet[], int vertexNum, int presentNum);

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
                //cout << source << " " << destination << " " << distance << endl;  //check input
                adjacencyMatrix[source][destination] = distance;
            }
        }

        //check adjacencyMatrix
        /*
        for(int i = 0; i < verticesNum; i++)
        {
            for(int j = 0; j < verticesNum; j++)
                cout << adjacencyMatrix[i][j] << " ";
            cout << endl;
        }
        */

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
                //cout << targetSource << " " << targetDestination << endl;
                int minPath = shortestPath(adjacencyMatrix, verticesNum, targetSource, targetDestination);
                cout << minPath << endl;
            }
        }
    }

    return 0;
}

int shortestPath(int **adjMatrix, int vertexNum, int source, int destination)
{
    //Step 1: initialization
    // Create a set vertexSet that contains only vertex 0
    int* vertexSet = new int [vertexNum];
    int presentNum = 0;
    vertexSet[presentNum] = source;
    // n = number of vertices in theGraph
    // for (v = 0 through n - 1) weight[v] = matrix[0][v]
    int* weight = new int [vertexNum];
    for (int i = 0; i < vertexNum; i++)
        weight[i] = adjMatrix[source][i];

    //Steps 2:
    for (int i = 2; i < vertexNum; i++)
    {
        //cout << "a";
        int v = 0;
        bool allZero = true;
        for(int j = 0; j < vertexNum; j++)
        {
            if(inSetFunc(j, vertexSet, vertexNum, presentNum) == false)
            {
                if(j != 0)
                    allZero = false;
            }
        }
        while ((weight[v] == 0) or (inSetFunc(v, vertexSet, vertexNum, presentNum) == true))
        {
            if(allZero == true)
                break;
            v = (v + 1) % vertexNum;
        }

        //for the rest vertex 1 to n-1
        //Find the smallest weight[v] such that v is not in vertexSet
        for (int j = 0; j < vertexNum; j++)
        {
            bool inSet = inSetFunc(j, vertexSet, vertexNum,presentNum);

            if (inSet == false)
            {
                if ((weight[j] != 0) and (weight[j] < weight[v]))
                    v = j;
            }
        }
        //Add v to vertexSet
        vertexSet[++presentNum] = v;
        //cout << v << endl;

        /*
        for (int i = 0; i < vertexNum; i++)
            cout << vertexSet[i] << " ";
        cout << endl << presentNum << endl;
        */

        /*for (all vertices u not in vertexSet)
        { // update weight[u] for all u not in vertexSet
            if (weight[u] > weight[v] + matrix[v][u])
                weight[u] = weight[v] + matrix[v][u]
        }*/
        for (int j = 0; j < vertexNum; j++)
        {
            bool inSet = inSetFunc(j, vertexSet, vertexNum, presentNum);

            if (inSet == false)
            {
                if(adjMatrix[v][j] != 0)
                {
                    if(weight[j] != 0)
                    {
                        if (weight[j] > weight[v] + adjMatrix[v][j])
                            weight[j] = weight[v] + adjMatrix[v][j];
                        //cout << weight[v] + adjMatrix[v][j] << endl;
                    }
                    else
                        weight[j] = weight[v] + adjMatrix[v][j]; //
                }
            }
        }
        /*
        for(int k = 0; k < vertexNum; k++)
            cout << weight[k] << " ";
        cout << endl;
        */
    }

    return weight[destination];
};

bool inSetFunc(int j, int vertexSet[], int vertexNum, int presentNum)
{
    for (int k = 0; k < vertexNum; k++)
    {
        if (k > presentNum)
            return false;

        if (j == vertexSet[k])
            return true;
    }
    return false;
};