# QuickSort

自己写的一个可以排序任何集合的快速排序算法，使用了C++类模板

```c++
#pragma once
#include<vector>
#include<iostream>

namespace QuickSort {
	
	template<typename T>
	void quickSortR(std::vector<T>& v, int begin, int end, bool compare(const T& a, const T& b)) {
		if (end - begin > 0) {
			int left = begin;
			int right = end;
			T pivot = v[begin];
			while (left < right) {
				while (left < right && !compare(v[right], pivot)) {
					right--;
				}
				if (left < right) {
					v[left++] = v[right];
				}
				while (left < right && compare(v[left], pivot)) {
					left++;
				}
				if (left < right) {
					v[right--] = v[left];
				}
			}
			v[left] = pivot;
			quickSortR(v, begin, left - 1, compare);
			quickSortR(v, left + 1, end, compare);
		}
	}
	
	template <typename T>
	void sort(std::vector<T>& v, bool compare(const T& a, const T& b)) {
		quickSortR(v, 0, v.size() - 1, compare);
	}
	
	
	template <typename T> 
	void print(const std::vector<T>& v) {
		typedef typename std::vector<T>::size_type size_type;
		std::cout << "[" << std::endl;
		for (size_type i = 0; i < v.size(); i++) {
			std::cout << v[i];
			if (i < v.size() - 1) {
				std::cout << " ";
			}
		}
		
		std::cout << std::endl << "]";
	}
};
```

用法案例：

`Person.h`

```c++
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



```



```c++
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
```

