#include <iostream>
#include <string>
#include "Graph.h"
#include "Menu.h"

using namespace std;

typedef string val_type;


int main()
{
	Graph<val_type> graph;
	menu(graph);


	Graph<val_type> graph2;
	menu(graph2);


	return 0;
}

std::ostream& operator<<(std::ostream& out, Graph<val_type>& graph)
{
	graph.show_graph();
	return out;
}