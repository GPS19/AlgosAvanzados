/*
Gianluca Beltrán A01029098
Pablo Yamamoto A01022382
Santiago Kohn A01029109
*/
//#include <fstream>
//#include <vector>
//#include <string>
#include "data.h"

using namespace std;

int main()
{
    Zones zones("input.txt");
    // zones.printGraphDistance();
    zones.DistanceGraph.kruskal();
    zones.DistanceGraph.printMST();

    zones.DistanceGraph.floydWarshall(0, zones.n-1);
    cout << endl;
    zones.transmisionGraph.fordFulkerson(0, zones.n - 1);
    cout << endl;
    Point a;
    tuple<Point, Point, float> ans = a.nearlyPoints(zones.coordinates, zones.coordinates.size());

    cout << "(" << get<1>(ans).x << ", " << get<1>(ans).y << ")\n"
         << "(" << get<0>(ans).x << ", " << get<0>(ans).y << ")\n";
    return 0;
}