/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include "tree.h"
#include "sum.h"
#include "equal.h"
#include "test.h"

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

using Symbol = Node<std::string>;
using Tree = Branch<Symbol>;
using SumTree = Sum<Tree>;
using EqualTree = Equal<Tree>;


auto construction = []() {
    vector<Symbol> nums { Symbol{"a"}, Symbol{"b"}, Symbol{"c"} };
    Test::Show( "Tree elements: ",
            nums[0].view(),
            nums[1].view(),
            nums[2].view() );
    
    Tree tree{"t"};
    tree.add(&nums[0], 0);
    tree.add(&nums[1], 1);
    tree.add(&nums[2], 2);
    Test::Show( "Full Tree: ", tree.view() );
};

auto swap = []() {
    vector<Symbol> nums { {"a"}, {"b"}, {"c"} };
    
    Tree tree{"t"};
    tree.add(&nums[0], 0);
    tree.add(&nums[1], 1);
    tree.add(&nums[2], 2);
    Test::Show( "Init tree: ", tree.view() );
    
    tree.swap(0, 1);
    Test::Show( "Swap first and second elem: ", tree.view() );
         
    tree.swap(0, 1);
    tree.swap(0, 2);
    Test::Show( "Swap first and last elem: ", tree.view() );
};

auto extract = []() {
    vector<Symbol> nums {{"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}, {"h"}, {"e"}};
    
    Tree tree{"t"};
    auto pos{0};
    for(auto& n : nums) {
        tree.add(&n, pos++);
    }
    
    Test::Show( "Tree init: ", tree.view() );
    
    auto s1 {tree.extract("s1", {0,1,2})};
    auto s2 {tree.extract("s2", {3,4,5})};
    auto s3 {tree.extract("s3", {6,7,8})};
    Test::Show( "Extracted: ", s1->view(), s2->view(), s3->view() );
    
    Tree tree2{"t2"};
    tree2.add(s1.get(), 0);
    tree2.add(s2.get(), 1);
    tree2.add(s3.get(), 2);
    
    Test::Show( "New Tree from elem of init tree: ", tree2.view() );
    
    Tree tree3{"t3"}, tree4{"t4"};
    tree3.add(s1.get(), 0);
    tree3.add(s2.get(), 1);
    tree4.add(s3.get(), 0);
    tree4.add(&tree3, 1);
    Test::Show( "New more folded Tree from elem of init tree: ", tree4.view() );
};

auto merge = []() {
    vector<Symbol> nums {{"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}};
    
    Tree tree1{"t1"};
    tree1.add(&nums[0], 0);
    tree1.add(&nums[1], 1);
    tree1.add(&nums[2], 2);
    
    Tree tree2{"t2"};
    tree2.add(&tree1, 0);
    tree2.add(&nums[3], 1);
    tree2.add(&nums[4], 2);
    //Test::Show( "init Tree: ", tree2.view() );
    
    Tree tree{"t"};
    tree.add(&tree2, 0);
    tree.add(&nums[5], 1);
    tree.add(&nums[6], 2);
    
    Test::Show( "init Tree: ", tree.view() );
    
    Tree treeFlat1{"tf"};
    treeFlat1.add(&nums[5], 0);
    treeFlat1.add(&nums[6], 1);
    treeFlat1.merge(&tree2, 0);
    Test::Show( "new more flatten Tree: ", treeFlat1.view() );
    
    Tree treeFlat2{"tf2"};
    treeFlat2.add(&nums[3], 0);
    treeFlat2.add(&nums[4], 1);
    treeFlat2.add(&nums[5], 2);
    treeFlat2.add(&nums[6], 3);
    treeFlat2.merge(&tree1, 0);
    Test::Show( "and more flatten Tree: ", treeFlat2.view() );
    
};

auto expanding = []() {
    vector<Symbol> nums {{"a"}, {"b"}, {"c"}, {"d"}, {"e"}, {"f"}, {"g"}};
    
    Tree tree1{"t1"};
    tree1.add(&nums[0], 0);
    tree1.add(&nums[1], 1);
    tree1.add(&nums[2], 2);
    
    Tree tree2{"t2"};
    tree2.add(&tree1, 0);
    tree2.add(&nums[3], 1);
    tree2.add(&nums[4], 2);
    
    Tree tree{"t"};
    tree.add(&tree2, 0);
    tree.add(&nums[5], 1);
    tree.add(&nums[6], 2);
    
    Test::Show( "init Tree: ", tree.view() );
    
    tree1.setExpanded(false);
    Test::Show( "Roll Tree: ", tree.view() );
    tree2.setExpanded(false);
    Test::Show( "Roll Tree: ", tree.view() );
    tree.setExpanded(false);
    Test::Show( "Roll Tree: ", tree.view() );
    
    tree1.setExpanded(true);
    tree2.setExpanded(true);
    tree.setExpanded(true);
    Test::Show( "Unroll back: ", tree.view() );
    
};

auto sumCulc = []() {
    
    auto test = [](vector<Symbol>&& nums) {
        
        Test::Show( "Tree elements: ",
            nums[0].view(),
            nums[1].view(),
            nums[2].view() );
    
        SumTree tree{"s"};
        tree.add(&nums[0], 0);
        tree.add(&nums[1], 1);
        tree.add(&nums[2], 2);
        Test::Show( "Full Tree: ", tree.view() );
    };
    test({ Symbol{"a"},   Symbol{"3"}, Symbol{"4"} });
    test({ Symbol{"4"},   Symbol{"b"}, Symbol{"4"} });
    test({ Symbol{"-13"}, Symbol{"3"}, Symbol{"4"} });
    test({ Symbol{"a"},   Symbol{"b"}, Symbol{"c"} });
    test({ Symbol{"-78"}, Symbol{"b"}, Symbol{"c"} });
    test({ Symbol{"78.000000001"}, Symbol{"0.0000006"}, Symbol{"0.0000005"} });
};

auto equalTree = []() {
    EqualTree eq{"Eq1"};
    Test::Show( "Empty Tree: ", eq.view() );
    Symbol a {"c"};
    eq.add(&a, 1);
    Test::Show( "With one node: ", eq.view() );
};

int main()
{
    Test::BlockTest<::construction>("construction");
    
    Test::BlockTest<::swap>("swap");
    
    Test::BlockTest<::extract>("extract");
    
    Test::BlockTest<::merge>("merge");
    
    Test::BlockTest<::expanding>("expanding");
    
    Test::BlockTest<::sumCulc>("sumCulc");
    
    Test::BlockTest<::equalTree>("equalTree");
    
    return 0;
}