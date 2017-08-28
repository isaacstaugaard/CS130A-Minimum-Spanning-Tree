#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <float.h>
#include <vector>
#include <string>
#include <cmath>
//allows use of sort function
#include <algorithm> 
using namespace std;


struct Edge
{
  string vertex1;
  string vertex2;
  int weight;
};


struct Graph 
{
  int* vertices;
  Edge* edges;
  int n;
  int m;
};


int* parent;
int* rank;


int find(int vertex) 
{
  if (parent[vertex] == vertex) 
    return parent[vertex];
  else
    return find(parent[vertex]);
}


void Union(int root1, int root2)
{
  //Rank of root1 > rank of root 2 ----> root1 is parent of root2
  if(rank[root1] > rank[root2])
    parent[root2] = root1;
  //rank of root2 > rank of root 1 ----> root2 is parent of root1
  else if(rank[root2] > rank[root1])
    parent[root1] = root2;
  //rank of root1 == rank of root 2 ----> root2 is parent of root1, increment rank of root2
  else
    {
      parent[root1] = root2;
      rank[root2]++;
    }
}


void Reset(int vertex)
{
  parent[vertex] = vertex;
  rank[vertex] = 0;
}


bool edgecompare(Edge lhs, Edge rhs)
{ 
  return lhs.weight < rhs.weight;
}


void sort(Edge* e, int m)
{
  sort(e, e + m, edgecompare);
}


void Kruskal(Graph g)
{	
  vector<Edge> MST;
  //Initialize weight to 0
  int MSTweight = 0;
  //Count used for tracking the number of successful inserts
  int count = 0;
  
  //Make new arrays for parent and rank (with size n)
  parent = new int[g.n];
  rank = new int[g.n];
  
  //Initialize the arrays with rank = 0 and parent[i] = i
  for(int i = 0; i <= g.n; i++)
    {
      parent[i] = i;
      rank[i] = 0;
    }
  
  //Loop through all m edges
  for (int i = 0; i < g.m; i++)
    {
      Edge tempE = g.edges[i];
      //convert string to integer for vertex 1 and vertex 2
      int tempV1 = atoi(tempE.vertex1.c_str());
      int tempV2 = atoi(tempE.vertex2.c_str());
      //call find on vertexes which returns the integer of parent[vertex]
      int root1 = find(tempV1);
      int root2 = find(tempV2);
      //nodes not in the same tree
      if (root1 != root2) 
	{
	  MSTweight = MSTweight + tempE.weight;
	  MST.push_back(tempE);
	  if (rank[root1] > rank[root2]) 
	    {
	      parent[root2] = root1;
	      rank[root1]++;
	      cout << "Edge (" << tempE.vertex1 << "," << tempE.vertex2 << ") successfully inserted" << "\n";
	      //The maximum number of inserts is n-1
	      count += 1;
	      if(count == g.n - 1)
		break;
	        //cout << "Count: " << count << "\n";
	    } 
	  else 
	    {
	      parent[root1] = root2;
	      rank[root2]++;
	      cout << "Edge (" << tempE.vertex1 << "," << tempE.vertex2 << ") successfully inserted" << "\n";
	      //The maximum number of inserts is n-1
	      count += 1;
	      if(count == g.n - 1)
		break;
	        //cout << "Count: " << count << "\n";
	    }
	}
      //nodes in same tree, create cycle
      else
	cout << "Edge (" << tempE.vertex1 << "," << tempE.vertex2 << ") creates cycle" << "\n";
    }
  
  //Print the resulting MST and weight when the MST has size n-1
  if(MST.size() == g.n - 1)
    {
      //look through the MST
      for (int i = 0; i < MST.size(); i++) 
	{
	  //cout the 2 vertex values in the MST
	  cout << MST[i].vertex1 << " " << MST[i].vertex2 << endl;
	}
      //cout the weight of the MST
      cout << MSTweight << "\n";
    }
  else
    cout << "ERROR: MST not found" << "\n";
}


//prints current arrays of vertices and edges
void printGraph(Edge* e, int m, int n, int* v)
{
  
  cout << "Number of Nodes: " << n << "\n";
  cout << "Number of Edges: " << m << "\n";
  cout << "Vertices: ";
  for(int i = 0; i < n; i++)
    {
      cout << v[i] << " ";
    }
  cout << "\n";	
  
  for(int i = 0; i < m; i++)
    {
      cout << e[i].vertex1 << " " << e[i].vertex2 << " " << e[i].weight << "\n";
    }
}
