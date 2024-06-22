#pragma once

#include "graph.h"

#include <forward_list>

template <typename VertexElement>
class TopologicalSorter {
private:

    struct VertexData {
        bool visited;
        VertexElement element;
    };

    typedef Graph<VertexData,int> G;
    typedef typename G::VertexList VertexList;
    typedef typename G::VertexItor VertexItor;
    typedef typename G::EdgeList EdgeList;
    typedef typename G::EdgeItor EdgeItor;
    
    G graph;

public:

    typedef typename G::Vertex Vertex;
    typedef typename G::Edge Edge;

    Vertex& insertVertex(const VertexElement& element) {
        return graph.insertVertex({false, element});
    }

    Edge& insertDirectedEdge(const Vertex& v, const Vertex& u) {
        return graph.insertDirectedEdge(v, u, 0);
    }

    std::forward_list<VertexElement> sort() {
        initialize();
        std::forward_list<VertexElement> sortedElements;
        VertexList verts = graph.vertices();
        for (VertexItor pv = verts.begin(); pv != verts.end(); ++pv) {
            Vertex& v = *pv;
            if (!isVisited(v)) {
                sort(*pv, sortedElements);
            }
        }
        return sortedElements;
    }

private:

    void initialize() {
        VertexList verts = graph.vertices();
        for (VertexItor pv = verts.begin(); pv != verts.end(); ++pv) {
            unvisit(*pv);
        }
    }

    void sort(Vertex& v, std::forward_list<VertexElement>& sortedElements) {
        // TODO
        visit(v);
        EdgeList edges = v.outEdges();
        for(EdgeItor pe = edges.begin(); pe != edges.end(); pe++){
            Vertex& w = (*pe).opposite(v);
            if(!isVisited(w)){
                sort(w,sortedElements);
            }
        }
        sortedElements.push_front((*v).element);
    }

    void visit(Vertex& v) {
        (*v).visited = true;
    }

    void unvisit(Vertex& v) {
        (*v).visited = false;
    }

    bool isVisited(Vertex& v) {
        return (*v).visited;
    }
};
