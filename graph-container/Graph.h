#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MATRIX_SIZE 50
#define NO_NODE "Node doest`t exists!"
#define NO_ARC "Arc doesn`t exists!"


template <class T>
class Graph
{
	template <class T>
	class Node
	{
	public:
		T data;
		int number;
		
		Node () {}
		Node(Graph<T>& graph, T data)
		{
			this->data = data;
			this->number = graph.node_counter;
			graph.node_counter++;
		}
		~Node() {}

		T get_data() { return this->data; }
	};

	template <class T>
	class Arc
	{
	public:
		Node<T>* begin;
		Node<T>* end;
		int number;

		Arc(Graph<T>& graph)
		{ 
			this->number = graph.arc_counter;
			graph.arc_counter++;
		}
		Arc(Graph<T> & graph, Node<T> &begin, Node<T> &end)
		{
			this->begin = begin;
			this->end = end;

			this->number = graph.arc_counter;
			graph.arc_counter++;
		}

		int get_begin_number() { return this->begin->number; }
		int get_end_number() { return this->end->number; }
	};


	/*vector<Node<T>> nodes;
	vector<Arc<T>> arcs;*/
	vector<vector<int>> matrix;

	int node_counter;
	int arc_counter;

	void delete_node_from_matrix(int number);
	void delete_arc_from_matrix(int number);
	void clear_matrix();
	static void copy_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2);
	static bool compare_by_matrix(const Graph<T> &graph1, const Graph<T>& graph2);


	vector<Node<T>> nodes;
	vector<Arc<T>> arcs;
public:
	template <class T>
	class GraphIterator
	{
		vector<typename T::iterator> ptr;
		bool reverse;
	public:
		GraphIterator(bool reverse = false) 
		{
			this->reverse = reverse;
		}
		~GraphIterator() {}

		void operator=(T* ptr) {
			this->ptr = ptr;
		}
		T* operator+(int n) {
			if (!this->reverse) {
				return this->ptr + n;
			}
			else {
				return this->ptr - n;
			}
		}
		T* operator-(int n) {
			if (!this->reverse) {
				return this->ptr - n;
			}
			else {
				return this->ptr + n;
			}
		}
		T* operator++(int) {
			if (!this->reverse) {
				return this->ptr++;
			}
			else {
				return this->ptr--;
			}
		}
		T* operator--(int) {
			if (!this->reverse) {
				return this->ptr--;
			}
			else {
				return this->ptr++;
			}
		}
		T* operator++() {
			if (!this->reverse) {
				return ++this->ptr;
			}
			else {
				return --this->ptr;
			}
		}
		T* operator--() {
			if (!this->reverse) {
				return --this->ptr;
			}
			else {
				return ++this->ptr;
			}
		}
		bool operator!=(GraphIterator& it) { return this->ptr != it.ptr; }
		bool operator==(GraphIterator& it) { return this->ptr == it.ptr; }
		T& operator*() { return *this->ptr; }
	};

	typedef GraphIterator<Graph<T>::Node<T>> node_iterator;
	typedef GraphIterator<Graph<T>::Arc<T>> arc_iterator;

	Graph()
	{
		this->node_counter = 0;
		this->arc_counter = 0;

		for (size_t i = 0; i < MATRIX_SIZE; ++i)
		{
			vector<int> temp;
			for (size_t j = 0; j < MATRIX_SIZE; ++j)
				temp.push_back(0);
			this->matrix.push_back(temp);
		}
	}

	Graph(Graph<T>& graph)
	{
		this->node_counter = graph.node_counter;
		this->arc_counter = graph.arc_counter;

		for (size_t i = 0; i < MATRIX_SIZE; ++i)
		{
			vector<int> temp;
			for (size_t j = 0; j < MATRIX_SIZE; ++j)
				temp.push_back(graph.matrix[i][j]);
			this->matrix.push_back(temp);
		}

		for (auto node : graph.nodes)
			this->nodes.push_back(node);

		for (auto arc : graph.arcs)
			this->arcs.push_back(arc);
	}
	~Graph() {}

	void add_node(T data);
	void add_arc(int begin, int end);
	void delete_node(T data);
	void delete_node(int number);
	void delete_arc(int begin, int end);
	void delete_arc(int number);

	int get_nodes_count() { return this->nodes.size(); }
	int get_arcs_count() { return this->arcs.size(); }
	int get_node_degree(int number);
	int get_arc_degree(int number);
	T get_node_data(int number); // what return if NO_NODE

	bool is_node_exists(int number);
	bool is_node_exists(T data);
	bool is_arc_exists(int begin, int end);
	bool is_arc_exists(int number);
	bool is_empty();

	vector<int> get_incident_arcs(int number);
	vector<int> get_adjance_nodes(int number); 

	void show_graph();
	void clear_graph();

	void operator=(Graph<T>& graph);
	bool operator==(Graph<T>& graph);
	bool operator!=(Graph<T>& graph);
	bool operator>(Graph<T>& graph);
	bool operator<(Graph<T>& graph);
	bool operator>=(Graph<T>& graph);
	bool operator<=(Graph<T>& graph);

	template <class T>
	vector<typename Node<T>::iterator> node_begin() { return this->nodes.begin(); }
	template <class T>
	vector<typename Node<T>::iterator> node_end() { return this->nodes.end(); }
	template <class T>
	vector<typename Arc<T>::iterator> arc_begin() { return this->arcs.begin(); }
	template <class T>
	vector<typename Arc<T>::iterator> arc_end() { return this->arcs.end(); }
};


