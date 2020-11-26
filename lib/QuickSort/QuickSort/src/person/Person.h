#pragma once
#include<string>
#include<iostream>
class Person
{
public:
	Person(std::string name, int age);
	~Person();
	std::string name;
	int age;
	bool operator==(const Person p);
private:
	
};

std::ostream& operator<<(std::ostream& os, const Person& p);

