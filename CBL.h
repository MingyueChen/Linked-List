
#ifndef _CBL_H_
#define _CBL_H_
#include "List.h"
#include <ostream>
#include <stdexcept>
#include <typeinfo>
#include <string>
namespace cop3530 {
	template <typename SS>
	class CBL : public List <SS> {
	public:
		//constructors and destructor
		CBL(size_t);
		CBL();
		~CBL() override;
		//Copy constructor
		CBL(const CBL &obj);
		//Copy assignment operator
		CBL& operator= (const CBL &obj);
		//Move constructor
		CBL(CBL&&) noexcept;
		//Move assignment operator
		CBL& operator=(CBL&& obj) noexcept;
		//operations
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
		bool contains(const SS& element, bool equals_function(const SS& existingElement, const SS& element)) override;
		void print(std::ostream &ostream) override;
		SS* contents(void) override;
		
	private:
		std::string type; //Check the type of the element
		SS* data;//head which points to the array
		size_t head;
		size_t tail;
		size_t arraySize = 51;
		size_t originalSize = 51;
		void expandSize(void);
		void saveMemory(void);
		void goBackSize(void);
		size_t next_index(size_t i);
		size_t prev_index(size_t i);
		//Create a CBL_Iter class
		template <typename SSI>
		class CBL_Iter {
		public:
			// type aliases required for C++ iterator compatibility
			using value_type = SSI;
			using reference = SSI&;
			using pointer = SSI*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			// type aliases for prettier code
			using self_type = CBL_Iter;
			using self_reference = CBL_Iter&;

		private:
			size_t here; //here refers to the index of the array
			size_t Itail;
			size_t array_size;
			size_t first;
			pointer Idata;

		public:
			// factories called by class rectangle
			//static because I will call these functions without calling on objects. I call functions on the class (iter)
			static self_type make_begin(size_t start, size_t heads, size_t tails, pointer datas, size_t size ) {
				CBL_Iter i(start, heads, tails, datas,size);
				return i;
			}
			static self_type make_end(size_t start, size_t heads, size_t tails, pointer datas, size_t size) {
				CBL_Iter i(start, heads, tails, datas, size);
				return i;
			}
			//Check if here is still pointing to the element of the list
			//Return true if here does not point to the element of the list
			bool check() {
				if (first > Itail) {
					if (here < first && here >= Itail)
						return true;
					else
						return false;
				}
				else {
					if (here < first || here >= Itail)
						return true;
					else
						return false;
				}
			}
			size_t next(size_t i) {
				//Set i to zero if i holds the last index previously
				if (++i == array_size) {
					i = 0;
				}
				return i;
			}
			size_t prev(size_t i) {
				//Set i to array_size-1 if i holds the zero index previously
				if (i == 0) {
					i = array_size - 1;
				}
				else {
					--i;
				}
				return i;
			}
			//if nothing is passed, it will start at 0
			//else, it will start at the number I passed in.
			explicit CBL_Iter(size_t start = 0, size_t heads = 0, size_t tails = 0, pointer datas = nullptr, size_t size = 0) : here(start), first(heads), Itail(tails), Idata(datas), array_size(size) {}
			//copy constructor
			//return the reference of the value pointed by an iterator
			CBL_Iter(const CBL_Iter& src) : here(src.here), Itail(src.Itail), Idata(src.Idata), first(src.first),array_size(src.array_size) {} 
			//return the reference of the value pointed by an iterator
			reference operator*() const {
				if (first == Itail) {
					throw std::runtime_error("Iterator points to nothing. The SDAL list is empty.\n");
				}
				if (first > Itail && here < first && here >= Itail) {
					throw std::runtime_error("Iterator exhausted.\n");
				}
				if ((here < first || here >= Itail) && first < Itail) {
					throw std::runtime_error("Iterator exhausted.\n");
			}			
				return Idata[here];
			}

			pointer operator->() const {
				return &(operator*());
			}	
			//Assignment
			self_reference operator=(CBL_Iter<SSI> const& src) {
				if (this == &src) {
					return (*this);
				}
				here = src.here;
				Itail = src.Itail;
				Idata = src.Idata;
				first = src.first;
				array_size = src.array_size;
				return *this;
			}

			// preincrement
			self_reference operator++() {
				if (!check() && (first != Itail) && here!=Itail) {
					here = next(here);
				}
				return (*this);
			}

