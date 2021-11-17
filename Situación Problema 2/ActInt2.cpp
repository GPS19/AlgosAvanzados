/*
Gianluca Beltrán A01029098
Pablo Yamamoto A01022382
Santiago Kohn A01029109
*/
#include <fstream>
#include <string>
#include "weightedGraph.h"
#include "points.h"

using namespace std;

// vector<string> readGraph(string codeFiles) // Function in charge of reading all of the mcodes and sstoring them into a vector
// {
//     vector<vector<int>> distanceGraphs;
//     vector<vector<int>> transmitionGraph;
//     vector<Point> coordinate;
//     ifstream MyFile;
//     MyFile.open(code);
//     string distances, transmitions, coordinates;

//     return codes;
// }

int main(int argc, char const *argv[])
{
    ifstream MyFile;
    MyFile.open("input.txt");
    string line;

    getline(MyFile, line, '\n');
    int N = stoi(line);

    GraphWeighted DistanceGraph;
    GraphWeighted transmisionGraph;
    vector<Point> coordinates;

    while(!MyFile.eof())
    {
        
    }


    return 0;
}