#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "src/Doctest/doctest.h"
#include "src/SkipList/SkipList.cpp"
#include <stdlib.h>

TEST_CASE("AVL Tree with 50 000 000 elements") {
	SkipList<int, int> testList(20);
    testList.insert(3, 3);
    testList.insert(6, 6);
    testList.insert(7, 7);
    testList.insert(9, 9);
    testList.insert(12, 12);
    testList.insert(19, 19);
    testList.insert(17, 17);
    testList.insert(26, 26);
    testList.insert(21, 21);
    testList.insert(25, 25);
    CHECK(testList.contains(3));
    CHECK(testList.contains(-1) == false);
    CHECK(testList.contains(0) == false);
    CHECK(testList.contains(7));
    testList.remove(7);
    CHECK(testList.contains(7) == false);
}