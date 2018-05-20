#ifndef _CDAL_H_
#define _CDAL_H_
#include "List.h"
#include <stdexcept>
#include <typeinfo>
#include <iostream>

namespace cop3530 {
	const size_t ARRAY_SIZE = 50;
	template <typename CD>
	class CDAL : public List <CD> {
	public:
		//constructors and destructor
		CDAL();
		~CDAL() override;
		//Copy constructor
		CDAL(const CDAL &obj);
		//Copy assignment operator
		CDAL& operator= (const CDAL &obj);
		//Move constructor
		CDAL(CDAL&&) noexcept;
		//Move assignment operator
		CDAL& operator=(CDAL&& obj) noexcept;
		//operations
		void insert(CD element, int position) override;
		void push_back(CD element) override;
		void push_front(CD element) override;
		CD replace(CD element, int position) override;
		CD remove(int position) override;
		CD pop_back(void) override;
		CD pop_front(void)override;
		CD& item_at(int position) override;
		CD& peek_back(void) override;
		CD& peek_front(void) override;
		bool is_empty(void) override;
		bool is_full(void) override;
		size_t length(void) override;
		void clear(void) override;
		bool contains(const CD& element, bool equals_function(const CD& existingElement, const CD& element)) override;
		void print(std::ostream &ostream) override;
		CD* contents(void) override;
		void newArray(void);
		void saveMemory(void);
	private:
		struct Node {
			CD* data_array;
			Node* next;
			Node() {
				data_array = new CD[ARRAY_SIZE];
			}
			~Node() {
				delete[] data_array;
			}
		};
		Node* data;
		int tail;
		std::string type; //type holds the type of the element
	public:
		template <typename CDI>
		class CDAL_Iter {
		public:
			// type aliases required for C++ iterator compatibility
			using value_type = CDI;
			using reference = CDI&;
			using pointer = CDI*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			// type aliases for prettier code
			using self_type = CDAL_Iter;
			using self_reference = CDAL_Iter&;

		private:
			int here;
			int Itail;
			Node* currNode;
			int const SIZE = 50;
		public:
			static self_type make_begin(int start, int tails, Node* first) {
				CDAL_Iter i(start, tails, first);
				return i;
			}
			static self_type make_end(int start, int tails, Node* end) {
				CDAL_Iter i(start, tails, end);
				return i;
			}
			//constructors
			explicit CDAL_Iter(int start = 0, int tails = 0, Node* first = 0) {
				here = start; Itail = tails; currNode = first;
			}
			CDAL_Iter(const CDAL_Iter& src) {
				here = src.here;
				Itail = src.Itail;
				currNode = src.currNode;
			}
			//output values
			reference operator*() const {
				if (here>=Itail) {
					throw new std::runtime_error("Iterator exhausted.");
				}
				if (Itail == 0) {
					throw new std::runtime_error("Iterator points to nothing");
				}
				return currNode->data_array[here%SIZE]; //return reference to the data_array
			}
			pointer operator->() const {
				 return &(operator*()); 
			}
			self_reference operator=(CDAL_Iter<CDI> const& src) {
				if (this == &src) {
					return(*this);
				}
				here = src.here;
				Itail = src.Itail;
				currNode = src.currNode;
				return *this;
			}
			// preincrement
			self_reference operator++() {
				if (here < Itail) {
					here++;
					//Move to the next node
					if ((here % (long long)SIZE) == 0 && here!=0) {
						currNode = currNode->next;
					}
				}
				return (*this);
			}
			//postincrement
			self_type operator++(int) {
				self_type tmp(*this);
				++(*this);
				return tmp;
			}

