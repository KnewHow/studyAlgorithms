# First Missing Positive

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

```Input: [1,2,0]
Input: [1,2,0]
Output: 3
```

Example 2:

```
Input: [3,4,-1,1]
Output: 2
```

Example 3:

```
Input: [7,8,9,11,12]
Output: 1
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/first-missing-positive
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一:先排序,再逐个查找

我们先将原数组排序，然后找出第一个 > 1 的数的角标`begin`,将它和`1` 比较，如果 `arr[begin] > 1` 返回 `1`,否则说明`arr[begin]==1`执行如下的循环：

```c
int counter = 1;
for(int i=begin; i < size; i++) {
    if(arr[i] == counter) { 
        // 每次让 counter 自增，如果 arr[i] > counter，说明中间有个最小正整数被遗漏
        counter++;
    } else {
        if(arr[i] > counter) { 
            return counter
        } else {
            // 如果 出现 arr[i] < counter,表示 arr[i] 和 arr[i-1] 出现重复，此时我们保持counter 不变，i 自增
        }
    }
}

// 如果循环结束依旧没有返回，说明arr[begin] ~ arr[size-1] 为连续正整数，此时返回 arr[size-1] + 1
```

排序的时间复杂度为`O(NlogN)`,然后遍历一遍数组的耗费`O(N)`,因此总得时间复杂度为`Nlog(N)`,还是达不到题目要求的 `O(N)`的复杂度。

具体的代码如下：

```c
void swap(int* arr, int index1, int index2) {
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}

void quickSortR(int* arr, int begin, int end) {
	if (end - begin > 0) {
		int left = begin;
		int right = end;
		int pivot = *(arr + begin);
		while (left < right) {
			while (left < right && *(arr + right) >= pivot) {
				right--;
			}

			while (left < right && *(arr + left) <= pivot) {
				left++;
			}
			swap(arr, left, right);
		}
		swap(arr, begin, left);
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, left + 1, end);
	}
}

void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

int firstMissingPositive(int* nums, int numsSize) {
	quickSort(nums, numsSize);
	int begin = 0;
	while (begin < numsSize) {
		if (*(nums + begin) < 1) {
			begin++;
		}
		else {
			break;
		}
	}
	if (begin == numsSize) { // 全部为负数
		return 1;
	}
	else {
		int counter = 1;
		for (int i = begin; i < numsSize; i++) {
			// 每次让 counter 自增，如果 arr[i] > counter，
			// 说明中间有个最小正整数被遗漏
			if (*(nums + i) == counter) {
				counter++;
			}
			else {
				if (*(nums + i) > counter) {
					return counter;
				}
				/*如果 出现 arr[i] < counter,
				表示 arr[i] 和 arr[i-1] 出现重复，
				此时我们保持counter 不变，i 自增 */
			}
		}
		/* 如果循环结束依旧没有返回，
		说明arr[begin] ~ arr[size-1] 为连续正整数，
		此时返回 arr[size-1] + 1 */
		return *(nums + numsSize - 1) + 1;
	}
}
```

通过所有测试用例需要 **4ms**,击败了"77%"的用户，看来性能不错啊！



## 解法二

通过上面的解题方案，我们发现这道题目实际上就是求数组中所有正整数项与`1`的差是否在正整数集中连续，如果连续，则返回 max+1,否则就返回其间断点的值。

由于题目给定的是n个元素，那么如果数组中有元素的值大于n,则必然存在一个间断点在1 ~ n 之间，我们可以将大于 n 的数忽略掉。

下面给出时间复杂度为`O(N)`的代码

```c
/**
* 对于 n 个数来说，如果他是从 1~ n 的，说明他不缺失，如果他有任意一个数
* 超过了 n, 说明他在 1~n 之内，肯定有缺失，因此下面程序中的 max 最大值为 n
*/
int firstMissingPositive2(int* nums, int numsSize) {
	int max = INT_MIN;
	for (int i = 0; i < numsSize; i++) {
		if (*(nums + i) > max) {
			max = *(nums + i);
		}
	}

	// 如果最大值超过 n,则在 1 ~ n 之间肯定有间断点，我们不需要再去考虑比 n 大的数
	if (max > numsSize) {
		max = numsSize;
	}

	if (max < 1) { // 所有的数都是小于 1，直接返回1
		return 1;
	}
	else {
		// 使用一个数组，来标记 nums[i] - 1 的值 
		int* arr = (int*)malloc(sizeof(int) * max);
		for (int i = 0; i < max; i++) {
			*(arr + i) = 0;
		}
		for (int i = 0; i < numsSize; i++) {
			int value = *(nums + i);
			// 只考虑 1~n 之间的数
			if (value >= 1 && value <= numsSize) {
				// 对于出现 nums[i]-1 的标记为 1
				int index = value - 1;
				*(arr + index) = 1;
			}
		}
		for (int i = 0; i < max; i++) {
			// 表示 arr[j] - 1 = i 数没有出现，在 i+1 出现间断点
			if (*(arr + i) == 0) {
				return i+1;
			}
		}
		// 所有值都存在，返回 max + 1
		return max+1; 
	}
}
```

