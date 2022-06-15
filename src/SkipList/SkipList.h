#ifndef SKIPLIST_H
#define SKIPLIST_H

#include<vector>
#include<random>

template<typename Key, typename Value>
class SkipList
{
	private:
		struct SkipListNode {
			Key key;
			Value value;

			std::vector<SkipListNode*> forward;

			SkipListNode(const Key&, const Value&, const unsigned int&);
			SkipListNode(const unsigned int&);
		};

		static std::default_random_engine generator;
		static std::uniform_real_distribution<double> distribution;

		unsigned int maxLevel;
		unsigned int heighestLevel;
		float probability;

		SkipListNode* insertAndDeleteHelper(std::vector<SkipListNode*>&, const Key&);

		unsigned int generateLevel() const;
		void deleteInternals();

		SkipListNode* head;
	public:
		~SkipList();
		SkipList(const unsigned int&, const float& = 0.50);

		void insert(const Key&, const Value&);
		bool contains(const Key&) const;
		void remove(const Key&);
};

#endif

