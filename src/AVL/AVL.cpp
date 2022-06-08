#include "AVL.h"
#include <stdlib.h>
#include <algorithm>

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

	return this->nodeHeight(node->left) - this->nodeHeight(node->right);
}

template<typename Key, typename Value>
int AVL<Key, Value>::nodeHeight(AVLNode* const& node) const {
	if (!node) {
		return -1;
	}

	return node->height;
}

template<typename Key, typename Value>
bool AVL<Key, Value>::isAVL() const {
	return this->isAVLInternal(this->root);
}

template<typename Key, typename Value>
bool AVL<Key, Value>::isAVLInternal(AVLNode* const& node) const {
	if (!node) {
		return true;
	}

	if (std::abs(this->nodeBalanceFactor(node)) > 1) {
		return false;
	}

	return this->isAVLInternal(node->left) && this->isAVLInternal(node->right);
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
	AVLNode* newNode = new AVLNode{ current.first, current.second };

	newNode->left = this->createTree(elements, start, currIndex - 1);
	newNode->right = this->createTree(elements, currIndex + 1, end);

	newNode->height = std::max(this->nodeHeight(newNode->left), this->nodeHeight(newNode->right));
	newNode->height += 1;

	return newNode;
}

template<typename Key, typename Value>
void AVL<Key, Value>::deleteTree(AVLNode* node) {
	if (!node) {
		return;
	}

	this->deleteTree(node->left);
	this->deleteTree(node->right);

	delete node;
}

template<typename Key, typename Value>
AVL<Key, Value>::~AVL() {
	this->deleteTree(this->root);
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
void AVL<Key, Value>::insert(const Key& key, const Value& value) {
	this->root = this->insertFromNode(this->root, key, value);
}

template<typename Key, typename Value>
typename AVL<Key, Value>::AVLNode* AVL<Key, Value>::rotateRight(AVLNode* y)
{
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	x->height = 1 + std::max(this->nodeHeight(x->left), this->nodeHeight(x->right));
	y->height = 1 + std::max(this->nodeHeight(y->left), this->nodeHeight(y->right));
	
	// Return new root
	return x;
}

template<typename Key, typename Value>
typename AVL<Key, Value>::AVLNode* AVL<Key, Value>::rotateLeft(AVLNode* x)
{
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = 1 + std::max(this->nodeHeight(x->left), this->nodeHeight(x->right));
	y->height = 1 + std::max(this->nodeHeight(y->left), this->nodeHeight(y->right));

	// Return new root
	return y;
}

template<typename Key, typename Value>
typename AVL<Key, Value>::AVLNode* AVL<Key, Value>::balanceNode(AVLNode* x)
{
	if (this->nodeBalanceFactor(x) < -1) {//left case
		if (this->nodeBalanceFactor(x->right) > 0) {//right left case
			x->right = this->rotateRight(x->right);
		}

		x = this->rotateLeft(x);
	} else if (this->nodeBalanceFactor(x) > 1) {//right case
		if (this->nodeBalanceFactor(x->left) < 0) {//left right case
			x->left = this->rotateLeft(x->left);
		}

		x = this->rotateRight(x);
	}

	return x;
}

template<typename Key, typename Value>
typename const AVL<Key, Value>::AVLNode* AVL<Key, Value>::findFromNode(AVLNode* const& node, const Key& key) const {
	if (!node) {
		return nullptr;
	}

	if (key < node->key) {
		return findFromNode(node->left, key);
	} else if (key > node->key) {
		return findFromNode(node->right, key);
	}

	return node;
}

template<typename Key, typename Value>
typename AVL<Key, Value>::AVLNode* AVL<Key, Value>::insertFromNode(AVLNode* node, const Key& key, const Value& value) {
	if (!node) {
		return new AVLNode(key, value);
	}

	if (key < node->key) {
		node->left = this->insertFromNode(node->left, key, value);
	} else if (key > node->key) {
		node->right = this->insertFromNode(node->right, key, value);
	} else {
		node->value = value;
		return node;
	}

	node->height = 1 + std::max(this->nodeHeight(node->left), this->nodeHeight(node->right));
	return this->balanceNode(node);
}

template<typename Key, typename Value>
typename AVL<Key, Value>::AVLNode* AVL<Key, Value>::removeFromNode(AVLNode* node, const Key& key) {
	if (!node) {
		return nullptr;
	}

	if (key < node->key) {
		node->left = this->removeFromNode(node->left, key);
	} else if (key > node->key) {
		node->right = this->removeFromNode(node->right, key);
	} else {
		if (!node->left || !node->right) { //node's # of children <= 1
			AVLNode* temp = node->left ? node->left : node->right;

			if (!temp) {//node's # of children == 0
				temp = node;
				node = nullptr;
			}
			else {//node's # of children == 1
				*node = *temp;
			}

			delete temp;
		} else { //node's # of childern == 2
			AVLNode* largestNode = this->largestNode(node->left);
			*node = *largestNode;

			node->left = this->removeFromNode(node->left, largestNode->key);
		}
	}

	if (!node) {//The root was removed
		return nullptr;
	}

	node->height = 1 + std::max(this->nodeHeight(node->left), this->nodeHeight(node->right));
	return this->balanceNode(node);
}

template<typename Key, typename Value>
typename AVL<Key, Value>::AVLNode* AVL<Key, Value>::largestNode(AVLNode* node) {
	if (node && node->right) {
		return this->largestNode(node->right);
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
void AVL<Key, Value>::remove(const Key& key) {
	this->root = this->removeFromNode(this->root, key);
}
