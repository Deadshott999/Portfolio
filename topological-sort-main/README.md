# Topological Sort

In this lab we will implement topological sorting for directed acyclic graphs (DAG).

## Directed Graph ADT

In a previous lab, we introduced a graph ADT based on the adjacency list representation. This lab provides an extended version of that ADT to support directed graphs and edges. It includes all of the same methods as the original graph ADT plus the following:

* `Graph::insertDirectedEdge`: inserts a directed edge between two vertices.
* `Vertex::outEdges`: returns a list of edges that are directed away from the given vertex.
* `Edge::origin`: returns the source vertex of the given directed edge.
* `Edge::dest`: returns the target vertex of the given directed edge.
* `Edge::isDirected`: returns true if the edge is directed; false if undirected.

## Topological Sorter

Also provided in this lab is a topological sort class built atop the directed graph ADT. It includes public methods for inserting vertices (`insertVertex`) and edges (`insertDirectedEdge`) and a method that returns all vertices as a linked list in topologically sorted order (`sort`).

The `sort` method has already been implemented for you, but it depends on a private helper method of the same name to perform the recursive DFS. Implement this helper method, then make sure all unit tests pass.

## Your Own Sort

Imagine a real-world scenario of topological sorting, perhaps something from your own life. Examples include getting dressed in the morning (see the "Clothing sort" test case), baking a cake, and college courses. Next, implement a simple version of your scenario as a graph in `main`, then sort it using the `TopologicalSorter` class.
