#include "Catch2/Catch.hpp"
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

	Vertex() : id(KeyType()), color(Color::WHITE), distance(-1), parent(nullptr) {}
	Vertex(KeyType p_id, Color p_color = Color::WHITE, int p_distance = -1, std::shared_ptr<Vertex<KeyType>> p_parent = nullptr)
		: id(p_id), color(p_color), distance(p_distance), parent(p_parent) {}
	bool operator==(const Vertex<KeyType>& other) const
	{
		return (id == other.id && color == other.color && parent == other.parent);
	}

	KeyType id;
	Color color;
	int distance;
	std::shared_ptr<Vertex<KeyType>> parent;
};

// Requires std::shared_ptr<Vertex<KeyType>> must start out with color WHITE.
// -	GraphType:	Container that used to store the graph, it must support subscript operator[KeyType][KeyType],
//				and method GraphType[KeyType].size() must exist.
// -	KeyType:	The type used to represent the Vertex in graph.
template<typename GraphType, typename KeyType>
void breadth_first_search(GraphType& p_graph, std::shared_ptr<Vertex<KeyType>>& p_source)
{
	p_source->color = Vertex<KeyType>::Color::GRAY;
	p_source->distance = 0;
	p_source->parent = nullptr;

	std::queue<std::shared_ptr<Vertex<KeyType>>> frontier;
	frontier.push(p_source);

	while (frontier.size())
	{
		std::shared_ptr<Vertex<KeyType>> source = frontier.front();
		frontier.pop();

		//Search the neighbors of this source vertex.
		for (int k = 0; k != p_graph[source->id].size(); ++k)
		{
			std::shared_ptr<Vertex<KeyType>>& neighbor = p_graph[source->id][k];

			// Is this neighbor being discovered now?
			if (nullptr != neighbor && Vertex<KeyType>::Color::WHITE == neighbor->color)
			{
				neighbor->color = Vertex<KeyType>::Color::GRAY;
				neighbor->distance = source->distance + 1;
				neighbor->parent = source;
				// this neighbor is now on the frontier.
				frontier.push(neighbor);
			}
		}
		//the source is now behind the frontier.
		source->color = Vertex<KeyType>::Color::BLACK;
	}
}

template<typename GraphType, typename KeyType>
void print_path(GraphType& p_graph, std::shared_ptr<Vertex<KeyType>>& p_source, std::shared_ptr<Vertex<KeyType>>& p_destination)
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

