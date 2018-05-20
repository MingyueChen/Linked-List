
#ifndef _SDAL_H_
#define _SDAL_H_
#include "List.h"
#include <stdexcept>
#include <typeinfo>
#include <string>
namespace cop3530 {
	template <typename SD>
	class SDAL : public List <SD> {
	public: 
		//constructors and destructor
		SDAL(size_t);
		SDAL();
		~SDAL() override;
		//Copy constructor
		//Copy constructor
		SDAL(const SDAL &obj);
		//Copy assignment operator
		SDAL& operator= (const SDAL &obj);
		//Move constructor
		SDAL(SDAL&&) noexcept;
		//Move assignment operator
		SDAL& operator=(SDAL&& obj) noexcept;
		//operations
		
		void insert(SD element, int position) override;
		void push_back(SD element) override;
		void push_front(SD element) override;
		SD replace(SD element, int position) override;
		SD remove(int position) override;
		SD pop_back(void) override;
		SD pop_front(void)override;
		SD& item_at(int position) override;
		SD& peek_back(void) override;
		SD& peek_front(void) override;
		bool is_empty(void) override;
		bool is_full(void) override;
		size_t length(void) override;
		void clear(void) override;
		bool contains(const SD& element, bool equals_function(const SD& existingElement, const SD& element)) override;
		void print(std::ostream &ostream) override;
		SD* contents(void) override;
	private:
		std::string type; //type holds the type of the element
		SD* data;//head which points to the array
		int tail; //tail holds the index of one past the last element	
		int arraySize = 50;
		int originalSize = 50;
		void expandSize(void);
		void saveMemory(void);
		void goBackSize(void);

	template <typename SDI>
	class SDAL_Iter {
	public:
		// type aliases required for C++ iterator compatibility
		using value_type = SDI;
		using reference = SDI&;
		using pointer = SDI*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;

		// type aliases for prettier code
		using self_type = SDAL_Iter;
		using self_reference = SDAL_Iter&;

	private:
		int here; //here refers to the index of the array
		int Itail;
		pointer Idata;

	public:
		// factories called by class rectangle
		//static because I will call these functions without calling on objects. I call functions on the class (iter)
		static self_type make_begin(int start, int tails, pointer datas) {
			SDAL_Iter i(start, tails, datas);
			return i;
		}
		static self_type make_end(int start, int tails, pointer datas) {
			SDAL_Iter i(start, tails, datas);
			return i;
		}

		explicit SDAL_Iter(int start = 0, int tails = 0, pointer datas = nullptr) : here(start), Itail (tails), Idata(datas)  {} //if nothing is passed, it will start at 0
																   //else, it will start at the number I passed in.
		SDAL_Iter(const SDAL_Iter& src) : here(src.here), Itail(src.Itail), Idata(src.Idata) {} //copy constructor
		//return the reference of the value pointed by an iterator
		reference operator*() const {
			if (here >= Itail) {
				throw new std::runtime_error("Iterator exhausted.\n");
		  }
			if (Itail == 0) {
				throw new std::runtime_error("Iterator points to nothing. The SDAL list is empty.\n");
			}
			return Idata[here];
		}
		pointer operator->() const {
			return &(operator*());
		}
		//Assignment
		self_reference operator=(SDAL_Iter<SDI> const& src) {
			if (this == &src) {
				return (*this);
			}
			here = src.here;
			Itail = src.Itail;
			Idata = src.Idata;
			return *this;
		}
		// preincrement
		self_reference operator++() {
			if (here < Itail) {
				here++;
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
		bool operator==(SDAL_Iter<SDI> const& rhs) const {
			return (here == rhs.here && Idata == rhs.Idata);
		}
		//Check if two iterators do not point to the same thing
		bool operator!=(SDAL_Iter<SDI> const& rhs)const {
			return (here != rhs.here || Idata != rhs.Idata);
		}
	  };//End of SDAL_Iter
	public:
	//using size_t = std::size_t;
	using value_type = SD;
	using iterator = SDAL_Iter<SD>;
	using const_iterator = SDAL_Iter<SD const>;
	// iterators over a non-const List
	iterator begin() { return iterator::make_begin(0,tail, data); }
	iterator end() { return iterator::make_end(tail, tail, data); }
	// iterators over a const List
	const_iterator begin() const { return const_iterator::make_begin(0, tail, data); }
	const_iterator end() const { return const_iterator::make_end(tail, tail, data); }
	};//End of SDAL

