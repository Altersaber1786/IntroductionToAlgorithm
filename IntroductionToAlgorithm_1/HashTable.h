#pragma once

#include "LinkedList.h"
#include <stdint.h>
#include <random>
namespace hashing
{
#define MAX_TABLE_LENGTH	10000000
#define MAX_KEY_RANGE		100000000
	bool isPowerOf2(UINT n);
	UINT knuth(UINT  key, uint32_t m);
	UINT simpleKnuth(UINT key, UINT m);
	UINT LinearProbing(UINT Key, UINT m);
	UINT QuadraticProbing(UINT key, UINT m);
	UINT DoubleHashing(UINT key, UINT m);

	enum HashingStyle {
		HASHING_WITH_CHAINING = 0,
		UNIVERSAL_HASHING = 1,
		OPEN_ADRESSING = 2,
		PERFECT_HASHING = 3
	};

	template <typename T>
	class ChainingHashMap
	{
	protected:
		
		DoublyLinkedList::HashList<T>** table;
		UINT size;
		UINT(*hashFunction) (UINT k, UINT m);

	public:
		ChainingHashMap(uint32_t s)
		{
			assert(s <= MAX_TABLE_LENGTH);
			size = s;
			table = new DoublyLinkedList::HashList<T>* [s];
			for (UINT i = 0; i < size; i++)
			{
				table[i] = new DoublyLinkedList::HashList<T>();
			}
			if(isPowerOf2(s))
				hashFunction = &knuth;
			hashFunction = &simpleKnuth;
		};

		bool Insert(UINT key, T data) {
			assert(key <= MAX_KEY_RANGE);
			UINT pos = hashFunction(key, size);
			return(table[pos]->insert(key, data));
		};
		bool Search(UINT k)
		{
			assert(k <= MAX_KEY_RANGE);
			UINT pos = hashFunction(k, size);
			return(table[pos]->search(k));
		}
		bool Search(UINT k, T& val)
		{
			assert(k <= MAX_KEY_RANGE);
			UINT pos = hashFunction(k, size);
			return(table[pos]->search(k, val));
		}
		~ChainingHashMap()
		{
			for (UINT i = 0; i < size; i++)
			{
					delete table[i];
			}
			delete table;
		};
	};

	template<typename T> 
	class UniversalChainingHashMap
	{
	#define P_CONST 201326611
	protected:

		DoublyLinkedList::HashList<T>** table;
		UINT size;
		UINT hashFunction(UINT k, UINT m)
		{
			return (((a*(unsigned long long)k + b) % P_CONST) % m);
		};
		long long a, b;

	public:
		UniversalChainingHashMap(UINT s)
		{
			assert(s <= MAX_TABLE_LENGTH);
			size = s;
			table = new DoublyLinkedList::HashList<T>*[s];
			for (UINT i = 0; i < this->size; i++)
			{
				table[i] = new DoublyLinkedList::HashList<T>();
			}
			a = rand() % 2;
			b = rand() % 2;
			for (int i = 0; i < 63; i++)
			{
				a <<= 1;
				a &= rand() % 2;
				b <<= 1;
				b &= rand() % 2;
			}
			a %= P_CONST;
			b %= P_CONST;
		};

		bool Insert(UINT key, T data) {
			assert(key <= MAX_KEY_RANGE);
			UINT pos = hashFunction(key, size);
			return(table[pos]->insert(key, data));
		};
		bool Search(UINT k)
		{
			assert(k <= MAX_KEY_RANGE);
			UINT pos = hashFunction(k, size);
			return(table[pos]->search(k));
		}
		bool Search(UINT k, T& val)
		{
			assert(k <= MAX_KEY_RANGE);
			UINT pos = hashFunction(k, size);
			return(table[pos]->search(k, val));
		}
		~UniversalChainingHashMap()
		{
			for (UINT i = 0; i < size; i++)
			{
				delete table[i];
			}
			delete table;
		};
	};
	
	template <typename T>
	class OpenAddressingHashMap
	{
#define NULL 0
#define DELETED -1
		struct HashNode {
					int key = NULL;
					T data;
				};
	private:
		UINT size;
		HashNode* table;

	public:
		OpenAddressingHashMap(UINT s)
		{
			assert(size <= MAX_TABLE_LENGTH);
			table = new HashNode[s];
			size = s;
		};

		bool Insert(UINT key, T data) {
			if (key >= size || key <= 0) return false;
			UINT pos;
			//Linear probing
			for (UINT i = 0; i < size; i++)
			{
				pos = (simpleKnuth((UINT)key, size) + i) % size;
				if (table[pos].key == NULL || table[pos].key == DELETED || table[pos].key == key)
					break;
			}
			table[pos].key = key;
			table[pos].data = data;
			return true;
		};
		bool Search(UINT k)
		{
			if (k >= size || k <= 0)
			{
				return false;
			};
			UINT pos;
			//Linear probing
			for (UINT i = 0; i < size; i++)
			{
				pos = (simpleKnuth((UINT)k, size) + i) % size;
				if (table[pos].key == NULL)
					return false;
				else if (table[pos].key == k) {
					return true;
				}
			}
			
			return false;
		}
		bool Search(UINT k, T& val)
		{
			if (k >= size || k <= 0)
			{
				return false;
			};
			UINT pos;
			//Linear probing
			for (UINT i = 0; i < size; i++)
			{
				pos = (simpleKnuth((UINT)k, size) + i) % size;
				if (table[pos].key == NULL)
					return false;
				else if (table[pos].key == k) {
					val = table[pos].data;
					return true;
				}
			}

			return false;
		}
		
		~OpenAddressingHashMap() {
			delete table;
		};

	};
}

