#ifndef __SUM_H
#define __SUM_H

#include "tree.h"

template <typename Branch>
class Sum : public Branch {

protected:
    using Node = Branch::Node; 
    using T = Node::templ_parnt_type;
    double valsConverted_ {0};
    bool isConvertable(String value) {
        try {
            const auto val {std::stod(value.c_str())};
            valsConverted_ += val;
            return true;
        } catch(...){
            return false;
        }
    }
    
public:
    Sum(String name) : Branch(name) { Branch::binOp_ = "+"; }
    ~Sum() override = default;
    
    T initVal() override { return "("; };
    T appendVal(T res, Node* node) override { 
        const auto binOp {res == "(" ? "": Branch::binOp_};
        const auto value {node->view()};
        if ( isConvertable(value) ) {
            return res;
        }
        return res + binOp + value;
    };
    T endVal() override {
        String res;
        if (valsConverted_) {
            auto binOp {valsConverted_<0? "": Branch::binOp_};
            res += (binOp + std::to_string(valsConverted_));
        }
        res += ")";
        return res;
    };
    
};


#endif //__SUM_H