	//goBackSize
	template <typename SD>
	void SDAL<SD>::goBackSize(void) {
		SD* newArray = new SD[originalSize];
		arraySize = originalSize;
		SD* temp = data;
		delete[] temp;
		data = newArray;
	}
	//saveMemory
	template <typename SD>
	void SDAL<SD>::saveMemory(void) {
		size_t len = length();
		if (arraySize >= 2*originalSize && len < 0.5*arraySize) {
			size_t newSize = 0.75*arraySize;
			SD* newArray = new SD[newSize];
			//Copy values
			for (size_t i = 0; i < len; i++) {
				newArray[i] = data[i];
			}
			arraySize = newSize;
			SD* temp = data;
			delete[] temp;
			data = newArray;
		}
	}
	//Expand the size
	template <typename SD>
	void SDAL<SD>::expandSize(void) {
		if (tail == arraySize) {
			//This statement is for debugging only.
			//I commented this statement out when I submitted it.
			//since I do not want this statement to be printed out when people use the list. 
			//std::cout << "new Size is created " << std::endl;

			int newSize = 1.5*arraySize;
			SD* newArray = new SD[newSize];
			//Copy values
			for (int i = 0; i < arraySize; i++) {
				newArray[i] = data[i];
			}
			arraySize = newSize;
			SD* temp = data;
			data = newArray;
			delete[] temp;
		}
		
	}

	//Constructor: the user can pass the array size
	template <typename SD>
	SDAL<SD>::SDAL(size_t array_size) {
		if (array_size <= 0) {
			throw std::runtime_error("Invalid array size.\n");
		}
		//Get the type of the elements in the list
		type = (typeid(SD).name());
		arraySize = array_size;
		originalSize = arraySize;
		data = new SD[arraySize];
		//Initialize tail with 0
		tail = 0;
	}

	//defalut constructor (defaultArraySize = 50)
	//const size_t DEFAULT_ARRAY_SIZE = 50;
	template <typename SD>
	SDAL<SD>::SDAL() {
		//Get the type of the elements in the list
		type = (typeid(SD).name());
		data = new SD [arraySize];
		//Initialize tail with 0
		tail = 0;
	}

	//destructor
	template <typename SD>
	SDAL <SD>::~SDAL() {		
		delete [] data;
	}

	//Copy constructor
	template <typename SD>
	SDAL <SD>::SDAL(const SDAL &obj) {
		type = (typeid(SD).name());
		//Start with blank
		data = nullptr;
		tail = 0; originalSize = 0; arraySize = 0;
		//Copy the list
		data = new SD[obj.arraySize];
		for (int i = 0; i < obj.tail; i++) {
			data[i] = obj.data[i];
		}
		tail = obj.tail;
		originalSize = obj.originalSize;
		arraySize = obj.arraySize;
	}
	//Copy assignment operator
	template <typename SD>
	SDAL<SD>& SDAL <SD>::operator= (const SDAL &obj) {
		//Check if two lists have the same address
		if (this != &obj) {
			//delete the original list
			delete[] data;
			tail = 0; originalSize = 0; arraySize = 0;
			//Move the list
			data = new SD[obj.tail];
			for (size_t i = 0; i < obj.tail; i++) {
				data[i] = obj.data[i];
			}
			tail = obj.tail;
			originalSize = obj.originalSize;
			arraySize = obj.arraySize;
		}
		return *this;
	}
	//Move constructor
	template <typename SD>
	SDAL<SD>::SDAL(SDAL &&obj) noexcept:
	 tail(0), type(""),data(nullptr), originalSize(0), arraySize(0)
	{
		//Move the values of data members from the source obejct
		data = obj.data;
		tail = obj.tail;
		type = obj.type;
		originalSize = obj.originalSize;
		arraySize = obj.arraySize;
		//leave obj in a destructible state
		obj.tail = 0;
		obj.type = "";
		obj.originalSize = 0; obj.arraySize = 0;
	}
	//Move assignment operator
	template <typename SD>
	SDAL<SD>& SDAL<SD>::operator=(SDAL &&obj) noexcept
	{
		//Check if there are two same lists
		if (this != &obj) {
			//Free existing elements
			delete[] data;
			tail = 0; originalSize = 0; arraySize = 0;
			//Move the values of data members from the source obejct
			data = obj.data;
			tail = obj.tail;
			type = obj.type;
			originalSize = obj.originalSize;
			arraySize = obj.arraySize;
			//leave obj in a destructible state
			obj.tail =0;
			obj.originalSize = 0; obj.arraySize = 0;
			obj.type = "";
		}
		return *this;
	}

	//insert(element, position)
	template<typename SD>
	void SDAL<SD>::insert(SD element, int position) {
		//check if the type of the element is correct
		if (type.compare(typeid(element).name()))
			throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element into SDAL list.\n");
		//Check if the position is valid
		if (position > tail || position < 0) {
			throw std::runtime_error("Invalid position.\n");
		}
		//check if the old array is full
		expandSize();
		//insert an element
		for (int i = tail; i >position; i--) {
			data[i] = data[i - 1];			
		}
		data[position] = element;
		tail++;
		//check if the list has wasted too much memory
		saveMemory(); 
	}
		//push_back(element)
		template <typename SD>
		void SDAL<SD>::push_back(SD element) {
			//check if the type of the element is correct
			if (type.compare(typeid(element).name()))
				throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element at the end of SDAL list.\n");
			//check if the old array is full
			expandSize();
			data[tail] = element;	
			tail++;
			//check if the list has wasted too much memory
			saveMemory();		
		}