template<class T>
inline void Graph<T>::delete_node_from_matrix(int number)
{
	vector<int> adjance_nodes = get_adjance_nodes(number);
	vector<int> incidence_arcs = get_incident_arcs(number);
	for (auto adj_node : adjance_nodes)
		for (size_t i = 0; i < this->nodes.size(); ++i)
			if (this->matrix[adj_node][i] != 0 && this->matrix[number][i] != 0)
			{
				this->matrix[number][i] = 0;
				this->matrix[adj_node][i] = 0;
			}

	for (auto el : incidence_arcs)
		delete_arc(el);
}

template<class T>
inline void Graph<T>::delete_arc_from_matrix(int number)
{
	for (auto& node : this->matrix)
		node[number] = 0;
}

template<class T>
inline void Graph<T>::clear_matrix()
{
	for (auto &node : this->matrix)
		for (auto &arc : node)
			arc = 0;
}

template<class T>
void Graph<T>::copy_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2)
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
		for (size_t j = 0; j < MATRIX_SIZE; ++j)
			matrix1[i][j] = matrix2[i][j];
}

template<class T>
bool Graph<T>::compare_by_matrix(const Graph<T>& graph1, const Graph<T>& graph2)
{
	for (size_t i = 0; i < graph1.nodes.size(); ++i)
		for (size_t j = 0; j < graph1.arcs.size(); j++)
			if (graph1.matrix[i][j] != graph2.matrix[i][j])
				return false;

	return true;
}

template<class T>
inline void Graph<T>::add_node(T data)
{
	Node<T> node(*this, data);
	this->nodes.push_back(node);
}

template<class T>
inline void Graph<T>::add_arc(int begin, int end)
{
	try
	{
		if (!(is_node_exists(begin) && is_node_exists(end)))
			throw -1;

		Arc<T> arc(*this);
		for (auto &node : this->nodes)
		{
			if (node.number == begin)
				arc.begin = &node;
			if (node.number == end)
				arc.end = &node;
		}
		this->arcs.push_back(arc);

		this->matrix[begin][arc.number] = 1;
		this->matrix[end][arc.number] = -1;
	}
	catch (int error)
	{
		cout << "\nadd_arc: " << NO_NODE << endl;
	}
}

template<class T>
inline void Graph<T>::delete_node(T data)
{
	try
	{
		if (!is_node_exists(data))
			throw - 1;

		for (auto node : this->nodes)
			if (node.data == data)
				delete_node(node.number);
	}
	catch (int error)
	{
		cout << "\ndelete_node: " << NO_NODE << endl;
	}
}

template<class T>
inline void Graph<T>::delete_node(int number)
{
	try
	{
		if (!is_node_exists(number))
			throw - 1;

		delete_node_from_matrix(number);
		this->nodes.erase(this->nodes.begin() + number);
	}
	catch (int error)
	{
		cout << "\ndelete_node: " << NO_NODE << endl;
	}
}

template<class T>
inline void Graph<T>::delete_arc(int begin, int end)
{
	try
	{
		if (!(is_node_exists(begin) && is_node_exists(end)))
			throw - 1;

		for (auto arc : this->arcs)
			if (arc.get_begin_number() == begin && arc.get_end_number() == end)
				delete_arc(arc.number);
	}
	catch (int error)
	{
		cout << "\ndelete_arc: " << NO_NODE << endl;
	}
}

template<class T>
inline void Graph<T>::delete_arc(int number)
{
	try
	{
		if (!is_arc_exists(number))
			throw - 1;

		delete_arc_from_matrix(number);
		for (size_t i = 0; i < this->arcs.size(); ++i)
			if (this->arcs[i].number == number)
				this->arcs.erase(this->arcs.begin() + i);
	}
	catch (int error)
	{
		cout << "\ndelete_arc: " << NO_ARC << endl;
	}
}

template<class T>
inline bool Graph<T>::is_node_exists(int number)
{
	for (auto node : this->nodes)
		if (node.number == number)
			return true;

	return false;
}

template<class T>
inline bool Graph<T>::is_node_exists(T data)
{
	for (auto node : this->nodes)
		if (node.data == data)
			return true;

	return false;
}

template<class T>
inline bool Graph<T>::is_arc_exists(int begin, int end)
{
	try
	{
		if (!(is_node_exists(begin) && is_node_exists(end)))
			throw - 1;

		for (size_t i = 0; i < this->nodes.size(); ++i)
			if (this->matrix[begin][i] != 0 && this->matrix[end][i] != 0 && begin != end)
				return true;

		return false;
	}
	catch (int error)
	{
		cout << "\nis_arc_exists: " << NO_NODE << endl;
	}
}

