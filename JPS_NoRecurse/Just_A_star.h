#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <memory>
#include <map>

namespace A_Star
{
	struct Node
	{
		Node() : m_x(-1), m_y(-1), m_px(-1), m_py(-1), m_opened(false), m_closed(false) {}
		Node(const int x, const int y, const int px = -1, const int py = -1, bool opened = false, bool closed = false) :
			m_x(x), m_y(y), m_px(px), m_py(py), m_opened(closed), m_closed(opened) {}
		int m_x;
		int m_y;

		int m_px;
		int m_py;
		bool m_opened;
		bool m_closed;

		friend bool operator<(const Node& lhs, const Node& rhs)
		{
			return (lhs.m_x < rhs.m_x) && (lhs.m_y < rhs.m_x);
		}
	};

	typedef std::pair<Node, int> Node_Pair;
	typedef std::vector<Node> Neighbour_Vector;

	struct Compare_Nodes
	{
		bool operator()(const Node_Pair& lhs, const Node_Pair& rhs)
		{
			return lhs.second > rhs.second;
		}
	};

	int manhattan_heuristic(const int x1, const int y1, const int x2, const int y2)
	{
		return abs(x1 - x2) + abs(y1 - y2);
	}

	int FindPath(const int nStartX, const int nStartY,
		const int nTargetX, const int nTargetY,
		const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
		int* pOutBuffer, const int nOutBufferSize);

	class Graph
	{
		Graph() {};

	public:

		Graph(const int width, const int height, const unsigned char* pmap) :
			m_width(width),
			m_height(height),
			m_pmap_size(width * height),
			m_neighbour_positions{ Node{ 0, -1 }, Node{ 1, 0 }, Node{ 0, 1 }, Node{ -1, 0 } },
			m_pMap(pmap),
			m_bad_node(new Node{}),
			cost_map_vec(m_pmap_size, 0)
		{
			m_neighbour_vector.reserve(4);
			m_neighbour_vector = { { -1, -1 },{ -1, -1 },{ -1, -1 },{ -1, -1 } };
			m_prune_neighbours.reserve(4);
			m_successors.reserve(10);
			m_map_rep = std::vector<Node>(m_pmap_size, Node{ -1, -1 });
		}

		int get_index_value(const int x, const int y) const
		{
			return x + (y * m_width);
		}

		bool is_in_bounds(const int x, const int y)
		{
			return x >= 0 && x < m_width && y >= 0 && y < m_height;
		}

		bool is_obstacle(const int x, const int y)
		{
			return m_pMap[x + (y * m_width)] == 0;
		}

		bool reachable(const int x, const int y)
		{
			return is_in_bounds(x, y) && !is_obstacle(x, y);
		}

		bool valid_node(const int x, const int y)
		{
			return x >= 0 && y >= 0;
		}

		//Get the neighbours of a given node in the map
		std::vector<Node> neighbours(const int x, const int y)
		{
			std::vector<Node> neighbours;

			for (auto& pos : m_neighbour_positions)
			{
				int new_x = x + pos.m_x;
				int new_y = y + pos.m_y;

				//If it's in bounds
				if ((new_x >= 0 && new_x < m_width && new_y >= 0 && new_y < m_height))
				{
					//Convert the combined position to get the real index value from pMap
					int real_index = get_index_value(new_x, new_y);

					//If the neighbour is valid
					if (real_index <= m_pmap_size && m_pMap[real_index] == 1)
					{
						neighbours.push_back(Node{ new_x, new_y, x, y });
					}
				}
			}

			return neighbours;
		}
		void add_to_vec(const Node& current, const Node& parent)
		{
			//Put the node into its correct place in the vector
			int index = current.m_x + (current.m_y * m_width);
			if (!current.m_opened)
			{
				m_map_rep[index] = Node{ current.m_x, current.m_y, parent.m_x, parent.m_y, current.m_opened, current.m_closed };
				m_map_rep[index].m_opened = true;
			}
		}

	private:
		int m_width;
		int m_height;
		int m_pmap_size;
		std::vector<Node> m_neighbour_positions;
		const unsigned char* m_pMap;

	public:
		std::priority_queue<Node_Pair, std::vector<Node_Pair>, Compare_Nodes> m_frontier;
		Neighbour_Vector m_neighbour_vector;
		Neighbour_Vector m_prune_neighbours;

