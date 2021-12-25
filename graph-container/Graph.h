#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


#define MATRIX_SIZE 50
#define NO_NODE "Node doest`t exists!"
#define NO_ARC "Arc doesn`t exists!"


template <class GraphType>
class Graph
{

	friend std::ostream& operator<<(ostream& out, pair<int, int>& it);
	friend std::ostream& operator<<(std::ostream& out, Graph<GraphType>& graph);
private:
	template <class NodeType>
	class Node
	{
	public:
		NodeType data;
		int number;
		
		Node () {}
		Node(Graph<NodeType>& graph, NodeType data)
		{
			this->data = data;
			this->number = graph.node_counter;
			graph.node_counter++;
		}
		~Node() {}

		NodeType get_data() { return this->data; }
	};

	template <class ArcType>
	class Arc
	{
	public:
		Node<ArcType>* begin;
		Node<ArcType>* end;
		int number;

		Arc(Graph<ArcType>& graph)
		{ 
			this->number = graph.arc_counter;
			graph.arc_counter++;
		}
		Arc(Graph<ArcType> & graph, Node<ArcType> &begin, Node<ArcType> &end)
		{
			this->begin = begin;
			this->end = end;

			this->number = graph.arc_counter;
			graph.arc_counter++;
		}

		int get_begin_number() { return this->begin->number; }
		int get_end_number() { return this->end->number; }
	};
	vector<Node<GraphType>> nodes;
	vector<Arc<GraphType>> arcs;
	vector<vector<int>> matrix;
	vector<pair<int, int>> arc_nodes;
	vector<GraphType> nodes_data;

	int node_counter;
	int arc_counter;

	void delete_node_from_matrix(int number);
	void delete_arc_from_matrix(int number);
	void clear_matrix();
	static void copy_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2);
	static bool compare_by_matrix(const Graph<GraphType> &graph1, const Graph<GraphType>& graph2);

	void show_graph();

