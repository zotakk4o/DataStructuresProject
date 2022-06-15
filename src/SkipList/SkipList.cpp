#include "SkipList.h"
#include <math.h>
#include <iostream>

template<typename Key, typename Value>
std::default_random_engine SkipList<Key, Value>::generator;

template<typename Key, typename Value>
std::uniform_real_distribution<double> SkipList<Key, Value>::distribution{ 0.0, 1.0 };

template<typename Key, typename Value>
SkipList<Key,Value>::SkipListNode::SkipListNode(const Key& _key, const Value& _value, const unsigned int& _level) : 
	key(_key), 
	value(_value),
	forward(_level + 1) {}

template<typename Key, typename Value>
SkipList<Key, Value>::SkipListNode::SkipListNode(const unsigned int& _level) :
    forward(_level + 1) {}

template<typename Key, typename Value>
void SkipList<Key, Value>::deleteInternals() {
	if (!this->head) {
		return;
	}

	while (this->head) {
		SkipListNode* current = this->head;
		this->head = this->head->forward[0];

		delete current;
	}
}

template<typename Key, typename Value>
unsigned int SkipList<Key, Value>::generateLevel() const {
    unsigned int levels = 0;

	while (SkipList::distribution(generator) < this->probability && levels < this->maxLevel) {
		levels++;
	}

	return levels;
}

template<typename Key, typename Value>
SkipList<Key, Value>::~SkipList() {
	this->deleteInternals();
}

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList(const unsigned int& maximumElements, const float& _probability) :
	probability(_probability),
	maxLevel(std::log2(maximumElements)),
    heighestLevel(0)
{
    this->head = new SkipListNode{ this->maxLevel };
}

template<typename Key, typename Value>
void SkipList<Key, Value>::insert(const Key& key, const Value& value) {
    std::vector<SkipListNode*> update{ this->maxLevel + 1 };
    SkipListNode* current = this->insertAndDeleteHelper(update, key);

    if (current && current->key == key) {
        return;
    }

    unsigned int generatedLevel = this->generateLevel();
    if (generatedLevel > this->heighestLevel) {
        for (unsigned int i = this->heighestLevel + 1; i < generatedLevel + 1; i++) {
            update[i] = this->head;
        }

        this->heighestLevel = generatedLevel;
    }

    SkipListNode* n = new SkipListNode{ key, value, generatedLevel };

    for (unsigned int i = 0; i <= generatedLevel; i++) {
        n->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = n;
    }
}

template<typename Key, typename Value>
typename SkipList<Key, Value>::SkipListNode* SkipList<Key, Value>::insertAndDeleteHelper(std::vector<SkipListNode*>& update, const Key& key) {
    SkipListNode* current = this->head;

    for (unsigned int i = this->heighestLevel; i >= 0 && i <= this->heighestLevel; i--)
    {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    return current;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::contains(const Key& key) const {
    SkipListNode* current = this->head;

    for (unsigned int i = this->heighestLevel; i >= 0 && i <= this->heighestLevel; i--) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    return current && current->key == key;
}

template<typename Key, typename Value>
void SkipList<Key, Value>::remove(const Key& key) {
    std::vector<SkipListNode*> update{ this->maxLevel + 1 };
    SkipListNode* current = this->insertAndDeleteHelper(update, key);

    if (!current || current->key != key) {
        return;
    }

    for (unsigned int i = 0; i <= this->heighestLevel; i++) {
        if (update[i]->forward[i] != current) {
            break;
        }

        update[i]->forward[i] = current->forward[i];
    }

    while (this->heighestLevel > 0 && !this->head->forward[this->heighestLevel]) {
        this->heighestLevel--;
    }

    delete current;
}