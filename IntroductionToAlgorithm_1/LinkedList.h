#pragma once
#include <cassert>
typedef unsigned int UINT;
namespace SingleLinkedList
{
	class LinkedList
	{
	public:
		LinkedList();
		~LinkedList();
	};

}
namespace DoublyLinkedList
{
#define MAX_UINT 2147483647

	template <typename T>
	class HashNode
	{
	public:
		HashNode(UINT k,T val)
		{
			next = nullptr;
			prev = nullptr;
			data = val;
			key = k;
		}
		HashNode(HashNode& nod)
		{
			next = nod.prev;
			prev = nod.next;
			data = nod.data;
			key = nod.key;
		}
		UINT key;
		~HashNode() {
		
		};
		T getdata()
		{
			return data;
		}

		HashNode* next;
		HashNode* prev;
	private:
		T	data;
	};
	template <typename T>
	class HashList
	{
	private:
		HashNode<T>* first;
		HashNode<T>* last;
		UINT size;

	public:
		HashList()
		{
			first = nullptr;
			last = nullptr;
			size = 0;
		}
		;
		~HashList()
		{
			if (this->isEmpty())
				return;
			HashNode<T>* temp = first;

			while (temp != last)
			{
				temp = temp->next;
				delete(temp->prev);
			};
			delete temp;
		};
		
		bool isEmpty()
		{
			if (first == nullptr && size == 0)
				return true;
			else if (first != nullptr && size != 0)
				return false;
			else assert(false);
			return false;
		};

		unsigned int getSize() {
			return size;
		}

		bool insert(UINT k, T val)
		{
			if (size == MAX_UINT) return false;
			HashNode<T>* temp = new HashNode<T>(k, val);
			if (this->isEmpty())
			{
				first = temp;
				last = temp;
				size++;
				return true;
			}
			last->next = temp;
			temp->prev = last;
			last = temp;
			size++;
			return true;
		}
		bool insert(UINT k, T val, unsigned int slot)
		{
			if (size == MAX_UINT) return false;
			if (slot + 1 > size ) return false;
			
			if (this->isEmpty() || size == 1)
			{
				insert(k, val);
			}

			HashNode<T>* temp = first;
			unsigned int i = 0;
			while (i < slot)
			{
				temp = temp->next;
				i++;
			}
			HashNode<T>* newNode = new HashNode<T>(val); // When insert in slot X, the new node will lay between X - 1 and X
			newNode->next = temp;
			newNode->prev = temp->prev;
			temp->prev->next = newNode;
			temp->prev = newNode;
			size++;
			return true;
		};
		bool remove(unsigned int slot)
		{
			if (slot + 1 > size ) return false;
			HashNode<T>* temp = first;
			if (size == 1)
			{
				first = nullptr;
				last = nullptr;
				size--;
				delete temp;
				return true;
			}
			while (i < slot)
			{
				temp = temp->next;
				i++;
			}
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			size--;
			return true;
		}
		bool search(UINT k)
		{
			if (size == 0) return false;
			HashNode<T>* temp = first;
			while (temp != nullptr)
			{
				if (temp->key == k)
				{
					return true;
				}
				temp = temp->next;
			}
			return false;
		}
		bool search(UINT k, T& val)
		{
			if (size == 0) return false;
			HashNode<T>* temp = first;
			while (temp != nullptr)
			{
				if (temp->key == k)
				{
					val = temp->getdata();
					return true;
				}
				temp = temp->next;
			}
			return false;
		}
		void printList() {
			if (size == 0)  return;
			HashNode<T>* temp = first;
			while (temp != nullptr)
			{
				printf("%d\n", temp->key);
				temp = temp->next;
			}
		};
	};
}