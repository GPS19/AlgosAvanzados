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

        DistanceGraph.setNodes(n);
        transmisionGraph.setNodes(n);

        getline(MyFile, line, '\n');
        getline(MyFile, line, '\n');

        int j = 0;
        while (j < n)
        {
            addToGraph(DistanceGraph, line, j);
            getline(MyFile, line, '\n');
            j++;
        }
        getline(MyFile, line, '\n');

        j = 0;
        while (j < n)
        {
            addToGraph(transmisionGraph, line, j);
            getline(MyFile, line, '\n');
            j++;
        }
        getline(MyFile, line, '\n');

        while(!MyFile.eof())
        {
            getline(MyFile, line, '(');
            getline(MyFile, line, ',');
            if (line == "")
                break;
            int x = stoi(line);
            getline(MyFile, line, ')');
            int y = stoi(line);
            
            coordinates.push_back(Point(x, y));
        }

        MyFile.close();
    }

    void addToGraph(GraphWeighted &graph, string &line, int j)
    {
        string temp = "";
        int k = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                graph.addEdge(j, k, stoi(temp));
                temp = "";
                k++;
            }
            else
            {
                temp.push_back(line[i]);
            }
        }
        graph.addEdge(j, k, stoi(temp));
    }
};