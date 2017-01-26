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
      Return type of Graph::Node::index(), Graph::num_nodes(),
      Graph::num_edges(), and argument type of Graph::node(size_type) */
  using size_type = unsigned;

 private:
  // Vector containing the node's ID and the point object
  std::vector<Point> points;

  // Vector containing the IDs of the two nodes associated with the edge
  std::vector<std::pair<size_type,size_type>> edge_node;

 public:
  //
  // CONSTRUCTORS AND DESTRUCTOR
  //

  /** Construct an empty graph. */
  Graph() :
    points(),
    edge_node() {
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
    }

    /** Return this node's position. */
    const Point& position() const {
      return graph_->points[this->uid_];
    }

    /** Return this node's index, a number in the range [0, graph_size). */
    size_type index() const {
      return uid_;
    }

    // Get the pointer to the graph of a node
    graph_type* getGraph() const {
      return graph_;
    }

    /** Test whether this node and @a n are equal.
     *
     * Equal nodes have the same graph and the same index.
     */
    bool operator==(const Node& n) const {
      return (this->uid_==n.index() && this->graph_==n.getGraph());
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
      if (this->graph_!=n.getGraph()) {
        return (this->graph_ < n.getGraph());
      }
      else {
        return (this->uid_ < n.index());
      }
    }

   private:
    // Allow Graph to access Node's private member data and functions
    friend class Graph;
    // Pointer back to the graph container
    graph_type* graph_;
    // The node's index in the graph
    size_type uid_;
    // Private constructor of Node object
    Node(const graph_type* graph, size_type uid)
      : graph_(const_cast<graph_type*>(graph)), uid_(uid) {
    }

  };

  /** Return the number of nodes in the graph.
   *
   * Complexity: O(1).
   */
  size_type size() const {
    return points.size();
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
    points.push_back(position);
    return Node(this, points.size()-1);
  }

  /** Determine if a Node belongs to this Graph
   * @return True if @a n is currently a Node of this Graph
   *
   * Complexity: O(1).
   */
  bool has_node(const Node& n) const {
    return (points[n.index()] == n.position());
  }

  /** Return the node with index @a i.
   * @pre 0 <= @a i < num_nodes()
   * @post result_node.index() == i
   *
   * Complexity: O(1).
   */
  Node node(size_type i) const {
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
    }

    /** Return a node of this Edge */
    Node node1() const {
      return Node(graph_,graph_->edge_node[this->uid_].first);
    }

    /** Return the other node of this Edge */
    Node node2() const {
      return Node(graph_,graph_->edge_node[this->uid_].second);
    }

    // Return the index of an Edge
    size_type index() const {
      return uid_;
    }

    // Return the pointer to the graph of an Edge
    graph_type* getGraph() const {
      return graph_;
    }

    /** Test whether this edge and @a e are equal.
     *
     * Equal edges represent the same undirected edge between two nodes.
     */
    bool operator==(const Edge& e) const {
      if (this->graph_!=e.getGraph()) {
        return false;
      }
      else {
        return (e.node1()==this->node1() && e.node2()==this->node2())
               ||(e.node1()==this->node2() && e.node2()==this->node1());
      }
    }

    /** Test whether this edge is less than @a e in a global order.
     *
     * This ordering function is useful for STL containers such as
     * std::map<>. It need not have any interpretive meaning.
     */
    bool operator<(const Edge& e) const {
      if (this->graph_!=e.getGraph()) {
        return (this->graph_ < e.getGraph());
      }
      else {
        return (this->uid_ < e.index());
      }
    }

   private:
    // Allow Graph to access Edge's private member data and functions.
    friend class Graph;
    // Pointer to the graph that the Edge belongs to
    graph_type* graph_;
    // Unique ID of the Edge
    size_type uid_;
    // Private constructor for Edge
    Edge(const graph_type* graph, size_type uid)
      : graph_(const_cast<graph_type*>(graph)), uid_(uid) {
    }

  };

  /** Return the total number of edges in the graph.
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  size_type num_edges() const {
    return edge_node.size();
  }

  /** Return the edge with index @a i.
   * @pre 0 <= @a i < num_edges()
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  Edge edge(size_type i) const {
    return Edge(this, i);
  }

  /** Test whether two nodes are connected by an edge.
   * @pre @a a and @a b are valid nodes of this graph
   * @return True if for some @a i, edge(@a i) connects @a a and @a b.
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  bool has_edge(const Node& a, const Node& b) const {
    size_type match = 0;
    for (size_type i=0; i<edge_node.size(); i++) {
      if ((a.index()==edge_node[i].first && b.index()==edge_node[i].second)
         ||(a.index()==edge_node[i].second && b.index()==edge_node[i].first)) {
        match += 1;
      }
    }
    return (match==1);
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
    size_type edgeuid;
    std::pair<size_type,size_type> pair1 = std::make_pair(a.index(),b.index());
    std::pair<size_type,size_type> pair2 = std::make_pair(b.index(),a.index());
    size_type index1 = find(edge_node.begin(),edge_node.end(),pair1)-edge_node.begin();
    size_type index2 = find(edge_node.begin(),edge_node.end(),pair2)-edge_node.begin();
    if (index1 >= edge_node.size() && index2 >= edge_node.size()) {
      edge_node.push_back(std::make_pair(a.index(),b.index()));
      edgeuid = edge_node.size()-1;
    }
    else if (index1 < edge_node.size()) {
      edgeuid = index1;
    }
    else {
      edgeuid = index2;
    }
    return Edge(this, edgeuid);
  }

  /** Remove all nodes and edges from this graph.
   * @post num_nodes() == 0 && num_edges() == 0
   *
   * Invalidates all outstanding Node and Edge objects.
   */
  void clear() {
    points.clear();
    edge_node.clear();
  }

};

#endif // CME212_GRAPH_HPP