		std::vector<Node> m_successors;

		Node* m_bad_node;

		std::vector<Node> m_map_rep;
		std::vector<int> cost_map_vec;
	};

	std::vector<int> reconstruct_path(const Node& start, const Node& target, const int mapWidth,
		int* pOutBuffer, const std::vector<Node>& pmap_vec, const int maxmiumPath)
	{
		std::vector<int> return_path{};

		Node current = pmap_vec[target.m_x + (target.m_y * mapWidth)];

		while (true)
		{
			if (current.m_x == start.m_x && current.m_y == start.m_y)
			{
				break;
			}

			return_path.push_back(current.m_x + (current.m_y * mapWidth));
			current = pmap_vec[current.m_px + (current.m_py * mapWidth)];
		}

		//Always pop the top -> If the node is the target then it's also the start node
		std::reverse(return_path.begin(), return_path.end());

		if (return_path.size() > maxmiumPath)
		{
			return return_path;
		}

		int count = 0;
		for (auto& x : return_path)
		{
			*pOutBuffer = x;
			++pOutBuffer;
			++count;
		}

		return return_path;
	}

	Node a_star(Graph& graph, const Node& start, const Node& target);

	int FindPath(const int nStartX, const int nStartY,
		const int nTargetX, const int nTargetY,
		const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
		int* pOutBuffer, const int nOutBufferSize)
	{
		Node start = { nStartX, nStartY };
		Node target = { nTargetX, nTargetY };

		if (nStartX == nTargetX && nStartY == nTargetY)
		{
			return 0;
		}

		Graph graph = Graph(nMapWidth, nMapHeight, pMap);
		auto target_found = a_star(graph, start, target);

		if (target_found.m_x == -1 && target_found.m_y == -1)
		{
			return -1;
		}

		return reconstruct_path(start, target_found, nMapWidth, pOutBuffer, graph.m_map_rep, nOutBufferSize).size();
	}

	//A* Search with JPS (Jump point search)
	Node a_star(Graph& graph, const Node& start, const Node& target)
	{
		auto correct_start = Node{ start.m_x, start.m_y, start.m_x, start.m_y };
		correct_start.m_opened = true;
		graph.m_frontier.emplace(correct_start, 0);

		//Set the start to the correct values
		graph.m_map_rep[graph.get_index_value(correct_start.m_x, correct_start.m_y)] = correct_start;
		graph.cost_map_vec[graph.get_index_value(correct_start.m_x, correct_start.m_y)] = 0;

		while (!graph.m_frontier.empty())
		{
			auto current = graph.m_frontier.top().first;
			current.m_closed = true;
			graph.m_frontier.pop();

			if (current.m_x == target.m_x && current.m_y == target.m_y)
			{
				//target acquired
				return current;
			}

			//Update successors
			auto neighbours = graph.neighbours(current.m_x, current.m_y);

			for (auto& neighbour : neighbours)
			{
				auto neighbour_index = graph.get_index_value(neighbour.m_x, neighbour.m_y);
				auto current_index = graph.get_index_value(current.m_x, current.m_y);

				if (graph.m_map_rep[neighbour_index].m_closed)
				{
					continue;
				}

				//adds the distance from the last node, plus one to make the cost
				int distance = manhattan_heuristic(neighbour.m_x, neighbour.m_y, current.m_x, current.m_y);
				int cost = graph.cost_map_vec[current_index] + distance;
				//int cost = graph.cost_map_vec[index];

				if (!graph.m_map_rep[neighbour_index].m_opened ||
					cost < graph.cost_map_vec[neighbour_index])
				{
					graph.cost_map_vec[neighbour_index] = cost;
					int new_f_value = cost + manhattan_heuristic(neighbour.m_x, neighbour.m_y, target.m_x, target.m_y);

					if (!graph.m_map_rep[neighbour_index].m_opened)
					{
						graph.m_frontier.emplace(neighbour, new_f_value);
						graph.add_to_vec(neighbour, current);
					}
					else
					{
						graph.m_frontier.emplace(neighbour, new_f_value);
						graph.add_to_vec(neighbour, current);
						//Update the current value
					}
				}
			}
		}

		//No target found
		return Node{ -1, -1 };
	}


}