			bool operator==(CDAL_Iter<CDI> const& rhs) const {
				return (here == rhs.here && currNode == rhs.currNode);
			}
			bool operator!=(CDAL_Iter<CDI> const& rhs) const {
				return (here != rhs.here || currNode != rhs.currNode);
			}
		
		};//end of CDAL_Iter
		//using size_t = std::size_t;
		using value_type = CD;
		using iterator = CDAL_Iter<CD>;
		using const_iterator = CDAL_Iter<CD const>;
		//using const_iterator = CDAL_Iter<CD const>;
		// iterators over a non-const List
		iterator begin() { return iterator::make_begin(0,tail,data); }
		iterator end() {
			Node* tempNode = data;
			for (unsigned int i = 0; i < (tail-1)/ (long long)ARRAY_SIZE && tail!=0; i++) {
				tempNode = tempNode->next;
			}
			if (tail%(long long) ARRAY_SIZE != 0 || tail == 0)
			return iterator::make_end(tail, tail, tempNode); //Pass in the current node
			else
				return iterator::make_end(tail, tail, tempNode->next); //The node passed in is the next node
	    }
		// iterators over a const List
		const_iterator begin() const { return const_iterator::make_begin(0, tail, data); }
		const_iterator end() const { 
			Node* tempNode = data;
			for (unsigned int i = 0; i < (tail-1) / (long long)ARRAY_SIZE && tail != 0; i++) {
				tempNode = tempNode->next;
			}
			if (tail % (long long)ARRAY_SIZE != 0 || tail == 0)
				return const_iterator::make_end(tail, tail, tempNode); //Pass in the current node
			else
				return const_iterator::make_end(tail, tail, tempNode->next);//The node passed in is the next node
		}

	};
	//newArray
	template <typename CD>
	void CDAL<CD>::newArray() {
		//This if statement checks if tail is 0 (the list is empty)
		if ((tail % ARRAY_SIZE == 0) && ((tail-1) >= (long long)(ARRAY_SIZE - 1))) {
			Node* curr = data;
			//Find out the last array which has data
			for (unsigned int i = 0; i != ((tail-1) / ARRAY_SIZE); i++) {
				curr = curr->next;
			}
			//Check if this array is the last array
			if (!(curr->next)) {
				Node* newNode = new Node();
				//Node* temp = data;
				//while (data->next)
					//data = data->next;
				curr->next = newNode;
				newNode->next = 0;
				//data = temp;
			}
		}
	}
	//saveMemory
	template <typename CD>
	void CDAL<CD>::saveMemory() {
		Node* curr = data;
		Node* temp;
		Node* temp1;
		//Create a variable which stores the number of unused and used arrays
		int numUnUsed = 0;
		int numUsed = 0;
		//The numebr of used arrays
		if (tail != 0) {
			numUsed = (tail-1) / ARRAY_SIZE + 1;
		}
		//Find the last used array (curr) first
		if (tail != 0) {
			for (unsigned int i = 0; i < (tail-1) / ARRAY_SIZE; i++) {
				curr = curr->next;
			}
			//temp is the first unused array
			temp = curr->next;
		}
		else {
			//curr = data;
			temp = data; // temp is the first unused array
		}
		//tempCurr is used to connect tempCurr to the unused array after deletion
		//tempCurr is the last used array when there is at least one unused array
		Node* tempCurr = curr;
		//Find the number of unused arrays
		while (curr->next) {
			curr = curr->next;
			numUnUsed++;
		}
		if (tail == 0) {
			numUnUsed++;
		}
		//Check to see if over half of the arrays are unused
		if (numUnUsed > numUsed && tail != 0) {
			while (numUnUsed > numUsed) {
				for (int i = 0; i != numUnUsed / 2; i++) {
					temp1 = temp;
					temp = temp->next;
					delete temp1;
					tempCurr->next = temp;
				}
				//Update the numUnUsed
				numUnUsed = numUnUsed - numUnUsed / 2;
			}
		}
		//If no arrays are used
		else if (numUnUsed / 2 > 0 && tail == 0) {
			//Make tempCurr the second unused node
			tempCurr = tempCurr->next;
			while (numUnUsed > numUsed && numUnUsed>1) {
				//Delete nodes
				for (int i = 0; i != numUnUsed / 2; i++) {
					temp1 = tempCurr;
					tempCurr = tempCurr->next;
					delete temp1;
					data->next = tempCurr;
				}
				//Update the numUnUsed
				numUnUsed = numUnUsed - numUnUsed / 2;
			}
		}
	}
	//constructor
	template <typename CD>
	CDAL<CD>::CDAL() {
		//Get the type of the elements in the list
		type = (typeid(CD).name());
		data = new Node();
		data->next = 0;
		tail = 0;
	}

