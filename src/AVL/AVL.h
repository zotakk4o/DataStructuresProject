#ifndef AVL_H
#define AVL_H

template<typename Key, typename Value>
class AVL
{
	private:
		struct AVLNode {
			const Key key;
			Value value;
			int height;

			AVLNode* left = nullptr;
			AVLNode* right = nullptr;

			Node(const Key& key, const Value& value, int height);
		};

		AVLNode* root;
	public:
		void insert(const Key&, const Value&);
		void contains(const Key&);
		void remove(const Key&);
};

#endif

