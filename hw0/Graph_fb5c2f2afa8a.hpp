#ifndef CME212_GRAPH_HPP
#define CME212_GRAPH_HPP

/** @file Graph.hpp
 * @brief An undirected graph type
 */

#include <algorithm>
#include <vector>
#include <cassert>

#include "CME212/Util.hpp"
#include "CME212/Point.hpp"


/** @class Graph
 * @brief A template for 3D undirected graphs.
 *
 * Users can add and retrieve nodes and edges. Edges are unique (there is at
 * most one edge between any pair of distinct nodes).
 */
class Graph {
 private:

	// HW0: YOUR CODE HERE
	// Use this space for declarations of important internal types you need
	// later in the Graph's definition.
	// (As with all the "YOUR CODE HERE" markings, you may not actually NEED
	// code here. Just use the space if you need it.)

	class InternalNode;
	class InternalEdge;

 public:

	//
	// PUBLIC TYPE DEFINITIONS
	//

	/** Type of this graph. */
	using graph_type = Graph;

	/** Predeclaration of Node type. */
	class Node;
	/** Synonym for Node (following STL conventions). */
	using node_type = Node;

	/** Predeclaration of Edge type. */
	class Edge;
	/** Synonym for Edge (following STL conventions). */
	using edge_type = Edge;

	/** Type of indexes and sizes.
	 * Return type of Graph::Node::index(), Graph::num_nodes(),
	 * Graph::num_edges(), and argument type of Graph::node(size_type) */
	using size_type = unsigned;

	//
	// CONSTRUCTORS AND DESTRUCTOR
	//

	/** Construct an empty graph. */
	Graph() {
		// HW0: YOUR CODE HERE
		size_ = 0;
	}

	/** Default destructor */
	~Graph() = default;

	//
  	// NODES
  	//

	/** @class Graph::Node
 	 * @brief Class representing the graph's nodes.
 	 *
	 * Node objects are used to access information about the Graph's nodes.
	 */
	class Node {

	 public:

		/** Construct an invalid node.
		 *
		 * Valid nodes are obtained from the Graph class, but it
		 * is occasionally useful to declare an @i invalid node, and assign a
		 * valid node to it later. For example:
		 *
		 * @code
		 * Graph::node_type x;
		 * if (...should pick the first node...)
		 *   x = graph.node(0);
		 * else
		 *   x = some other node using a complicated calculation
		 * do_something(x);
		 * @endcode
		 */
		Node() {
			// HW0: YOUR CODE HERE
		}

		/** Return this node's position. */
		const Point& position() const {
			// HW0: YOUR CODE HERE
			return fetch().point;
		}

		/** Return this node's index, a number in the range [0, graph_size). */
		size_type index() const {
			// HW0: YOUR CODE HERE
			return ind_;
		}

		/** Test whether this node and @a n are equal.
		 *
		 * Equal nodes have the same graph and the same index.
		 */
		bool operator==(const Node& n) const {
			// HW0: YOUR CODE HERE
			(void) n;          // Quiet compiler warning
			if (n.graph_== graph_ && n.ind_ == ind_) {
				return true;
			}
			return false;
		}

		/** Test whether this node is less than @a n in a global order.
		 *
		 * This ordering function is useful for STL containers such as
		 * std::map<>. It need not have any geometric meaning.
		 *
		 * The node ordering relation must obey trichotomy: For any two nodes x
		 * and y, exactly one of x == y, x < y, and y < x is true.
		 */
		bool operator<(const Node& n) const {
			// HW0: YOUR CODE HERE
			return (n.ind_ < ind_);
		}

	 private:

		// Allow Graph to access Node's private member data and functions.
		friend class Graph;
		// HW0: YOUR CODE HERE
		// Use this space to declare private data members and methods for Node
		// that will not be visible to users, but may be useful within Graph.
		// i.e. Graph needs a way to construct valid Node objects
		graph_type* graph_;
		size_type ind_;

		// Private constructor
		Node(const graph_type* graph, size_type ind)
			: graph_(const_cast<graph_type*>(graph)), ind_(ind) {

		}

		/* Helper method to return the appropriate element
		 * It loops through the elements until the element with the correct
		 * index is found.
		 */
		InternalNode& fetch() const {
			if (ind_ >= graph_->size()) {
				assert(false);
			}
			return graph_->nodes[ind_];
		}

	};

	/** Return the number of nodes in the graph.
	 *
	 * Complexity: O(1).
	 */
	size_type size() const {
		// HW0: YOUR CODE HERE
		return size_;
	}

	/** Synonym for size(). */
	size_type num_nodes() const {
		return size();
	}

	/** Add a node to the graph, returning the added node.
	 * @param[in] position The new node's position
	 * @post new num_nodes() == old num_nodes() + 1
	 * @post result_node.index() == old num_nodes()
	 *
	 * Complexity: O(1) amortized operations.
	 */
	Node add_node(const Point& position) {
		// HW0: YOUR CODE HERE
		InternalNode node;
		node.ind = size_;
		node.point = position;
		nodes.push_back(node);
		size_++;
		return Node(this, size_ - 1);        // Invalid node
	  }

	/** Determine if a Node belongs to this Graph
	 * @return True if @a n is currently a Node of this Graph
	 *
	 * Complexity: O(1).
	 */
	bool has_node(const Node& n) const {
		// HW0: YOUR CODE HERE
		InternalNode node;
		node.ind = n.index();
		// Try to find node in vector of nodes
		auto p = std::find(nodes.begin(), nodes.end(), node);
		if (p == nodes.end()) {
			return false;
		}
		return true;
	}

