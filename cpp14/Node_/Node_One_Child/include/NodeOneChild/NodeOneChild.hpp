/**
 * @headerfile NodeOneChild.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Node class with one child.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_NodeOneChild
#define __self_NodeOneChild 1

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self {

/**
 * @class NodeOneChild
 * @brief Node One Child Template Class.
 * @tparam T Type used for Node
*/
template <typename T> class NodeOneChild {
    T data;  /// Node Data
    NodeOneChild* next;  /// Node Child

 public:
    /**
     * @brief Counstructor.
     * @param elem Data to be stored in node
    */
    explicit NodeOneChild(T elem): data(elem), next(nullptr) { ; }
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
     * @brief Getter method for node child.
     * @return NodeOneChild* Node Child 
    */
    NodeOneChild* getNext() { return next; }
    /**
     * @brief Setter method for node child.
     * @param next_ New child
    */
    void setNext(NodeOneChild* next_) { next = next_; }
};

}  // namespace self
#endif
