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