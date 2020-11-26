#include<vector>
#include "QuickSort.h"
#include "person/Person.h"


int main() {
	std::vector<int> nums = { 2,0,2,1,1,0 };
	std::vector<Person> persons = {
		Person("KnewHow",25),
		Person("How",23)
	};
	QuickSort::sort<Person>(
		persons, 
		[](const Person& a, const Person& b)->bool {return a.age < b.age;}
	);
	// quickSort(nums);
	QuickSort::print(persons);
	// std::cout << persons[0];
	std::cin.get();
}