#include "List.h"
#ifndef _PSLL_H_
#define _PSLL_H_
#include <stdexcept>
#include<iostream>
#include<typeinfo>
namespace cop3530 {
	template <typename PS>
	class PSLL : public List <PS> {
	public:
		//constructors & destructiors
		PSLL();
		~PSLL() override;
		//Copy constructor
		PSLL(const PSLL &obj);
		//Copy assignment operator
		PSLL& operator= (const PSLL &obj);
		//Move constructor
		PSLL(PSLL&&) noexcept;
		//Move assignment operator
		PSLL& operator=(PSLL&& obj) noexcept;
		//operations
		void insert(PS element, int position) override;
		void push_back(PS element) override;
		void push_front(PS element) override;
		PS replace(PS element, int position) override;
		PS remove(int position) override;
		PS pop_back(void) override;
		PS pop_front(void)override;
		PS& item_at(int position) override;
		PS& peek_back(void) override;
		PS& peek_front(void) override;
		bool is_empty(void) override;
		bool is_full(void) override;
		size_t length(void) override;
		void clear(void) override;
		//bool equals_function(PS element) override;
		bool contains(const PS& element, bool equals_function(const PS& existingElement, const PS& element)) override;
		void print(std::ostream &ostream) override;
		PS* contents(void) override;
		size_t freeListLength(void);
	private:
		void checkFreePool(void);	
		
		void saveMemory(void);

		struct Node {
			PS data;
			Node* next;
			Node(PS element) {
				data = element;
			}
			Node() {
				
			}
		};
		void push_front_free(Node* newNode);
		Node* head;
		Node* tail;
		Node* freeNode;
		const size_t POOL_SIZE = 50;
		std::string type;
	public:
		template <typename PSI>
		class PSLL_Iter {
		public:
			// type aliases required for C++ iterator compatibility
			using value_type = PSI;
			using reference = PSI&;
			using pointer = PSI*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			// type aliases for prettier code
			using self_type = PSLL_Iter;
			using self_reference = PSLL_Iter&;

		private:
			Node* here;

		public:
			// factories called by class rectangle
			//static because I will call these functions without calling on objects. I call functions on the class (iter)
			static self_type make_begin(Node* here) {
				PSLL_Iter i(here);
				return i;
			}
			static self_type make_end(Node* here) {
				PSLL_Iter i(here);
				return i;
			}
			explicit PSLL_Iter(Node* start = nullptr) : here(start) {} //if nothing is passed, it will start at the nullptr
																	   //else, it will start at the node I passed in.
			PSLL_Iter(const PSLL_Iter& src) : here(src.here) {} //copy constructor

																//return the value in the current node pointed by the iterator (which is here)
			reference operator*() const {
				if (!here) {
					throw new std::runtime_error("here is a null pointer.");
				}
				return here->data; //return reference to the data
			}
			pointer operator->() const { return &(operator*()); } //return a pointer to the address of here->data

			self_reference operator=(PSLL_Iter<PSI> const& src) {
				if (this == &src) {
					return(*this);
				}
				here = src.here; //the pointer on the left side points to whatever the pointer on the right side points to
				return *this;
			}
			// preincrement
			self_reference operator++() {
				if (here)
					here = here->next;
				return *this;
			}
			// postincrement
			self_type operator++(int) {
				self_type tmp(*this);
				++(*this);
				return tmp;
			}

			bool operator==(PSLL_Iter<PSI> const& rhs) const {
				return (here == rhs.here);
			}
			bool operator!=(PSLL_Iter<PSI> const& rhs) const {
				return (here != rhs.here);
			}

		};//end SSLL_Iter
		//using size_t = std::size_t;
		using value_type = PS;
		using iterator = PSLL_Iter<PS>;
		using const_iterator = PSLL_Iter<PS const>;
		// iterators over a non-const List
		iterator begin() { 
			//PSLL_Iter i(head);
			//return i;
			return iterator::make_begin(head); 
		}
		iterator end() { return iterator::make_end(nullptr); }

