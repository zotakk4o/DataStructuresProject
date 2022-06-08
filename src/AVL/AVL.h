#ifndef AVL_H
#define AVL_H

#include<vector>

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

		int nodeBalanceFactor(AVLNode* const&) const;
		int nodeHeight(AVLNode* const&) const;
		bool isAVLInternal(AVLNode* const&) const;

		AVLNode* rotateRight(AVLNode*);
		AVLNode* rotateLeft(AVLNode*);
		AVLNode* balanceNode(AVLNode*);

		AVLNode* largestNode(AVLNode*);
		const AVLNode* findFromNode(AVLNode* const&, const Key&) const;
		AVLNode* insertFromNode(AVLNode*, const Key&, const Value&);
		AVLNode* removeFromNode(AVLNode*, const Key&);

		AVLNode* createTree(const std::vector<std::pair<Key, Value>>&, const int&, const int&);
		void deleteTree(AVLNode*);

		AVLNode* root;

	public:
		~AVL();
		AVL();
		AVL(std::vector<std::pair<Key, Value>>);

		int height() const;
		int balanceFactor() const;

		bool isAVL() const;
		
		void insert(const Key&, const Value&);
		const Value* getValue(const Key&) const;
		bool contains(const Key&) const;
		void remove(const Key&);
};

#endif