			//postincrement
			self_type operator++(int) {
				self_type tmp(*this);
				++(*this);
				return tmp;
			}
			//Check if two iterators point to the same thing
			bool operator==(CBL_Iter<SSI> const& rhs) const {
				return (here == rhs.here && Idata == rhs.Idata);
			}
			//Check if two iterators do not point to the same thing
			bool operator!=(CBL_Iter<SSI> const& rhs)const {
				return (here != rhs.here || Idata != rhs.Idata);
			}
		}; //End of CBL iterator
	public:
		//using size_t = std::size_t;
		using value_type = SS;
		using iterator = CBL_Iter<SS>;
		using const_iterator = CBL_Iter<SS const>;
		
		// iterators over a non-const List
		iterator begin() {return iterator::make_begin(head, head, tail, data, arraySize); }
		iterator end() {return iterator::make_end(tail, head, tail, data,arraySize); }
		// iterators over a const List
		const_iterator begin() const { return const_iterator::make_begin(head, head, tail, data, arraySize); }
		const_iterator end() const { return const_iterator::make_end(tail, head, tail, data, arraySize); }
			
	}; //End of CBL
	//Constructor
	template <typename SS>
	CBL<SS>::CBL(size_t array_size) {
		if (arraySize <= 0) {
			throw std::runtime_error("Invalid array size for CBL.\n");
		}
		//Type holds the type of the element
		type = (typeid(SS).name());
		arraySize = array_size + 1;
		originalSize = arraySize;
		data = new SS[arraySize];
		//Initialize head and tail
		head = 0;
		tail = 0;
	}

	//defalut constructor (defaultArraySize = 50)
	//const size_t DEFAULT_ARRAY_SIZE = 50;
	template <typename SS>
	CBL<SS>::CBL() {
		type = (typeid(SS).name());
		data = new SS[arraySize];
		//Initialize head and tail
		head = 0;
		tail = 0;
	}
	//destructor
	template <typename SS>
	CBL <SS>::~CBL() {
		delete[] data;
	}
	//Go back to the original size
	template <typename SS>
	void CBL <SS>::goBackSize() {
		SS* newArray = new SS[originalSize];
		arraySize = originalSize;
		SS* temp = data;
		delete[] temp;
		data = newArray;
	}
	//Expand Size	
	template <typename SS>
	void CBL<SS>::expandSize(void) {
		if (head == next_index(tail)) {
			//Store the old arraySize
			size_t tempSize = arraySize;
			//Increase the size and create a new array
			//I subtract 1 from arraySize because I used one more slot for the tail
			//Then I added one because I still need one more slot for the tail
			size_t newSize = 1.5*(arraySize-1)+1;
			SS* newArray = new SS[newSize];
			//Copy the values from the old array to the new one
			for (size_t i = 0, j = head; i != (arraySize - 1); ++i, j = next_index(j)) {
				newArray[i] = data[j];
			}
			arraySize = newSize;
			SS* temp = data;
			data = newArray;
			//Delete the original array
			delete[] temp;
			head = 0;
			tail = tempSize - 1;
		}
	}
	//Save Memory
	template <typename SS>
	void CBL<SS>::saveMemory(void) {
		size_t len = length();
		//I subtract one from the arraySize because I used one more slot for tail. 
		//Therefore the actual array size is arraySize - 1, that is, I can have arraiSize - 1 elements at maximum
		if ((arraySize-1) >= 2*(originalSize-1) && len < 0.5*(arraySize-1)) {
				size_t newSize = 0.75*(arraySize-1) + 1;
				SS* newArray = new SS[newSize];
				for (size_t i = 0, j = head; i != len; ++i, j = next_index(j)) {
					newArray[i] = data[j];
				}
				arraySize = newSize;
				SS* temp = data;
				delete[] temp;
				data = newArray;
			
			//Set head and tail to new values
			tail = len;
			head = 0;
		}
	}
	//next_index(i)
	template <typename SS>
	size_t CBL<SS>::next_index(size_t i) {
		//set tail to zero if tail holds the last index previously
		if (++i == arraySize) {
			i = 0;
		}
		return i;
	}
	//prev_index(i)
	template <typename SS>
	size_t CBL<SS>::prev_index(size_t i) {
		if (i == 0) {
			i = arraySize - 1;
		}
		else {
			--i;
		}
		return i;
	}
	//Copy constructor
	template <typename SS>
	CBL <SS>::CBL(const CBL &obj) {
		type = (typeid(SS).name());
		//Start with blank
		data = nullptr;
		head = 0;
		tail = 0;	
		originalSize = 0;
		arraySize = 0;
		size_t len;
		if (obj.head <= obj.tail)
			len = obj.tail - obj.head;
		else
			len=obj.tail+ obj.arraySize - obj.head;
		//Copy the list
		data = new SS[obj.arraySize];
		for (size_t i = obj.head; i < len; i= next_index(i)) {
			data[i] = obj.data[i];
		}
		head = obj.head;
		tail = obj.tail;
		originalSize = obj.originalSize;
		arraySize = obj.arraySize;
	}
	//Copy assignment operator
	template <typename SS>
	CBL<SS>& CBL <SS>::operator= (const CBL &obj) {
		//Check if two lists have the same address
		if (this != &obj) {
			//delete the original list
			delete [] data;
			head = 0;
			tail = 0;
			originalSize = 0;
			arraySize = 0;
			size_t len;
			if (obj.head <= obj.tail)
				len = obj.tail - obj.head;
			else
				len = obj.tail + obj.arraySize - obj.head;
			//Copy the list
			data = new SS[obj.arraySize];
			for (size_t i = obj.head; i < len; i = next_index(i)) {
				data[i] = obj.data[i];
			}
			head = obj.head;
			tail = obj.tail;
			originalSize = obj.originalSize;
			arraySize = obj.arraySize;
		}
		return *this;
	}
	//Move constructor
	template <typename SS>
	CBL<SS>::CBL(CBL &&obj) noexcept:
	head(0), tail(0), type(""),data(nullptr), originalSize(0), arraySize(0)
	{
		//Copy the values of data members from the source obejct
		head = obj.head;
		tail = obj.tail;
		type = obj.type;
		data = obj.data;
		originalSize = obj.originalSize;
		arraySize = obj.arraySize;
		//leave obj in a destructible state
		obj.head = 0; obj.tail = 0; obj.data = nullptr;
		obj.type = "";
		obj.originalSize = 0; obj.arraySize = 0;
	}
	//Move assignment operator
	template <typename SS>
	CBL<SS>& CBL<SS>::operator=(CBL &&obj) noexcept
	{
		//Check if there are two same lists
		if (this != &obj) {
			//Free existing elements
			delete[] data;
			head = 0;
			tail = 0;
			originalSize = 0;
			arraySize = 0;
			type = "";
			//Copy the values of data members from the source obejct
			head = obj.head;
			tail = obj.tail;
			type = obj.type;
			data = obj.data;
			originalSize = obj.originalSize;
			arraySize = obj.arraySize;
			//leave obj in a destructible state
			obj.head = 0; obj.tail = 0; obj.data = nullptr;
			obj.type = "";
			obj.originalSize = 0; obj.arraySize = 0;
		}
		return *this;
	}

