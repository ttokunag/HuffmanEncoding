#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

// class SimpleHCTreeFixture : public ::testing::Test {
//   protected:
//     HCTree tree;

//   public:
//     SimpleHCTreeFixture() {
//         // initialization code here
//         vector<unsigned int> freqs(256);
//         freqs['a'] = 2;
//         freqs['b'] = 3;
//         tree.build(freqs);
//     }
// };

// TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
//     ostringstream os;
//     tree.encode('a', os);
//     ASSERT_EQ(os.str(), "0");
// }

// TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
//     istringstream is("1");
//     ASSERT_EQ(tree.decode(is), 'b');
// }

TEST(SimpleHCTreeTest, BUILD_TEST) {
    HCTree tree;

    vector<unsigned int> freqs;
    for (int i = 0; i < 256; i++) {
        if (i == 50) {
            freqs.push_back(55);
        } else if (i == 100) {
            freqs.push_back(105);
        } else {
            freqs.push_back(0);
        }
    }

    tree.build(freqs);
}
