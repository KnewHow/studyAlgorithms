#include "Person.h"


Person::Person(std::string name, int age)
	:name(name), age(age)
{

}

Person::~Person()
{
	
}

bool Person::operator==(const Person p)
{
	return name == p.name && age == p.age;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	return os << "Name: " << p.name << ", Age: " << p.age << "." << std::endl;
}


