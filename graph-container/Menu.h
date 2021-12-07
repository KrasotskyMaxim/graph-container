#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

typedef string val_type;

enum KEYS
{
	CLEAR = 0,
	IS_EMPTY = 10,
	ADD_NODE = 1,
	DELETE_NODE = 11,
	ADD_ARC = 2,
	DELETE_ARC = 22,
	ADJ_NODES = 3,
	INCIDENCE_ARCS = 33,
	IS_NODE_EXISTS = 4,
	IS_ARC_EXISTS = 44,
	NODE_DATA = 5,
	NODE_DEGREE = 55,
	SHOW = 100,
	EXIT = -1
};

Graph<val_type> menu(Graph<val_type> &graph)
{
	cout << "0. clear graph\n"
		<< "10. is empty\n"
		<< "1. Add node\n"
		<< "11. Delete node\n"
		<< "2. Add arc\n"
		<< "22. Delete arc\n"
		<< "3. Get adjance nodes\n"
		<< "33. Get incidence arcs\n"
		<< "4. Is node exists\n"
		<< "44. Is arc exists\n"
		<< "5. Get node data\n"
		<< "55. Get node degree\n"
		<< "100. Show graph\n"
		<< "-1. Exit\n";

	int key, number, choose;
	val_type data;
	while (true)
	{
		f0:
		cout << "Enter key: ";
		cin >> key;
		switch (key)
		{
		case CLEAR:
			graph.clear_graph();
			break;
		case IS_EMPTY:
			if (graph.is_empty())
				cout << "\nYes\n";
			else cout << "\nNo\n";
			break;
		case ADD_NODE:
			cout << "\nEnter data: ";
			cin >> data;
			graph.add_node(data);
		case ADD_ARC:
			int begin, end;
			cout << "\nEnter begin and end: ";
			cin >> begin >> end;
			graph.add_arc(begin, end);
		case DELETE_NODE:
			f1:
			int choose;
			cout << "\nd - by data\nn - by number\nEnter: ";
			cin >> choose;
			switch (choose)
			{
			case  0:
				cout << "\nEnter target data: ";
				cin >> data;
				graph.delete_node(data);
				break;
			case 1:
				cout << "\nEnter node number: ";
				cin >> number;
				graph.delete_node(number);
				break;
			default:
				cout << "\nIncorrect input!\n";
				goto f1;
				break;
			}
			break;
		case ADJ_NODES:
			cout << "\nEnter node number: ";
			cin >> number;
			for (auto node : graph.get_adjance_nodes(number))
				cout << node << "\t";
			break;
		case INCIDENCE_ARCS:
			cout << "\nEnter node number: ";
			cin >> number;
			for (auto arc : graph.get_incident_arcs(number))
				cout << arc << "\t";
			break;
		case IS_NODE_EXISTS:
			f2:
			cout << "\nd - by data\nn - by number\nEnter: ";
			cin >> choose;
			switch (choose)
			{
			case 0:
				cout << "\nEnter target data: ";
				cin >> data;
				if (graph.is_node_exists(data))
					cout << "\nYes\n";
				else cout << "\nNo\n";
				break;
			case 1:
				cout << "\nEnter node number: ";
				cin >> number;
				if (graph.is_node_exists(number))
					cout << "\nYes\n";
				else cout << "\nNo\n";
				break;
			default:
				cout << "\nIncorrect input!\n";
				goto f2;
				break;
			}
			break;
		case IS_ARC_EXISTS:
			f3:
			cout << "\nd - begin - end\nn - by number\nEnter: ";
			cin >> choose;
			switch (choose)
			{
			case 0:
				int begin, end;
				cout << "\nEnter begin and end: ";
				cin >> begin >> end;
				if (graph.is_arc_exists(begin, end))
					cout << "\nYes\n";
				else cout << "\nNo\n";
				break;
			case 1:
				cout << "\nEnter node number: ";
				cin >> number;
				if (graph.is_arc_exists(number))
					cout << "\nYes\n";
				else cout << "\nNo\n";
				break;
			default:
				cout << "\nIncorrect input!\n";
				goto f3;
				break;
			}
			break;
		case NODE_DATA:
			cout << "\nEnter node number: ";
			cin >> number;
			cout << "\ndata: " << graph.get_node_data(number);
			break;
		case NODE_DEGREE:
			cout << "\nEnter node number: ";
			cin >> number;
			cout << "\nnode degree: " << graph.get_node_degree(number);
			break;
		case SHOW:
			graph.show_graph();
			break;
		case -1:
			return graph;
		default:
			cout << "\nIncorrect input!\n";
			goto f0;
			break;
		}
	}
}