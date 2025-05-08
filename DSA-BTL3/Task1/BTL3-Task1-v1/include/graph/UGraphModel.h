
/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"


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
        // Lấy các VertexNode tương ứng với các đỉnh from và to
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        if (fromNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(from));  // Ném ngoại lệ nếu không tìm thấy đỉnh from
        }
        
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (toNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(to));  // Ném ngoại lệ nếu không tìm thấy đỉnh to
        }
        // Nếu from và to là cùng một đỉnh, thêm cạnh tự vòng
        if (from == to) {
            fromNode->connect(toNode, weight);  // Thêm cạnh tự vòng từ from đến to
        } else {
            // Nếu từ from đến to đã tồn tại, xóa cạnh cũ để đồng bộ trọng số
            typename AbstractGraph<T>::Edge* existingEdge = fromNode->getEdge(toNode);
            if (existingEdge != nullptr) {
                fromNode->removeTo(toNode);
                toNode->removeTo(fromNode);
            }

            // Thêm cạnh từ from đến to và từ to đến from với cùng trọng số
            fromNode->connect(toNode, weight);
            toNode->connect(fromNode, weight);  // Dùng cùng trọng số như cạnh từ `from` đến `to`
        }
    }
    void disconnect(T from, T to)
    {
        // Lấy các VertexNode tương ứng với các đỉnh from và to
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        if (fromNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(from));  // Ném ngoại lệ nếu không tìm thấy đỉnh from
        }

        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (toNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(to));  // Ném ngoại lệ nếu không tìm thấy đỉnh to
        }

        // Nếu from và to là cùng một đỉnh, xóa cạnh tự vòng
        if (from == to) {
            typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
            if (edge == nullptr) {
                throw EdgeNotFoundException("E(" + this->vertex2str(from) + "," + this->vertex2str(to) + ")");  // Ném ngoại lệ nếu không có cạnh
            }
            fromNode->removeTo(toNode);  // Xóa cạnh tự vòng
        }
        else {
            // Nếu from và to khác nhau, xóa cả hai cạnh (từ from đến to và ngược lại)
            typename AbstractGraph<T>::Edge* edge1 = fromNode->getEdge(toNode);
            if (edge1 == nullptr) {
                throw EdgeNotFoundException("E(" + this->vertex2str(from) + "," + this->vertex2str(to) + ")");  // Ném ngoại lệ nếu không có cạnh
            }
            fromNode->removeTo(toNode);  // Xóa cạnh từ from đến to

            typename AbstractGraph<T>::Edge* edge2 = toNode->getEdge(fromNode);
            if (edge2 == nullptr) {
                throw EdgeNotFoundException("E(" + this->vertex2str(from) + "," + this->vertex2str(to) + ")");  // Ném ngoại lệ nếu không có cạnh
            }
            toNode->removeTo(fromNode);  // Xóa cạnh từ to đến from
        }
    }
    void remove(T vertex)
    {
        // Lấy VertexNode tương ứng với đỉnh cần xóa
        typename AbstractGraph<T>::VertexNode* nodeToRemove = this->getVertexNode(vertex);
        if (nodeToRemove == nullptr) {
            throw VertexNotFoundException(this->vertex2str(vertex));  // Ném ngoại lệ nếu không tìm thấy đỉnh
        }

        // Duyệt qua tất cả các đỉnh trong đồ thị, xóa các cạnh kết nối đến đỉnh cần xóa
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this->nodeList.begin();
        while (it != this->nodeList.end()) {
            typename AbstractGraph<T>::VertexNode* currentNode = *it;
            if (currentNode != nodeToRemove) {
                // Xóa các cạnh kết nối từ currentNode đến nodeToRemove
                typename AbstractGraph<T>::Edge* edge = currentNode->getEdge(nodeToRemove);
                if (edge != nullptr) {
                    currentNode->removeTo(nodeToRemove);  // Xóa cạnh từ currentNode đến nodeToRemove
                }
                // Xóa các cạnh từ nodeToRemove đến currentNode (cạnh từ nodeToRemove đến currentNode)
                edge = nodeToRemove->getEdge(currentNode);
                if (edge != nullptr) {
                    nodeToRemove->removeTo(currentNode);  // Xóa cạnh từ nodeToRemove đến currentNode
                }
            }
            ++it;
        }

        // Xóa đỉnh khỏi danh sách các đỉnh của đồ thị
        this->nodeList.removeItem(nodeToRemove, [](typename AbstractGraph<T>::VertexNode* node) { delete node; });
    }

    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // (a) Khởi tạo đối tượng UGraphModel mới
        UGraphModel<T>* graph = new UGraphModel<T>(vertexEQ, vertex2str);
        
        // (b) Thêm tất cả các đỉnh vào đồ thị
        for (int i = 0; i < nvertices; ++i) {
            graph->add(vertices[i]);  // Thêm từng đỉnh vào đồ thị
        }
        
        // (c) Thêm tất cả các cạnh vào đồ thị
        for (int i = 0; i < nedges; ++i) {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);  // Thêm cạnh vào đồ thị
        }
        
        // (d) Trả về con trỏ đến đồ thị đã tạo
        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
