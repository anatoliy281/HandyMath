#ifndef __EQUAL_H
#define __EQUAL_H

#include "tree.h"
#include <memory>

template<typename Branch>
class Equal : public Branch {
protected:
    using Node = Branch::Node; 
    using T = Node::templ_parnt_type;
    std::unique_ptr<Node> self;

public:
    Equal(String name) : self{std::make_unique<Node>(name)}, Branch(name) {
        Branch::binOp_ = "=";
        Branch::add(self.get(), 0);
    }

    ~Equal() override = default;

};

#endif //__EQUAL_H