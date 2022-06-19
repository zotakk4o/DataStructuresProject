#ifndef SKIPLIST_H
#define SKIPLIST_H

#include<vector>
#include<random>


/// <summary>
/// A template class representing a Skip list data structure
/// Duplicate keys are not supported - the lastly added value for a key is taken
/// </summary>
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

		/// <summary>
		/// Used to populate the update list with the traversed nodes between the head and the node for which key >= node.key
		/// </summary>
		/// <param>std::vector<SkipListNode*>& the update list to be populated while searching for the position to insert/node to delete</param>
		/// <param>const Key& the key to insert/delete</param>
		/// <return>SkipListNode* the first node for which key >= node.key</return>
		SkipListNode* findInsertOrDeleteNode(std::vector<SkipListNode*>&, const Key&);

		/// <summary>
		/// Uses the built-in random generation via uniform real distribution between 0 and 1
		/// to calculate the levels of a node to be inserted
		/// </summary>
		/// <return>unsigned int the randomly generated level for the new node</return>
		unsigned int generateLevel() const;

		/// <summary>
		/// Used by the destructor to delete the list elements
		/// </summary>
		void deleteInternals();

		SkipListNode* head;
	public:
		~SkipList();
		/// <summary>
		/// Creates a skip list with maximum elements expected and probability for new node levels generation
		/// </summary>
		/// <param>const unsigned int& the number of maximum elements</param>
		/// <param>const float& the probability for generating levels, default is 0.5</param>
		SkipList(const unsigned int&, const float& = 0.50);

		/// <summary>
		/// Inserts a new node for a given key or updates and existing one
		/// </summary>
		/// <param>const Key& the key to look for</param>
		/// <param>const Key& the value to insert/update</param>
		void insert(const Key&, const Value&);

		/// <summary>
		/// Searches for a node with key
		/// </summary>
		/// <param>const Key& the key to look for</param>
		/// <return>bool whether the key was found</return>
		bool contains(const Key&) const;

		/// <summary>
		/// Removes a node with key
		/// </summary>
		/// <param>const Key& the key to look for</param>
		void remove(const Key&);

		/// <summary>
		/// Counts the number of elements at level 0
		/// </summary>
		/// <return>unsigned int the number of elements at level 0</return>
		unsigned int numberOfElements() const;
};

#endif

