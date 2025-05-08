/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"



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
        // Lấy các VertexNode tương ứng với các đỉnh from và to
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        if (fromNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(from));
        }

        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (toNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(to));
        }
        // Kiểm tra nếu cạnh đã tồn tại
        typename AbstractGraph<T>::Edge* existingEdge = fromNode->getEdge(toNode);
        if (existingEdge != nullptr) {
            // Nếu cạnh đã tồn tại, xóa cạnh cũ
            fromNode->removeTo(toNode); // Điều này tự động cập nhật số inDegree và outDegree
        }

        // Thêm cạnh mới với trọng số mới
        fromNode->connect(toNode, weight);
    }
    void disconnect(T from, T to){
        // Lấy các VertexNode tương ứng với các đỉnh from và to
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        if (fromNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(from));
        }

        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (toNode == nullptr) {
            throw VertexNotFoundException(this->vertex2str(to));
        }

        // Lấy cạnh từ từ đỉnh from đến đỉnh to
        typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
        if (edge == nullptr) {
            throw EdgeNotFoundException("E(" + this->vertex2str(from) + "," + this->vertex2str(to) + ")");
        }

        // Xóa cạnh khỏi đồ thị
        fromNode->removeTo(toNode);
    }
    void remove(T vertex){
        // Lấy VertexNode tương ứng với đỉnh cần xóa
        typename AbstractGraph<T>::VertexNode* nodeToRemove = this->getVertexNode(vertex);
        if (nodeToRemove == nullptr) {
            throw VertexNotFoundException(this->vertex2str(vertex));
        }

        // Duyệt qua tất cả các đỉnh trong đồ thị và xóa các cạnh liên kết đến hoặc từ nodeToRemove
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this->nodeList.begin();
        while (it != this->nodeList.end()) {
            typename AbstractGraph<T>::VertexNode* currentNode = *it;
            if (currentNode != nodeToRemove) {
                // Xóa cạnh từ currentNode đến nodeToRemove (nếu có)
                typename AbstractGraph<T>::Edge* edge = currentNode->getEdge(nodeToRemove);
                if (edge != nullptr) {
                    currentNode->removeTo(nodeToRemove);
                }
                // Xóa các cạnh từ nodeToRemove đến currentNode (cạnh từ nodeToRemove đến currentNode)
                edge = nodeToRemove->getEdge(currentNode);
                if (edge != nullptr) {
                    nodeToRemove->removeTo(currentNode);  // Xóa cạnh từ nodeToRemove đến currentNode
                }
            }
            ++it;
        }

        // Xóa đỉnh khỏi danh sách các đỉnh
        this->nodeList.removeItem(nodeToRemove, [](typename AbstractGraph<T>::VertexNode* node) { delete node; });
    }
    static DGraphModel<T>* create(
            T* vertices, int nvertices, Edge<T>* edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)){
        // (a) Khởi tạo một đối tượng DGraphModel mới
        DGraphModel<T>* graph = new DGraphModel<T>(vertexEQ, vertex2str);

        // (b) Thêm tất cả các đỉnh vào đồ thị
        for (int i = 0; i < nvertices; ++i) {
            graph->add(vertices[i]);
        }

        // (c) Thêm tất cả các cạnh vào đồ thị
        for (int i = 0; i < nedges; ++i) {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }

        // (d) Trả về con trỏ tới đồ thị được tạo
        return graph;
    }
};

#endif /* DGRAPHMODEL_H */

