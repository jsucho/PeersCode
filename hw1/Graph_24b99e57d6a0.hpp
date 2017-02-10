#ifndef CME212_GRAPH_HPP
#define CME212_GRAPH_HPP

/** @file Graph.hpp
 * @brief An undirected graph type
 */

#include <algorithm>
#include <cassert>
#include <vector>

#include "CME212/Util.hpp"
#include "CME212/Point.hpp"


/** @class Graph
 * @brief A template for 3D undirected graphs.
 *
 * Users can add and retrieve nodes and edges. Edges are unique (there is at
 * most one edge between any pair of distinct nodes).
 */
template <typename V>
class Graph {
 private:

  // Use this space for declarations of important internal types you need
  // later in the Graph's definition.
  // (As with all the "YOUR CODE HERE" markings, you may not actually NEED
  // code here. Just use the space if you need it.)

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

  using node_value_type = V;

  /** Predeclaration of Edge type. */
  class Edge;
  /** Synonym for Edge (following STL conventions). */
  using edge_type = Edge;

  /** Type of node iterators, which iterate over all graph nodes. */
  class NodeIterator;
  /** Synonym for NodeIterator */
  using node_iterator = NodeIterator;

  /** Type of edge iterators, which iterate over all graph edges. */
  class EdgeIterator;
  /** Synonym for EdgeIterator */
  using edge_iterator = EdgeIterator;

  /** Type of incident iterators, which iterate incident edges to a node. */
  class IncidentIterator;
  /** Synonym for IncidentIterator */
  using incident_iterator = IncidentIterator;

  /** Type of indexes and sizes.
      Return type of Graph::Node::index(), Graph::num_nodes(),
      Graph::num_edges(), and argument type of Graph::node(size_type) */
  using size_type = unsigned;

  //
  // CONSTRUCTORS AND DESTRUCTOR
  //

  /** Construct an empty graph. */
  Graph() : nodes(),edges(),adjacency(){
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
  class Node : private totally_ordered<Node> {
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
      return graph_->nodes[uid_].first;
    }

    /** Return this node's index, a number in the range [0, graph_size). */
    size_type index() const {
      return uid_;
    }

    /** Return a reference to the value of a node.
    * @post result == reference to the value of the node.
    */
    node_value_type& value(){
      return graph_->nodes[uid_].second;
    }
    /** Return the value of a node.
    * @post result == value of the node.
    */
    const node_value_type& value() const{
      return graph_->nodes[uid_].second;
    }

    /** Return the degree of a node.
    * @post result == n<N. Where n is the number of adjacent nodes to the current 
             node, and N the total number of nodes in the graph.
    */
    size_type degree() const{
    return graph_->adjacency[uid_].size();
    }

    /** Return the first incident iterator.
    * @post result <= a. Where a any other valid incident iterator for the node.
    */
    incident_iterator edge_begin() const{
      return IncidentIterator(graph_,uid_,0);
    }

    /** Return the last incident iterator.
    * @post result >= a. Where a is any other valid incident iterator for the node.
    */
    incident_iterator edge_end() const{
      return IncidentIterator(graph_,uid_,this->degree());
    }

    /** Test whether this node and @a n are equal.
     *
     * Equal nodes have the same graph and the same index.
     */
    bool operator==(const Node& n) const {
      if (graph_ == n.graph_)
        if (uid_ ==  n.uid_)
          return true;
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
      if (graph_ == n.graph_){
        if (uid_ <  n.uid_)
          return true;
      }
      else{
        if (graph_ < n.graph_)
          return true;
      }
      return false;
    }

   private:
    // Allow Graph to access Node's private member data and functions.
    friend class Graph;
    Graph* graph_;
    size_type uid_;
    Node(const Graph* graph_pointer, size_type uid)
        : graph_(const_cast<Graph*>(graph_pointer)), uid_(uid) {
    }
    // Use this space to declare private data members and methods for Node
    // that will not be visible to users, but may be useful within Graph.
    // i.e. Graph needs a way to construct valid Node objects
  };

