#include "Catch2.hpp"
#include <queue>
#include <memory>
#include <list>
#include <map>
#include <iostream>

template<typename ValueType>
struct Vertex;

template<typename ValueType>
class Matrix
{
public:
	Matrix(size_t p_rows, size_t p_columns, ValueType p_value = nullptr) : m_matrix(p_rows)
	{
		for (auto& row : m_matrix)
		{
			row.resize(p_columns);
			for (auto& i : row)
			{
				i = p_value;
			}
		}
	}

	Matrix(const std::vector<std::vector<ValueType>>& p_args) : m_matrix(p_args.size())
	{
		for (size_t i(0); i != rows(); ++i)
		{
			m_matrix[i] = p_args[i];
		}
	}

	size_t rows() const { return m_matrix.size(); }
	size_t columns() const { return 0 == rows() ? 0 : m_matrix[0].size(); }

	std::vector<ValueType>& operator[](size_t p_index)
	{
		if (0 == rows())
			throw std::runtime_error("Matrix is empty");
		if (p_index < 0 || rows() <= p_index)
			throw std::runtime_error("Index out of range");

		return m_matrix[p_index];
	}

	const std::vector<ValueType>& operator[](size_t p_index) const
	{
		if (0 == rows())
			throw std::runtime_error("Matrix is empty");
		if (p_index < 0 || rows() <= p_index)
			throw std::runtime_error("Index out of range");

		return m_matrix[p_index];
	}

private:
	std::vector<std::vector<ValueType>> m_matrix;
};

template<typename ValueType>
bool operator==(const Matrix<ValueType>& p_first, const Matrix<ValueType>& p_second)
{
	if (p_first.rows() != p_second.rows())
		return false;
	if (p_first.columns() != p_second.columns())
		return false;

	for (size_t i(0); i != p_first.rows(); ++i)
	{
		for (size_t k(0); k != p_first.columns(); ++k)
		{
			if (p_first[i][k] != p_second[i][k])
				return false;
		}
	}

	return true;
}

template <typename KeyType>
struct Vertex
{
	enum class Color
	{
		WHITE, // We haven't reach this Vertex yet.
		GRAY, // The frontier Vertex.
		BLACK // Vertex has been discovered.
	};

	Vertex() : id(KeyType()), color(Color::WHITE), discovery_time(-1), parent(nullptr) {}
	Vertex(KeyType p_id, Color p_color = Color::WHITE, int p_distance = -1, std::shared_ptr<Vertex<KeyType>> p_parent = nullptr)
		: id(p_id), color(p_color), discovery_time(p_distance), parent(p_parent) {}
	bool operator==(const Vertex<KeyType>& other) const
	{
		return (id == other.id && color == other.color && parent == other.parent);
	}

	KeyType id;
	Color color;
	int discovery_time;
	int finish_time;
	std::shared_ptr<Vertex<KeyType>> parent;
};


static int timestamp = 0;
template<typename GraphType, typename KeyType>
void depth_first_search_visit(GraphType& p_graph, std::shared_ptr<Vertex<KeyType>>& p_source)
{
	// White vertex p_source has just been discovered.
	timestamp = timestamp + 1;
	p_source->discovery_time = timestamp;
	p_source->color = Vertex<KeyType>::Color::GRAY;
	// explore each edge p_source, and its neighbors.
	for (int k = 0; k != p_graph[p_source->id].size(); ++k)
	{
		std::shared_ptr<Vertex<KeyType>>& neighbor = p_graph[p_source->id][k];

		// Is this neighbor being discovered now?
		if (nullptr != neighbor && Vertex<KeyType>::Color::WHITE == neighbor->color)
		{
			neighbor->parent = p_source;
			// this neighbor is now on the frontier.
			depth_first_search_visit(p_graph, neighbor);
		}
	}

	timestamp = timestamp + 1;
	p_source->finish_time = timestamp;
	// Blacken p_source, it is finished.
	p_source->color = Vertex<KeyType>::Color::BLACK;
}

// Requires std::shared_ptr<Vertex<KeyType>> must start out with color WHITE.
// -	GraphType:	Container that used to store the graph, it must support subscript operator[KeyType][KeyType],
//				and method GraphType[KeyType].size() must exist.
// -	KeyType:	The type used to represent the Vertex in graph.
template<typename KeyType>
void depth_first_search(std::map<KeyType, std::vector<std::shared_ptr<Vertex<KeyType>>>>& p_graph, std::vector<KeyType>& p_keys, std::map<char, std::shared_ptr<Vertex<char>>>& p_vertices)
{
	timestamp = 0;
	for (KeyType key : p_keys)
	{
		std::shared_ptr<Vertex<KeyType>>& vertex = p_vertices[key];
		if (Vertex<KeyType>::Color::WHITE == vertex->color)
		{
			depth_first_search_visit(p_graph, vertex);
		}
	}
}

template<typename KeyType>
void print_path(std::list<std::list<std::shared_ptr<Vertex<KeyType>>>>& p_graph, std::shared_ptr<Vertex<KeyType>>& p_source, std::shared_ptr<Vertex<KeyType>>& p_destination)
{
	if (p_source == p_destination)
		std::cout << p_source << " ";
	else if (p_destination->parent == nullptr)
		std::cout << "No path from " << p_source->id << " to " << p_destination->id << " exist." << std::endl;
	else
	{
		print_path(p_graph, p_source, p_destination->parent);
		std::cout << p_destination->id << " ";
	}
}

TEST_CASE("Figure 20.4 CLRS", "[Figure 20.4 CLRS]")
{
	std::vector<char> input_key_char
	{
		'u',
		'v',
		'w',

		'x',
		'y',
		'z',
	};

	// std::map is not guarantee to print out in the right order of input.
	std::map<char, std::shared_ptr<Vertex<char>>> vertices
	{
		{'u', std::make_shared<Vertex<char>>('u')},
		{'v', std::make_shared<Vertex<char>>('v')},
		{'w', std::make_shared<Vertex<char>>('w')},

		{'x', std::make_shared<Vertex<char>>('x')},
		{'y', std::make_shared<Vertex<char>>('y')},
		{'z', std::make_shared<Vertex<char>>('z')},
	};

	SECTION("Figure 20.4 CLRS: using std::map<char, std::vector<std::shared_ptr<Vertex<char>>>>")
	{
		// We need to update properties of Vertex<char>, that's why we can not use std::set here.
		std::map<char, std::vector<std::shared_ptr<Vertex<char>>>> graph;

		graph['u'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['v'], vertices['x'] };
		graph['v'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['y'] };
		graph['w'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['y'], vertices['z'] };
		graph['x'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['v'] };
		graph['y'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['x'] };
		graph['z'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['z'] };

		depth_first_search(graph, input_key_char, vertices);

		for (char& key : input_key_char)
		{
			std::cout << std::string(1, vertices[key]->id) << " " << vertices[key]->discovery_time << "/" << vertices[key]->finish_time << ", parent: " << ((vertices[key]->parent) ? std::string(1, vertices[key]->parent->id) : "nullptr") << std::endl;
		}

		std::cout << "-------------\n";
	}
}