	//destructor
	template <typename CD>
	CDAL<CD>::~CDAL() {
		//while loop
		//delete curr
		Node* curr = data;
		while(data) {
			data = data->next;
			delete curr;
			curr = data;
		}
	}
	//Copy constructor
	template <typename CD>
	CDAL <CD>::CDAL(const CDAL &obj) {
		type = (typeid(CD).name());
		//Start with blank
		data = nullptr;
		tail = 0;
		//Copy the list
		Node* d = obj.data;
		Node* curr = data;
		//Check if there is a node in the obj list
		while (d) {
			//Create a new node
			Node* newf = new Node(d->data_array);
			//If curr is null
			if (!data) {
				data = newf;
				curr = data;
				newf->next = nullptr;
			}
			else {
				curr->next = newf;
				newf->next = nullptr;
				curr = curr->next;
			}
			d = d->next;
		}
		tail = obj.tail;
	}
	//Copy assignment operator
	template <typename CD>
	CDAL<CD>& CDAL <CD>::operator= (const CDAL &obj) {
		type = (typeid(CD).name());
		//Check if two lists have the same address
		if (this != &obj) {
			//delete the original list
			clear();
			tail = 0;
			//Delete the first node
			while (data) {
				Node* temp = data;
				delete temp;
				data = data->next;
			}
			//Copy the list
			Node* d = obj.data;
			Node* curr = data;
			//Check if there is a node in the obj list
			while (d) {
				//Create a new node
				Node* newf = new Node(d->data_array);
				//If curr is null
				if (!data) {
					data = newf;
					curr = data;
					newf->next = nullptr;
				}
				else {
					curr->next = newf;
					newf->next = nullptr;
					curr = curr->next;
				}
				d = d->next;
			}
			tail = obj.tail;
		}
		return *this;
	}
	//Move constructor
	template <typename CD>
	CDAL<CD>::CDAL(CDAL &&obj) noexcept:
	tail(0), type(""), data(nullptr)
	{
		//Move the values of data members from the source obejct
		data = obj.data;
		tail = obj.tail;
		type = obj.type;
		//leave obj in a destructible state
		obj.tail = 0;
		obj.type = "";
		obj.data = nullptr;
	}
	//Move assignment operator
	template <typename CD>
	CDAL<CD>& CDAL<CD>::operator=(CDAL &&obj) noexcept
	{
		//Check if there are two same lists
		if (this != &obj) {
			//Free existing elements
			tail = 0;
			clear();
			//Delete the first node
			while (data) {
				Node* temp = data;
				delete temp;
				data = data->next;
			}
			//Move the values of data members from the source obejct
			data = obj.data;
			tail = obj.tail;
			type = obj.type;
			//leave obj in a destructible state
			obj.tail = 0;
			obj.type = "";
			obj.data = nullptr;
		}
		return *this;
	}


