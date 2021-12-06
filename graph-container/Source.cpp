#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;


int main()
{
	Graph<string> graph;
	graph.add_node("a");
	graph.add_node("b");
	graph.add_node("c");
	graph.add_arc(1, 2);
	graph.add_arc(2, 1);
	graph.add_arc(1, 0);
	
	/*graph.show_graph();
	graph.delete_arc(1, 2);
	graph.show_graph();*/

	Graph<string> graph2(graph);

	bool is = graph == graph2;
	cout << is;

	return 0;
}