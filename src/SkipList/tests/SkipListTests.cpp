#include "src/Doctest/doctest.h"
#include "src/SkipList/SkipList.cpp"
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>

using namespace std::chrono;

void generateInputWithLength(SkipList<int, int>& skipList, const int& length) {
	for (size_t i = 0; i < length; i++)
	{
		skipList.insert(rand(), i);
	}
}

double testSkipListWithElements(const unsigned int& numberOfElements, const int& numberOfTests, const char& operation) {
	srand(time(NULL));
	float mean = 0;
	for (size_t i = 0; i < numberOfTests; i++) {
		SkipList<int, int> skipList{numberOfElements};
		generateInputWithLength(skipList, numberOfElements);
		auto start = high_resolution_clock::now();
		switch (operation) {
			case 'c':
				skipList.contains(rand());
				break;
			case 'i':
				skipList.insert(rand(), rand());
				break;
			case 'r':
				skipList.remove(rand());
				break;
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		mean += duration.count();
	}
	mean /= (float)numberOfTests;

	std::cout << "SkipList Elements: " << numberOfElements << ", opreation: " << operation << ", duration in microseconds: " << mean << std::endl;
	return mean;
}

TEST_CASE("SkipList Insert") {
	SkipList<int, int> skipList{11};
	skipList.insert(8, 8);
	skipList.insert(9, 9);
	skipList.insert(10, 10);
	skipList.insert(1, 1);
	skipList.insert(2, 2);
	skipList.insert(3, 3);
	skipList.insert(4, 4);
	skipList.insert(5, 5);
	skipList.insert(11, 11);
	skipList.insert(12, 12);
	skipList.insert(7, 7);

	CHECK(skipList.numberOfElements() == 11);
}

TEST_CASE("SkipList Insert, duplicate node") {
	SkipList<int, int> skipList{ 2 };
	skipList.insert(8, 8);
	skipList.insert(8, 8);

	CHECK(skipList.numberOfElements() == 1);
}

TEST_CASE("SkipList Remove") {
	SkipList<int, int> skipList{ 11 };
	skipList.insert(8, 8);
	skipList.insert(9, 9);
	skipList.insert(10, 10);
	skipList.insert(1, 1);
	skipList.insert(2, 2);
	skipList.insert(3, 3);
	skipList.insert(4, 4);
	skipList.insert(5, 5);
	skipList.insert(11, 11);
	skipList.insert(12, 12);
	skipList.insert(7, 7);

	skipList.remove(1);
	skipList.remove(2);
	skipList.remove(3);
	skipList.remove(5);
	skipList.remove(8);

	CHECK(skipList.numberOfElements() == 6);
}

TEST_CASE("SkipList Remove root") {
	SkipList<int, int> skipList{ 1 };
	skipList.insert(1, 1);
	CHECK(skipList.numberOfElements() == 1);
	skipList.remove(1);
	CHECK(skipList.numberOfElements() == 0);
}

TEST_CASE("SkipList Remove, empty list") {
	SkipList<int, int> skipList{ 1 };
	CHECK(skipList.numberOfElements() == 0);
	skipList.remove(1);
	CHECK(skipList.numberOfElements() == 0);
}

TEST_CASE("SkipList Remove, element that does not exist") {
	SkipList<int, int> skipList{ 1 };
	int numberOfElements = skipList.numberOfElements();
	skipList.remove(143);
	CHECK(skipList.numberOfElements() == numberOfElements);
}

TEST_CASE("SkipList Containts") {
	SkipList<int, int> skipList{ 11 };
	skipList.insert(8, 8);
	skipList.insert(9, 9);
	skipList.insert(10, 10);
	skipList.insert(1, 1);
	skipList.insert(2, 2);
	skipList.insert(3, 3);
	skipList.insert(4, 4);
	skipList.insert(5, 5);
	skipList.insert(11, 11);
	skipList.insert(12, 12);
	skipList.insert(7, 7);
	CHECK(skipList.contains(1));
}

TEST_CASE("SkipList Containts, empty list") {
	SkipList<int, int> skipList{ 1 };
	CHECK(skipList.contains(1) == false);
}

TEST_CASE("SkipList Containts, node that does not exist") {
	SkipList<int, int> skipList{ 2 };
	skipList.insert(8, 8);
	skipList.insert(9, 9);

	CHECK(skipList.contains(893223) == false);
}

TEST_CASE("SkipList Tree with 50 elements") {
	CHECK(testSkipListWithElements(50, 1, 'i') < 10);
	CHECK(testSkipListWithElements(50, 1, 'c') < 10);
	CHECK(testSkipListWithElements(50, 1, 'r') < 10);
}

TEST_CASE("SkipList Tree with 500 elements") {
	CHECK(testSkipListWithElements(500, 1, 'i') < 10);
	CHECK(testSkipListWithElements(500, 1, 'c') < 10);
	CHECK(testSkipListWithElements(500, 1, 'r') < 10);
}

TEST_CASE("SkipList Tree with 5 000 elements") {
	CHECK(testSkipListWithElements(5000, 1, 'i') < 10);
	CHECK(testSkipListWithElements(5000, 1, 'c') < 10);
	CHECK(testSkipListWithElements(5000, 1, 'r') < 10);
}

TEST_CASE("SkipList Tree with 50 000 elements") {
	CHECK(testSkipListWithElements(50000, 1, 'i') < 20);
	CHECK(testSkipListWithElements(50000, 1, 'c') < 20);
	CHECK(testSkipListWithElements(50000, 1, 'r') < 20);
}

TEST_CASE("SkipList Tree with 500 000 elements") {
	CHECK(testSkipListWithElements(500000, 1, 'i') < 20);
	CHECK(testSkipListWithElements(500000, 1, 'c') < 20);
	CHECK(testSkipListWithElements(500000, 1, 'r') < 20);
}

TEST_CASE("SkipList Tree with 5 000 000 elements") {
	CHECK(testSkipListWithElements(5000000, 1, 'i') < 50);
	CHECK(testSkipListWithElements(5000000, 1, 'c') < 50);
	CHECK(testSkipListWithElements(5000000, 1, 'r') < 50);
}

//TEST_CASE("SkipList Tree with 50 000 000 elements") {
//	CHECK(testSkipListWithElements(50000000, 1, 'i') < 50);
//	CHECK(testSkipListWithElements(50000000, 1, 'c') < 50);
//	CHECK(testSkipListWithElements(50000000, 1, 'r') < 50);
//}