TEST_CASE("Exercises 20.2-1", "[Exercises 20.2-1]")
{
	// std::map is guarantee to print out the same order as input stored (because it's a number here).
	std::map<int, std::shared_ptr<Vertex<int>>> vertices
	{
		{1, std::make_shared<Vertex<int>>(1)},
		{2, std::make_shared<Vertex<int>>(2)},
		{3, std::make_shared<Vertex<int>>(3)},

		{4, std::make_shared<Vertex<int>>(4)},
		{5, std::make_shared<Vertex<int>>(5)},
		{6, std::make_shared<Vertex<int>>(6)},
	};

	SECTION("Exercises 20.2-1: using std::vector<std::vector<std::shared_ptr<Vertex<int>>>>")
	{
		std::vector<std::vector<std::shared_ptr<Vertex<int>>>> graph(7);

		graph[1] = std::vector<std::shared_ptr<Vertex<int>>>{ vertices[2], vertices[4], };
		graph[2] = std::vector<std::shared_ptr<Vertex<int>>>{ vertices[5] };
		graph[3] = std::vector<std::shared_ptr<Vertex<int>>>{ vertices[6], vertices[5] };
		graph[4] = std::vector<std::shared_ptr<Vertex<int>>>{ vertices[2] };
		graph[5] = std::vector<std::shared_ptr<Vertex<int>>>{ vertices[4] };
		graph[6] = std::vector<std::shared_ptr<Vertex<int>>>{ vertices[6] };

		std::shared_ptr<Vertex<int>> source = vertices[3];
		breadth_first_search(graph, source);
		for (auto& i : vertices)
		{
			if (nullptr != i.second)
				std::cout << i.second->id << ", Distance: " << i.second->distance << ", parent: " << ((i.second->parent) ? i.second->parent->id : -1) << std::endl;
		}

		std::cout << "-------------\n";
	}

	SECTION("Exercises 20.2-1: using Matrix<std::shared_ptr<Vertex<int>>>")
	{
		Matrix<std::shared_ptr<Vertex<int>>> graph(7, 7);
		graph[1][2] = vertices[2];
		graph[1][4] = vertices[4];

		graph[2][5] = vertices[5];

		graph[3][6] = vertices[6];
		graph[3][5] = vertices[5];

		graph[4][2] = vertices[2];

		graph[5][4] = vertices[4];

		graph[6][6] = vertices[6];

		std::shared_ptr<Vertex<int>> source = vertices[3];
		breadth_first_search(graph, source);
		for (auto& i : vertices)
		{
			if (nullptr != i.second)
				std::cout << i.second->id << ", Distance: " << i.second->distance << ", parent: " << ((i.second->parent) ? i.second->parent->id : -1) << std::endl;
		}

		std::cout << "-------------\n";
	}

	SECTION("Exercises 20.2-1: using std::map<int, std::map<int, std::shared_ptr<Vertex<int>>>>")
	{
		std::map<int, std::map<int, std::shared_ptr<Vertex<int>>>> graph;
		graph[1][2] = vertices[2];
		graph[1][4] = vertices[4];

		graph[2][5] = vertices[5];

		graph[3][6] = vertices[6];
		graph[3][5] = vertices[5];

		graph[4][2] = vertices[2];

		graph[5][4] = vertices[4];

		graph[6][6] = vertices[6];

		std::shared_ptr<Vertex<int>> source = vertices[3];
		breadth_first_search(graph, source);
		for (auto& i : vertices)
		{
			if (nullptr != i.second)
				std::cout << i.second->id << ", Distance: " << i.second->distance << ", parent: " << ((i.second->parent) ? i.second->parent->id : -1) << std::endl;
		}

		std::cout << "-------------\n";
	}
}

