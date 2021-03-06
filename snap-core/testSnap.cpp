// Small example testing basic functionality of SNAP

#include "Snap.h"
#include <time.h>

int main(int argc, char* argv[]) {
  // create a graph and save it
  { PNGraph Graph = TNGraph::New();
  for (int i = 0; i < 10; i++) {
    Graph->AddNode(i); }
  for (int i = 0; i < 10; i++) {
    Graph->AddEdge(i, TInt::Rnd.GetUniDevInt(10)); }
  TSnap::SaveEdgeList(Graph, "graph.txt", "Edge list format"); }
  // load a graph
  PNGraph Graph;
  Graph = TSnap::LoadEdgeList<PNGraph>("graph.txt", 0, 1);
  // traverse nodes
  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
    printf("NodeId: %d, InDegree: %d, OutDegree: %d\n", NI.GetId(), NI.GetInDeg(), NI.GetOutDeg());
    printf("OutNodes: ");
    for (int e = 0; e < NI.GetOutDeg(); e++) { printf("  %d", NI.GetOutNId(e)); }
    printf("\nInNodes: ");
    for (int e = 0; e < NI.GetInDeg(); e++) { printf("  %d", NI.GetInNId(e)); }
    printf("\n\n");
  }
  // graph statistic
  TSnap::PrintInfo(Graph, "Graph info");
  PNGraph MxWcc = TSnap::GetMxWcc(Graph);
  TSnap::PrintInfo(MxWcc, "Largest Weakly connected component");
  // random graph
  PNGraph RndGraph = TSnap::GenRndGnm<PNGraph>(100, 1000);
  TGStat GraphStat(RndGraph, TSecTm(1), TGStat::AllStat(), "Gnm graph");
  GraphStat.PlotAll("RndGraph", "Random graph on 1000 nodes");
  // Forest Fire graph
  { TFfGGen ForestFire(false, 1, 0.35, 0.30, 1.0, 0.0, 0.0);
  ForestFire.GenGraph(100);
  PNGraph FfGraph = ForestFire.GetGraph(); }
  // network
  TPt<TNodeEDatNet<TStr, TStr> > Net = TNodeEDatNet<TStr, TStr>::New();
  Net->AddNode(0, "zero");
  Net->AddNode(1, "one");
  Net->AddEdge(0, 1, "zero to one");

  const PNGraph DirectedGraph = TNGraph::New();
  for (int i = 0; i < 10; i++) {
    DirectedGraph->AddNode(i);
  }

  DirectedGraph->AddEdge(0, 1);
  DirectedGraph->AddEdge(1, 2);
  DirectedGraph->AddEdge(2, 3);
  DirectedGraph->AddEdge(3, 4);
  DirectedGraph->AddEdge(4, 5);
  DirectedGraph->AddEdge(5, 6);
  DirectedGraph->AddEdge(6, 7);
  DirectedGraph->AddEdge(7, 2);
  DirectedGraph->AddEdge(8, 9);

  // TIntFltH nodeBtwH;
  // TIntPrFltH edgeBtwH;

  // printf("Testing Betweenness Centrality Calculation \n");
  // TSnap::GetBetweennessCentr<PNGraph> (DirectedGraph, nodeBtwH, edgeBtwH, true);
  // for (TIntFltH::TIter It = nodeBtwH.BegI(); It < nodeBtwH.EndI(); It++) {
  //   int node_id = It.GetKey();
  //   double centr = It.GetDat();
  //   printf("NodeId: %d, Centr: %f \n", node_id, centr);
  // }

  const PNEANet graph = TNEANet::New();
  for (int i = 0; i < 10; i++) {
    graph->AddNode(i);
  }

  graph->AddEdge(0, 2);
  graph->AddEdge(1, 7);
  graph->AddEdge(2, 6);
  graph->AddEdge(3, 5);
  graph->AddEdge(4, 3);
  graph->AddEdge(5, 6);
  graph->AddEdge(7, 0);
  graph->AddEdge(8, 2);
  graph->AddEdge(9, 5);

  TIntFltH pathLength;
  TFltV attr, attr1;
  attr.Add(0.5);
  attr.Add(1.0);
  attr.Add(0.5);
  attr.Add(1.0);
  attr.Add(0.5);
  attr.Add(1.0);
  attr.Add(0.5);
  attr.Add(1.0);
  attr.Add(0.5);
  
  printf("Testing Closeness Centrality Calculation \n");
  for (TNEANet::TNodeI NI = graph->BegNI(); NI < graph->EndNI(); NI++) {
    int id = NI.GetId();
    double centr = TSnap::GetWeightedClosenessCentr(graph, id, true, attr);
    printf("NodeId: %d, Centr: %f \n", id, centr);
  }

  TIntFltH nodeBtwH;
  TIntPrFltH edgeBtwH;

  printf("Testing Betweenness Centrality Calculation \n");
  TSnap::GetWeightedBetweennessCentr (graph, nodeBtwH, edgeBtwH, attr, true);
  for (TIntFltH::TIter It = nodeBtwH.BegI(); It < nodeBtwH.EndI(); It++) {
    int node_id = It.GetKey();
    double centr = It.GetDat();
    printf("NodeId: %d, Centr: %f \n", node_id, centr);
  }

  PNGraph G= TSnap::LoadEdgeList<PNGraph>("../../cs399/soc-LiveJournal1.txt", 0, 1);

  // clock_t t1,t2;
  // t1=clock();
  // printf("Testing Performance of Closeness Centrality Calculation \n");
  // for (TNGraph::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) {
  //   int id = NI.GetId();
  //   double centr = TSnap::GetClosenessCentr<PNGraph>(G, id, true);
  //   printf("NodeId: %d, Centr: %f \n", id, centr);
  //   if (id == 10) {
  //     break;
  //   }
  // }
  // t2=clock();
  // float diff ((float)t2-(float)t1);
  // printf("%lf \n", diff);
  // t1 = clock();
  // for (TNGraph::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) {
  //   int id = NI.GetId();
  //   double centr = TSnap::GetClosenessCentrMP<PNGraph>(G, id, true);
  //   printf("NodeId: %d, Centr: %f \n", id, centr);
  //   if (id == 10) {
  //     break;
  //   }
  // }
  // t2=clock();
  // diff = (float)t2-(float)t1;
  // printf("%lf \n", diff);

  printf("Testing Betweenness Centrality Calculation \n");
  TSnap::GetWeightedBetweennessCentr (graph, nodeBtwH, edgeBtwH, attr, true);
  for (TIntFltH::TIter It = nodeBtwH.BegI(); It < nodeBtwH.EndI(); It++) {
    int node_id = It.GetKey();
    double centr = It.GetDat();
    printf("NodeId: %d, Centr: %f \n", node_id, centr);
  }


  return 0;
}
