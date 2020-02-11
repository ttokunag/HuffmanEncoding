#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCNode.hpp"

using namespace std;
using namespace testing;

TEST(HCNodeTest, OPERATOR_TEST) {
    HCNode* node1 = new HCNode(3, 'a');
    HCNode* node2 = new HCNode(2, 'b');
    HCNode* node3 = new HCNode(2, 'c');

    HCNodePtrComp cmp;
    // test count comparison
    ASSERT_EQ(cmp(node1, node2), false);
    ASSERT_EQ(cmp(node2, node1), true);
    // test symbol comparison
    ASSERT_EQ(cmp(node2, node3), true);
    ASSERT_EQ(cmp(node3, node2), false);
}