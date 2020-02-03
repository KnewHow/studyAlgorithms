# question
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

Tips1:
A really brute force way would be to search for all possible pairs of numbers but that would be too slow. Again, 
it's best to try out brute force solutions for just for completeness. It is from these brute force solutions that 
you can come up with optimizations.

Tips2��
So, if we fix one of the numbers, say
x
, we have to scan the entire array to find the next number
y
which is
value - x
where value is the input parameter. Can we change our array somehow so that this search becomes faster?

Tip3:
The second train of thought is, without changing the array, can we use additional space somehow? Like maybe a hash map
to speed up the search?

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/two-sum
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������

# answer
���������⣬��ʾ�Ѿ�˵�ĺ������ˣ����Ǳ���һ�θ��������飬����������`i`��Ԫ�ص�ʱ��������Ҫ����`target-nums[i]`��λ�á���ô�����Ŀ�ͱ���������������һ��Ԫ�ص����⡣

## �ⷨһ����������

���ǵ�Ȼ�����ȱ���һ�����飬����������`i`��Ԫ�ص�ʱ������ʹ����һ��`for`ѭ�����������ԭ���飬�ҳ�`target-nums[i]` ,���������㷨Ч�ʲ��ߣ�ʱ�临�Ӷ�ΪO(N^2)

```c
int* twoSumFource(int* nums, int numsSize, int target, int* returnSize) {
	for (int* x = nums; x < nums + numsSize; x++) {
		int y = target - *x;
		for (int* p = nums; p < nums + numsSize; p++) {
			if ((x - nums) == (p - nums)) { // ������ĿҪ���������ֲ�����ͬһ������
				continue;
			}
			else
			{
				if (*p == y) {
					int* r = (int*)malloc(2 * sizeof(int));
					if (r != NULL) {
						r[0] = (x - nums);
						r[1] = (p - nums);
						*returnSize = 2;
						return r;
					}
					else
					{
						return NULL;
					}

				}
			}
		}
	}
	return NULL;
}
```



## �ⷨ����������Ȼ��Ȼ��ʹ�ö��ֲ���

��ĿҪ�����Ƿ���Ԫ�ص�ԭ����Ǳ꣬էһ���������ƺ����ܶ�ԭ�������������Ϊ�����ı������λ�á��������ǿ��Ը���һ��ԭ���飬Ȼ��������������ź����������ʹ�ö��ֲ����Ų���`target-num[i]`,Ȼ����ԭ�����в��Ҹ�Ԫ�ص�ԭʼ�Ǳꡣ

����һ���µĶ���������Ҫ`O(N)`��ʱ�䣬ʹ�ÿ��������㷨����һ��������Ҫ`O(NlgN)`������һ������Ȼ��Ȼ��ʹ�ö��ֲ��Ҳ�������Ԫ����Ҫ`O(N * lnN)`,�����ܵ�ʱ�临�Ӷ�Ϊ��`O(NlgN)`

```c
// ��������-����copy
int* copyArray(int* nums, int numsSize) {
	int* p = NULL;
	p = (int*)malloc(numsSize * sizeof(int));
	if (p != NULL) {
		for (int* i = nums; i < nums + numsSize; i++) {
			p[i - nums] = *i;
		}
		return p;
	}
	else
	{
		return NULL;
	}
}

// ��������-��������
void quickSort(int* nums, int left, int right) {
	if (right - left > 1) {
		int pivod = nums[left];
		int i = left;
		int j = right;
		while (i < j) {
			while (nums[j] >= pivod && i < j) {
				j--;
			}
			while (nums[i] <= pivod && i < j) {
				i++;
			}
			int temp = nums[i];
			nums[i] = nums[j];
			nums[j] = temp;
		}
		int temp = nums[left];
		nums[left] = nums[i];
		nums[i] = temp;
		quickSort(nums, left, i - 1);
		quickSort(nums, j + 1, right);
	}
}

// ��������-���ֲ���
int binarySearch(int* nums, int numsSize, int target) {
	int isFound = 1;
	int left = 0;
	int right = numsSize - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (nums[mid] == target) {
			return mid;
		}
		else if (nums[mid] > target) {
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
   int* p = NULL;
	p = copyArray(nums, numsSize);
	if (p != NULL) {
		quickSort(p, 0, numsSize - 1);
		for (int* x = nums; x < nums + numsSize; x++) {
			int y = target - *x;
			int index = binarySearch(p, numsSize, y);
			if (index != -1) { // �ҵ���
				int value = p[index];
				// ����ԭ���飬����ԭ�Ǳ�
				for (int i = 0; i < numsSize; i++) {
					// ��ĿҪ���������ֵĽǱ겻���ظ�����˶��ֲ��ҵ�Ԫ�صĽǱ겻����x�ĽǱ�һ��
					if (nums[i] == value && i != (x - nums)) {
						// �ɹ��ҵ�Ԫ��
						free(p);
						int* r = (int*)malloc(2 * sizeof(int));
						if (r != NULL) {
							r[0] = (x - nums);
							r[1] = i;
							*returnSize = 2;
							return r;
						}
					}
				}
			}
		}
		free(p);
		return NULL;
	}
	else
	{
		return NULL;
	}
}
```

## �ⷨ������������������

��Ȼ�ǲ��ң�����������Ȼ��ʹ�ö��ֲ������⣬���ǻ�����ֱ�ӹ���һ��AVL(�����)�������ҡ�����AVL����ʱ�临�Ӷ�ΪO(NlgN)���������ҵ�ʱ�临�Ӷ�Ϊ��O(NlgN)���ܵ�ʱ�临�Ӷ�Ϊ��O(Nlgn)



## �ⷨ�ģ�����ɢ�б�Hash Table��ʵ�ֽ���O(n)���㷨

��Ȼ�ǲ��ң����ǿ���ʹ��ɢ�б�����ÿ�β��ҵ�Ч�ʾ�λO(1),��ô�������ҵ�ʱ�临�ӶȾ�λO(n).��������ι���ɢ�б��أ�����ѧJava��С�����˵��`HashMap`����һ����Ȼ��ɢ�б�������ѧ`C`��ͬѧ��˵�����ܾ͵�ȥ���ϲ�鰸�����Լ�д�ˣ����ǣ���Ȼ��ѧ�㷨���Լ�дһ��������ء