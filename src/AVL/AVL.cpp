#include "AVL.h"

template<typename Key, typename Value>
AVL<Key, Value>::AVLNode::AVLNode(const Key& _key, const Value& _value, const int& _height) : 
	key(_key), 
	value(_value), 
	height(_height), 
	left(nullptr), 
	right(nullptr) {}

template<typename Key, typename Value>
int AVL<Key, Value>::nodeBalanceFactor(AVLNode* const& node) const {
	if (!node) {
		return 0;
	}

	return height(node->left) - height(node->right);
}

template<typename Key, typename Value>
int AVL<Key, Value>::nodeHeight(AVLNode* const& node) const {
	if (!node) {
		return -1;
	}

	return node->height;
}

template<typename Key, typename Value>
AVL<Key, Value>::AVL() 
	: root(nullptr) {}


template<typename Key, typename Value>
typename AVL<Key, Value>::AVLNode* AVL<Key, Value>::createTree(const std::vector<std::pair<Key, Value>>& elements, const int& start, const int& end) {
	if (end - start < 0) {
		return nullptr;
	}

	int elementsSize = end + 1 - start;
	int currIndex = start;
	currIndex += elementsSize % 2 == 0 ? elementsSize / 2 - 1 : elementsSize / 2;

	std::pair<Key, Value> current = elements[currIndex];
	AVLNode* newNode = new AVLNode{ current.first, current.second, 0 };

	newNode->left = this->createTree(elements, start, currIndex - 1);
	newNode->right = this->createTree(elements, currIndex + 1, end);

	int leftNodeHeight = this->nodeHeight(newNode->left);
	int rightNodeHeight = this->nodeHeight(newNode->right);

	newNode->height = leftNodeHeight > rightNodeHeight ? leftNodeHeight : rightNodeHeight;
	newNode->height += 1;

	return newNode;
}

template<typename Key, typename Value>
AVL<Key, Value>::AVL(std::vector<std::pair<Key, Value>> elements) {
	std::qsort(
		elements.data(),
		elements.size(),
		sizeof(std::pair<Key, Value>),
		[](const void* x, const void* y) {
			const std::pair<Key, Value> arg1 = *static_cast<const std::pair<Key, Value>*>(x);
			const std::pair<Key, Value> arg2 = *static_cast<const std::pair<Key, Value>*>(y);

			if (arg1.first < arg2.first) return -1;
			if (arg1.first > arg2.first) return 1;
			return 0;
		});

	//Remove duplicate keys, last duplicate is taken
	size_t elementsSize = elements.size();
	std::vector<std::pair<Key, Value>> filtered;
	for (size_t i = 0; i < elementsSize; i++) {
		while (i < elementsSize - 1 && elements[i] == elements[i + 1]) {
			i++;
		}

		filtered.push_back(elements[i]);
	}

	this->root = this->createTree(filtered, 0, filtered.size() - 1);
}

template<typename Key, typename Value>
int AVL<Key, Value>::height() const {
	return this->nodeHeight(this->root);
}

template<typename Key, typename Value>
int AVL<Key, Value>::balanceFactor() const {
	return this->nodeBalanceFactor(this->root);
}

template<typename Key, typename Value>
void AVL<Key, Value>::insert(const Key&, const Value&) {

}

template<typename Key, typename Value>
typename const AVL<Key, Value>::AVLNode* AVL<Key, Value>::findFromNode(AVLNode* const& node, const Key& key) const {
	if (!node) {
		return nullptr;
	}

	if (key < node->key) {
		return findFromNode(node->left, key);
	}
	else if (key > node->key)
	{
		return findFromNode(node->right, key);
	}

	return node;
}

template<typename Key, typename Value>
const Value* AVL<Key, Value>::getValue(const Key& key) const {
	AVLNode* result = this->findFromNode(this->root, key);
	if (!result) {
		return nullptr;
	}

	return result->value;
}

template<typename Key, typename Value>
bool AVL<Key, Value>::contains(const Key& key) const {
	return this->findFromNode(this->root, key) != nullptr;
}

template<typename Key, typename Value>
void AVL<Key, Value>::remove(const Key&) {

}
