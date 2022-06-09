#ifndef AVL_H
#define AVL_H

#include<vector>

/// <summary>
/// A template class representing an AVL tree data structure
/// Duplicate keys are not supported - the lastly added value for a key is taken
/// </summary>
template<typename Key, typename Value>
class AVL
{
	private:
		struct AVLNode {
			Key key;
			Value value;
			int height;

			AVLNode* left;
			AVLNode* right;

			AVLNode(const Key&, const Value&, const int& = 0);
		};

		/// <summary>
		/// Used to calculated the balance factor by height of a node
		/// </summary>
		/// <param>AVLNode* const& the node to be operated on</param>
		int nodeBalanceFactor(AVLNode* const&) const;

		/// <summary>
		/// Used to calculate the height of a node
		/// </summary>
		/// <param>AVLNode* const& the node to be operated on</param>
		int nodeHeight(AVLNode* const&) const;

		/// <summary>
		/// A recursive function to check whether the tree is a valid AVL
		/// </summary>
		/// <param>AVLNode* const& the node from which to start</param>
		bool isAVLInternal(AVLNode* const&) const;

		/// <summary>
		/// Performs a right rotation on a node
		/// </summary>
		/// <param>AVLNode* the node to be rotated against</param>
		/// <return>AVLNode* the new root of the rotated tree</return>
		AVLNode* rotateRight(AVLNode*);

		/// <summary>
		/// Performs a left rotation on a node
		/// </summary>
		/// <param>AVLNode* the node to be rotated against</param>
		/// <return>AVLNode* the new root of the rotated tree</return>
		AVLNode* rotateLeft(AVLNode*);

		/// <summary>
		/// Performs a one of the left left/left right/right right/right left rotations on a node if needed
		/// Otherwise, returns the node passed
		/// </summary>
		/// <param>AVLNode* the node to be balanced</param>
		/// <return>AVLNode* the root of the balanced tree or nullptr if the parameter is nullptr</return>
		AVLNode* balanceNode(AVLNode*);

		/// <summary>
		/// Finds the largest node inside a tree with root the parameter
		/// </summary>
		/// <param>AVLNode* the root of the tree to be searched for largest node</param>
		/// <return>AVLNode* the largest node found or nullptr if the parameter is nullptr</return>
		AVLNode* largestNode(AVLNode*);

		/// <summary>
		/// Finds a node by key performing BST search operation
		/// </summary>
		/// <param>AVLNode* the root of the tree to be searched for the key</param>
		/// <param>const Key& the key to look for</param>
		/// <return>AVLNode* the node found or nullptr otherwise</return>
		const AVLNode* findFromNode(AVLNode* const&, const Key&) const;

		/// <summary>
		/// Inserts a node into the tree with root the parameter
		/// If a node with the same key exists, its value will be changed
		/// </summary>
		/// <param>AVLNode* the root of the tree into which to insert</param>
		/// <param>const Key& the key to insert</param>
		/// <param>const Value& the new value</param>
		/// <return>AVLNode* the new root of the tree - may change from rebalancing</return>
		AVLNode* insertFromNode(AVLNode*, const Key&, const Value&);

		/// <summary>
		/// Removes a node from the tree with root the parameter
		/// </summary>
		/// <param>AVLNode* the root of the tree to be searched for the key</param>
		/// <param>const Key& the key to look for</param>
		/// <return>AVLNode* the new root of the tree - may change from rebalancing</return>
		AVLNode* removeFromNode(AVLNode*, const Key&);

		/// <summary>
		/// Creates a tree from a vector of key-value pairs by sorting them and taking the last occurrence of a key-value pair
		/// </summary>
		/// <param>const std::vector<std::pair<Key, Value>>& the elements to insert</param>
		/// <param>const int& start index - used to recursively build the tree</param>
		/// <param>const int& end index - used to recursively build the tree</param>
		/// <return>AVLNode* the new root</return>
		AVLNode* createTree(const std::vector<std::pair<Key, Value>>&, const int&, const int&);

		/// <summary>
		/// Deletes a tree recursively, used by the destructor
		/// </summary>
		/// <param>AVLNode* the root of the tree to be deleted</param>
		void deleteTree(AVLNode*);

		/// <summary>
		/// Counts the number of nodes in a tree
		/// </summary>
		/// <param>AVLNode* const& the root of the tree to be counted</param>
		/// <return>int the number of nodes inside the tree with root the parameter</return>
		int nodesCountInternal(AVLNode* const&) const;

		AVLNode* root;
	public:
		~AVL();
		AVL();
		AVL(std::vector<std::pair<Key, Value>>);

		/// <summary>
		/// Getter for the height of the AVL tree
		/// </summary>
		/// <return>int the height of the AVL tree</return>
		int height() const;

		/// <summary>
		/// Getter for the balance factor of the AVL tree root
		/// </summary>
		/// <return>int the balance factor of the AVL tree root</return>
		int balanceFactor() const;

		/// <summary>
		/// Checks whether the current tree is a valid AVL tree
		/// </summary>
		bool isAVL() const;
		
		/// <summary>
		/// Inserts an element in the current AVL tree by key using the insertFromNode method
		/// </summary>
		void insert(const Key&, const Value&);

		/// <summary>
		/// Getter for the value of a node, found by key
		/// </summary>
		/// <return>const Value*</return>
		const Value* getValue(const Key&) const;

		/// <summary>
		/// Getter for the value of the root
		/// </summary>
		/// <return>const Value*</return>
		const Value* getRootValue() const;

		/// <summary>
		/// Getter for the key of the root
		/// </summary>
		/// <return>const Key*</return>
		const Key* getRootKey() const;

		/// <summary>
		/// Checks whether an element is inside the current AVL tree by key using the findFromNode method
		/// </summary>
		bool contains(const Key&) const;

		/// <summary>
		/// Removes an element from the current AVL tree by key using the removeFromNode method
		/// </summary>
		void remove(const Key&);

		/// <summary>
		/// Getter for the number of nodes in the current AVL tree
		/// </summary>
		int nodesCount() const;
};

#endif