		// iterators over a const List
		const_iterator begin() const { return const_iterator::make_begin(head); }
		const_iterator end() const { return const_iterator::make_end(nullptr); }
	};
	//Check the length of the free list
	template <typename PS>
	size_t PSLL<PS>::freeListLength(void) {
		//Set curr to head
		size_t len = 0;
		Node* curr = freeNode;
		while (curr) {
			len++;
			curr = curr->next;
		}
		return len;
	}
	//Define saveMemory (check if there are too many unused nodes in the free list)
	template <typename PS>
	void PSLL<PS>::saveMemory(void) {
		int listLen = length();
		int freeLen = freeListLength();

		if (listLen >= 100 && freeLen > 0.5*listLen) {
			Node* prev = freeNode;
			Node* curr = prev->next;
            //delete the rest of the nodes 
			for (int i = 1; i < listLen / 2; i++) {
				prev = curr;
				curr = curr->next;
			}
			Node* temp;
			prev->next = 0;
			while (curr) {
				temp = curr;
				curr = curr->next;
				delete temp;
			}
			
		}
	}

	//Define checkFreePool (pop_back_pool) -- check if there is a node in the pool
	template <typename PS>
	void PSLL<PS>::checkFreePool(void) {
		//Set curr to freeNode
		Node* curr = freeNode;
		//If there is one free node in the free list, then set the freeNode to a null pointer
		if (curr->next == 0) {
			freeNode = 0;
		}
		//If there is more than one free node in the free list, then set the last free node to a null pointer
		else {
			while (curr->next->next) {
				curr = curr->next;
			}
			curr->next = 0;
		}		
	}

	//Define push_front_free (newNode) -- add new node in front of the pool
	template <typename PS>
	void PSLL<PS>::push_front_free(Node* newNode) {
		//If there is more than one node in the free list, then add the new free Node to the front of the free list
		if (freeNode) {
			newNode->next = freeNode;
			freeNode = newNode;
		}
		//If there is no free nodes in the free list, then set freeNode to the new free node.
		else {
			freeNode = newNode;
			freeNode->next = 0;
		}
	}

	//Define constructor and destructor
	template <typename PS>
	PSLL<PS>::PSLL() {
		head = 0;
		tail = 0;
		freeNode = 0;
		type = (typeid(PS).name());
	}
	//Destructor
	template <typename PS>
	PSLL <PS>::~PSLL() {
		Node* curr = head;
		//delete the list
		while (head) {
			head = head->next;
			delete curr;
			curr = head;
		}
		Node* curr1 = freeNode;
		//delete the freeNode list
		while (freeNode) {
			freeNode = freeNode->next;
			delete curr1;
			curr1 = freeNode;
		}
	}

	//Copy constructor
	template <typename PS>
	PSLL <PS>::PSLL(const PSLL &obj) {
		type = (typeid(PS).name());
		//Start with blank
		head = nullptr;
		tail = nullptr;
		freeNode = nullptr;
		//Copy the list
		Node *n = obj.head;
		while (n) {
			push_back(n->data);
			n = n->next;
		}
	}
	//Copy assignment operator
	template <typename PS>
	PSLL<PS>& PSLL <PS>::operator= (const PSLL &obj) {
		//Check if two lists have the same address
		if (this != &obj) {
			//delete the original list
			Node* curr = head;
			while (head) {
				head = head->next;
				delete curr;
				curr = head;
			}
			//Copy the list
			head = nullptr;
			tail = nullptr;
			Node* temp_pool = freeNode;
			freeNode = nullptr;
			//Copy the list
			Node *n = obj.head;
			//head = n;
			while (n) {
				push_back(n->data);
				n = n->next;
			}
			freeNode = temp_pool;
			/*
			//Copy the pool
			Node* f = obj.freeNode;
			Node* curr1 = freeNode;
			while (f) {
				Node* newf = new Node(f->data);
				if (!freeNode) {
					freeNode = newf;
					curr = freeNode;
					newf->next = 0;
				}
				else {
					curr->next = newf;
					newf->next = 0;
					curr = curr->next;
				}
				f = f->next;
			}
			*/
		}
		return *this;
	}
	//Move constructor
	template <typename PS>
	PSLL<PS>::PSLL(PSLL &&obj) noexcept:
	head(nullptr), tail(nullptr), type("")
	{
		//Copy the values of data members from the source obejct
		head = obj.head;
		tail = obj.tail;
		type = obj.type;
		freeNode = nullptr;
		//leave obj in a destructible state
		obj.head = obj.tail =  obj.freeNode = nullptr;
		obj.type = "";
	}
	//Move assignment operator
	template <typename PS>
	PSLL<PS>& PSLL<PS>::operator=(PSLL &&obj) noexcept
	{
		//Check if there are two same lists
		if (this != &obj) {
			//delete the original list
			Node* curr = head;
			while (head) {
				head = head->next;
				delete curr;
				curr = head;
			}
			//Copy the values of data members from the source obejct
			head = obj.head;
			tail = obj.tail;
			type = obj.type;
			//leave obj in a destructible state
			obj.head = obj.tail = obj.freeNode = nullptr ;
			obj.type = "";
		}
		return *this;
	}

