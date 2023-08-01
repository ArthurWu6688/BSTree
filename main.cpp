#include "BSTree.h"

void TestBSTree1() {
    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
    BSTree<int> t;
    for (auto e: a) {
        t.Insert(e);
    }
    t.InOrder();
}

int main() {
    TestBSTree1();

    return 0;
}
