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

int main(int argc, char const *argv[])
{
    Zones zones("input.txt");
    cout << ".h\n";
    zones.DistanceGraph.kruskal();
    zones.DistanceGraph.printMST();
    return 0;
}