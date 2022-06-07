#ifndef AVL_H
#define AVL_H

#include<vector>

template<typename Key, typename Value>
class AVL
{
	private:
		struct AVLNode {
			const Key key;
			Value value;
			int height;

			AVLNode* left;
			AVLNode* right;

			AVLNode(const Key&, const Value&, const int&);
		};

		int nodeBalanceFactor(AVLNode* const&) const;
		int nodeHeight(AVLNode* const&) const;

		const AVLNode* findFromNode(AVLNode* const&, const Key&) const;

		AVLNode* createTree(const std::vector<std::pair<Key, Value>>&, const int&, const int&);

		AVLNode* root;
	public:
		AVL();
		AVL(std::vector<std::pair<Key, Value>>);

		int height() const;
		int balanceFactor() const;
		
		void insert(const Key&, const Value&);
		const Value* getValue(const Key&) const;
		bool contains(const Key&) const;
		void remove(const Key&);
};

#endif

