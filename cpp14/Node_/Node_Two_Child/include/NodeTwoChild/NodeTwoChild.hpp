// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Node Two Child

#pragma once
#ifndef __self_NodeTwoChild
#define __self_NodeTwoChild 1

namespace self
{

template <typename T>
class NodeTwoChild
{
    T data;
    NodeTwoChild* left;
    NodeTwoChild* right;
public:
    NodeTwoChild(T elem): data(elem), left(nullptr), right(nullptr) { ; }
    T getData() { return data; }
    void setData(T elem) { data = elem; }
    NodeTwoChild* getLeft() { return left; }
    void setLeft(NodeTwoChild* left_) { left = left_; }
    NodeTwoChild* getRight() { return right; }
    void setRight(NodeTwoChild* right_) { right = right_; }
};

}
#endif
