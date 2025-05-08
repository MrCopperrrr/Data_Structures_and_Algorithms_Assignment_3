/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
// #include "stacknqueue/Queue.h"
// #include "stacknqueue/Stack.h"
// #include "hash/XHashMap.h"
// #include "stacknqueue/PriorityQueue.h"
// #include "sorting/DLinkedListSE.h"


//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        //TODO
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);

        if (!fromNode) throw VertexNotFoundException("from vertex not found");
        if (!toNode) throw VertexNotFoundException("to vertex not found");

        // Add edge from 'fromNode' to 'toNode'
        fromNode->connect(toNode, weight);
    }
    void disconnect(T from, T to){
        //TODO
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);

        if (!fromNode) throw VertexNotFoundException("from vertex not found");
        if (!toNode) throw VertexNotFoundException("to vertex not found");

        // Remove edge from 'fromNode' to 'toNode'
        fromNode->removeTo(toNode);
    }
    void remove(T vertex){
        //TODO
        typename AbstractGraph<T>::VertexNode* targetNode = this->getVertexNode(vertex);
        if (!targetNode) throw VertexNotFoundException("vertex not found");

        // Remove all incoming edges
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator nodeIt = this->nodeList.begin();
        while (nodeIt != this->nodeList.end()) {
            typename AbstractGraph<T>::VertexNode* currentNode = *nodeIt;
            currentNode->removeTo(targetNode);
            ++nodeIt;
        }

        // Remove outgoing edges and the vertex itself
        this->nodeList.removeItem(targetNode);
        delete targetNode;
    }
    
    static DGraphModel<T>* create(
            T* vertices, int nvertices, Edge<T>* edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)){
        //TODO
        // Create a new graph instance
        DGraphModel<T>* graph = new DGraphModel<T>(vertexEQ, vertex2str);

        // Add all vertices to the graph
        for (int i = 0; i < nvertices; ++i) {
            graph->add(vertices[i]);
        }

        // Add all edges to the graph
        for (int i = 0; i < nedges; ++i) {
            graph->connect(edges[i].from->getVertex(), edges[i].to->getVertex(), edges[i].weight);
        }

        return graph;
    }
};

#endif /* DGRAPHMODEL_H */

