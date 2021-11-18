#include <iostream>
#include <cmath>
#include <utility>
#include <tuple>
#include <vector>

using namespace std;

#pragma once
class Point
{
public:
    int x, y;

    Point(int x_, int y_)
    {
        x = x_;
        y = y_;
    }

    Point() {}

    float distance(Point a, Point b)
    {
        return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    }

    static bool compareX(Point a, Point b)
    {
        return a.x < b.x;
    }

    static bool compareY(Point a, Point b)
    {
        return a.y < b.y;
    }

    tuple<Point, Point, float> nearlyPoints(vector<Point> points, int n)
    {
        sort(points.begin(), points.end(), this->compareX);

        tuple<Point, Point, float> ans;
        int mid = n/2;
        Point midPoint = points[mid];

        if (points.size() == 2)
        {
            return make_tuple(points[0], points[1], distance(points[0], points[1]));
        }
        else if (points.size() == 1)
        {
            return make_tuple(points[0], points[0], INT16_MAX);
        }

        tuple<Point, Point, float> a1 = nearlyPoints(vector<Point>(points.begin(), points.begin() + mid), mid);
        tuple<Point, Point, float> a2 = nearlyPoints(vector<Point>(points.begin() + mid, points.end()), mid);

        // Min distance of two parts.
        float d;
        tuple<Point, Point, float> a;
        if (get<2>(a1) < get<2>(a2))
        {
            d = get<2>(a1);
            a = a1;
        }
        else
        {
            d = get<2>(a2);
            a = a2;
        }

        // Delete all points further thna d.
        vector<Point> closersPoints;
        for (int i = 0; i < n; i++)
        {
            if (midPoint.x - points[i].x < d)
            {
                closersPoints.push_back(points[i]);
            }
        }

        // Sort remaining points by y.
        sort(closersPoints.begin(), closersPoints.end(), compareY);

        // scan near points and check if its a closer pair.

        for (int i = 0; i < closersPoints.size()-1; i++)
        {
            for (int j = i+1; j < closersPoints.size(); j++)
            {
                float dist = distance(points[i], points[j]);
                if (dist < get<2>(a))
                {
                    a = make_tuple(points[i], points[j], dist);
                }
            }
        }

        return a;
    }
};