		//push_front(element)
		template <typename SD>
		void SDAL<SD>::push_front(SD element) {
			//check if the type of the element is correct
			if (type.compare(typeid(element).name()))
				throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to insert an element at the front of SDAL list.\n");
			for (int i = tail; i > 0; i--) {
				data[i] = data[i - 1];				
			}
			//check if the old array is full
			expandSize();
			data[0] = element;
			tail++;
			//check if the list has wasted too much memory
			saveMemory();			
		}

		//replace(element, position)
		template <typename SD>
		SD SDAL<SD>::replace(SD element, int position) {
			//check if the type of the element is correct
			if (type.compare(typeid(element).name()))
				throw std::runtime_error("The type of the element entered does not match the type of the list. Failed to replace an element in the SDAL list.\n");
			
			if (is_empty()) {
				throw std::runtime_error("The SDAL list is empty. No elements can be replaced.\n");
			}
			if (position<0 || position > (tail-1)) {
				throw std::runtime_error("Invalid position.\n");
			}
			SD temp = data[position];
			data[position] = element;
			return temp;
		}

		//remove (position)
		template <typename SD>
		SD SDAL<SD>::remove(int position) {
			//Check if the list is empty
			if (is_empty()) {
				throw std::runtime_error("The SDAL list is empty. No elements can be removed.\n");
			}
			if (position<0 || position >(tail-1)) {
				throw std::runtime_error("Invalid position.\n");
			}
			SD temp = data[position];
			for (int i = position ; i <(tail-1); i++) {
				data[i] = data[i + 1];
			}
			tail--;
			//check if the list has wasted too much memory
			saveMemory();
			return temp;
		}

		//pop_back()
		template <typename SD>
		SD SDAL<SD>::pop_back(void) {
			//Check if the list is empty
			if (is_empty()) {
				throw std::runtime_error("The SDAL list is empty. No elements can be removed from the back.\n");
			}
			SD temp = data[tail-1];
			tail--;
			//check if the list has wasted too much memory
			saveMemory();
			return temp;
		}

		//pop_front()
		template <typename SD>
		SD SDAL<SD>::pop_front(void) {
			//Check if the list is empty
			if (is_empty()) {
				throw std::runtime_error("The SDAL list is empty. No elements can be removed from the head.\n");
			}
			SD temp = data[0];
			for (int i = 0; i < tail-1; i++) {
				data[i] = data[i + 1];
			}
			tail--;
			//check if the list has wasted too much memory
			saveMemory();
			return temp;
		}

		//item_at(position)
		template <typename SD>
		SD& SDAL<SD>::item_at(int position) {
			if (is_empty()) {
				throw std::runtime_error("The SDAL list is empty. No element can be returned.\n");
			}
			if (position < 0 || position >tail-1) {
				throw std::runtime_error("Invalid position.\n");
			}
			return data[position];
		}

		//peek_back()
		template  <typename SD>
		SD& SDAL<SD>::peek_back() {
			if (is_empty()) {
				throw std::runtime_error("The SDAL list is empty. No element can be returned.\n");
			}
			return data[tail-1];
		}
		 //peek_front()
		template <typename SD>
		SD& SDAL<SD>::peek_front() {
			if (is_empty()) {
				throw std::runtime_error("The SDAL list is empty. No element can be returned.\n");
			}
			return data[0];
		}
		//is_empty()
		template <typename SD>
		bool SDAL <SD>::is_empty() {
			return (tail == 0);
		}

		//is_full()
		template <typename SD>
		bool SDAL <SD>::is_full() {
			return false;
		}
		//length()
		template <typename SD>
		size_t SDAL <SD>::length() {
			return tail;
		}
		
		//clear()
		template <typename SD>
		void SDAL <SD>::clear() {
			tail = 0;
			goBackSize();
		}

		//contains(element, equals_function)
		template <typename SD>
		bool SDAL<SD>::contains(const SD& element, bool equals_function(const SD& existingElement, const SD& element)) {
			for (int i = 0; i < tail; i++) {
				const SD& curr_data = data[i];
				if (equals_function(curr_data, element)) {
					return true;
				}
			}
			return false;
		}

		//print(ostream)
		template <typename SD>
		void SDAL<SD>::print(std::ostream &ostream) {
			if (is_empty())
				ostream << "<empty list>";
			else {
				ostream << "[";
				for (int i = 0; i < tail; i++) {
					ostream << data[i];
					if (i != tail-1)
						ostream << ",";
				}
				ostream << "]";
			}

		}

		//contents()
		template <typename SD>
		SD* SDAL<SD>::contents() {
			//Get the length of the list
			size_t len = length();
			SD* newArray = new SD[len];
			//Copy values
			for (size_t i = 0; i < len; i++) {
				newArray[i] = data[i];
			}
			//return the address of allocated array
			return newArray;
		}
	
}
#endif

