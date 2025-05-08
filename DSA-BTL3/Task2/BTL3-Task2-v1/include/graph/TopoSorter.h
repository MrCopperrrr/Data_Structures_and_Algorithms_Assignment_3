
#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"

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
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        //TODO
    }
    DLinkedList<T> bfsSort(bool sorted=true){ 
        //TODO
    }

    DLinkedList<T> dfsSort(bool sorted=true){
        //TODO
    }

protected:

    //Helper functions
    XHashMap<T, int> vertex2inDegree(int (*hash)(T&, int));
    XHashMap<T, int> vertex2outDegree(int (*hash)(T&, int));
    DLinkedList<T> listOfZeroInDegrees();

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