TEST_CASE("Exercises 20.2-2", "[Exercises 20.2-2]")
{
	// std::map is not guarantee to print out in the right order of input.
	std::list<std::shared_ptr<Vertex<char>>> input_vertices
	{
		std::make_shared<Vertex<char>>('s'),
		std::make_shared<Vertex<char>>('r'),
		std::make_shared<Vertex<char>>('u'),

		std::make_shared<Vertex<char>>('v'),
		std::make_shared<Vertex<char>>('t'),
		std::make_shared<Vertex<char>>('w'),

		std::make_shared<Vertex<char>>('y'),
		std::make_shared<Vertex<char>>('x'),
		std::make_shared<Vertex<char>>('z')
	};

	// The max size of input is z = 172 in ASCII.
	std::vector<std::shared_ptr<Vertex<char>>> vertices(173);
	for (auto& key : input_vertices)
	{
		vertices[key->id] = key;
	}

	SECTION("Exercises 20.2-2: using std::vector<std::vector<std::shared_ptr<Vertex<char>>>>")
	{
		// We need to update properties of Vertex<char>, that's why we can not use std::set here.
		std::vector<std::vector<std::shared_ptr<Vertex<char>>>> graph(1000);
		{
			graph['s'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['r'], vertices['u'], vertices['v'] };
			graph['r'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['s'], vertices['t'], vertices['w'] };
			graph['u'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['s'], vertices['t'], vertices['y'] };
			graph['v'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['s'], vertices['w'], vertices['y'] };
			graph['t'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['r'], vertices['u'] };
			graph['w'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['r'], vertices['v'], vertices['x'], vertices['z'] };
			graph['y'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['u'], vertices['v'], vertices['x'] };
			graph['x'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['w'], vertices['y'], vertices['z'] };
			graph['z'] = std::vector<std::shared_ptr<Vertex<char>>>{ vertices['w'], vertices['x'] };
		}
		std::shared_ptr<Vertex<char>> source = vertices['s'];
		breadth_first_search(graph, source);

		for (auto& i : input_vertices)
		{
			if (nullptr != i)
				std::cout << i->id << ", Distance: " << i->distance << ", parent: " << ((i->parent) ? std::string(1, i->parent->id) : "nullptr") << std::endl;
		}
		std::shared_ptr<Vertex<char>> destination = vertices['y'];
		print_path(graph, source, destination);
		std::cout << "-------------\n";
	}

	SECTION("Exercises 20.2-2: using Matrix<std::shared_ptr<Vertex<char>>>")
	{
		Matrix<std::shared_ptr<Vertex<char>>> graph(1000, 1000);
		{
			graph['s']['r'] = vertices['r'];
			graph['s']['u'] = vertices['u'];
			graph['s']['v'] = vertices['v'];

			graph['r']['s'] = vertices['s'];
			graph['r']['t'] = vertices['t'];
			graph['r']['w'] = vertices['w'];

			graph['u']['s'] = vertices['s'];
			graph['u']['t'] = vertices['t'];
			graph['u']['y'] = vertices['y'];

			graph['v']['s'] = vertices['s'];
			graph['v']['w'] = vertices['w'];
			graph['v']['y'] = vertices['y'];

			graph['t']['r'] = vertices['r'];
			graph['t']['u'] = vertices['u'];

			graph['w']['r'] = vertices['r'];
			graph['w']['v'] = vertices['v'];
			graph['w']['x'] = vertices['x'];
			graph['w']['z'] = vertices['z'];

			graph['y']['u'] = vertices['u'];
			graph['y']['v'] = vertices['v'];
			graph['y']['x'] = vertices['x'];

			graph['x']['w'] = vertices['w'];
			graph['x']['y'] = vertices['y'];
			graph['x']['z'] = vertices['z'];

			graph['z']['w'] = vertices['w'];
			graph['z']['x'] = vertices['x'];
		}

		std::shared_ptr<Vertex<char>> source = vertices['s'];
		breadth_first_search(graph, source);

		for (auto& i : input_vertices)
		{
			if (nullptr != i)
				std::cout << i->id << ", Distance: " << i->distance << ", parent: " << ((i->parent) ? std::string(1, i->parent->id) : "nullptr") << std::endl;
		}
		std::shared_ptr<Vertex<char>> destination = vertices['y'];
		print_path(graph, source, destination);
		std::cout << "-------------\n";
	}

	SECTION("Exercises 20.2-2: using std::map<char, std::map<char, std::shared_ptr<Vertex<char>>>>")
	{
		// We need to update properties of Vertex<char>, that's why we can not use std::set here.
		std::map<char, std::map<char, std::shared_ptr<Vertex<char>>>> graph;
		{
			graph['s']['r'] = vertices['r'];
			graph['s']['u'] = vertices['u'];
			graph['s']['v'] = vertices['v'];

			graph['r']['s'] = vertices['s'];
			graph['r']['t'] = vertices['t'];
			graph['r']['w'] = vertices['w'];

			graph['u']['s'] = vertices['s'];
			graph['u']['t'] = vertices['t'];
			graph['u']['y'] = vertices['y'];

			graph['v']['s'] = vertices['s'];
			graph['v']['w'] = vertices['w'];
			graph['v']['y'] = vertices['y'];

			graph['t']['r'] = vertices['r'];
			graph['t']['u'] = vertices['u'];

			graph['w']['r'] = vertices['r'];
			graph['w']['v'] = vertices['v'];
			graph['w']['x'] = vertices['x'];
			graph['w']['z'] = vertices['z'];

			graph['y']['u'] = vertices['u'];
			graph['y']['v'] = vertices['v'];
			graph['y']['x'] = vertices['x'];

			graph['x']['w'] = vertices['w'];
			graph['x']['y'] = vertices['y'];
			graph['x']['z'] = vertices['z'];

			graph['z']['w'] = vertices['w'];
			graph['z']['x'] = vertices['x'];
		}

		std::shared_ptr<Vertex<char>> source = vertices['s'];
		breadth_first_search(graph, source);

		for (auto& i : input_vertices)
		{
			if (nullptr != i)
				std::cout << i->id << ", Distance: " << i->distance << ", parent: " << ((i->parent) ? std::string(1, i->parent->id) : "nullptr") << std::endl;
		}
		std::shared_ptr<Vertex<char>> destination = vertices['y'];
		print_path(graph, source, destination);
		std::cout << "-------------\n";
	}
}
