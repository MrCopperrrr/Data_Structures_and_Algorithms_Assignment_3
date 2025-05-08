/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
// #include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
         typename AbstractGraph<T>::VertexNode *fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(to);

        if (!fromNode)
            throw VertexNotFoundException("from vertex not found");
        if (!toNode)
            throw VertexNotFoundException("to vertex not found");

        // Thêm cạnh hai chiều
        fromNode->connect(toNode, weight);
        toNode->connect(fromNode, weight);
    }
    void disconnect(T from, T to)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(to);

        if (!fromNode)
            throw VertexNotFoundException("from vertex not found");
        if (!toNode)
            throw VertexNotFoundException("to vertex not found");

        // Xóa cạnh hai chiều
        fromNode->removeTo(toNode);
        toNode->removeTo(fromNode);
    }
    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *targetNode = this->getVertexNode(vertex);
        if (!targetNode)
            throw VertexNotFoundException("vertex not found");

        // Xóa tất cả các cạnh liên quan đến targetNode
        typename DLinkedList<typename AbstractGraph<T>::VertexNode *>::Iterator nodeIt = this->nodeList.begin();
        while (nodeIt != this->nodeList.end())
        {
            typename AbstractGraph<T>::VertexNode *currentNode = *nodeIt;
            currentNode->removeTo(targetNode);
            targetNode->removeTo(currentNode);
            ++nodeIt;
        }

        // Xóa đỉnh ra khỏi danh sách
        this->nodeList.removeItem(targetNode);
        delete targetNode;
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
         // Tạo một đồ thị mới
        UGraphModel<T> *graph = new UGraphModel<T>(vertexEQ, vertex2str);

        // Thêm các đỉnh vào đồ thị
        for (int i = 0; i < nvertices; ++i)
        {
            graph->add(vertices[i]);
        }

        // Thêm các cạnh vào đồ thị
        for (int i = 0; i < nedges; ++i)
        {
            graph->connect(edges[i].from->getVertex(), edges[i].to->getVertex(), edges[i].weight);
        }

        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
