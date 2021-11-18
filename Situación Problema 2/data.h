#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "weightedGraph.h"
#include "points.h"

using namespace std;

#pragma once

class Zones
{
public:
    int n;
    GraphWeighted DistanceGraph;
    GraphWeighted transmisionGraph;
    vector<Point> coordinates;

    Zones(string fileName)
    {
        // Read the file and complete the graphs.

        ifstream MyFile;
        MyFile.open(fileName);

        string line;
        getline(MyFile, line, '\n');
        n = stoi(line);
        cout << n << endl;

        DistanceGraph.setNodes(n);
        transmisionGraph.setNodes(n);

        getline(MyFile, line, '\n');
        getline(MyFile, line, '\n');

        int j = 0;
        while (j < n)
        {
            cout << j << " - " << line;
            addToGraph(DistanceGraph, line, j);
            getline(MyFile, line, '\n');
            j++;
        }
        getline(MyFile, line, '\n');

        // j = 0;
        // while (line != "\n")
        // {
        //     addToGraph(transmisionGraph, line, j);
        //     getline(MyFile, line, '\n');
        //     j++;
        // }


    }

    void addToGraph(GraphWeighted &graph, string line, int j)
    {
        string temp = "";
        int k = 0;
        //cout << j << endl;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                //cout << temp << endl;
                graph.addEdge(j, k, stoi(temp));
                temp = "";
                k++;
            }
            else
            {
                temp.push_back(line[i]);
            }
        }
    }
};