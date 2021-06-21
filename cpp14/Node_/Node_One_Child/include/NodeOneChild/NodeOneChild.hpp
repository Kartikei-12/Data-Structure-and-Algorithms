// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Node One Child

#pragma once
#ifndef __self_NodeOneChild
#define __self_NodeOneChild 1

namespace self
{

template <typename T>
class NodeOneChild
{
    T data;
    NodeOneChild* next;
public:
    NodeOneChild(T elem): data(elem), next(nullptr) { ; }
    T getData() { return data; }
    void setData(T elem) { data = elem; }
    NodeOneChild* getNext() { return next; }
    void setNext(NodeOneChild* next_) { next = next_; }
};

}
#endif
