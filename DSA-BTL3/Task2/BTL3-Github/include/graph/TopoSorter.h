/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "hash/xMap.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
template <class T, class V>
using XHashMap = xMap<T, V>;
template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        //TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        //TODO
        if (mode)
            bfsSort(sorted);
        else   
            dfsSort(sorted);
    }
    DLinkedList<T> bfsSort(bool sorted=true){ 
        //TODO
        DLinkedList<T> list;
        Queue<T> q;
        xMap<T, int> inMap = vertex2inDegree(this->hash_code);
        bool compare = [](T a, T b){return a < b;};
        DLinkedListSE<T> listzero = listOfZeroInDegrees();

        if (sorted){
            listzero.sort(compare);
        }
        for (T vertex : listzero){
            q.push(vertex);
        }
        while (!q.empty()){
            T vertex = q.pop();
            list.add(vertex);
            DLinkedListSE<T> neighbors = this->graph->getOutwardEdges(vertex);
            if (sorted){
                neighbors.sort(compare);
            }
            for (T neighbor : neighbors) {
                int inDegree = inMap.get(neighbor) - 1;
                inMap.put(neighbor, inDegree);
                if (inDegree == 0){
                    q.push(neighbor);
                }
            }
        }
        return list;
    }

    DLinkedList<T> dfsSort(bool sorted=true){
        //TODO
        DLinkedList<T> list;
        Stack<T> s;
        xMap<T, int> outMap = vertex2outDegree(this->hash_code);
        bool compare = [](T a, T b){return a < b;};
        DLinkedListSE<T> listzero = listOfZeroInDegrees();

        if (sorted){
            listzero.sort(compare);
        }
        for (T vertex : listzero){
            s.push(vertex);
        }
        while (!s.empty()) {
            T vertex = s.pop();
            list.add(vertex);
            DLinkedListSE<T> neighbors = this->graph->getOutwardEdges(vertex);
            if (sorted) {
                neighbors.sort(compare);
            }
            for (T neighbor : neighbors) {
                int outDegree = outMap.get(neighbor) - 1;
                outMap.put(neighbor, outDegree);
                if (outDegree == 0) {
                    s.push(neighbor);
                }
            }
        }

        return list;
    }

protected:

    //Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int)){
        xMap<T, int> degmap(hash);
        DLinkedList<T> vertices = this->graph->vertices();
        
        for (T vertex : vertices) {
            degmap.put(vertex, this->graph->inDegree(vertex));
        }
        return degmap;
    };
    xMap<T, int> vertex2outDegree(int (*hash)(T&, int)){
        xMap<T, int> degmap(hash);
        DLinkedList<T> vertices = this->graph->vertices();
        
        for (T vertex : vertices) {
            degmap.put(vertex, this->graph->outDegree(vertex)); 
        }
        return degmap;
    };
    DLinkedList<T> listOfZeroInDegrees(){
        DLinkedList<T> listdeg;
        DLinkedList<T> vertices = this->graph->vertices();

        for (T vertex : vertices){
            if (this->graph->inDegree(vertex) == 0)
                listdeg.add(vertex);
        }

        return listdeg;
    }

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

