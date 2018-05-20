#ifndef _PERSON_H_
#define _PERSON_H_
#include <stdexcept>
#include <string>
#include<iostream>
class Person {
public: 
	int age = 0;
	std::string name = " ";
	friend std::ostream& operator << (std::ostream& os, const Person& per);
	Person(int, std::string);
	Person(const Person& p);
	bool compare(Person const& ppl) const;
	bool operator == (Person const& p) const;
	void setAge(int a);
};
std::ostream& operator <<(std::ostream& os, const Person& per) {
	os << per.age << " " << per.name;
	return os;
}

Person::Person (int ages = 0, std::string names = " "){
	age = ages;
	name = names;
}
Person::Person(const Person& p) {
	age = p.age;
	std::string newname (p.name);
	name = newname;
}
void Person:: setAge(int a) {
	age = a;
}
bool Person::compare(Person const& ppl) const {
	return (ppl.age == age && ppl.name == name);
}
bool Person::operator == (Person const& p) const {
	return Person::compare(p);
}
#endif