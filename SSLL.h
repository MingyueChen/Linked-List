#ifndef _SSLL_H_
#define _SSLL_H_
#include <stdexcept>
#include<typeinfo>
#include "List.h"
#include<iostream>
#include<string>

namespace cop3530 {
	// Used template to create a classed named SSLL which is a child class of SSLL_Base
	template <typename SS>
	class SSLL : public List <SS> {
	public:
		//constructors 
		SSLL();
		//Destructor
		~SSLL() override;
		//Copy constructor
		SSLL(const SSLL &obj);
		//Copy assignment operator
		SSLL& operator= (const SSLL &obj);
		//Move constructor
		SSLL(SSLL&&) noexcept;
		//Move assignment operator
		SSLL& operator=(SSLL&& obj) noexcept;
		//operations for the SSLL
		void insert(SS element, int position) override;
		void push_back(SS element) override;
		void push_front(SS element) override;
		SS replace(SS element, int position) override;
		SS remove(int position) override;
		SS pop_back(void) override;
		SS pop_front(void)override;
		SS& item_at(int position) override;
		SS& peek_back(void) override;
		SS& peek_front(void) override;
		bool is_empty(void) override;
		bool is_full(void) override;
		size_t length(void) override;
		void clear(void) override;
		//bool equals_function(SS element) override;
		bool contains(const SS& element, bool equals_function(const SS& existingElement, const SS& element)) override;
		void print(std::ostream &ostream) override;
		SS* contents(void) override;
		
	private:
		struct Node {
			SS data;
			Node* next;

			Node(SS element) {
				data = element;
			}
			Node() {
			}
		};
		Node* head;
		Node* tail;
		std::string type;
	public:
		template <typename SSI>
		class SSLL_Iter {
		public:
			// type aliases required for C++ iterator compatibility
			using value_type = SSI;
			using reference = SSI&;
			using pointer = SSI*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			// type aliases for prettier code
			using self_type = SSLL_Iter;
			using self_reference = SSLL_Iter&;

		private:
			Node* here;
		   
		public:
			// factories called by class rectangle
			//static because I will call these functions without calling on objects. I call functions on the class (iter)
			static self_type make_begin(Node* here) {
				SSLL_Iter i(here);
				return i;
			}
			 static self_type make_end(Node* here) {
				SSLL_Iter i(here);
				return i;
			}
			explicit SSLL_Iter(Node* start = nullptr) : here(start) {} //if nothing is passed, it will start at the nullptr
			//else, it will start at the node I passed in.
			SSLL_Iter(const SSLL_Iter& src) : here(src.here) {} //copy constructor

			//return the value in the current node pointed by the iterator (which is here)
			reference operator*() const {
				if (!here) {
					throw std::runtime_error("here is a null pointer.");
				}
				return here->data; //return reference to the data
			}
			pointer operator->() const { return &(operator*()); } //return a pointer to the address of here->data

			self_reference operator=(SSLL_Iter<SSI> const& src) {
				if (this == &src) {
					return(*this);
				}
				here = src.here; //the pointer on the left side points to whatever the pointer on the right side points to
				return *this;
			}
			// preincrement
			self_reference operator++() {
				if (here)
					here=here->next;
				return *this;
			} 
			// postincrement
			self_type operator++(int) {
				self_type tmp(*this);
				++(*this);
				return tmp;
			} 

			bool operator==(SSLL_Iter<SSI> const& rhs) const {
				return (here == rhs.here);
			}
			bool operator!=(SSLL_Iter<SSI> const& rhs) const {
				return (here != rhs.here);
			}
			
		};//end SSLL_Iter
		//using size_t = std::size_t;
		using value_type = SS;
		using iterator = SSLL_Iter<SS>;
		using const_iterator = SSLL_Iter<SS const>;
		  // iterators over a non-const List
		iterator begin() { return iterator::make_begin(head); }
		iterator end() { return iterator::make_end(nullptr); }

		// iterators over a const List
		const_iterator begin() const { return const_iterator::make_begin(head);}
		const_iterator end() const { return const_iterator::make_end(nullptr); }
	};

	//Define constructor and destructor
	template <typename SS>
	SSLL <SS>::SSLL()
	{
    	type = (typeid(SS).name());
		head = 0;
		tail = 0;
	}