	//insert(element, position)
	template <typename PS>
	void PSLL<PS>::insert(PS element, int position) {
		Node* curr = head;
		int len = length();
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element into PSLL list.\n");
		//Insert a node in the middle of the list
		if (len > position && position > 0) {
			//Look for the node whose position is right in front of the position entered by the user
			for (int i = 1; i != position; i++) {
				curr = curr->next;
			}
			//If the pool is not empty
				if (freeNode) {
					//Node* prev = freeNode;
					//Node* current = prev->next;
					//There is only one free node in the free list
					/*
					if (prev->next == 0) {
						prev->next = curr->next;
						curr->next = prev;
						freeNode = 0;
					}
					//There is more than one node in the free list
					else {
						while (current->next) {
							prev = current;
							current = current->next;
						}
						current->next = curr->next;
						curr->next = current;
						prev->next = 0;
					}*/
					Node* current = freeNode;
					freeNode = freeNode->next;
					current->next = curr->next;
					curr->next = current;
					curr->next->data = element;
				}
				//If the pool is empty
				else {
					Node *newNode = new Node(element);
					newNode->next = curr->next;
					curr->next = newNode;
				}			
		}
			//Insert the node in front
			else if (position == 0) {
				push_front(element);
			}
			//Insert the node at the back
			else if (position == len) {
				push_back(element);
			}
			/******************************************/
			else {
				throw std::runtime_error("Invalid position!\n");
			}
			//saveMemory();
	}

		//push_back (element)
		template <typename PS>
		void PSLL<PS>::push_back(PS element) {
			//check if the type of the element is correct
			if (type.compare(typeid(element).name()))
				throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element into PSLL list.\n");
			//If the list is not empty
			if (length()) {
				//If there is at least one node in the pool
				if (freeNode) {
					Node* curr = freeNode;
					/*
					while (curr->next) {
						curr = curr->next;
					}*/
					freeNode = freeNode->next;
					tail->next = curr;
					curr->next = 0;
					tail = curr;
					curr->data = element;
					//checkFreePool();
				}
				//The pool is empty
				else {
					/*
					Node* temp = head;
					head= head->next;
					*/
					Node* newNode = new Node(element);
					newNode->next = 0;
					tail->next = newNode;
					tail = newNode;
				}
			}

			//The list is empty
			else {
				//Check if there is at least one node in the pool
				if (freeNode) {
					Node* curr = freeNode;
					freeNode = freeNode->next;
					/*
					while (curr->next) {
						curr = curr->next;
					}*/
					head = curr;
					tail = curr;
					tail->next = nullptr;
					tail->data = element;
					//checkFreePool();
				}
				//The pool is empty;
				else {
					Node* newNode = new Node(element);
					newNode->next = 0;
					head = newNode;
					tail = newNode;
				}
			}
			//saveMemory();
		}

		//push_front(element) 
		template <typename PS>
		void PSLL<PS>::push_front(PS element) {
			if (!is_empty()) {
				if ((typeid(tail->data).name()) != (typeid(element).name()))
					throw std::runtime_error("The type of the element entered does not match the type of other elements in this list.\n");
			}
			//If the list is not empty
			if (length()) {
				//If the pool is not empty
				if (freeNode) {
					Node* curr = freeNode;
					freeNode = freeNode->next;
					curr->next = head;
					head = curr;
					head->data = element;
					/*
					Node* prev = freeNode;
					if (prev->next == 0) {
						prev->next = head;
						head = prev;
						head->data = element;
						freeNode = 0;
					}
					else {
						Node* curr = prev->next;
						while (curr->next) {
							prev = curr;
							curr = curr->next;
						}

						curr->next = head;
						head = curr;
						head->data = element;
						prev->next = 0;
					}*/
				}
				//The pool is empty
				else {
					Node* newNode = new Node(element);
					newNode->next = head;
					head = newNode;
				}
			}
			//The list is empty
			else {
				//If the pool is not empty
				if (freeNode) {
					Node* curr = freeNode;
					freeNode = freeNode->next;
					/*
					while (curr->next) {
						curr = curr->next;
					}*/
					head = curr;
					tail = curr;
					head->next = 0;
					curr->data = element;
					//checkFreePool();
				}
				//The pool is empty
				else {
					Node* newNode = new Node(element);
					head = newNode;
					tail = newNode;
					head->next = 0;
				}
			}
			//saveMemory();
		}

