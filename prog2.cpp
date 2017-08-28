#include <iostream>
#include <string>
#include "mst.h"
using namespace std;

int main()
{  
  Graph g;
  
  //read to n
  string tmpn;
  getline(cin,tmpn,' ');
  g.n = atoi(tmpn.c_str());
  
  //read to m
  string tmpm;
  getline(cin,tmpm);
  g.m = atoi(tmpm.c_str());	
  
  g.vertices = new int[g.n];
  
  for(int i = 0; i < g.n; i++)
    {
      int j = i + 1;
      g.vertices[i] = j;
    }
  
  g.edges = new Edge[g.m];	
  
  //store m edges in array e
  for(int i = 0; i < g.m; i++)
    {
      int w = 0;
      string tmpw;
      
      getline(cin, g.edges[i].vertex1,' ');
      
      getline(cin, g.edges[i].vertex2,' ');
      
      getline(cin,tmpw);
      w = atoi(tmpw.c_str());
      g.edges[i].weight = w;
    }
  
  sort(g.edges, g.m);
  
  //printGraph(g.edges, g.m, g.n, g.vertices);
  
  Kruskal(g);
  
  return 1;
}
