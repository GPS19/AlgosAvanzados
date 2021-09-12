#include "data.h"

using namespace std;

vector<string> readCodes(vector<string> codeFiles)
{
    vector<string> codes;
    string line;

    for (string code : codeFiles)
    {
        ifstream MyFile;
        MyFile.open(code);
        getline(MyFile, line, '\n');
        codes.push_back(line);
    }

    return codes;
}

void printPartOne(Transmission T, vector<string> codes)
{
    for (int i = 0; i < codes.size(); i++)
    {
        vector<int> partOne(T.searchCode(codes[i]));
        if (partOne[0])
        {
            cout << "true"
                 << " " << partOne[1] << " " << partOne[2] << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }
}

void printPartTwo(Transmission T)
{
    vector<int> partTwo(T.findLongestPalindrome());
    for (int i = 0; i < partTwo.size(); i++)
    {
        cout << partTwo[i] << " ";
    }
    cout << endl;
}

int main()
{
    Transmission transmission1("transmission1.txt");
    Transmission transmission2("transmission2.txt");

    //vector<string> codeFiles ();
    vector<string> codes(readCodes({"mcode1.txt", "mcode2.txt", "mcode3.txt"}));

    printPartOne(transmission1, codes);
    printPartOne(transmission2, codes);
    cout << endl;
    printPartTwo(transmission1);
    printPartTwo(transmission2);
}
