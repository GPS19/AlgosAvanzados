#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#pragma once

class Edge
{
public:
    int src, dst;
    float weight;

    Edge(int src_, int dst_, float weight_)
    {
        src = src_;
        dst = dst_;
        weight = weight_;
    }
    ~Edge() {}

    friend bool operator<(const Edge &a, const Edge &b)
    {
        return a.weight < b.weight;
    }
};

// ----------------------- GRAPH WEIGHTED -----------------------

class GraphWeighted
{
public:
    vector<vector<int>> adj; // adjacency metrix
    vector<Edge> edges;
    vector<Edge> mst; // Minimu Spanning Tree
    vector<int> parent;
    int V; // Number of vertices

    GraphWeighted() {}
    GraphWeighted(int V_)
    {
        V = V_;

        for (int i = 0; i < V; i++)
        {
            adj.push_back(vector<int>(V));
        }
    };

    ~GraphWeighted(){};

    void addEdge(int src, int dst, int weight)
    {
        edges.push_back(Edge(src, dst, weight));
        adj[src][dst] = weight;
    }

    void setNodes(int V_)
    {
        V = V_;
        adj = vector<vector<int>>();

        for (int i = 0; i < V; i++)
        {
            adj.push_back(vector<int>(V));
            parent.push_back(i);
        }
    }

    // --------------------- Find Set ---------------------

    int find(int i)
    {
        if (i == parent[i])
            return i;
        return find(parent[i]);
    }

    // --------------------- Union Set ---------------------

    void union_set(int src, int dst)
    {
        parent[src] = parent[dst];
    }

    // --------------------- Kruskal -----------------------

    void kruskal()
    {
        stable_sort(edges.begin(), edges.end());

        int srcParent, dstParent;
        for (int i = 0; i < edges.size(); i++)
        {
            srcParent = find(edges[i].src);
            dstParent = find(edges[i].dst);

            if (srcParent != dstParent)
            {
                mst.push_back(edges[i]);
                union_set(srcParent, dstParent);
            }
        }
    }

    void printMST()
    {
        for (int i = 0; i < mst.size(); i++)
        {
            cout << "(" << mst[i].src << ", " << mst[i].dst << ")\n"; //<< mst[i].weight << endl;
        }
        cout << endl;
    }

    void floydWarshall(int src, int dst)
    {
        /*
        floydWarshall algoritm recive two intergers, the start and finish of the path that we want.
        */
        vector<vector<int>> dist(adj.begin(), adj.end());
        vector<vector<int>> next(V, vector<int>(V, -1));

        // setuo the distance matrix and next matrix, copy the adjacency matrix to distance and if isn't infinit add to next.
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                next[i][j] = j;
            }
        }

        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        // change the value of the distance if the sum less than the original value and add to next de next of this node.
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        // Print the result, we use the path that we create in next.
        int actualNode = src;
        int nextNode;
        while (actualNode != dst)
        {
            nextNode = next[actualNode][dst];
            cout << actualNode << " " << nextNode << endl;
            actualNode = nextNode;
        }
    }

    bool bfs(vector<vector<int>> graph, int s, int f, vector<int> &parent)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);
        parent[s] = -1;
        visited[s] = true;

        // Check if its a path from start to finish.
        while (!q.empty())
        {
            int actualNode = q.front();

            for (int i = 0; i < V; i++)
            {
                if (graph[actualNode][i] != 0 && !visited[i])
                {
                    if (i == f)
                    {
                        parent[i] = actualNode;
                        return true; // return true if get the finich node.
                    }
                    q.push(i);
                    parent[i] = actualNode;
                    visited[i] = true;
                }
            }
            q.pop();
        }

        return false;
    }

    float fordFulkerson(int s, int f)
    {
        vector<vector<int>> graphFC(adj); // graph to modify the flow and capacity.
        vector<int> parent(V, -1);        // to check the paths with the bfs
        int max_flow = 0;

        while (bfs(graphFC, s, f, parent))
        {
            int flow = graphFC[parent[f]][f];
            int i = f; // iterator for the path.
            while (parent[i] != -1)
            {
                flow = min(flow, graphFC[parent[i]][i]); // find the augment flow
                i = parent[i];
            }

            i = f;
            while (parent[i] != -1)
            {
                graphFC[parent[i]][i] -= flow;
                graphFC[i][parent[i]] += flow;
                i = parent[i];
            }

            max_flow += flow;
        }

        cout << max_flow << endl;
        return max_flow;
    }
};