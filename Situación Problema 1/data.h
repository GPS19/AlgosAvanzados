#include <iostream>
#include <vector>
#include <fstream>
#include "boyerMoore.h"
#include "longestPalindrome.h"

using namespace std;

#pragma once
class Transmission
{
public:
    vector<string> transmission;

    Transmission(string fileName)
    {
        ifstream MyFile;
        MyFile.open(fileName);
        string line;

        while (!MyFile.eof())
        {
            getline(MyFile, line, '\n');
            transmission.push_back(line);
        }
    }

    vector<int> searchCode(string code)
    {
        Search searcher;
        vector<int> ans;
        for (int i = 0; i < transmission.size(); i++)
        {
            vector<int> a(searcher.booyerMore(transmission[i], code));

            if (!a.empty())
            {
                ans.push_back(1);
                ans.push_back(i);
                ans.push_back(a[0]);
                return ans;
            }
        }

        if (ans.empty())
        {
            ans.push_back(0);
        }

        return ans;
    }

    vector<int> findLongestPalindrome()
    {
        Palindrome longestPalindrome;
        vector<int> ans(3, 0);
        for (int i = 0; i < transmission.size(); i++)
        {
            vector<int> a = longestPalindrome.palindrome(transmission[i]);

            if (ans[2] < a[1])
            {
                ans[0] = i;
                ans[1] = a[0];
                ans[2] = a[1];
            }
        }

        return ans;
    }
};