	//insert(element, position)
	template <typename SS>
	void CBL<SS>::insert(SS element, int position) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element into CBL list.\n");
		int len = length();
		if (position > len || position < 0) {
			throw std::runtime_error("Invalid position.\n");
		}
		//Call push_front if position is 0
		if (position == 0) {
			push_front(element);
		}
		//Call push_back if position is equal to the length of the list
		else if (position == len) {
			push_back(element);
		}
		else {
			//check if the old array is full
			expandSize();
			size_t relative_pos = (position + head) % arraySize;
			//insert an element
			for (size_t i = tail; i != relative_pos; i = prev_index(i)) {
				data[i] = data[prev_index(i)];
			}
			data[relative_pos] = element;
			tail = next_index(tail);
			//check if the list has wasted too much memory
			saveMemory();
		}
		
	}
	//push_back(element)
	template <typename SS>
	void CBL<SS>::push_back(SS element) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element at the end of CBL list.\n");
		
		//check if the old array is full
		//If the array is full, expand it	
			expandSize();
		//Add the element to the end of the list
		data[tail] = element;
		//Update the tail
		tail = next_index(tail);
		//check if the list has wasted too much memory
			saveMemory();
	}
	//push_front(element)
	template <typename SS>
	void CBL<SS>::push_front(SS element) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element at the front of CBL list.\n");
		//check if the old array is full
		//If the array is full, expand it	
		expandSize();
		if (is_empty()) {
			data[head] = element;
			tail = next_index(tail);
		}
		else {
			//Update the head and add the element to the front of the list
			head = prev_index(head);
			data[head] = element;
		}
		//check if the list has wasted too much memory
		saveMemory();
	}
	//replace(element, position)
	template <typename SS>
	SS CBL<SS>::replace(SS element, int position) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to replace an element in the CBL list.\n");
		int len = length();
		if (is_empty()) {
			throw std::runtime_error("The CBL list is empty. No elements can be replaced.\n");
		}
		if (position<0 || position >= len) {
			throw std::runtime_error("Invalid position.\n");
		}
		//Find the position
		size_t relative_pos = (position + head) % arraySize;
		//Store the element in that position to temp
		SS temp = data[relative_pos];
		//Store a new value into the position
		data[relative_pos] = element;
		return temp;
	}
	//remove (position)
	template <typename SS>
	SS CBL<SS>::remove(int position) {
		int len = length();
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CBL list is empty. No elements can be removed from the CBL list.\n");
		}
		if (position<0 || position > len-1) {
			throw std::runtime_error("Invalid position.\n");
		}
		//Get the position
		size_t relative_pos = (position + head) % arraySize;
		SS temp = data[relative_pos];
		//Shift elements
		for (size_t i = relative_pos; i != tail - 1; i = next_index(i)) {
			data[i] = data[next_index(i)];
		}
		tail = prev_index(tail);
		saveMemory();
		return temp;
	}
	//pop_back()
	template <typename SS>
	SS CBL<SS>::pop_back() {
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CBL list is empty. No elements can be removed from the back.\n");
		}
		SS temp = data[prev_index(tail)];
		tail = prev_index(tail);
		saveMemory();
		return temp;
	}
	//pop_front()
	template <typename SS>
	SS CBL<SS>::pop_front() {
		//Check if the list is empty
		if (is_empty()) {
			throw std::runtime_error("The CBL list is empty. No elements can be removed from the head.\n");
		}
		//Store the first element into the temp
		SS temp = data[head];
		//Change the index that head holds
		head = next_index(head);
		//Check if too many slots are wasted
		saveMemory();
		return temp;
	}
	//item_at (position)
	template <typename SS>
	SS& CBL<SS>::item_at(int position) {
		int len = length();
		if (is_empty()) {
			throw std::runtime_error("The CBL list is empty. No element can be returned.\n");
		}
		if (position < 0 || position >= len) {
			throw std::runtime_error("Invalid position.\n");
		}
		return data[(position + head) % arraySize];
	}
	//peek_back()
	template <typename SS>
	SS& CBL<SS>::peek_back() {
		if (is_empty()) {
			throw std::runtime_error("The CBL list is empty. No element can be returned from the back.\n");
		}
		return data[prev_index(tail)];
	}
	//peek_front()
	template <typename SS>
	SS& CBL<SS>::peek_front() {
		if (is_empty()) {
			throw std::runtime_error("The CBL list is empty. No element can be returned from the head.\n");
		}
		return data[head];
	}
	//is_empty()
	template <typename SS>
	bool CBL <SS>::is_empty() {
		return (tail == head);
	}
	//is_full()
	template <typename SS>
	bool CBL <SS>::is_full() {
		return false;
	}
	//length()
	template <typename SS>
	size_t CBL<SS>::length() {
		if (head <= tail)
			return (tail - head);
		else
			return ((tail)+(arraySize - head));
	}
	//clear()
	template <typename SS>
	void CBL<SS>::clear(void) {
		goBackSize();
		head = 0; tail = 0;
	}
	//contains(element, equals_function)
	template <typename SS>
	bool CBL<SS>::contains(const SS& element, bool equals_function(const SS& existingElement, const SS& element)) {		
		for (size_t i = head; i != tail; i = next_index(i)) {
			const SS& curr_data = data[i];
			if (equals_function(curr_data, element)) {
				return true;
			}
		}
		return false;
	}
	//print(ostream)
	template <typename SS>
	void CBL<SS>::print(std::ostream &ostream) {
		if (is_empty())
			ostream << "<empty list>";
		else {
			size_t len = length();
			ostream << "[";
			for (size_t i = 0, j = head; i != len; ++i, j = next_index(j)) {
				ostream << data[j];
				if (j != prev_index(tail))
					ostream << ",";
			}
			ostream << "]";
		}
	}
	//contents()
	template <typename SS>
	SS* CBL<SS>::contents() {
		//Get the length of the list
		size_t len = length();
		//Create a new array
		SS* newArray = new SS[len];
		//Copy values
		for (size_t i = 0, j = head; i != len; ++i, j = next_index(j)) {
			newArray[i] = data[j];
		}	
		//return the address of allocated array
		return newArray;
	}
}
#endif
	
