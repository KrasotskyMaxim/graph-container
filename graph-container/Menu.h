#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;


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
	CLEAR_CONSOLE = -100,
	EXIT = -1
};

template <typename T2>
void comparing(Graph<T2>& graph, Graph<T2>& graph2);
void menu_logo();
void show_arc_it(pair<int, int>& it);
void show_arc_it(const pair<int, int>& it);

template <typename T1>
Graph<T1> menu(Graph<T1> &graph)
{	
	menu_logo();
	int key, number, choose;
	T1 data;
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
			break;
		case ADD_ARC:
			int begin, end;
			cout << "\nEnter begin and end: ";
			cin >> begin >> end;
			graph.add_arc(begin, end);
			break;
		case DELETE_NODE:
			f1:
			int choose;
			cout << "\n0 - by data\n1 - by number\nEnter: ";
			cin >> choose;
			switch (choose)
			{
			case 0:
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
			cout << "\n0 - by data\n1 - by number\nEnter: ";
			cin >> choose;
			switch (choose)
			{
			case 0:
				cout << "\nEnter target data: ";
				cin >> data;
				if (graph.is_node_exists(data))
					cout << "\nYes\n";
				else 
					cout << "\nNo\n";
				break;
			case 1:
				cout << "\nEnter node number: ";
				cin >> number;
				if (graph.is_node_exists(number))
					cout << "\nYes\n";
				else 
					cout << "\nNo\n";
				break;
			default:
				cout << "\nIncorrect input!\n";
				goto f2;
				break;
			}
			break;
		case IS_ARC_EXISTS:
			f3:
			cout << "\n0 - begin - end\n1 - by number\nEnter: ";
			cin >> choose;
			switch (choose)
			{
			case 0:
				int begin, end;
				cout << "\nEnter begin and end: ";
				cin >> begin >> end;
				if (graph.is_arc_exists(begin, end))
					cout << "\nYes\n";
				else 
					cout << "\nNo\n";
				break;
			case 1:
				cout << "\nEnter node number: ";
				cin >> number;
				if (graph.is_arc_exists(number))
					cout << "\nYes\n";
				else 
					cout << "\nNo\n";
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
			cout << "\ndata: " << graph.get_node_data(number) << endl;
			break;
		case NODE_DEGREE:
			cout << "\nEnter node number: ";
			cin >> number;
			cout << "\nnode degree: " << graph.get_node_degree(number) << endl;
			break;
		case SHOW:
			cout << graph;
			break;
		case CLEAR_CONSOLE:
			system("cls");
			menu_logo();
			break;
		case EXIT:
			return graph;
		default:
			cout << "\nIncorrect input!\n";
			goto f0;
			break;
		}
	}
}


void menu_logo()
{
	cout << "\n0. clear graph\n"
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
		<< "-100. clear console\n"
		<< "-1. Exit\n";
}

inline void show_arc_it(pair<int, int>& it)
{
	cout << endl << it.first << " -> " << it.second << endl;
}

inline void show_arc_it(const pair<int, int>& it)
{
	cout << endl << it.first << " -> " << it.second << endl;
}

template <typename T2>
void comparing(Graph<T2>& graph, Graph<T2>& graph2)
{
	cout << "\ncompairing graph1 and graph2:\t";
	cout << (graph == graph2)
		<< "\t" << (graph != graph2)
		<< "\t" << (graph > graph2)
		<< "\t" << (graph < graph2)
		<< "\t" << (graph >= graph2)
		<< "\t" << (graph <= graph2);
	cout << endl << endl;
}