	//Destructor
	template <typename SS>
	SSLL <SS>::~SSLL() {
		Node* curr = head;
		while (head) {
			head = head->next;
			delete curr;
			curr = head;
		}
	}

	//Copy constructor
	template <typename SS>
	SSLL <SS>::SSLL(const SSLL &obj) {
		type = (typeid(SS).name());
		//Start with blank
		head = nullptr;
		tail = nullptr;
		//Copy the list
		Node *n = obj.head;
		while (n) {
			//SS data (n->data);
			//push_back(data);
			push_back(n->data);
			n = n->next;
		}
	}
	//Copy assignment operator
	template <typename SS>
	SSLL<SS>& SSLL <SS>::operator= (const SSLL &obj) {
		//Check if two lists have the same address
		if (this != &obj) {
			//delete the original list
			clear();
			//Copy the list
			Node *n = obj.head;
			while (n) {
				//SS data (n->data);
				//push_back(data);
				push_back(n->data);
				n = n->next;
			}
		}
		return *this;
	}
	//Move constructor
	template <typename SS>
	SSLL<SS>::SSLL(SSLL &&obj) noexcept:
	head(nullptr), tail(nullptr), type("")
	{
		//Copy the values of data members from the source obejct
		head = obj.head;
		tail = obj.tail;
		type = obj.type;
		//leave obj in a destructible state
		obj.head = obj.tail = nullptr;
		obj.type = "";
	}
	//Move assignment operator
	template <typename SS>
	SSLL<SS>& SSLL<SS>::operator=(SSLL &&obj) noexcept
	{
		//Check if there are two same lists
		if (this != &obj) {
			//Free existing elements
			clear();
			//Copy the values of data members from the source obejct
			head = obj.head;
			tail = obj.tail;
			type = obj.type;
			//leave obj in a destructible state
			obj.head = obj.tail = nullptr;
			obj.type = "";
		}
		return *this;
	}

	//insert
	template <typename SS>
	void SSLL<SS>::insert(SS element, int position) {
		//check if the type of the element is correct
			if (type.compare(typeid(element).name()))
				throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element into SSLL list.\n");
		int len = length();
		Node* curr = head;
		if (len > position && position > 0) {

			for (int i = 1; i != position; i++) {
				curr = curr->next;
			}
			Node *newNode = new Node(element);
			newNode->next = curr->next;
			curr->next = newNode;
		}
		else if (position == 0) {
			push_front(element);
		}
		else if (position == len) {
			push_back(element);
		}
		else {
			throw std::runtime_error("Invalid position. Failed to insert an element into SSLL list.\n");
		}
	}