		//replace( element, position )
		template <typename PS>
		PS PSLL<PS>::replace(PS element, int position) {
			if (!is_empty()) {
				if ((typeid(tail->data).name()) != (typeid(element).name()))
					throw std::runtime_error("The type of the element entered does not match the type of other elements in this list.\n");
			}
			PS originalElement;
			int len = length();
			//Replace the existing element when the position is valid
			if (len == 0) {
				throw std::runtime_error("The list is empty. No element can be replaced.\n");
			}
			else if (position >= 0 && position <= len-1) {
				Node* curr = head;
				//Look for the position
				for (int i = 0; i != position; i++) {
					curr = curr->next;
				}
				originalElement = curr->data;
				curr->data = element;
			}
			else {
				throw std::runtime_error("Invalid position!\n");
			}
			return originalElement;
		}

		//remove (position)
		template <typename PS>
		PS PSLL<PS>::remove(int position) {
			if (is_empty()) {
				throw std::runtime_error("The list is empty. No element can be removed.\n");
			}
			Node* curr = head;
			Node* toBeDeleted;
			int len = length();
			PS removedElement;
			//Remove a node when the position is less than the length of the list but greater than 1
			if (position > 0 && position < len-1) {
				for (int i = 0; i != (position - 1); i++) {
					curr = curr->next;
				}
				toBeDeleted = curr->next;
				removedElement = curr->next->data;
				curr->next = curr->next->next;
				//Check if the pool has 50 nodes alreday
				if (freeListLength() < POOL_SIZE)
					push_front_free(toBeDeleted);
				else
					delete (toBeDeleted);//Delete the node if the pool has 50 nodes
			}
			else if (position == 0) {
				removedElement = pop_front();
			}
			else if (position == len-1) {
				removedElement = pop_back();
			}
			else {
				throw std::runtime_error("Invalid position!\n");
			}
			//saveMemory();
			return removedElement;
		}

		//pop_back()
		template <typename PS>
		PS PSLL<PS>::pop_back(void) {
			if (is_empty()) {
				throw std::runtime_error("The list is empty. No element can be removed from the back.\n");
			}
			Node* curr = head;
			PS removedElement;
			//If there is only one node in the list, then set both head and tail to null pointers
			if (curr->next == 0) {
				head = 0;
				tail = 0;
				removedElement = curr->data;
				//Check if the pool has 50 nodes alreday
				if (freeListLength() < POOL_SIZE)
					push_front_free(curr);
				//Delete the node if there are 50 nodes in the pool
				else
					delete (curr);
				//saveMemory();
				return removedElement;
			}
			//If there is more than one node in the list, set tail to the second last node
			while (curr->next->next) {
				curr = curr->next;
			}
			tail = curr;
			removedElement = curr->next->data;
			//Check if the pool has 50 nodes alreday
			if (freeListLength() < POOL_SIZE)
				push_front_free(curr->next);
			//Delete the node if there are 50 nodes in the pool
			else
				delete (curr->next);
			curr->next = 0;
			//saveMemory();
			return removedElement;
		}

		//pop_front()
		template <typename PS>
		PS PSLL<PS>::pop_front(void) {
			if (is_empty()) {
				throw std::runtime_error("The pool list is empty. No element can be removed from the front.\n");
			}
			Node* curr = head;
			PS removedElement;
			//If there is only one node in the list, then set both head and tail to null pointers
			if (curr->next == 0) {
				head = 0;
				tail = 0;
				removedElement = curr->data;
				//Check if the pool has 50 nodes alreday
				if (freeListLength() < POOL_SIZE)
					push_front_free(curr);
				//Delete the node if there are 50 nodes in the pool
				else
					delete (curr);
				//saveMemory();
				return removedElement;
			}
			//If there is more than one node in the list, then set head to the second node in the list
			head = curr->next;
			removedElement = curr->data;
			//Check if the pool has 50 nodes alreday
			if (freeListLength() < POOL_SIZE)
				push_front_free(curr);
			//Delete the node if there are 50 nodes in the pool
			else
				delete (curr);
			//saveMemory();
			return removedElement;
		}