	//insert(element, position)
	template <typename CD>
	void CDAL<CD>::insert(CD element, int position) {
		int len = length();
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element into CDAL list.\n");
		//Check if the position is valid
		if (position < 0 || position > len) {
			throw std::runtime_error("Invalid position.\n");
		}
		//Check if a new array is needed
		newArray();
		Node* curr = data;
		//Find the node where there is the element with the corresponding position
		for (unsigned int i = 0; i < position / ARRAY_SIZE; i++) {
			curr = curr->next;
		}
		CD temp1 = curr->data_array[position%ARRAY_SIZE];
		CD temp2 = 0;
		bool full = 0;
		bool pushBack = 0;
		//add an element at front when the list is empty
		if (tail == 0) {
			data->data_array[0] = element;
		}
		//Add an element at the back of the list
		else if (position == len) {
			push_back(element);
			pushBack = 1;
		}
		else {
			//Remove all the elements at or after the original position one index down
			for (unsigned int j = position / ARRAY_SIZE; j <= (tail-1) / ARRAY_SIZE; j++) {
				//This array is already full before the new element is added and the position is in this array
				if ((tail % ARRAY_SIZE == 0 || j < (tail-1) / ARRAY_SIZE) && j == position / ARRAY_SIZE) {
					//The last array is full
					if (j == (tail-1) / ARRAY_SIZE)
						full = 1;
					//Shift elements one index down
					for (unsigned int i = position % ARRAY_SIZE; i < ARRAY_SIZE; i++) {
						if (i % 2 == 0) {
							temp2 = curr->data_array[i];
							curr->data_array[i] = temp1;
						}
						else {
							temp1 = curr->data_array[i];
							curr->data_array[i] = temp2;
						}
					}
					//Store the element into the corresponding position
					curr->data_array[position%ARRAY_SIZE] = element;
					//Move to another node
					curr = curr->next;
				}
				//If the array is not full before the any element is added and the position is in the current node
				else if (j == (tail-1) / ARRAY_SIZE && tail % ARRAY_SIZE != 0 && j == position / ARRAY_SIZE) {
					for (unsigned int i = position % ARRAY_SIZE; i <= tail % ARRAY_SIZE; i++) {
						if (i % 2 == 0) {
							//Shift elements
							temp2 = curr->data_array[i];
							curr->data_array[i] = temp1;
						}
						else {
							temp1 = curr->data_array[i];
							curr->data_array[i] = temp2;
						}
					}
					//Store the element into the corresponding position
					curr->data_array[position%ARRAY_SIZE] = element;
				}
				//If position is not in the array and the array is full
				else if ((tail % ARRAY_SIZE == 0 || j < (tail-1) / ARRAY_SIZE) && j != position / ARRAY_SIZE) {
					//The last array is full
					if (j == (tail-1) / ARRAY_SIZE)
						full = 1;
					for (unsigned int i = 0; i <ARRAY_SIZE; i++) {
						//Shift elements
						if (i % 2 == 0) {
							temp2 = curr->data_array[i];
							curr->data_array[i] = temp1;
						}
						else {
							temp1 = curr->data_array[i];
							curr->data_array[i] = temp2;
						}
					}
					//Move to another node
					curr = curr->next;
				}
				//If position is not in the array and the array is not full
				else if ( j == (tail-1) / ARRAY_SIZE &&  tail % ARRAY_SIZE != 0 && j != position / ARRAY_SIZE) {
					for (unsigned int i = 0; i <= tail % ARRAY_SIZE; i++) {
						//Shift elements 
						if (i % 2 == 0) {
							temp2 = curr->data_array[i];
							curr->data_array[i] = temp1;
						}
						else {
							temp1 = curr->data_array[i];
							curr->data_array[i] = temp2;
						}
					}
				}

			}
		}
		//Copy values to the first slot of the node
		if (full)
			curr->data_array[0] = temp1;
		//Update the tail
		if (!pushBack) {
			tail++;
		}
	}

