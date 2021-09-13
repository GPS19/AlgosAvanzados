#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Search
{
public:
    int badCharacterRule(map<char, vector<int>> &R, int i, char T)
    {
        if (R.find(T) != R.end()) // check if the letter exists.
        {
            for (int k = R[T].size() - 1; k >= 0; k--)
            {
                if (R[T][k] < i)
                {
                    return i - R[T][k];
                }
            }
        }
        return i + 1; // return the size of the move that we have to do.
    }

    vector<int> boyerMoore(string &txt, string &pattern)
    {
        int size = pattern.length();
        vector<int> ans;

        // Bad Charachter preprocessing
        map<char, vector<int>> Bad; // map with letters with index in pattern.
        for (int i = 0; i < size; i++)
        {
            //fill the map and vectors.
            Bad[pattern[i]].push_back(i);
        }

        // Good suffix preprocessing
        vector<int> table(size, -1);
        table[size - 1] = size - 2;

        int i = size - 1;
        int j = size - 2;

        while (j > -1)
        {
            if (pattern[i] == pattern[j])
            {
                if (table[i] == -1)
                {
                    table[i] = j;
                }
                i--;
                j--;
            }
            else
            {
                if (i == size - 1)
                {
                    j--;
                }
                i = size - 1;
            }
        }

        int aux;
        for (int i = size - 1; i >= 0; i--)
        {
            if (table[i] == -1)
            {
                table[i] = aux;
            }
            aux = table[i];
        }

        i = size - 1; // pattern
        j = 0;        // text
        int s, m;     // Where we store the max of bad character rule or good suffix rule

        while (j < txt.length() - size + 1)
        {
            // Compare P to T[k ... P.length()] from right to left
            while (txt[j + i] == pattern[i] && i > 0)
            {
                i--;
            }
            if (i == 0 && txt[j] == pattern[i])
            {
                ans.push_back(j);
                m = size - 1;
            }
            else
            {
                // good suffix  -  Bad character
                m = max(size - table[i] - 1, badCharacterRule(Bad, i, txt[j + i]));
            }

            i = size - 1;
            j += m;
            // Max(good, bad)
        }

        return ans;
    }
};