public:
	class NodeIterator
	{
	protected:
		GraphType* ptr;
	public:
		NodeIterator() {}
		NodeIterator(GraphType* ptr) { this->ptr = ptr; }

		void operator=(GraphType* ptr) { this->ptr = ptr; }
		GraphType* operator+(int n) { return this->ptr + n; }
		GraphType* operator-(int n) { return this->ptr - n; }
		GraphType* operator++(int) { return this->ptr++; }
		GraphType* operator--(int) { return this->ptr--; }

		bool operator!=(NodeIterator& it) { return this->ptr != it.ptr; }
		bool operator==(NodeIterator& it) { return this->ptr == it.ptr; }
		GraphType& operator*() { return *this->ptr; }
	};

	class ConstNodeIterator : public NodeIterator
	{
	protected:
		const GraphType* ptr;
	public:
		ConstNodeIterator() {}
		ConstNodeIterator(const GraphType* ptr) { this->ptr = ptr; }

		const GraphType* operator=(const GraphType* ptr) { this->ptr = ptr; }
		const GraphType* operator+(int n) { return this->ptr + n; }
		const GraphType* operator-(int n) { return this->ptr - n; }
		const GraphType* operator++(int) { return this->ptr++; }
		const GraphType* operator--(int) { return this->ptr--; }

		bool operator!=(const NodeIterator& it) { return this->ptr != it.ptr; }
		bool operator==(const NodeIterator& it) { return this->ptr == it.ptr; }
		const GraphType& operator*() { return *this->ptr; }
	};
	
	class ReverseNodeIterator : public NodeIterator
	{
	public:
		ReverseNodeIterator() {}
		ReverseNodeIterator(GraphType* ptr) : NodeIterator(ptr) {}

		GraphType* operator+(int n) { return this->ptr - n; }
		GraphType* operator-(int n) { return this->ptr + n; }
		GraphType* operator++(int) { return this->ptr--; }
		GraphType* operator--(int) { return this->ptr++; }
	};

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

	class ArcIterator
	{
	protected:
		pair<int, int>* ptr;
	public:
		ArcIterator() {}
		ArcIterator(pair<int, int>* ptr) { this->ptr = ptr; }

		void operator=(pair<int, int>* ptr) { this->ptr = ptr; }
		pair<int, int>* operator+(int n) { return this->ptr + n; }
		pair<int, int>* operator-(int n) { return this->ptr - n; }
		pair<int, int>* operator++(int) { return this->ptr++; }
		pair<int, int>* operator--(int) { return this->ptr--; }

		bool operator!=(ArcIterator& it) { return this->ptr != it.ptr; }
		bool operator==(ArcIterator& it) { return this->ptr == it.ptr; }
		pair<int, int>& operator*() { return *this->ptr; }
	};

	class ConstArcIterator : public ArcIterator
	{
	protected:
		const pair<int, int>* ptr;
	public:
		ConstArcIterator() {}
		ConstArcIterator(const pair<int, int>* ptr) { this->ptr = ptr; }

		void operator=(const pair<int, int>* ptr) { this->ptr = ptr; }
		const pair<int, int>* operator+(int n) { return this->ptr + n; }
		const pair<int, int>* operator-(int n) { return this->ptr - n; }
		const pair<int, int>* operator++(int) { return this->ptr++; }
		const pair<int, int>* operator--(int) { return this->ptr--; }

		bool operator!=(const ArcIterator& it) { return this->ptr != it.ptr; }
		bool operator==(const ArcIterator& it) { return this->ptr == it.ptr; }
		const pair<int, int>& operator*() { return *this->ptr; }
	};

	class ReverseArcIterator : public ArcIterator
	{
	public:
		ReverseArcIterator() {}
		ReverseArcIterator(pair<int, int>* ptr) : ArcIterator(ptr) {}

		pair<int, int>* operator+(int n) { return this->ptr - n; }
		pair<int, int>* operator-(int n) { return this->ptr + n; }
		pair<int, int>* operator++(int) { return this->ptr--; }
		pair<int, int>* operator--(int) { return this->ptr++; }
	};

	Graph(Graph<GraphType>& graph)
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

	void add_node(GraphType data);
	void add_arc(int begin, int end);
	void delete_node(GraphType data);
	void delete_node(int number);
	void delete_node(NodeIterator it);
	void delete_arc(int begin, int end);
	void delete_arc(int number);
	void delete_arc(GraphType begin, GraphType end);
	void delete_arc(NodeIterator begin, NodeIterator end);
	void delete_arc(ArcIterator it);

	int get_nodes_count() { return this->nodes.size(); }
	int get_arcs_count() { return this->arcs.size(); }
	int get_node_degree(int number);
	int get_arc_degree(int number);
	GraphType get_node_data(int number);

	bool is_node_exists(int number);
	bool is_node_exists(GraphType data);
	bool is_arc_exists(int begin, int end);
	bool is_arc_exists(int number);
	bool is_empty();

	vector<int> get_incident_arcs(int number);
	vector<int> get_adjance_nodes(int number); 

	void clear_graph();

	void operator=(Graph<GraphType>& graph);
	bool operator==(Graph<GraphType>& graph);
	bool operator!=(Graph<GraphType>& graph);
	bool operator>(Graph<GraphType>& graph);
	bool operator<(Graph<GraphType>& graph);
	bool operator>=(Graph<GraphType>& graph);
	bool operator<=(Graph<GraphType>& graph);

	typedef Graph<GraphType>::NodeIterator node_iterator;
	typedef Graph<GraphType>::ConstNodeIterator const_node_iterator;
	typedef Graph<GraphType>::ReverseNodeIterator reverse_node_iterator;
	typedef Graph<GraphType>::ArcIterator arc_iterator;
	typedef Graph<GraphType>::ConstArcIterator const_arc_iterator;
	typedef Graph<GraphType>::ReverseArcIterator reverse_arc_iterator;

	NodeIterator get_node_iterator(GraphType data)
	{
		try
		{
			if (!is_node_exists(data))
				throw - 1;

			for (size_t i = 0; i < this->nodes.size(); ++i)
				if (this->nodes[i].data == data)
				{
					NodeIterator it(&(*(this->nodes_data.begin() + i)));
					return it;
				}
		}
		catch (int error)
		{
			cout << "\nget_node_iterator: " << NO_NODE << endl;
		}
	}

	ArcIterator get_arc_iterator(int number)
	{
		try
		{
			if (!is_arc_exists(number))
				throw - 1;

			for (size_t i = 0; i < this->arcs.size(); ++i)
				if (this->arcs[i].number == number)
				{
					ArcIterator it(&(*(this->arc_nodes.begin() + i)));
					return it;
				}
		}
		catch (int error)
		{
			cout << "\nget_arc_iterator: " << NO_ARC << endl;
		}
	}

	ConstNodeIterator cbegin()
	{
		try
		{
			if (this->nodes.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\ncbegin: No nodes!\n";
		}
		const GraphType* p = &(*(this->nodes_data.cbegin()));
		ConstNodeIterator it(p);
		return it;
	}

	ConstArcIterator arc_cbegin()
	{
		try
		{
			if (this->arcs.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nbegin: No arcs!\n";
		}
		const pair<int, int>* p = &(*(this->arc_nodes.cbegin()));
		ConstArcIterator it(p);
		return it;
	}

	ConstNodeIterator cend()
	{
		try
		{
			if (this->nodes.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\ncbegin: No nodes!\n";
		}
		const GraphType* p = &(*(this->nodes_data.cend()));
		ConstNodeIterator it(p);
		return it;
	}

	ConstArcIterator arc_cend()
	{
		try
		{
			if (this->arcs.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nbegin: No arcs!\n";
		}
		const pair<int, int>* p = &(*(this->arc_nodes.cend()));
		ConstArcIterator it(p);
		return it;
	}

	NodeIterator begin()
	{
		try
		{
			if (this->nodes.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nbegin: No nodes!\n";
		}
		GraphType* p = &(*(this->nodes_data.begin()));
		NodeIterator it(p);
		return it;
	}


	ArcIterator arc_begin()
	{
		try
		{
			if (this->arcs.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nbegin: No arcs!\n";
		}
		pair<int, int>* p = &(*(this->arc_nodes.begin()));
		ArcIterator it(p);
		return it;
	}

	NodeIterator end()
	{
		try
		{
			if (this->nodes.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nend: No nodes!\n";
		}
		GraphType* p = &(*(this->nodes_data.end()-1));
		NodeIterator it(p);
		return it;
	}

	ArcIterator arc_end()
	{
		try
		{
			if (this->arcs.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nbegin: No arcs!\n";
		}
		pair<int, int>* p = &(*(this->arc_nodes.end()-1));
		ArcIterator it(p);
		return it;
	}

	ReverseNodeIterator rbegin()
	{
		try
		{
			if (this->nodes.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nrbegin: No nodes!\n";
		}
		GraphType* p = &(*(this->nodes_data.end()-1));
		ReverseNodeIterator it(p);
		return it;
	}

	ReverseArcIterator arc_rbegin()
	{
		try
		{
			if (this->arcs.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nbegin: No arcs!\n";
		}
		pair<int, int>* p = &(*(this->arc_nodes.end()-1));
		ReverseArcIterator it(p);
		return it;
	}

	ReverseNodeIterator rend()
	{
		try
		{
			if (this->nodes.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nrend: No nodes!\n";
		}
		GraphType* p = &(*(this->nodes_data.begin()));
		ReverseNodeIterator it(p);
		return it;
	}

	ReverseArcIterator arc_rend()
	{
		try
		{
			if (this->arcs.size() < 2)
				throw - 1;
		}
		catch (int error)
		{
			cout << "\nbegin: No arcs!\n";
		}
		pair<int, int>* p = &(*(this->arc_nodes.begin()));
		ReverseArcIterator it(p);
		return it;
	}
};


template<class GraphType>
inline void Graph<GraphType>::delete_node_from_matrix(int number)
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

template<class GraphType>
inline void Graph<GraphType>::delete_arc_from_matrix(int number)
{
	for (auto& node : this->matrix)
		node[number] = 0;
}

template<class GraphType>
inline void Graph<GraphType>::clear_matrix()
{
	for (auto &node : this->matrix)
		for (auto &arc : node)
			arc = 0;
}

template<class GraphType>
void Graph<GraphType>::copy_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2)
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
		for (size_t j = 0; j < MATRIX_SIZE; ++j)
			matrix1[i][j] = matrix2[i][j];
}

template<class GraphType>
bool Graph<GraphType>::compare_by_matrix(const Graph<GraphType>& graph1, const Graph<GraphType>& graph2)
{
	for (size_t i = 0; i < graph1.nodes.size(); ++i)
		for (size_t j = 0; j < graph1.arcs.size(); j++)
			if (graph1.matrix[i][j] != graph2.matrix[i][j])
				return false;

	return true;
}

template<class GraphType>
inline void Graph<GraphType>::add_node(GraphType data)
{
	Node<GraphType> node(*this, data);
	this->nodes.push_back(node);
	this->nodes_data.push_back(data);
}

template<class GraphType>
inline void Graph<GraphType>::add_arc(int begin, int end)
{
	try
	{
		if (!(is_node_exists(begin) && is_node_exists(end)))
			throw -1;

		Arc<GraphType> arc(*this);
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
		pair<int, int> beg_end;
		beg_end.first = begin;
		beg_end.second = end;
		this->arc_nodes.push_back(beg_end);
	}
	catch (int error)
	{
		cout << "\nadd_arc: " << NO_NODE << endl;
	}
}

template<class GraphType>
inline void Graph<GraphType>::delete_node(GraphType data)
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

template<class GraphType>
inline void Graph<GraphType>::delete_node(int number)
{
	try
	{
		if (!is_node_exists(number))
			throw - 1;

		delete_node_from_matrix(number);
		for (size_t i = 0; i < this->nodes.size(); ++i)
			if (this->nodes[i].number == number)
			{
				this->nodes.erase(this->nodes.begin() + i);
				this->nodes_data.erase(this->nodes_data.begin() + i);
			}
	}
	catch (int error)
	{
		cout << "\ndelete_node: " << NO_NODE << endl;
	}
}

template<class GraphType>
inline void Graph<GraphType>::delete_node(NodeIterator it)
{
	try
	{
		delete_node(*it);
	}
	catch (int error)
	{
		cout << "\ndelete_node: " << NO_NODE << endl;
	}
}

template<class GraphType>
inline void Graph<GraphType>::delete_arc(int begin, int end)
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

template<class GraphType>
inline void Graph<GraphType>::delete_arc(int number)
{
	try
	{
		if (!is_arc_exists(number))
			throw - 1;

		delete_arc_from_matrix(number);
		for (size_t i = 0; i < this->arcs.size(); ++i)
			if (this->arcs[i].number == number)
			{
				this->arc_nodes.erase(this->arc_nodes.begin() + i);
				this->arcs.erase(this->arcs.begin() + i);
			}
	}
	catch (int error)
	{
		cout << "\ndelete_arc: " << NO_ARC << endl;
	}
}

template<class GraphType>
inline void Graph<GraphType>::delete_arc(GraphType begin, GraphType end)
{
	int beg_num, end_num;
	for (auto node : this->nodes)
		if (node.data == begin)
		{
			beg_num = node.number;
			break;
		}

	for (auto node : this->nodes)
		if (node.data == end)
		{
			end_num = node.number;
			break;
		}
	delete_arc(beg_num, end_num);
}

template<class GraphType>
inline void Graph<GraphType>::delete_arc(NodeIterator begin, NodeIterator end)
{
	try
	{
		delete_arc(*begin, *end);
	}
	catch (int error)
	{
		cout << "\ndelete_arc: " << NO_ARC << endl;
	}
}

template<class GraphType>
inline void Graph<GraphType>::delete_arc(ArcIterator it)
{
	for (auto arc : this->arcs)
		if ((*arc.begin).number == (*it.ptr).first && (*arc.end).number == (*it.ptr).second)
			delete_arc(arc.number);
}

template<class GraphType>
inline bool Graph<GraphType>::is_node_exists(int number)
{
	for (auto node : this->nodes)
		if (node.number == number)
			return true;

	return false;
}

template<class GraphType>
inline bool Graph<GraphType>::is_node_exists(GraphType data)
{
	for (auto node : this->nodes)
		if (node.data == data)
			return true;

	return false;
}

template<class GraphType>
inline bool Graph<GraphType>::is_arc_exists(int begin, int end)
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

template<class GraphType>
inline bool Graph<GraphType>::is_arc_exists(int number)
{
	for (auto &arc : this->arcs)
		if (arc.number == number)
			return true;

	return false;
}

template<class GraphType>
inline bool Graph<GraphType>::is_empty()
{
	if (this->nodes.size() == 0)
		return true;

	return false;
}

template<class GraphType>
inline vector<int> Graph<GraphType>::get_incident_arcs(int number)
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

template<class GraphType>
inline vector<int> Graph<GraphType>::get_adjance_nodes(int number)
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

template<class GraphType>
inline int Graph<GraphType>::get_node_degree(int number)
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

template<class GraphType>
inline int Graph<GraphType>::get_arc_degree(int number)
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

template<class GraphType>
inline GraphType Graph<GraphType>::get_node_data(int number)
{
	try
	{
		if (!is_node_exists(number))
			throw - 1;

		for(auto node : this->nodes)
			if (node.number == number)
				return node.data;
	}
	catch (int error)
	{
		cout << "\nget_node_data: " << NO_NODE << endl;
		return this->nodes[0].data;
	}
}

template<class GraphType>
inline void Graph<GraphType>::show_graph()
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

template<class GraphType>
inline void Graph<GraphType>::clear_graph()
{
	clear_matrix();
	this->nodes.clear();
	this->arcs.clear();
}

template<class GraphType>
inline void Graph<GraphType>::operator=(Graph<GraphType>& graph)
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

template<class GraphType>
bool Graph<GraphType>::operator==(Graph<GraphType>& graph)
{
	if (this->get_nodes_count() == graph.get_nodes_count())
		return compare_by_matrix(*this, graph);

	return false;
}

template<class GraphType>
inline bool Graph<GraphType>::operator!=(Graph<GraphType>& graph)
{
	return !(*this == graph);
}

template<class GraphType>
inline bool Graph<GraphType>::operator>(Graph<GraphType>& graph)
{
	if (this->get_nodes_count() > graph.get_nodes_count())
		return compare_by_matrix(graph, *this);

	return false;
}

template<class GraphType>
inline bool Graph<GraphType>::operator<(Graph<GraphType>& graph)
{
	if (this->get_nodes_count() < graph.get_nodes_count())
		return compare_by_matrix(*this, graph);

	return false;
}

template<class GraphType>
inline bool Graph<GraphType>::operator>=(Graph<GraphType>& graph)
{
	if (this->get_nodes_count() >= graph.get_nodes_count())
		return compare_by_matrix(graph, *this);

	return false;
}

template<class GraphType>
inline bool Graph<GraphType>::operator<=(Graph<GraphType>& graph)
{
	if (this->get_nodes_count() <= graph.get_nodes_count())
		return compare_by_matrix(*this, graph);

	return false;
}