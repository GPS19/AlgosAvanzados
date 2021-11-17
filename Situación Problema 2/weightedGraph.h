#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

// ----------------------- GRAPH VERTEX WEIGHTED -----------------------

class GraphVertexWeighted
{
private:
    vector<pair<int, float>> adj;

public:
    ~GraphVertexWeighted(){};
    GraphVertexWeighted(){};

    vector<pair<int, float>> get_adj() { return adj; };
    void add_to_adj(int idx, float weight) { adj.push_back(make_pair(idx, weight)); };
};

// ----------------------- GRAPH WEIGHTED -----------------------

class GraphWeighted
{
private:
    vector<GraphVertexWeighted> nodes;
    vector<Edge> edges;
    vector<Edge> mst; // Minimu Spanning Tree
    int V; // Number of vertices

public:
    GraphWeighted() {}
    GraphWeighted(int V_)
    {
        V = V_;

        for (int i = 0; i < V; i++)
        {
            nodes.push_back(vector<int>(V));
        }
    };

    ~GraphWeighted(){};

    void add_edge(int src, int dst, int weight)
    {
        edges.push_back(Edge(src, dst, weight));
        nodes[src][dst] = weight;
    }

    void Prim(int startNode)
    {
        vector<bool> reached(nodes.size(), 0);

        vector<Edge> edges(nodes[startNode].get_adj());

        // priority queue for de edges with the first adjacency edges.
        priority_queue<Edge, vector<Edge>, compareByWeight> pQueue(edges.begin(), edges.end());
        reached[startNode] = true;
        int actualNode;
        Edge lastEdge;

        for (int i = 0; i < nodes.size() - 1; i++)
        {
            // pass all the adjacency that we have already reached.
            do
            {
                lastEdge = pQueue.top();
                pQueue.pop();
            } while (reached[lastEdge.src] && reached[lastEdge.dst]);

            mst.push_back(lastEdge);

            if (reached[lastEdge.src])
                actualNode = lastEdge.dst;
            else
                actualNode = lastEdge.src;

            reached[actualNode] = true;

            // adjacency of actual node.
            vector<Edge> edges(nodes[actualNode].get_adj());

            // Push to priority queue all the adjacency.
            for (int j = 0; j < edges.size(); j++)
            {
                pQueue.push(edges[j]);
            }
        }

        stable_sort(mst.begin(), mst.end());
    }

    void printMST()
    {
        for (int i = 0; i < mst.size(); i++)
        {
            cout << mst[i].src << " " << mst[i].dst << " " << mst[i].weight << endl;
        }
        cout << endl;
    }

    void floydWarshall(int src, int dst)
    {
        /*
        floydWarshall algoritm recive two intergers, the start and finish of the path that we want. 
        */
        vector<vector<float>> dist(V, vector<float>(V, INT16_MAX));
        vector<vector<int>> next(V, vector<int>(V, -1));

        // setuo the distance matrix and next matrix, copy the adjacency matrix to distance and if isn't infinit add to next.
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                dist[i][j] = adj[i][j];
                if (dist[i][j] != INT16_MAX)
                {
                    next[i][j] = j;
                }
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
                        //change the value of the distance if the sum less than the original value and add to next de next of this node.
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        //Print the result, we use the path that we create in next. 
        int actualNode = src;
        int nextNode;
        while (actualNode != dst)
        {
            nextNode = next[actualNode][dst];
            cout << actualNode << " " <<  nextNode << " " << endl;
            actualNode = nextNode;
        }
    }

    bool bfs(vector<vector<float> > graph, int s, int f, vector<int> &parent)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);
        parent[s] = -1;
        visited[s] = true;

        //Check if its a path from start to finish.
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
        vector<vector<float> > graphFC(adj); // graph to modify the flow and capacity.
        vector<int> parent(V, -1); // to check the paths with the bfs
        float max_flow = 0;

        while(bfs(graphFC, s, f, parent))
        {
            float flow = graphFC[parent[f]][f];
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

        return max_flow;
    }
};