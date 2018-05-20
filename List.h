#ifndef _LIST_H_
#define _LIST_H_

//Include two files needed to use size_t
#include <stdio.h>
#include <sys/types.h>
namespace cop3530 {
	template <typename SS>
	class List {
	public:
		virtual void insert(SS element, int position) = 0;
		virtual void push_back(SS element) = 0;
		virtual void push_front(SS element) = 0;
		virtual SS replace(SS element, int position) = 0;
		virtual SS remove(int position) = 0;
		virtual SS pop_back(void) = 0;
		virtual SS pop_front(void) = 0;
		virtual SS& item_at(int position) = 0;
		virtual SS& peek_back(void) = 0;
		virtual SS& peek_front(void) = 0;
		virtual bool is_empty(void) = 0;
		virtual bool is_full(void) = 0;
		virtual size_t length(void) = 0;
		virtual void clear(void) = 0;
		virtual bool contains(const SS& element, bool equals_function(const SS& existingElement, const SS& element)) = 0;
		virtual void print(std::ostream& ostream) = 0;
		virtual SS* contents(void) = 0;
		//Destructor
		virtual ~List() {};
	};
}
#endif