	  /** Return the node with index @a i.
	   * @pre 0 <= @a i < num_nodes()
	   * @post result_node.index() == i
	   *
	   * Complexity: O(1).
	   */
	Node node(size_type i) const {
		// HW0: YOUR CODE HERE
		return Node(this, i);
	}

	//
	// EDGES
	//

	/** @class Graph::Edge
	 * @brief Class representing the graph's edges.
	 *
	 * Edges are order-insensitive pairs of nodes. Two Edges with the same nodes
	 * are considered equal if they connect the same nodes, in either order.
	 */
	class Edge {
	 public:
		/** Construct an invalid Edge. */
		Edge() {
			// HW0: YOUR CODE HERE
		}

		/** Return a node of this Edge */
		Node node1() const {
			// HW0: YOUR CODE HERE
			return graph_->node(graph_->edges[ind_].node1);
		}

		/** Return the other node of this Edge */
		Node node2() const {
			// HW0: YOUR CODE HERE
			return graph_->node(graph_->edges[ind_].node2);
		}

		/** Test whether this edge and @a e are equal.
		 *
		 * Equal edges represent the same undirected edge between two nodes.
		 */
		bool operator==(const Edge& e) const {
			if ((node1() == e.node1() && node2() == e.node2()) ||
				(node2() == e.node1() && node1() == e.node2())) {
				return true;
			}
			return false;
		}

		/** Test whether this edge is less than @a e in a global order.
		 *
		 * This ordering function is useful for STL containers such as
		 * std::map<>. It need not have any interpretive meaning.
		 */
		bool operator<(const Edge& e) const {
			return (ind_ < e.ind_);
		}

	 private:
		// Allow Graph to access Edge's private member data and functions.
		friend class Graph;
		// HW0: YOUR CODE HERE
		// Use this space to declare private data members and methods for Edge
		// that will not be visible to users, but may be useful within Graph.
		// i.e. Graph needs a way to construct valid Edge objects
		graph_type* graph_;
		size_type ind_;

		// Private constructor
		Edge(const graph_type* graph, size_type ind)
			: graph_(const_cast<graph_type*> (graph)), ind_(ind) {

			}
	};

	/** Return the total number of edges in the graph.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	size_type num_edges() const {
		// HW0: YOUR CODE HERE
		return edges.size();
	}

	/** Return the edge with index @a i.
	 * @pre 0 <= @a i < num_edges()
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	Edge edge(size_type i) const {
		// HW0: YOUR CODE HERE
		return Edge(this, i);
	}

	/** Test whether two nodes are connected by an edge.
	 * @pre @a a and @a b are valid nodes of this graph
	 * @return True if for some @a i, edge(@a i) connects @a a and @a b.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	bool has_edge(const Node& a, const Node& b) const {
		// HW0: YOUR CODE HERE
		// Build edge using a and b's indices
		InternalEdge edge;
		edge.node1 = a.index();
		edge.node2 = b.index();
		// Try to find a matching node in this graph.
		auto p = std::find(edges.begin(), edges.end(), edge);
		// If the find() function returns end, the element was not found
		if (p == edges.end()) {
			return false;
		}
		return true;
	}

	/** Add an edge to the graph, or return the current edge if it already exists.
	 * @pre @a a and @a b are distinct valid nodes of this graph
	 * @return an Edge object e with e.node1() == @a a and e.node2() == @a b
	 * @post has_edge(@a a, @a b) == true
	 * @post If old has_edge(@a a, @a b), new num_edges() == old num_edges().
	 *       Else,                        new num_edges() == old num_edges() + 1.
	 *
	 * Can invalidate edge indexes -- in other words, old edge(@a i) might not
	 * equal new edge(@a i). Must not invalidate outstanding Edge objects.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	Edge add_edge(const Node& a, const Node& b) {
		// HW0: YOUR CODE HERE
		InternalEdge edge;
		edge.node1 = a.index();
		edge.node2 = b.index();
		// Try to find the edge in the vector of edges
		auto p = std::find(edges.begin(), edges.end(), edge);
		// If it's not there, add the edge
		if (p == edges.end()) {
			edge.ind = edges.size();
			edges.push_back(edge);
			return Edge(this, edge.ind);
		} else {
			return Edge(this, p->ind);
		}
 	}

	/** Remove all nodes and edges from this graph.
	 * @post num_nodes() == 0 && num_edges() == 0
	 *
	 * Invalidates all outstanding Node and Edge objects.
	 */
	void clear() {
		size_ = 0;
		nodes.clear();
		edges.clear();
	}

 private:

	// HW0: YOUR CODE HERE
	// Use this space for your Graph class's internals:
	// helper functions, data members, and so forth.  

	class InternalNode {
	 public:
		Point point;
		size_type ind;

		// Need to define the == operator for nodes
		// for use in has_node()
		bool operator==(const InternalNode& n) const {
			if (ind == n.ind) {
				return true;
			}
			return false;
		}
	};

	class InternalEdge {
	 public:
		size_type node1;
		size_type node2;
		size_type ind;

		// Need to define the == operator for edges
		// for use in has_edge() and add_edge()
		bool operator==(const InternalEdge& e) const {
			if ((node1 == e.node1 && node2 == e.node2) ||
				(node1 == e.node2 && node2 == e.node1)) {
				return true;
			}
			return false;
		}
	};

	size_type size_;

	std::vector<InternalNode> nodes;
	std::vector<InternalEdge> edges;

};

#endif // CME212_GRAPH_HPP