		//item_at(position)
		template <typename PS>
		PS& PSLL<PS>::item_at(int position) {
			int len = length();
			if (is_empty()) {
				throw std::runtime_error("The list is empty. Failed to return the element at the position you entered.\n");
			}
			if (position < 0 || position > len - 1) {
				throw std::runtime_error("The position you entered is invalid. Failed to return the element at the position you entered.\n");
			}
			Node* curr = head;
			for (int i = 0; i != position; i++) {
				curr = curr->next;
			}
			return curr->data;		
		}

		//peek_back()
		template <typename PS>
		PS& PSLL<PS>::peek_back(void) {
			if (is_empty()) {
				throw std::runtime_error("The list is empty, so no element front the back of the list can be returned.\n");
			}
			return tail->data;
		}

		//peek_front()
		template <typename PS>
		PS& PSLL<PS>::peek_front(void) {
			if (is_empty()) {
				throw std::runtime_error("The list is empty, so no element front the front of the list can be returned.\n");
			}
			return head->data;
		}

		//is_empty()
		template <typename PS>
		bool PSLL<PS>::is_empty(void) {
			return (head == 0 && tail == 0);
		}

		//is_full()
		template <typename PS>
		bool PSLL<PS>::is_full(void) {
			return false;
		}

		//clear()
		template <typename PS>
		void PSLL<PS>::clear(void) {
			/*
			//if there are no nodes in the free list
			if (freeNode == 0) {
				freeNode = head;
			}
			else {
				Node* curr = freeNode;
				while (curr->next) {
					curr = curr->next;
				}
				curr->next = head;
			}
			head = 0;
			tail = 0;*/
			//Check how many nodes can be added to the pool
			int availableSpace = POOL_SIZE - freeListLength();
			//Calculate how many nodes are going to be deleted
			int numNodesDelete = length() - availableSpace;
			//Delete the nodes
			for (int i = 0; i < numNodesDelete; i++) {
				Node* curr1 = head;
				head = head->next;
				delete curr1;
			}
			//Add the rest nodes (if any) to the pool
			//if there are no nodes in the free list
			if (freeNode == 0) {
				freeNode = head;
			}
			//Else, add the nodes to the end of the free list
			else {
				Node* curr = freeNode;
				while (curr->next) {
					curr = curr->next;
				}
				curr->next = head;
			}
			head = 0;
			tail = 0;
		}

		//length()
		template <typename PS>
		size_t PSLL<PS>::length(void) {
			size_t len = 0;
			//Set curr to head
			Node* curr = head;

			while (curr) {
				len++;
				curr = curr->next;
			}
			return len;
		}

		//contains(element, equals_function) 
		template <typename PS>
		bool PSLL<PS>::contains(const PS& element, bool equals_function(const PS& existingElement, const PS& element)) {
			Node* curr = head;
			
			while (curr) {
				const PS& curr_data = curr->data;
				if (equals_function(curr_data, element))
					return true;
				curr = curr->next;
			}
			return false;
		}

		//print(ostream)
		template <typename PS>
		void PSLL<PS>::print(std::ostream &ostream) {
			if (is_empty())
				ostream << "<empty list>";
			else {
				int len = length();
				PS* array = contents();
				ostream << "[";
				for (int i = 0; i < len; i++) {
					ostream << array[i];
					if (i != len - 1)
						ostream << ",";
				}
				ostream << "]";
			}

		}

		//contents()
		template <typename PS>
		PS* PSLL<PS>::contents() {
			int len = length();
			//int minIndex, minValue;
			int k = 0;
			PS *array = new PS[len];
			Node *curr = head;
			while (curr) {
				array[k] = curr->data;
				curr = curr->next;
				k++;
			}/*
			for (int i = 0; i < len - 1; i++) {
				minIndex = i;
				minValue = array[i];
				for (int j = i + 1; j < len; j++) {
					if (minValue > array[j]) {
						minIndex = j;
						minValue = array[j];
					}
				}
				array[minIndex] = array[i];
				array[i] = minValue;
			}*/
			//return the address of allocated array
			return array;
		}
		/*
		//equals_function()
		template <typename PS>
		bool PSLL<PS>::equals_function(PS element) {
			Node* curr = head;
			PS elementInList;
			bool value;
			if (is_empty())
				value = 0;
			while (curr) {
				elementInList = curr->data;
				value = (element == elementInList);
				if (value)
					return true;
				curr = curr->next;
			}
			return value;
		}*/
}
#endif