template<class T>
inline bool Graph<T>::is_arc_exists(int number)
{
	for (auto &arc : this->arcs)
		if (arc.number == number)
			return true;

	return false;
}

template<class T>
inline bool Graph<T>::is_empty()
{
	if (this->nodes.size() == 0)
		return true;

	return false;
}

template<class T>
inline vector<int> Graph<T>::get_incident_arcs(int number)
{
	vector<int> incidence_arcs;
	try
	{
		if (!is_node_exists(number))
			throw - 1;

		for (size_t i = 0; i < this->matrix[number].size(); ++i)
			if (this->matrix[number][i] != 0)
				incidence_arcs.push_back(i);

		return incidence_arcs;
	}
	catch (int error)
	{
		cout << "\nget_incident_arcs: " << NO_NODE << endl;
		return incidence_arcs;
	}
}

template<class T>
inline vector<int> Graph<T>::get_adjance_nodes(int number)
{
	vector<int> adjance_nodes;
	try
	{
		if (!is_node_exists(number))
			throw - 1;

		for (auto node : this->nodes)
			if (is_arc_exists(number, node.number) || is_arc_exists(node.number, number))
				adjance_nodes.push_back(node.number);

		return adjance_nodes;
	}
	catch (int error)
	{
		cout << "\nget_adjance_nodes: " << NO_NODE << endl;
		return adjance_nodes;
	}
}

template<class T>
inline int Graph<T>::get_node_degree(int number)
{
	try
	{
		if (!is_node_exists(number))
			throw - 1;

		int degree = 0;
		for (auto el : this->matrix[number])
		{
			if (el == -1)
				continue;
			else
				degree += el;
		}


		return degree;
	}
	catch (int error)
	{
		cout << "\nget_node_degree: " << NO_NODE << endl;
		return -1;
	}
}

template<class T>
inline int Graph<T>::get_arc_degree(int number)
{
	try
	{
		if (!is_arc_exists(number))
			throw - 1;

		return 2;
	}
	catch (int error)
	{
		cout << "\nget_arc_degree: " << NO_ARC << endl;
		return -1;
	}
}

template<class T>
inline T Graph<T>::get_node_data(int number)
{
	try
	{
		if (!is_node_exists(number))
			throw - 1;

		for(auto node : this->nodes)
			if (node.number = number)
				return node.data;
	}
	catch (int error)
	{
		cout << "\nget_node_data: " << NO_NODE << endl;
		return this->nodes[0].data;
	}
}

template<class T>
inline void Graph<T>::show_graph()
{
	cout << "\t";
	for (size_t i = 0; i < this->arcs.size(); ++i)
		cout << "A" << this->arcs[i].number << "\t";
	cout << endl << endl;
	for (size_t i = 0; i < this->nodes.size(); ++i)
	{
		cout << "N" << this->nodes[i].number;
		for(auto &arc : this->arcs)
			cout << "\t" + to_string(this->matrix[this->nodes[i].number][arc.number]);
		cout << endl;
	}
}

template<class T>
inline void Graph<T>::clear_graph()
{
	clear_matrix();
	this->nodes.clear();
	this->arcs.clear();
}

template<class T>
inline void Graph<T>::operator=(Graph<T>& graph)
{
	this->clear_matrix();
	this->nodes.clear();
	this->arcs.clear();

	this->node_counter = graph.node_counter;
	this->arc_counter = graph.arc_counter;

	for (auto node : graph.nodes)
		this->nodes.push_back(node);

	for (auto arc : graph.arcs)
		this->arcs.push_back(arc);

	copy_matrix(this->matrix, graph.matrix);
}

template<class T>
bool Graph<T>::operator==(Graph<T>& graph)
{
	if (this->get_nodes_count() == graph.get_nodes_count())
		return compare_by_matrix(*this, graph);

	return false;
}

template<class T>
inline bool Graph<T>::operator!=(Graph<T>& graph)
{
	return !(*this == graph);
}

template<class T>
inline bool Graph<T>::operator>(Graph<T>& graph)
{
	if (this->get_nodes_count() > graph.get_nodes_count())
		return compare_by_matrix(graph, *this);

	return false;
}

template<class T>
inline bool Graph<T>::operator<(Graph<T>& graph)
{
	if (this->get_nodes_count() < graph.get_nodes_count())
		return compare_by_matrix(*this, graph);

	return false;
}

template<class T>
inline bool Graph<T>::operator>=(Graph<T>& graph)
{
	if (this->get_nodes_count() >= graph.get_nodes_count())
		return compare_by_matrix(graph, *this);

	return false;
}

template<class T>
inline bool Graph<T>::operator<=(Graph<T>& graph)
{
	if (this->get_nodes_count() <= graph.get_nodes_count())
		return compare_by_matrix(*this, graph);

	return false;
}
