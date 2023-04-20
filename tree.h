#ifndef __TREE_H
#define __TREE_H

#include <list>
#include <string>
#include <sstream>
#include <numeric>
#include <memory>

#include "types_global.h"

template<typename T>
class Node {
    T repr_;
    
protected:
    using templ_parnt_type = T;

public:
    Node(T repr) : repr_{repr} {}
    virtual ~Node() = default;
    
    virtual T view() { return repr_; };
};

template<typename Node>
class Branch: public Node {
    Node* parent_;
    std::list<Node*> nodes_;
    using T = typename Node::templ_parnt_type;

protected:
    std::string binOp_ {","};
    virtual T initVal() { return "("; };
    virtual T appendVal(T res, Node* node) { 
        const auto binOp {res == "(" ? "": binOp_};
        return res + binOp + node->view();
    };
    virtual T endVal() { return ")"; };
    bool expanded_ = true;

public:
    Branch(String name) : Node{name} {}
    ~Branch() override  = default;
    
    bool isExpanded() const { return expanded_; }
    
    void setExpanded(bool expanded) { expanded_ = expanded; }
    
    auto getNode(int pos) { return std::next(nodes_.begin(), pos); }
    
    void add(Node* node, int pos) {
        nodes_.insert(getNode(pos), node);
    }

    void del(int pos) {
        nodes_.erase(getNode(pos));
    }

    T view() override {
        
        if (!expanded_) return Node::view();
        
        T res0 {initVal()};
        T res = std::accumulate(nodes_.cbegin(),
                                nodes_.cend(), 
                                res0,
                                [this](auto res, auto it) { return appendVal(res, it); }
        );
        res += endVal();
        return res;
    }
    
    void swap(int pos1, int pos2) {
        std::swap(*getNode(pos1), *getNode(pos2));
    }
    
    std::unique_ptr<Branch> extract(String name, std::initializer_list<int> nodes) {
        auto subBranch {std::make_unique<Branch>(name)};
        auto insPos {0};
        for(auto takePos: nodes) {
            subBranch->add(*getNode(takePos), insPos++);
        }
        return subBranch;
    }
    
    void merge(Branch* subTree, int pos) {
        for(auto n: subTree->nodes_) {
            add(n , pos++);
        }
    }
};

#endif //__TREE_H