	//push_back(element)
	template <typename CD>
	void CDAL<CD>::push_back(CD element) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element at the back of CDAL list.\n");
		//Check if a new array is needed
		newArray();
		Node* curr = data;
		if (tail == 0) {
			curr->data_array[0] = element;
		}
		else {
			//Find add the element to which array
			for (unsigned int i = 0; i < (tail-1) / ARRAY_SIZE; i++) {
				curr = curr->next;
			}
			//If the current array is not full
			if ((tail % ARRAY_SIZE) != 0) {
				curr->data_array[tail % ARRAY_SIZE] = element;
			}
			//If the current array is full
			else {
				curr = curr->next;
				curr->data_array[0] = element;
			}

		}
		tail++;
	}

	//push_front(element)
	template <typename CD>
	void CDAL<CD>::push_front(CD element) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element at the front of CDAL list.\n");
		//Check if a new array is needed
		newArray();
		Node* curr = data;
		CD temp1 = curr->data_array[0];
		CD temp2;
		bool full = 0;
		//add an element at front when the list is empty
		if (tail == 0) {
			curr->data_array[0] = element;
		}
		else {
			//Remove all the elements one index down
			for (unsigned int j = 0; j <= (tail-1) / ARRAY_SIZE; j++) {
				//This array is already full.
				if (tail % ARRAY_SIZE == 0 || j < (tail-1) / ARRAY_SIZE) {
					//The last array is full
					if (j == (tail-1) / ARRAY_SIZE)
						full = 1;
					//Shift elements
					for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
						if (i % 2 == 0) {
							temp2 = curr->data_array[i];
							curr->data_array[i] = temp1;
						}
						else {
							temp1 = curr->data_array[i];
							curr->data_array[i] = temp2;
						}
					}
					//Move to another node
					curr = curr->next;
				}
				//This is the last array but it is not full
				else if (j == (tail-1) / ARRAY_SIZE && (tail % ARRAY_SIZE != 0)) {
					//Shift elements
					for (unsigned int i = 0; i <= tail % ARRAY_SIZE; i++) {
						if (i % 2 == 0) {
							temp2 = curr->data_array[i];
							curr->data_array[i] = temp1;
						}
						else {
							temp1 = curr->data_array[i];
							curr->data_array[i] = temp2;
						}
					}
				}

			}
			//Save the element as the first element in the list
			data->data_array[0] = element;
		}
		if (full)
			curr->data_array[0] = temp1;
		tail++;
	}
	//replace (element, position)
	template<typename CD>
	CD CDAL<CD>::replace(CD element, int position) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to replace an element in the CDAL list.\n");
		if (is_empty()) {
			throw std::runtime_error("The CDAL list is empty. No elements can be replaced.\n");
		}
		if (position<0 || position >(tail - 1)) {
			throw std::runtime_error("Invalid position.\n");
		}
		//Find the node where the position can be found
		Node* curr = data;
		for (unsigned int i = 0; i < position / ARRAY_SIZE; i++) {
			curr = curr->next;
		}
		//Get the original element
		CD temp = curr->data_array[position%ARRAY_SIZE];
		//Replace the original element with the element entered by the user
		curr->data_array[position%ARRAY_SIZE] = element;
		return temp;
	}

	//remove(position)
	template <typename CD>
	CD CDAL<CD>::remove(int position) {
		int len = length();
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CDAL list is empty. No elements can be removed.\n");
		}
		//Check if the position is valid
		if (position < 0 || position >= len) {
			throw std::runtime_error("Invalid position.\n");
		}
		Node* curr = data;
		//Find the node where there is the element with the corresponding position
		for (unsigned int i = 0; i < position / ARRAY_SIZE; i++) {
			curr = curr->next;
		}
		//Move all the elements at or after the original position one index up
		CD temp = curr->data_array[position%ARRAY_SIZE];
		for (unsigned int j = position / ARRAY_SIZE; j <= (tail-1) / ARRAY_SIZE; j++) {
			//If the position is in this array, and this array is full before an element is removed
			if ((tail % ARRAY_SIZE == 0 || j < (tail-1) / ARRAY_SIZE) && j == position / ARRAY_SIZE) {
				//Move elements one up
				for (unsigned int i = position%ARRAY_SIZE; i < ARRAY_SIZE - 1; i++) {
					curr->data_array[i] = curr->data_array[i + 1];
				}
				//check if there is an array which contains values after this array
				if (j != (tail-1) / ARRAY_SIZE) {
					//The first value of the next array will be the last value of the current array
					curr->data_array[ARRAY_SIZE - 1] = curr->next->data_array[0];
				}
				//Move to another node
				curr = curr->next;
			}
			//If the position is in this array, and this array is not full (which indicates that this array is the last array)
			else if (j == position / ARRAY_SIZE && j ==( tail-1) / ARRAY_SIZE && tail % ARRAY_SIZE != 0) {
				//Move elements one up
				for (unsigned int i = position%ARRAY_SIZE; i < (tail-1)%ARRAY_SIZE; i++) {
					curr->data_array[i] = curr->data_array[i + 1];
				}
			}
			//If the position is not in this array, and this array is full before the element is removed
			else if (j != position / ARRAY_SIZE && (tail % ARRAY_SIZE == 0 || j < (tail-1) / ARRAY_SIZE)) {
				//Move elements one up
				for (unsigned int i = 0; i < ARRAY_SIZE - 1; i++) {
					curr->data_array[i] = curr->data_array[i + 1];
				}
				//check if there is an array which contains values after this array
				if (j != (tail-1) / ARRAY_SIZE) {
					//The first value of the next array will be the last value of the current array
					curr->data_array[ARRAY_SIZE - 1] = curr->next->data_array[0];
				}
				//Move to another node
				curr = curr->next;
			}
			//If the position is not in this array, and this array is not full (which indicates that this array is the last one)
			else if (j != position / ARRAY_SIZE && (j == (tail-1) / ARRAY_SIZE) && tail% ARRAY_SIZE != 0) {
				//Move elements one up
				for (unsigned int i = 0; i < (tail-1)%ARRAY_SIZE; i++) {
					curr->data_array[i] = curr->data_array[i + 1];
				}
			}
		}

		tail--;
		//Check if too much memory is wasted
		saveMemory();
		return temp;
	}
	//pop_back()
	template <typename CD>
	CD CDAL<CD>::pop_back() {
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CDAL list is empty. No elements can be removed from the back.\n");
		}
		Node* curr = data;
		for (unsigned int i = 0; i < (tail-1) / ARRAY_SIZE; i++) {
			curr = curr->next;
		}
		//Get the original element
		CD temp = curr->data_array[(tail-1)%ARRAY_SIZE];
		tail--;
		//Check if a lot of arrays are unused
		saveMemory();
		return temp;

	}

	//pop_front()
	template <typename CD>
	CD CDAL<CD>::pop_front() {
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CDAL list is empty. No elements can be removed from the front.\n");
		}
		Node* curr = data;
		CD temp = curr->data_array[0];
		//Count how many nodes I need
		for (unsigned int i = 0; i <= (tail-1) / ARRAY_SIZE; i++) {
			//Check if the array is full
			if (tail % ARRAY_SIZE == 0 || i < (tail-1) / ARRAY_SIZE) {
				//Move elements one up
				for (unsigned int j = 0; j < ARRAY_SIZE - 1; j++) {
					curr->data_array[j] = curr->data_array[j + 1];
				}
				//check if there is an array after this array
				if (i != (tail-1) / ARRAY_SIZE) {
					//The first value of the next array will be the last value of the current array
					curr->data_array[ARRAY_SIZE - 1] = curr->next->data_array[0];
				}
				//move to the next node
				curr = curr->next;
			}

			//Check if the array is not full (which means this is the last array)
			else if (i == (tail-1) / ARRAY_SIZE && tail % ARRAY_SIZE != 0) {
				//Move all the elements one up
				for (unsigned int j = 0; j < (tail-1)%ARRAY_SIZE; j++) {
					curr->data_array[j] = curr->data_array[j + 1];
				}
			}
		}
		tail--;
		//Check if too much memory is wasted
		saveMemory();
		return temp;
	}
	//item_at(position)
	template <typename CD>
	CD& CDAL<CD>::item_at(int position) {
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CDAL list is empty. No elements can be returned.\n");
		}
		if (position< 0 || position > (tail-1)) {
			throw std::runtime_error("Invalid position.\n");
		}
		Node* curr = data;
		//Find the array where the item is
		for (unsigned int i = 0; i < position / ARRAY_SIZE; i++) {
			curr = curr->next;
		}
		//Return the item at the position entered by the user
		return curr->data_array[position%ARRAY_SIZE];

	}
	//peek_back()
	template <typename CD>
	CD& CDAL<CD>::peek_back() {
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CDAL list is empty. No elements can be returned from the back.\n");
		}
		Node* curr = data;
		//Find the array where the last item is
		for (unsigned int i = 0; i < (tail-1) / ARRAY_SIZE; i++) {
			curr = curr->next;
		}
		//Return the tail-1 
		return curr->data_array[(tail-1)%ARRAY_SIZE];
	}

	//peek_front()
	template <typename CD>
	CD& CDAL<CD>::peek_front() {
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CDAL list is empty. No elements can be returned from the head.\n");
		}
		return data->data_array[0];
	}

	//is_empty()
	template <typename CD>
	bool CDAL <CD>::is_empty() {
		return (tail == 0);
	}

	//is_full()
	template <typename CD>
	bool CDAL <CD>::is_full() {
		return false;
	}

	//length()
	template <typename CD>
	size_t CDAL<CD>::length() {
		return tail;
	}

	//clear()
	template <typename CD>
	void CDAL<CD>::clear() {
		Node* temp = data;
		//Check if there is more than one array
		if (data->next) {
			data = data->next;
			Node* curr = data;
			//Delete all the nodes but the first node until null is hit
			while(data) {
				data = data->next;
				delete curr;
				curr = data;
			}
		}
		//Make data the first node
		data = temp;
		data->next = 0;
		tail = 0;
	}

	//contains(element, equals_function)
	template <typename CD>
	bool CDAL<CD>::contains(const CD& element, bool equals_function(const CD& existingElement, const CD& element)) {
		if (tail == 0) {
			return false;
		}
		
		for (unsigned int i = 0; i <= (tail-1) / ARRAY_SIZE; i++) {
			Node* curr = data;
			
			//Check if this array is full
			if (tail % ARRAY_SIZE == 0 || i < (tail-1) / ARRAY_SIZE) {
				for (unsigned int j = 0; j < ARRAY_SIZE; j++) {
					const CD& curr_data = curr->data_array[j];
					if (equals_function(curr_data, element)) {
						return true;
					}
				}
			}
			//Check if ths array is not full		
			else if (i == (tail-1) / ARRAY_SIZE && tail % ARRAY_SIZE != 0) {
				for (unsigned int j = 0; j <= (tail-1)%ARRAY_SIZE; j++) {
					const CD& curr_data = curr->data_array[j];
					if (equals_function(curr_data, element)) {
						return true;
					}
				}
			}
			curr = curr->next;
		}
		return false;
	}

	//print(ostream)
	template <typename CD>
	void CDAL<CD>::print(std::ostream &ostream) {
		if (is_empty())
			ostream << "<empty list>";
		else {
			Node* curr = data;
			ostream << "[";
			for (unsigned int i = 0; i <= (tail-1) / ARRAY_SIZE; i++) {
				//Check if this array is full
				if (tail % ARRAY_SIZE == 0 || i < (tail-1) / ARRAY_SIZE) {
					for (unsigned int j = 0; j < ARRAY_SIZE; j++) {
						ostream << curr->data_array[j];
						//Print out a comma unless the last element is printed out
						if (i != (tail-1) / ARRAY_SIZE || j != ARRAY_SIZE - 1)
							ostream << ",";
					}
				}
				//Check if this array is not full
				else if (i == (tail-1) / ARRAY_SIZE && tail % ARRAY_SIZE != 0) {
					for (unsigned int j = 0; j <= (tail-1)%ARRAY_SIZE; j++) {
						ostream << curr->data_array[j];
						//Print out a comma unless the last element is printed out
						if (j != (tail-1)%ARRAY_SIZE)
							ostream << ",";
					}
				}
				//Move to the next node
				curr = curr->next;
			}
			ostream << "]";
		}
	}
	//contents()
	template <typename CD>
	CD* CDAL<CD>::contents() {
		CD* new_array = new CD[tail];
		if (tail == 0) 
			return new_array;
		int k = 0;
		Node* curr = data;
		for (unsigned int i = 0; i <= (tail-1) / ARRAY_SIZE; i++) {
			//Check if this array is full
			if (tail % ARRAY_SIZE == 0 || i < (tail-1) / ARRAY_SIZE) {
				for (unsigned int j = 0; j < ARRAY_SIZE; j++) {
					new_array[k] = curr->data_array[j];
					k++;
				}
			}
			//Check if this array is not full
			else if (i == (tail-1) / ARRAY_SIZE && tail % ARRAY_SIZE != 0) {
				for (unsigned int j = 0; j <= (tail-1)%ARRAY_SIZE; j++) {
					new_array[k] = curr->data_array[j];
					k++;
				}
			}
			//Move to the next node
			curr = curr->next;
		}
		//return the address of allocated array
		return new_array;
	}
}
#endif

