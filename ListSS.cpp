//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "SSLL.h"
#include<iostream>
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include <typeinfo>
#include "Person.h"
#include "CBL.h"
#include<string>
//#include "catch.hpp"
#define DEBUG

bool equals_function(const int& existingElement, const int& element) {
	return (element == existingElement);
}
bool equals_function(const Person& existingElement, const Person& element) {
	return existingElement.age == element.age && existingElement.name == element.name;
}

using namespace cop3530;

int main() {
	/*
	SDAL_Child<int>*sdalList = new SDAL_Child<int>(2);
	sdalList->push_back(11);
	sdalList->push_back(12);
	sdalList->push_back(13);*/
	//Create ssllTest to determine whether SSLL_Child<int> passes this test or not
	bool ssllTest = true;
	//Create a pointer to a linked list (SSLL) with integer type
	std::cout << "#### The first test for SSLL with integer type ####\n\n";
	SSLL<int> *ssllList = new SSLL<int>();
	//Test if the list is empty/full
	ssllTest &= ssllList->is_empty() == true;
	ssllTest &= ssllList->is_full() == false;
	//Use push_front to add elements. After ths following for loop, the list should contain the numbers with this order: 0, 1, 2
	for (int i = 2; i >= 0; i--) {
		ssllList->push_front(i);
	}
	//Use push_back to add elements. After ths following for loop, the list should contain the numbers with this order: 0, 1, 2, 6, 7, 8
	for (int i = 6; i <9; i++) {
		ssllList->push_back(i);
	}
	//Use insert to add elements. After there statements, the list should contain the numbers with this order: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	ssllList->insert(3, 3); //Insert 3 into the third position
	ssllList->insert(5, 4); //Insert 5 into the fourth position
	ssllList->insert(4, 4); //Insert 4 into the fourth position
	//Test length()
	ssllTest &= ssllList->length() == 9; //The list's length should be 9 now
	std::cout << "#### Use print function to print out the values in the SSLL <int> list ####\n";
	ssllList->print(std::cout);
	std::cout << std::endl;
	//Create a pointer to an array to test if contents function works
	int* ssllArray = ssllList->contents();
	std::cout << "#### Use contents to print out the values in the SSLL<int> list ####\n";
	for (unsigned int a = 0; a < ssllList->length(); a++) {
		std::cout << ssllArray[a] << " ";
	}
	std::cout << std::endl<<std::endl;
	//Use an iterator to test if the iterator works
	SSLL<int>::iterator ssllIterB = ssllList->begin();
	SSLL<int>::iterator ssllIterE = ssllList->end();
	std::cout << "#### Use an iterator to print out the values in the SSLL <int> list ####\n";
	for (; ssllIterB != ssllIterE; ++ssllIterB) {
		std::cout << *ssllIterB
			<< " ";
	}
	//Test replace(), peek_front(), and item_at()
	std::cout << std::endl<<std::endl;
	//Check if the element which was replaced is 0. Replace the first element with 9
	ssllTest &= ssllList->replace(9, 0) == 0;
	//The list becomes 9, 1, 2, 3, 4, 5, 6, 7, 8
	//The first element should be 9 now
	ssllTest &= ssllList->peek_front() == 9;
	//Test item_at
	ssllTest &= ssllList->item_at(3) == 3;
	//Test if peek_front() returns by reference
	int &ssreff = ssllList->peek_front();
	ssllTest &= ssreff == 9;
	//Update the first element in the ssllList with 10
	ssllList->peek_front() = 10;
	//Test if both ssref and the first element of ssllList holds value 10
	ssllTest &= ssreff == 10;
	ssllTest &= ssllList->peek_front() == 10;
	//Test if item_at() returns by reference
	int &ssrefi = ssllList->item_at(4);
	ssllTest &= ssrefi == 4;
	//Update the fifth element in the ssllList with 12;
	ssllList->item_at(4) = 12;
	//Test if both ssref and the first element of ssllList holds value 10
	ssllTest &= ssrefi == 12;
	ssllTest &= ssllList->item_at(4) == 12;
	//The list looks like 10, 1, 2, 3, 12, 5, 6, 7, 8
	//Test is_empty() and is_full()
	ssllTest &= ssllList->is_empty() == false;
	ssllTest &= ssllList->is_full() == false;
	//Test remove(), pop_back(), and pop_front()
	ssllList->remove(0); //The list becomes 1, 2, 3, 12, 5, 6, 7, 8
	ssllList->pop_back();//The list becomes 1, 2, 3, 12, 5, 6, 7
	ssllList->pop_front();//The list becomes 2, 3, 12, 5, 6, 7
	ssllList->remove(2); //The list becomes 2, 3, 5, 6, 7
	//Test peek_back()
	int &ssrefb = ssllList->peek_back();
	ssllTest &= ssrefb == 7;
	ssllTest &= ssllList->peek_back() == 7;
	ssllList->peek_back() = 8;
	ssllTest &= ssrefb == 8;
	ssllTest &= ssllList->peek_back() == 8;
	ssllIterB = ssllList->begin();
	ssllIterE = ssllList->end();
	ssllTest &= !(ssllIterB == ssllIterE); //ssllIterB does not point to the same value as ssllIterE does, so the return value should be false; !false = true
	//Use the iterator to print out the list: 2, 3, 5, 6, 8
	std::cout << "#### Use an iterator to print out the values in the SSLL<int> list ####\n";
	for (; ssllIterB != ssllIterE; ++ssllIterB) {
		std::cout << *ssllIterB
			<< " ";
	}
	std::cout << std::endl <<std::endl;
	//Test if contains works. Since 3 is in the list, contain should return true
	ssllTest &= ssllList->contains(3, equals_function);
	ssllTest &= !(ssllList->contains(10, equals_function)); //Since 10 is not in the list, contain should return false
	//Test if the exception can thrown properly when I enter an valid position
	std::cout << "\n** Check if appropriate exceptions are thrown when the position is invalid. **\n\n";
	//The functions which check the validity of the position are: insert, replace, remove, and item_at
	try {
		//The list is 2, 3, 5, 6, 8, so it is impossible to insert an element at the 6th position
		ssllList->insert(3,6);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//It is impossible to get an element at -1st position
		ssllList->item_at(-1);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list is 2, 3, 5, 6, 8, so it is impossible to insert an element at the 5th position
		ssllList->replace(3, 5);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list is 2, 3, 5, 6, 8, so it is impossible to remove an element at the 5th position
		ssllList->remove(5);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//Use an iterator to test if the constant iterator works
	const SSLL<int>* const_ssllList = ssllList;
	SSLL<int>::const_iterator  ssllIterBC = const_ssllList->begin();
	SSLL<int>::const_iterator ssllIterEC = const_ssllList->end();
	//The output should be 2, 3, 5, 6, 8
	std::cout << "\n#### Use a constant iterator to print out the values in the SSLL<int> list ####\n";
	for (; ssllIterBC != ssllIterEC; ++ssllIterBC) {
		std::cout << *ssllIterBC
			<< " ";
	}
	//Test if operator== works
	ssllTest &= (ssllIterBC == ssllIterEC);
	//Test postincrement and preincrement
	SSLL<int>::const_iterator ssiterb = const_ssllList->begin();
	//The list should be 2, 3, 5, 6, 8
	ssllTest &= *(ssiterb++) == 2;
	ssllTest &= *(++ssiterb) == 5;
	std::cout << std::endl;
	ssllList->clear();
	ssllTest &= ssllList->length() == 0; //Test if length becomes 0 after clear function is called
	std::cout << "\n**** Check if appropriate exceptions are thrown when the list is empty. ****\n\n";
	//Test if the exception can thrown properly when I try to remove elements from an empty list or replace elements in an empty list
	//The functions which check if the list is empty are: replace, remove, pop_back, pop_front, item_at, peek_back, and peek_front
	//test remove
	try {
		ssllList->remove(2);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_back
	try {
		ssllList->pop_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_front
	try {
		ssllList->pop_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test replace
	try {
		ssllList->replace(1,3);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test item_at
	try {
		ssllList->item_at(-2);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_back
	try {
		ssllList->peek_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_front
	try {
		ssllList->peek_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//Print out "pass" to indicate that SSLL_Child passes this test case
	if (ssllTest) {
		std::cout << "\n#### Pass the first test for SSLL<int> ####\n" << std::endl;
	}
	else {
		std::cout << "\n#### Fail the first test for SSLL<int> ####\n" << std::endl;
	}
	delete ssllList;

	//Print out asterisks to separate two tests
	std::cout << "\n*********************************************************************\n\n\n";
	//Insert person objects into the SSLL list
	std::cout << "#### The second test for SSLL with Person object type ####\n\n";
	//ssllTestP is used to test if my program passes this test (true indicates passing)
	bool ssllTestP = true;
	//Create a list with Person objects
	SSLL<Person> *personListSS = new SSLL<Person>();
	//Create some Person objects
	Person person1(20, "John");
	Person person2(19, "Mary");
	Person person3(20, "John");
	Person person4(19, "Mike");
	Person person5(21, "Kitty");
	Person person6(18, "Andy");
	//Use push_back, push_front, and insert to add Person objects to the list
	personListSS->push_back(person2);
	personListSS->push_front(person1);
	personListSS->insert(person4, 1); //Right now the list should contain the fields of the following classes in the following order: person1, person4, and person2
	//Use print, contents, and iterators to print out values in the list
	std::cout << "### Use print function to print out the values in the SSLL<Person>\n";
	personListSS->print(std::cout); std::cout << std::endl << std::endl;
	Person* ssllArrayP = personListSS->contents();
	std::cout << "#### Use contents to print out the values in the SSLL<Person> ####\n";
	for (unsigned int a = 0; a < personListSS->length(); a++) {
		std::cout << ssllArrayP[a] << " ";
	}
	std::cout << std::endl << std::endl;
	ssllTestP &= personListSS->contains(person3, equals_function);//contains should return true since person 3 is exactly the same as person1 and person1 is in the list
	ssllTestP &= !(personListSS->contains(person5, equals_function)); //contains should return false since person 5 is not in the list
	//User the iterator to print out the list
	SSLL<Person>::iterator ssllIterFP = personListSS->begin();
	SSLL<Person>::iterator ssllIterBP;
	//Test if operator= and operaotr++(int) (postincrement)
	//ssllIterBP should point to the first element of the list (which is person1)
	//ssllIterFP should point to the second element of the list (which is person4)
	ssllIterBP = ssllIterFP++;
	SSLL<Person>::iterator ssllIterEP = personListSS->end();
	//Test if operator-> works (print out the fields of person1: 20 John)
	std::cout << "#### Use operator-> to print out the fields of person1: 20 John (ssllIterBP points to person1) ####\n";
	std::cout << ssllIterBP->age <<" " <<ssllIterBP->name <<"\n\n";
	//Test if operator-> works (print out the fields of person4: 19 Mike)
	std::cout << "#### Use operator-> to print out the fields of person4: 19 Mike (ssllIterFP points to person4) ####\n";
	std::cout << ssllIterFP->age << " " << ssllIterFP->name << "\n\n";
	std::cout << "#### Use an iterator to print out the values in the SSLL<Person> ####\n";
	for (; ssllIterBP != ssllIterEP; ++ssllIterBP) {
		std::cout << *ssllIterBP
			<< " ";
	}
	//Test if operator == works
	ssllTestP &= ssllIterBP == ssllIterEP;
	//Test if an appropriate exception can be thrown if the iterator points to a null pointer
	std::cout << "\n**** Check if an appropriate exception can be thrown if the iterator points to a null pointer. ****\n\n";
	try {
		//std::cout<<"test operator  " << ssllIterBP->operator==(0);
		*ssllIterBP;
	}
	catch (std::runtime_error const & d) {
		std::cout << std::endl;
		std::cout << d.what();
	}

	std::cout << std::endl << std::endl;

	//Replace the first element with person5
	ssllTestP &= personListSS->replace(person5, 0) == (person1);//Check if the list returns the original element-- person1. The list now becomes person5, person4, and person2
	ssllTestP &= personListSS->item_at(1)==(person4); //The second item in the list is person4
	ssllTestP &= personListSS->peek_back() == (person2); //The last item in the list is person2
	ssllTestP &= personListSS->peek_front() == (person5); //The first item in the list is person5

	ssllTestP &= personListSS->pop_back() == (person2); //Remove the last element in the list, which is person2. The list becomes person5 and person4.
	ssllTestP &= personListSS->length() == 2; //The length of the list should be 2
	personListSS->insert(person6, 0); //Now the list becomes person6, person5, and person4
	ssllTestP &= personListSS->remove(1) == person5;  //Now the list becomes person6 and person4
	ssllTestP &= personListSS->pop_front() == person6; //Now the list becomes person4

	ssllTestP &= personListSS->is_empty() == false;
	ssllTestP &= personListSS->is_full() == false;
	//The functions which check the validity of the position are: insert, replace, remove, and item_at
	std::cout << "\n** Check if appropriate exceptions are thrown when the position is invalid. **\n\n";
	//The functions which check the validity of the position are: insert, replace, remove, and item_at
	try {
		//The list is person4, so it is impossible to insert an element at the 2nd position
		personListSS->insert(person1, 2);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//It is impossible to get an element at -1st position
		personListSS->item_at(-1);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list is person4, so it is impossible to insert an element at the 3rd position
		personListSS->replace(person2, 3);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list is person4, so it is impossible to insert an element at the -2nd position
		personListSS->remove(-2);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	personListSS->clear();
	ssllTestP &= personListSS->length() == 0;
	ssllTestP &= personListSS->is_empty() == true;
	//Use print function to print out the list (the list is already empty)
	std::cout << "\nUse print function to print out SSLL<Person> list after clear function is called\n";
	personListSS->print(std::cout); std::cout <<std::endl;
	std::cout << "\n**** Check if appropriate exceptions are thrown when the list is empty. ****\n\n";
	//Test if the exception can thrown properly when I try to remove elements or get elements from an empty list or replace elements in an empty list
	//The functions which check if the list is empty are: replace, remove, pop_back, pop_front, item_at, peek_back, and peek_front
	//test remove
	try {
		personListSS->remove(2);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_back
	try {
		personListSS->pop_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_front
	try {
		personListSS->pop_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test replace
	try {
		personListSS->replace(person1, 3);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test item_at
	try {
		personListSS->item_at(-2);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_back
	try {
		personListSS->peek_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_front
	try {
		personListSS->peek_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	if (ssllTestP) {
		std::cout << "\n#### Pass the second test for SSLL with Person type ####\n";
	}
	else {
		std::cout << "\n#### Fail the second test for SSLL with Person type ####\n";
	}
	delete personListSS;
	//Print out asterisks to separate two tests
	std::cout << "\n\n*********************************************************************\n\n";
	std::cout << "\n#### The first test for PSLL with integer type ####\n";
	//Test PSLL with integer type
	PSLL<int> *psllList = new PSLL<int>();
	//Create a psllTestInt to test if program can pass this test
	bool psllTestInt = true;
	//Test push_front, insert, and push_back
	psllList->push_front(4); psllList->push_front(3); psllList->push_front(1);
	psllList->insert(0, 0); psllList->insert(5, 4); psllList->insert(2, 2);
	for (int i = 6; i < 51; i++) {
		psllList->push_back(i);
	}
	//The list should contain integers from 0 to 50 in an ascending order
	std::cout<<std::endl<<std::endl << "### Use print function to print out the values in the PSLL<Int>\n"<<std::endl<<std::endl;
	psllList->print(std::cout); std::cout << std::endl << std::endl;
	psllTestInt &= psllList->length() == 51;
	//Test remove, pop_back, and pop_front
	psllTestInt &= psllList->remove(0)==0; psllTestInt &= psllList->remove(49)==50;
	//Remove 41 elements from the back 
	for (int i = 48; i >= 8; i--) {
		psllList->pop_back();
	} //Now the list should look like: 1, 2, 3, 4, 5, 6, 7, 8
	psllTestInt &= psllList->pop_front() == 1;
	//Test replace
	psllTestInt &= psllList->replace(1, 2) == 4;
	//The list should look like: 2, 3, 1, 5, 6, 7, 8
	//Call print to print out the elements in the list
	std::cout << std::endl << std::endl << "### Use print function to print out the values in the PSLL<Int>\n" << std::endl << std::endl;
	psllList->print(std::cout); std::cout << std::endl << std::endl;
	//Test item_at, peek_back, and peek_front and test if these functions return by reference
	//Test if item_at returns by reference
	int &psrefi = psllList->item_at(3);
	psllTestInt &= psrefi == 5;
	//Update the third element in the psllList with 0;
	psllList->item_at(3) = 0;
	//Test if both psrefi and the third element of psllList holds value 0
	psllTestInt &= psrefi == 0;
	psllTestInt &= psllList->item_at(3) == 0; //The list should be: 2, 3, 1, 0, 6, 7, 8
	//Test if peek_back() returns by reference
	int &psrefb = psllList->peek_back();
	psllTestInt &= psrefb == 8;
	//Update the last element in the psllList with 9;
	psllList->peek_back() = 9;
	//Test if both psrefb and the last element of psllList holds value 9
	psllTestInt &= psrefb == 9;
	psllTestInt &= psllList->peek_back() == 9; //The list should be: 2, 3, 1, 0, 6, 7, 9
	//Test if peek_front() returns by reference
	int &psreff = psllList->peek_front();
	psllTestInt &= psreff == 2;
	//Update the first element in the psllList with 2;
	psllList->peek_front() = 8;
	//Test if both psreff and the first element of psllList holds value 8
	psllTestInt &= psreff == 8;
	psllTestInt &= psllList->peek_front() == 8; //The list should be: 8, 3, 1, 0, 6, 7, 9
	//Test if contains works. Since 3 is in the list, contain should return true
	psllTestInt &= psllList->contains(3, equals_function);
	psllTestInt &= !(psllList->contains(10, equals_function)); //Since 10 is not in the list, contain should return false
    //Test is_empty() and is_full()
	psllTestInt = psllList->is_empty() == false; //is_empty() should return false since the list contains elements
	psllTestInt = psllList->is_full() == false;
	//Call print to print out the elements in the list
	std::cout << std::endl << std::endl << "### Use print function to print out the values in the PSLL<Int>\n" << std::endl << std::endl;
	psllList->print(std::cout); std::cout << std::endl << std::endl;
	//Call contents to print out the elements
	//Create a pointer to an array to test if contents function works
	int* psllArray = psllList->contents();
	std::cout << "#### Use contents to print out the values in the PSLL<int> list ####\n";
	for (unsigned int a = 0; a < psllList->length(); a++) {
		std::cout << psllArray[a] << " ";
	}
	std::cout << std::endl << std::endl;
	//Test if the iterator works
	PSLL<int>::iterator psllIterBT = psllList->begin();
	PSLL<int>::iterator psllIterB = psllIterBT++;
	psllTestInt &= (*psllIterBT == 3);
	PSLL<int>::iterator psllIterE = psllList->end();
	std::cout << "#### Use an iterator to print out the values in the PSLL<int> list ####\n\n";
	for (; psllIterB != psllIterE; ++psllIterB) {
		std::cout << *psllIterB
			<< " ";
	}std::cout << std::endl << std::endl;
	//Test if operator == works
	psllTestInt &= psllIterB == psllIterE;
	//Test if the constant iterator works
	const PSLL<int>* const_psllList = psllList;
	PSLL<int>::const_iterator  psllIterBC = const_psllList->begin();
	PSLL<int>::const_iterator psllIterEC = const_psllList->end();
	//The output should be 8, 3, 1, 0, 6, 7, 9
	std::cout << "\n#### Use a constant iterator to print out the values in the PSLL<int> list ####\n";
	for (; psllIterBC != psllIterEC; ++psllIterBC) {
		std::cout << *psllIterBC
			<< " ";
	}std::cout << std::endl << std::endl;
	//The functions which check the validity of the position are: insert, replace, remove, and item_at
	try {
		//The list contains seven elements, so it is impossible to insert an element at the 8th position
		psllList->insert(4, 8);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//It is impossible to get an element at 7th position
		psllList->item_at(7);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list contains seven elements, so it is impossible to replace an element at the 7th position
		psllList->replace(9, 7);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list contains seven elements, so it is impossible to remove an element at the 7th position
		psllList->remove(7);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	std::cout << std::endl << std::endl;
	//Test if clear function works
	psllList->clear();
	psllTestInt &= psllList->length() == 0; //Length should be 0
	psllTestInt &= psllList->is_empty() == true; //The list should be empty
    //The functions which check if the list is empty are: replace, remove, pop_back, pop_front, item_at, peek_back, and peek_front
	//test remove
	try {
		psllList->remove(0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_back
	try {
		psllList->pop_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_front
	try {
		psllList->pop_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test replace
	try {
		psllList->replace(1, 0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test item_at
	try {
		psllList->item_at(0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_back
	try {
		psllList->peek_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_front
	try {
		psllList->peek_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	if (psllTestInt) {
		std::cout << "\n#### Pass the first test for PSLL with integer type ####\n";
	}
	else {
		std::cout << "\n#### Fail the first test for PSLL with integer type ####\n";
	}
	delete psllList;
	//Print out asterisks to separate two tests
	std::cout << "\n*********************************************************************\n\n\n";
	//Insert person objects into the PSLL list
	std::cout << "#### The second test for PSLL with Person object type ####\n\n";
	//psllTestP is used to test if my program passes this test (true indicates passing)
	bool psllTestP = true;
	//Create a list with Person objects
	PSLL<Person> *psll_p = new PSLL<Person>();
	//Use push_back, push_front, and insert to add Person objects to the list
	psll_p->push_back(person2);
	psll_p->push_front(person1);
	psll_p->insert(person4, 1); //Right now the list should contain the fields of the following classes in the following order: person1, person4, and person2
	//Use print, contents, and iterators to print out values in the list
	std::cout << "### Use print function to print out the values in the PSLL<Person>\n";
	psll_p->print(std::cout); std::cout << std::endl << std::endl;
	Person* psllArrayP = psll_p->contents();
	std::cout << "#### Use contents to print out the values in the PSLL<Person> ####\n";
	for (unsigned int a = 0; a < psll_p->length(); a++) {
		std::cout << psllArrayP[a] << " ";
	}
	psllTestP &= psll_p->pop_back() == (person2);
	psllTestP &= psll_p->length() == 2;
	psllTestP &=!( psll_p->is_empty());
	std::cout << std::endl << std::endl;
	//User the iterator to print out the list
	PSLL<Person>::iterator psllIterFP = psll_p->begin();
	PSLL<Person>::iterator psllIterBP;
	//Test if operator= and operaotr++(int) (postincrement)
	//psllIterBP should point to the first element of the list (which is person1)
	psllIterBP = psllIterFP++;
	//Test if operator-> works (print out the fields of person1: 20 John)
	std::cout << "#### Use operator-> to print out the fields of person1: 20 John (psllIterBP points to person1) ####\n";
	std::cout << psllIterBP->age << " " << psllIterBP->name << "\n\n";
	if (psllTestP) {
		std::cout << "\n#### Pass the second test for PSLL with Person type ####\n";
	}
	else {
		std::cout << "\n#### Fail the second test for PSLL with Person type ####\n";
	}
	delete psll_p;
	//Print out asterisks to separate two tests
	std::cout << "\n\n*********************************************************************\n\n";
	std::cout << "\n#### The first test for SDAL with integer type ####\n";
	//Test SDAL with integer type
	SDAL<int> *sdallist = new SDAL<int>(3);
	//Create a sdali to test if program can pass this test
	bool sdali = true;
	//Test push_front, insert, and push_back
	sdallist->push_front(4); sdallist->push_front(2); sdallist->insert(3,1);
	sdallist->push_back(5); sdallist->insert(1,0);
	std::cout<<std::endl << "### Use print function to print out the values in the SDAL<Int>\n";
	sdallist->print(std::cout); std::cout << std::endl;
	//Test remove, pop_back, and pop_front
	sdali &= sdallist->remove(3) == 4; sdali &= sdallist->pop_back() == 5;
	sdali &= sdallist->pop_front() == 1;
	//Check length and replace
	sdali &= sdallist->length() == 2;
	sdali &= sdallist->replace(6, 0)== 2;
	sdallist->insert(1, 0);
	//Test if item_at returns by reference
	int &sdrefi = sdallist->item_at(1);
	sdali &= sdrefi == 6;
	//Update the first element in the sdallist with 8;
	sdallist->item_at(1) = 8;
	//Test if both sdrefi and the first element of sdallist holds value 8
	sdali &= sdrefi == 8;
	sdali &= sdallist->item_at(1) == 8; //The list should be: 1,8,3
    //Test if peek_back() returns by reference
	int &sdrefb = sdallist->peek_back();
	sdali &= sdrefb == 3;
	//Update the last element in the sdal with 6;
	sdallist->peek_back() = 6;
	//Test if both sdrefb and the last element of sdallist holds value 6
	sdali &= sdrefb == 6;
	sdali &= sdallist->peek_back() == 6; //The list should be: 1,8,6	
    //Test if peek_front() returns by reference
	int &sdreff = sdallist->peek_front();
	sdali &= sdreff == 1;
	//Update the first element in the sdallist with 3;
	sdallist->peek_front() = 3;
	//Test if both psreff and the first element of sdallist holds value 8
	sdali &= sdreff == 3;
	sdali &= sdallist->peek_front() == 3; //The list should be: 3,8,6
	//Test contains
	sdali &= sdallist->contains(3, equals_function);
	sdali &= !(sdallist->contains(10, equals_function));	
	//Call contents to print out the elements
	//Create a pointer to an array to test if contents function works
	int* sdallArray = sdallist->contents(); std::cout << std::endl ;
	std::cout << "#### Use contents to print out the values in the SDAL<int> list ####\n";
	for (unsigned int a = 0; a < sdallist->length(); a++) {
		std::cout << sdallArray[a] << " ";
	}
	std::cout << std::endl << std::endl;
	//Test is_empty and is_full
	sdali &= !(sdallist->is_empty());
	sdali &= !(sdallist->is_full());
	//Test iterator
	SDAL<int>::iterator sdalIterBT = sdallist->begin();
	SDAL<int>::iterator sdalIterB = sdalIterBT++;
	//sdalIterBT points to the 2nd element: 8
	sdali &= (*sdalIterBT == 8);
	SDAL<int>::iterator sdalIterE = sdallist->end();
	//Test if operator= works
	SDAL<int>::iterator sdalIterE1; sdalIterE1 = sdalIterE;
	sdali &= sdalIterE1 == sdalIterE;
	std::cout << "#### Use an iterator to print out the values in the SDAL<int> list ####\n";
	for (; sdalIterB != sdalIterE; ++sdalIterB) {
		std::cout << *sdalIterB
			<< " ";
	}std::cout << std::endl << std::endl;
	//Test if operator == works
	sdali &= sdalIterB == sdalIterE;
	//Test if the constant iterator works
	const SDAL<int>* const_sdallist = sdallist;
	SDAL<int>::const_iterator  sdalIterBC = const_sdallist->begin();
	SDAL<int>::const_iterator sdalIterEC = const_sdallist->end();
	//The output should be 3, 8, 6
	std::cout << "\n#### Use a constant iterator to print out the values in the SDAL<int> list ####\n";
	for (; sdalIterBC != sdalIterEC; ++sdalIterBC) {
		std::cout << *sdalIterBC
			<< " ";
	}std::cout << std::endl << std::endl;
	
	//The functions which check the validity of the position are: insert, replace, remove, and item_at
	try {
		//The list contains three elements, so it is impossible to insert an element at the 5th position
		sdallist->insert(5,4);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//It is impossible to get an element at 4th position
		sdallist->item_at(3);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list contains three elements, so it is impossible to replace an element at the 4th position
		sdallist->replace(9, 3);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list contains three elements, so it is impossible to remove an element at the 4th position
		sdallist->remove(3);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	std::cout << std::endl << std::endl;
	//Test if clear function works
	sdallist->clear();
	sdali &= sdallist->length() == 0; //Length should be 0
	sdali &= sdallist->is_empty(); //The list should be empty
    //The functions which check if the list is empty are: replace, remove, pop_back, pop_front, item_at, peek_back, and peek_front
	//test remove
	try {
		sdallist->remove(0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_back
	try {
		sdallist->pop_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_front
	try {
		sdallist->pop_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test replace
	try {
		sdallist->replace(1, 0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test item_at
	try {
		sdallist->item_at(0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_back
	try {
		sdallist->peek_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_front
	try {
		sdallist->peek_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	if (sdali) {
		std::cout << "\n#### Pass the first test for SDAL with Int type ####\n";
	}
	else {
		std::cout << "\n#### Fail the first test for SDAL with Int type ####\n";
	}
	delete sdallist;
	//Print out asterisks to separate two tests
	std::cout << "\n*********************************************************************\n\n\n";
	//Insert person objects into the SDAL list
	std::cout << "#### The second test for SDAL with Person object type ####\n\n";
	//psllTestP is used to test if my program passes this test (true indicates passing)
	bool sdalp = true;
	//Create a list with Person objects
	SDAL<Person> *sdal_p = new SDAL<Person>();
	//Use push_back, push_front, and insert to add Person objects to the list
	sdal_p->push_back(person2);
	sdal_p->push_front(person1);
	sdal_p->insert(person4, 1); //Right now the list should contain the fields of the following classes in the following order: person1, person4, and person2
	//Use print, contents, and iterators to print out values in the list
	std::cout << "### Use print function to print out the values in the SDAL<Person>\n";
	sdal_p->print(std::cout); std::cout << std::endl << std::endl;
	Person* sdalArrayP = sdal_p->contents();
	std::cout << "#### Use contents to print out the values in the SDAL<Person> ####\n";
	for (unsigned int a = 0; a < sdal_p->length(); a++) {
		std::cout << sdalArrayP[a] << " ";
	}
	sdalp &= sdal_p->pop_back() == (person2);
	sdalp &= sdal_p->length() == 2;
	sdalp &= !(sdal_p->is_empty());
	std::cout << std::endl << std::endl;
	//User the iterator to print out the list
	SDAL <Person>::iterator sdalIterFP = sdal_p->begin();
	SDAL<Person>::iterator sdalIterBP;
	//Test if operator= and operaotr++(int) (postincrement)
	//sdllIterBP should point to the first element of the list (which is person1)
	sdalIterBP = sdalIterFP++;
	//Test if operator-> works (print out the fields of person1: 20 John)
	std::cout << "#### Use operator-> to print out the fields of person1: 20 John (sdalIterBP points to person1) ####\n";
	std::cout << sdalIterBP->age << " " << sdalIterBP->name << "\n\n";
	if (sdalp) {
		std::cout << "\n#### Pass the second test for SDAL with Person type ####\n";
	}
	else {
		std::cout << "\n#### Fail the second test for SDAL with Person type ####\n";
	}
	delete sdal_p;
	//Print out asterisks to separate two tests
	std::cout << "\n\n*********************************************************************\n\n";
	std::cout << "\n#### The first test for CDAL with integer type ####\n";
	//Test SDAL with integer type
	CDAL<int> *cdallist = new CDAL<int>();
	//Create a sdali to test if program can pass this test
	bool cdali = true;
	//Test push_front, insert, and push_back
	cdallist->push_front(4); cdallist->push_front(2); cdallist->insert(3, 1);
	cdallist->push_back(5); cdallist->insert(1, 0); cdallist->push_front(0);
	for (int i = 6; i < 250; i++) {
		cdallist->push_back(i);
	}
	cdallist->insert(251, 68);
	cdali &= cdallist->remove(68) == 251;
	cdallist->insert(13, 149);
	cdali &= cdallist->remove(149) == 13;
	cdallist->insert(55, 0); cdali &= cdallist->remove(0) == 55;
	cdallist->insert(3, 250); cdali &= cdallist->remove(250) == 3;
	cdallist->push_front(21); cdali &= cdallist->pop_front() == 21;
	//Test remove, pop_back, and pop_front
	cdali &= cdallist->remove(0) == 0; cdali &= cdallist->pop_back() == 249;
	cdali &= cdallist->pop_front() == 1; cdali &= cdallist->remove(246) == 248;
	//Remove 240 elements
	for (int i = 245; i > 5; i--) {
		cdali &= cdallist->pop_back() == (i+2);
	}
	//Print out the result
	cdallist->print(std::cout); std::cout << std::endl;
	//Test replace
	cdali &= cdallist->replace(8, 2) == 4;
	//Test if item_at returns by reference
	int &cdrefi = cdallist->item_at(1);
	cdali &= cdrefi == 3;
	//Update the first element in the cdallist with 2;
	cdallist->item_at(1) = 2;
	//Test if both cdrefi and the second element of cdallist holds value 2
	cdali &= cdrefi == 2;
	cdali &= cdallist->item_at(1) == 2; //The list should be: 2,2,8,5,6,7
	//Test if peek_back() returns by reference
	int &cdrefb = cdallist->peek_back();
	cdali &= cdrefb == 7;
	//Update the last element in the cdal with 9;
	cdallist->peek_back() = 9;
	//Test if both cdrefb and the last element of cdallist holds value 9
	cdali &= cdrefb == 9;
	cdali &= cdallist->peek_back() == 9; //The list should be: 2,2,8,5,6,9	
    //Test if peek_front() returns by reference
	int &cdreff = cdallist->peek_front();
	cdali &= cdreff == 2;
	//Update the first element in the cdallist with 1;
	cdallist->peek_front() = 1;
	//Test if both psreff and the first element of sdallist holds value 1
	cdali &= cdreff == 1;
	cdali &= cdallist->peek_front() == 1; //The list should be: 1,2,8,5,6,9
	//Test contains
	cdali &= cdallist->contains(2, equals_function);
	cdali &= !(cdallist->contains(10, equals_function));
	cdali &= !(cdallist->is_empty()); cdali &= !(cdallist->is_full());
	cdali &= cdallist->length() == 6;
	//Create a pointer to an array to test if contents function works
	int* cdallArray = cdallist->contents(); std::cout << std::endl;
	std::cout << "#### Use contents to print out the values in the CDAL<int> list ####\n";
	for (unsigned int a = 0; a < cdallist->length(); a++) {
		std::cout << cdallArray[a] << " ";
	}
	std::cout << std::endl << std::endl;
	//Test iterator
	CDAL<int>::iterator cdalIterBT = cdallist->begin();
	CDAL<int>::iterator cdalIterB = cdalIterBT++;
	//cdalIterBT points to the 2nd element: 2
	cdali &= (*cdalIterBT == 2);
	CDAL<int>::iterator cdalIterE = cdallist->end();
	//Test if operator= works
	CDAL<int>::iterator cdalIterE1; cdalIterE1 = cdalIterE;
	cdali &= cdalIterE1 == cdalIterE;
	std::cout << "#### Use an iterator to print out the values in the CDAL<int> list ####\n";
	for (; cdalIterB != cdalIterE; ++cdalIterB) {
		std::cout << *cdalIterB
			<< " ";
	}std::cout << std::endl << std::endl;
	//Test if operator == works
	cdali &= cdalIterB == cdalIterE;
	//Test if the constant iterator works
	const CDAL<int>* const_cdallist = cdallist;
	CDAL<int>::const_iterator  cdalIterBC = const_cdallist->begin();
	CDAL<int>::const_iterator cdalIterEC = const_cdallist->end();
	//The output should be 1, 2, 8, 5, 6, 9
	std::cout << "\n#### Use a constant iterator to print out the values in the CDAL<int> list ####\n";
	for (; cdalIterBC != cdalIterEC; ++cdalIterBC) {
		std::cout << *cdalIterBC
			<< " ";
	}std::cout << std::endl << std::endl;

	//The functions which check the validity of the position are: insert, replace, remove, and item_at
	try {
		//The list contains five elements, so it is impossible to insert an element at the 7th position
		cdallist->insert(5, 7);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//It is impossible to get an element at 7th position
		cdallist->item_at(6);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what(); 
	}
	try {
		//The list contains six elements, so it is impossible to replace an element at the 7th position
		cdallist->replace(9, 6);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	try {
		//The list contains six elements, so it is impossible to remove an element at the 7th position
		cdallist->remove(6);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	std::cout << std::endl << std::endl;
	//Test if clear function works
	cdallist->clear();
	cdali &= cdallist->length() == 0; //Length should be 0
	cdali &= cdallist->is_empty(); //The list should be empty
    //The functions which check if the list is empty are: replace, remove, pop_back, pop_front, item_at, peek_back, and peek_front
    //test remove
	try {
		cdallist->remove(0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_back
	try {
		cdallist->pop_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test pop_front
	try {
		cdallist->pop_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test replace
	try {
		cdallist->replace(1, 0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test item_at
	try {
		cdallist->item_at(0);
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_back
	try {
		cdallist->peek_back();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	//test peek_front
	try {
		cdallist->peek_front();
	}
	catch (std::runtime_error const & d) {
		std::cout << d.what();
	}
	if (cdali) {
		std::cout << "\n#### Pass the first test for CDAL with integer type ####\n";
	}
	else {
		std::cout << "\n#### Fail the first test for CDAL with integer type ####\n";
	}
	delete cdallist;
	//Print out asterisks to separate two tests
	std::cout << "\n*********************************************************************\n\n\n";
	//Insert person objects into the SDAL list
	std::cout << "#### The second test for CDAL with Person object type ####\n\n";
	//psllTestP is used to test if my program passes this test (true indicates passing)
	bool cdalp = true;
	//Create a list with Person objects
	CDAL<Person> *cdal_p = new CDAL<Person>();
	//Use push_back, push_front, and insert to add Person objects to the list
	cdal_p->push_back(person2);
	cdal_p->push_front(person1);
	cdal_p->insert(person4, 1); //Right now the list should contain the fields of the following classes in the following order: person1, person4, and person2
	//Use print, contents, and iterators to print out values in the list
	std::cout << "### Use print function to print out the values in the CDAL<Person>\n";
	cdal_p->print(std::cout); std::cout << std::endl << std::endl;
	Person* cdalArrayP = cdal_p->contents();
	std::cout << "#### Use contents to print out the values in the CDAL<Person> ####\n";
	for (unsigned int a = 0; a < cdal_p->length(); a++) {
		std::cout << cdalArrayP[a] << " ";
	}
	cdalp &= cdal_p->pop_back() == (person2);
	cdalp &= cdal_p->length() == 2;
	cdalp &= !(cdal_p->is_empty());
	std::cout << std::endl << std::endl;
	//User the iterator to print out the list
	CDAL <Person>::iterator cdalIterFP = cdal_p->begin();
	CDAL<Person>::iterator cdalIterBP;
	//Test if operator= and operaotr++(int) (postincrement)
	//cdllIterBP should point to the first element of the list (which is person1)
	cdalIterBP = cdalIterFP++;
	//Test if operator-> works (print out the fields of person1: 20 John)
	std::cout << "#### Use operator-> to print out the fields of person1: 20 John (cdalIterBP points to person1) ####\n";
	std::cout << cdalIterBP->age << " " << cdalIterBP->name << "\n\n";
	if (cdalp) {
		std::cout << "\n#### Pass the second test for CDAL with Person type ####\n";
	}
	else {
		std::cout << "\n#### Fail the second test for CDAL with Person type ####\n";
	}
	delete cdal_p;
	CBL<char> *list = new CBL<char>();
	list->insert('A', 0);
	list->insert('B', 1);
	list->push_back('C');
	list->push_front('D');
	list->insert('E', 2);
	list->insert('F', 5);
	//Test iterator
	CBL<char>::iterator i = list->begin();
	CBL<char>::iterator e = list->end();
	std::cout << "#### Use an iterator to print out the values in the CBL<char> list ####\n";
	for (; i != e; ++i) {
		std::cout << *i
			<< " ";
	}std::cout << std::endl << std::endl;
return 0;
}

	
