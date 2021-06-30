/**
 * @headerfile NodeTwoChild.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Node class with two child.
 * @author Kartikei Mittal
*/
#pragma once
#ifndef __self_NodeTwoChild
#define __self_NodeTwoChild 1

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self {

/**
 * @class NodeTowChild
 * @brief Node Two Child Template Class.
 * @tparam T Type used for Node
*/
template <typename T> class NodeTwoChild {
    T data; /// Node Data
    NodeTwoChild* left; /// Node left child
    NodeTwoChild* right; /// Node right child
public:
    /**
     * @brief Counstructor.
     * @param elem Data to be stored in node
    */
    explicit NodeTwoChild(T elem): data(elem), left(nullptr), right(nullptr) { ; }
    /**
     * @brief Getter Method for data.
     * @return T Data in node
    */
    T getData() { return data; }
    /**
     * @brief Setter Method for data.
     * @param elem New Value of the node
    */
    void setData(T elem) { data = elem; }
    /**
     * @brief Getter method for node left child.
     * @return NodeTwoChild* Node Child 
    */
    NodeTwoChild* getLeft() { return left; }
    /**
     * @brief Setter method for node left child.
     * @param left_ New child
    */
    void setLeft(NodeTwoChild* left_) { left = left_; }
    /**
     * @brief Getter method for node right child.
     * @return NodeTwoChild* Node Child 
    */
    NodeTwoChild* getRight() { return right; }
    /**
     * @brief Setter method for node right child.
     * @param right_ New child
    */
    void setRight(NodeTwoChild* right_) { right = right_; }
};

} // namespace self
#endif