	//push_back(element)
	template <typename SS>
	void SSLL<SS>::push_back(SS element) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to add an element at the back of SSLL list.\n");
		Node* newNode = new Node(element);
		newNode->next = NULL;
		//The way to add the node to the end of the list if the list is not empty
		if (length()) {
			tail->next = newNode;
			tail = newNode;
		}
		else {
			head = newNode;
			tail = newNode;
		}
	}

	//push_front(element)
	template <typename SS>
	void SSLL<SS>::push_front(SS element) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to add an element at the beginning of the SSLL list.\n");
		Node* newNode = new Node(element);
		//The way to add a new node when the list is not empty
		if (length()) {
			newNode->next = head;
			head = newNode;
		}
		//The way to add a new node when the list is empty
		else {
			head = newNode;
			newNode->next = 0;
			tail = newNode;
		}
	}

	//replace( element, position )
	template <typename SS>
	SS SSLL<SS>::replace(SS element, int position) {
		SS originalElement;
		int len = length();
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to replace an element in the SSLL list.\n");
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
			throw std::runtime_error("Invalid position. Failed to replace an element in the SSLL list.\n");
		}
		return originalElement;
	}

	//remove(position)
	template <typename SS>
	SS SSLL<SS>::remove(int position) {
		if (is_empty()) {
			throw std::runtime_error("The list is empty. No element can be removed from the position you entered.\n");
		}
		Node* curr = head;
		Node* toBeDeleted;
		int len = length();
		SS removedElement;
		//Remove a node when the position is less then the length of the list but greater than 1
		if (position > 0 && position < len-1) {
			for (int i = 0; i != (position - 1); i++) {
				curr = curr->next;
			}
			toBeDeleted = curr->next;
			removedElement = curr->next->data;
			curr->next = curr->next->next;
			delete (toBeDeleted);
		}
		else if (position == 0) {
			removedElement = pop_front();
		}
		else if (position == len-1) {
			removedElement = pop_back();
		}
		else {
			throw std::runtime_error("Invalid position! Failed to remove an element from SSLL list.\n");
		}
		return removedElement;
	}

	//pop_back()
	template <typename SS>
	SS SSLL<SS>::pop_back() {
		if (is_empty()) {
			throw std::runtime_error("The list is empty. No element can be removed from the back.\n");
		}
		Node* curr = head;
		SS removedElement;
		if (curr->next == 0) {
			head = 0;
			tail = 0;
			removedElement = curr->data;
			delete curr;
			return removedElement;
		}
		while (curr->next->next) {
			curr = curr->next;
		}
		tail = curr;
		removedElement = curr->next->data;
		delete (curr->next);
		curr->next = 0;
		return removedElement;
	}

	//pop_front()
	template <typename SS>
	SS SSLL<SS>::pop_front() {
		if (is_empty()) {
			throw std::runtime_error("The list is empty. No element can be removed from the front.\n");
		}
		Node* curr = head;
		SS removedElement;
		if (curr->next == 0) {
			head = 0;
			tail = 0;
			removedElement = curr->data;
			delete curr;
			return removedElement;
		}
		head = curr->next;
		removedElement = curr->data;
		delete curr;
		return removedElement;
	}

	//item_at(position)
	template <typename SS>
	SS& SSLL<SS>::item_at(int position) {
		int len = length();
		if (is_empty()) {
			throw std::runtime_error("The list is empty. Failed to return the element at the position you entered.\n");
		}
		if (position < 0 || position > len-1) {
			throw std::runtime_error("The position you entered is invalid. Failed to return the element at the position you entered.\n");
		}
		Node* curr = head;
		for (int i = 0; i != position; i++) {
			curr = curr->next;
		}
		return curr->data;
	}

	//peek_back()
	template <typename SS>
	SS& SSLL<SS>::peek_back(void) {
		if (is_empty()) {
			throw std::runtime_error("The list is empty, so no element from the back of the list can be returned.\n");
		}
		return tail->data;
	}

	//peek_front()
	template <typename SS>
	SS& SSLL<SS>::peek_front(void) {
		if (is_empty()) {
			throw std::runtime_error("The list is empty, so no element from the beginning of the list can be returned.\n");
		}
		return head->data;
	}

	//is_empty()
	template <typename SS>
	bool SSLL<SS>::is_empty(void) {
		return (!head && !tail);
	}

	//is_full()
	template <typename SS>
	bool SSLL<SS>::is_full(void) {
		return false;
	}

	//length()
	template <typename SS>
	size_t SSLL<SS>::length(void) {
		size_t len = 0;
		//Set curr to head
		Node* curr = head;
		while (curr) {
			len++;
			curr = curr->next;
		}

		return len;
	}

	//clear()
	template <typename SS>
	void SSLL<SS>::clear(void) {
		Node* curr = head;
		while (head) {
			head = head->next;
			delete curr;
			curr = head;
		}
		head = 0;
		tail = 0;
	}

	//contains(element, equals_function) 
	template <typename SS>
	bool SSLL<SS>::contains(const SS& element, bool equals_function(const SS& existingElement, const SS& element)) {
		Node* curr = head;
		
		while (curr) {
			const SS& curr_data = curr->data;
			if (equals_function(curr_data, element))
				return true;
			curr = curr->next;
		}
		return false;
	}

	//print(ostream)
	template <typename SS>
	void SSLL<SS>::print(std::ostream &ostream) {
		if (is_empty())
			ostream << "<empty list>";
		else {
			int len = length();
			SS* array = contents();
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
	template <typename SS>
	SS* SSLL<SS>::contents() {
		int len = length();
		//int minIndex, minValue;
		int k = 0;
		SS *array = new SS[len];
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
	template <typename SS>
	bool SSLL<SS>::equals_function(SS element) {
		Node* curr = head;
		SS elementInList;
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