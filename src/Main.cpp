#include<src/AVL/AVL.cpp>
#include<iostream>

int main() {
	std::vector<std::pair<int, int>> input{ {6,6}, {4,4}, {2,2}, {1,1}, {3,3}, {6,6}, {5,5}, {6,6}, {4,4}, {6,6}, {1,1}, {7,7} };
	AVL<int, int> tree{input};
	//tree with no duplicates
	std::cout << tree.height();
}