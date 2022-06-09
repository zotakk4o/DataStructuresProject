#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "src/Doctest/doctest.h"
#include "src/AVL/AVL.cpp"
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std::chrono;

std::vector<std::pair<int, int>> input{ {6,6}, {4,4}, {2,2}, {1,1}, {3,3}, {6,6}, {5,5}, {6,6}, {4,4}, {6,6}, {1,1}, {7,7}, {8,8}, {9,9}, {10,10} };

void generateInputWithLength(AVL<int, int>& tree, const int& length) {
	for (size_t i = 0; i < length; i++)
	{
		tree.insert(rand(), i);
	}
}

double testAVLWithElements(const int& numberOfElements, const int& numberOfTests, const char& operation) {
	srand(time(NULL));
	float mean = 0;
	for (size_t i = 0; i < numberOfTests; i++) {
		AVL<int, int> tree;
		generateInputWithLength(tree, numberOfElements);
		auto start = high_resolution_clock::now();
		switch (operation) {
			case 'c':
				tree.contains(rand());
				break;
			case 'i':
				tree.insert(rand(), rand());
				break;
			case 'r':
				tree.remove(rand());
				break;
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		mean += duration.count();
	}
	mean /= (float)numberOfTests;

	std::cout << "Elements: " << numberOfElements << ", opreation: " << operation << ", duration in microseconds: " << mean << std::endl;
	return mean;
}

TEST_CASE("AVL Insert") {
	AVL<int, int> tree;
	tree.insert(8, 8);
	tree.insert(9, 9);
	tree.insert(10, 10);
	tree.insert(1, 1);
	tree.insert(2, 2);
	tree.insert(3, 3);
	tree.insert(4, 4);
	tree.insert(5, 5);
	tree.insert(11, 11);
	tree.insert(12, 12);
	tree.insert(7, 7);

	CHECK(tree.height() == 3);
	CHECK(*tree.getRootKey() == 8);
	CHECK(tree.isAVL());
}

TEST_CASE("AVL Insert, duplicate node") {
	AVL<int, int> tree{ input };
	int nodesCount = tree.nodesCount();
	tree.insert(8, 8);

	CHECK(tree.nodesCount() == nodesCount);
	CHECK(tree.isAVL());
}

TEST_CASE("AVL Remove") {
	AVL<int, int> tree{ input };
	int nodesCount = tree.nodesCount();

	tree.remove(1);
	tree.remove(2);
	tree.remove(3);
	tree.remove(5);
	tree.remove(8);

	CHECK(tree.nodesCount() == nodesCount - 5);
	CHECK(tree.isAVL());
}

TEST_CASE("AVL Remove root") {
	AVL<int, int> tree;
	tree.insert(1, 1);
	CHECK(tree.nodesCount() == 1);
	tree.remove(1);
	CHECK(tree.nodesCount() == 0);
}

TEST_CASE("AVL Remove, empty tree") {
	AVL<int, int> tree;
	CHECK(tree.nodesCount() == 0);
	tree.remove(1);
	CHECK(tree.nodesCount() == 0);
}

TEST_CASE("AVL Remove, node that does not exist") {
	AVL<int, int> tree{ input };
	int nodesCount = tree.nodesCount();
	tree.remove(143);
	CHECK(tree.nodesCount() == nodesCount);
}

TEST_CASE("AVL Containts") {
	AVL<int, int> tree{ input };
	CHECK(tree.contains(1));
}

TEST_CASE("AVL Containts, empty tree") {
	AVL<int, int> tree;
	CHECK(tree.contains(1) == false);
}

TEST_CASE("AVL Containts, node that does not exist") {
	AVL<int, int> tree{ input };
	CHECK(tree.contains(893223) == false);
}

TEST_CASE("AVL Tree with 50 elements") {
	CHECK(testAVLWithElements(50, 1, 'i') < 5);
	CHECK(testAVLWithElements(50, 1, 'c') < 5);
	CHECK(testAVLWithElements(50, 1, 'r') < 5);
}

TEST_CASE("AVL Tree with 500 elements") {
	CHECK(testAVLWithElements(500, 1, 'i') < 5);
	CHECK(testAVLWithElements(500, 1, 'c') < 5);
	CHECK(testAVLWithElements(500, 1, 'r') < 5);
}

TEST_CASE("AVL Tree with 5 000 elements") {
	CHECK(testAVLWithElements(5000, 1, 'i') < 5);
	CHECK(testAVLWithElements(5000, 1, 'c') < 5);
	CHECK(testAVLWithElements(5000, 1, 'r') < 5);
}

TEST_CASE("AVL Tree with 50 000 elements") {
	CHECK(testAVLWithElements(50000, 1, 'i') < 10);
	CHECK(testAVLWithElements(50000, 1, 'c') < 10);
	CHECK(testAVLWithElements(50000, 1, 'r') < 10);
}

TEST_CASE("AVL Tree with 500 000 elements") {
	CHECK(testAVLWithElements(500000, 1, 'i') < 20);
	CHECK(testAVLWithElements(500000, 1, 'c') < 20);
	CHECK(testAVLWithElements(500000, 1, 'r') < 20);
}

TEST_CASE("AVL Tree with 5 000 000 elements") {
	CHECK(testAVLWithElements(5000000, 1, 'i') < 20);
	CHECK(testAVLWithElements(5000000, 1, 'c') < 20);
	CHECK(testAVLWithElements(5000000, 1, 'r') < 20);
}

TEST_CASE("AVL Tree with 50 000 000 elements") {
	CHECK(testAVLWithElements(50000000, 1, 'i') < 20);
	CHECK(testAVLWithElements(50000000, 1, 'c') < 20);
	CHECK(testAVLWithElements(50000000, 1, 'r') < 20);
}