  /** Return the number of nodes in the graph.
   *
   * Complexity: O(1).
   */
  size_type size() const {
    return nodes.size();
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
  Node add_node(const Point& position, const node_value_type& value= node_value_type()) {
  //jffNode add_node(const Point& position) {
    nodes.push_back(std::make_pair(position,value));
    //nodes.push_back(position);
    adjacency.push_back(std::vector<std::pair<size_type, size_type>> ());
    return Node(this,nodes.size()-1);
  }

  /** Determine if a Node belongs to this Graph
   * @return True if @a n is currently a Node of this Graph
   *
   * Complexity: O(1).
   */
  bool has_node(const Node& n) const {
    if (n.graph_ == this)
      if (n.uid_<nodes.size())
        return true;
    return false;
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
  class Edge : private totally_ordered<Edge> {
   public:
    /** Construct an invalid Edge. */
    Edge() {
    }

    /** Return a node of this Edge */
    Node node1() const {
      return Node(graph_,node1_id);
    }

    /** Return the other node of this Edge */
    Node node2() const {
      return Node(graph_,node2_id);
    }

    /** Test whether this edge and @a e are equal.
     *
     * Equal edges represent the same undirected edge between two nodes.
     */
    bool operator==(const Edge& e) const {
      if (graph_ == e.graph_){
        if ((node1_id == e.node1_id and node2_id == e.node2_id) or 
             (node1_id == e.node2_id and node2_id == e.node1_id)){
          return true;
        }
      }
      return false;
    }

    /** Test whether this edge is less than @a e in a global order.
     *
     * This ordering function is useful for STL containers such as
     * std::map<>. It need not have any interpretive meaning.
     */
    bool operator<(const Edge& e) const {
      if (graph_ == e.graph_){
        if (uid_ < e.uid_)
          return true;
      }
      else{
        if (graph_ < e.graph_)
          return true;
      }
      return false;
    }

   private:
    // Allow Graph to access Edge's private member data and functions.
    friend class Graph;
    Graph* graph_;
    size_type uid_;
    size_type node1_id;
    size_type node2_id;
    Edge(const Graph* graph_pointer, size_type uid, size_type node1, size_type node2)
        : graph_(const_cast<Graph*>(graph_pointer)), uid_(uid), node1_id(node1), node2_id(node2){
    }
    // Use this space to declare private data members and methods for Edge
    // that will not be visible to users, but may be useful within Graph.
    // i.e. Graph needs a way to construct valid Edge objects
  };

  /** Return the total number of edges in the graph.
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  size_type num_edges() const {
    return edges.size();
  }

  /** Return the edge with index @a i.
   * @pre 0 <= @a i < num_edges()
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  Edge edge(size_type i) const {
    return Edge(this, i, edges[i].first, edges[i].second);
  }

  /** Test whether two nodes are connected by an edge.
   * @pre @a a and @a b are valid nodes of this graph
   * @return True if for some @a i, edge(@a i) connects @a a and @a b.
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  bool has_edge(const Node& a, const Node& b) const {
    for (unsigned int i=0; i<adjacency[a.uid_].size(); i++)
       if (b.uid_ == adjacency[a.uid_][i].first)
         return true;
    return false;
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
    for (unsigned int i=0; i<adjacency[a.uid_].size(); i++)
       if (b.uid_ == adjacency[a.uid_][i].first)
         return Edge(this, adjacency[a.uid_][i].second, a.uid_, b.uid_);
    if (a<b)
      edges.push_back(std::make_pair(a.uid_,b.uid_));
    else
      edges.push_back(std::make_pair(b.uid_,a.uid_));
    adjacency[a.uid_].push_back(std::make_pair(b.uid_,edges.size()-1));
    adjacency[b.uid_].push_back(std::make_pair(a.uid_,edges.size()-1));
    return Edge(this,edges.size()-1,a.uid_,b.uid_);
  }

  /** Remove all nodes and edges from this graph.
   * @post num_nodes() == 0 && num_edges() == 0
   *
   * Invalidates all outstanding Node and Edge objects.
   */
  void clear() {
    nodes.clear();
    edges.clear();
    adjacency.clear();
  }

  //
  // Node Iterator
  //

  /** @class Graph::NodeIterator
   * @brief Iterator class for nodes. A forward iterator. */
  class NodeIterator: private totally_ordered<NodeIterator> {
   public:
    // These type definitions let us use STL's iterator_traits.
    using value_type        = Node;                     // Element type
    using pointer           = Node*;                    // Pointers to elements
    using reference         = Node&;                    // Reference to elements
    using difference_type   = std::ptrdiff_t;           // Signed difference
    using iterator_category = std::input_iterator_tag;  // Weak Category, Proxy

    /** Construct an invalid NodeIterator. */
    NodeIterator() {
    }

    /** Return the value of the iterator.
    * @post result is a node n with n.uid_==index_ and n.graph_==graph_
    */
    Node operator*() const{
      return graph_->node(index_);
    }

    /** Return the next iterator.
    * @post result is a NodeIterator with new_index_ == old_index_ + 1
    */
    NodeIterator& operator++(){
      ++index_;
      return *this;
    }

    /** Test whether this NodeIterator and @a n are equal.
    *
    * Equal NodeIterator have the same graph and the same index.
    */
    bool operator==(const NodeIterator& n) const{
      return index_==n.index_ and graph_==n.graph_;
    }

   private:
    friend class Graph;
     const graph_type* graph_;
     size_type index_;
     NodeIterator(const Graph* graph_pointer, size_type index)
       : graph_(graph_pointer), index_(index){
     }
  };

  /** Return the first node iterator.
  * @post result == node_iterator iter such that *iter.index() == 0
           and *iter.graph_ == this.
  */
  node_iterator node_begin() const{
     return NodeIterator(this,0);
  }

  /** Return the last node iterator.
    * @post result == node_iterator iter such that *iter.index() == n and
             *iter.graph_ == this. Where n is the total number of nodes.
    */
  node_iterator node_end() const{
     return NodeIterator(this, this->num_nodes());
  }

  //
  // Incident Iterator
  //

  /** @class Graph::IncidentIterator
   * @brief Iterator class for edges incident to a node. A forward iterator. */
  class IncidentIterator: private totally_ordered<IncidentIterator> {
   public:
    // These type definitions let us use STL's iterator_traits.
    using value_type        = Edge;                     // Element type
    using pointer           = Edge*;                    // Pointers to elements
    using reference         = Edge&;                    // Reference to elements
    using difference_type   = std::ptrdiff_t;           // Signed difference
    using iterator_category = std::input_iterator_tag;  // Weak Category, Proxy

    /** Construct an invalid IncidentIterator. */
    IncidentIterator() {
    }

    /** Return the value of the iterator.
    * @post result is an edge e with e.uid_==index_, e.graph_==graph_,
             e.node1()==node_id_ and e.node2()==n. Such that edge e connects
             node n and node node_id_.
    */
    Edge operator*() const{
      return Edge(graph_,graph_->adjacency[node_id_][index_].second,node_id_,graph_->adjacency[node_id_][index_].first);
    }

    /** Return the next iterator.
    * @post result is a IncidentIterator with new_index_ == old_index_ + 1
    */
    IncidentIterator& operator++(){
      ++index_;
      return *this;
    }

    /** Test whether this IncidentIterator and @a e are equal.
    *
    * Equal IncidentIterators have the same graph, the same index
       and the same node_id_.
    */
    bool operator==(const IncidentIterator& e) const{
      return index_==e.index_ and graph_==e.graph_ and node_id_==e.node_id_;
    }

   private:
    friend class Graph;
     const graph_type* graph_;
     size_type node_id_;
     size_type index_;
     IncidentIterator(const Graph* graph_pointer,size_type node_id, size_type index)
       : graph_(graph_pointer), node_id_(node_id), index_(index){
     }
  };

  //
  // Edge Iterator
  //

  /** @class Graph::EdgeIterator
   * @brief Iterator class for edges. A forward iterator. */
  class EdgeIterator: private totally_ordered<EdgeIterator> {
   public:
    // These type definitions let us use STL's iterator_traits.
    using value_type        = Edge;                     // Element type
    using pointer           = Edge*;                    // Pointers to elements
    using reference         = Edge&;                    // Reference to elements
    using difference_type   = std::ptrdiff_t;           // Signed difference
    using iterator_category = std::input_iterator_tag;  // Weak Category, Proxy

    /** Construct an invalid EdgeIterator. */
    EdgeIterator() {
    }

    /** Return the value of the iterator.
    * @post result is an edge e with e.uid_==index_ and e.graph_==graph_
    */
    Edge operator*() const{
      return graph_->edge(index_);
    }

    /** Return the next iterator.
    * @post result is a EdgeIterator with new_index_ == old_index_ + 1
    */
    EdgeIterator& operator++(){
      ++index_;
      return *this;
    }

    /** Test whether this EdgeIterator and @a e are equal.
    *
    * Equal EdgeIterators have the same graph and the same index.
    */
    bool operator==(const EdgeIterator& e) const{
      return index_==e.index_ and graph_==e.graph_;
    }

   private:
    friend class Graph;
     const graph_type* graph_;
     size_type index_;
     EdgeIterator(const Graph* graph_pointer, size_type index)
       : graph_(graph_pointer), index_(index){
     }
  };

  /** Return the first edge iterator.
  * @post result == edge_iterator iter such that *iter.uid_ == 0
           and *iter.graph_ == this.
  */
  edge_iterator edge_begin() const{
    return EdgeIterator(this,0);
  }
  /** Return the last edge iterator.
  * @post result == edge_iterator iter such that *iter.uid_ == e
           and *iter.graph_ == this. Where e is the total number of edges in
           the graph.
  */
  edge_iterator edge_end() const{
    return EdgeIterator(this,this->num_edges());
  }
 private:

  // Use this space for your Graph class's internals:
  //   helper functions, data members, and so forth.
  // * @nodes is a list with the position of node @i in index i
  std::vector<std::pair<Point, node_value_type>> nodes;
  // * @edges is a list containing pairs of nodes for each edge.
  //   The pair stored in position i corresponds to edge i.
  std::vector<std::pair<size_type, size_type>> edges;
  // * @adjacency is a vector containing vector with pairs. It contains
  //   at position i the pairs of each node adjacent to node i and the
  //   the edge id that connect node i to the adjacent node.
  std::vector<std::vector<std::pair<size_type, size_type>>> adjacency;
};

#endif // CME212_GRAPH_HPP
