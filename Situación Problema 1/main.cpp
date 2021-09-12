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

void printResults(Transmission T, vector<string> codes)
{
    for (int i = 0; i < codes.size(); i++)
    {
        vector<int> a(T.searchCode(codes[i]));
        if (a[0])
        {
            cout << "true"
                 << " " << a[1] << " " << a[2] << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }
}

int main()
{
    Transmission transmission1("transmission1.txt");
    Transmission transmission2("transmission2.txt");

    //vector<string> codeFiles ();
    vector<string> codes(readCodes({"mcode1.txt", "mcode2.txt", "mcode3.txt"}));
    
    printResults(transmission1, codes);
    printResults(transmission2, codes);
}
