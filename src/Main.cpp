#include<src/AVL/AVL.cpp>
#include<iostream>

int main() {
	std::vector<std::pair<int, int>> input{ {6,6}, {4,4}, {2,2}, {1,1}, {3,3}, {6,6}, {5,5}, {6,6}, {4,4}, {6,6}, {1,1}, {7,7} };
	AVL<int, int> tree{input};
	tree.insert(8, 8);
	tree.insert(9, 9);
	tree.insert(10, 10);
	//tree with no duplicates
	std::cout << tree.height() << std::endl;
	std::cout << tree.isAVL() << std::endl;

	tree.remove(1);
	tree.remove(2);
	tree.remove(3);
	std::cout << tree.height() << std::endl;
	std::cout << tree.isAVL();
}