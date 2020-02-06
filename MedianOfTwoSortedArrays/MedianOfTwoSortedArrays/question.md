# sQuestion

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Answer

## 解法一：先合并，在取值

直接将两个数组按顺序合并，然后取其中位数，奇数取 `length / 2`，偶数取`length / 2 - 1`和`length / 2`，总的时间复杂度为`O(max(m,n))`,这个虽然达不到题目要求的`Log(m+n)`，但是我已经已经比较满意了，代码如下：

```c
double findMedianSortedArraysWithMerge(
	int* nums1, 
	int nums1Size, 
	int* nums2, 
	int nums2Size) {
	int total = nums1Size + nums2Size;
	// 申请内存，存放合并后的新数组
	int* arr = (int*)(malloc(total * sizeof(int)));
	int i = 0;
	int j = 0;
	int index = 0;
	// 合并操作
	while (i < nums1Size || j < nums2Size) {
		if (i < nums1Size && j < nums2Size) {
			if (nums1[i] < nums2[j]) {
				arr[index] = nums1[i];
				i++;
			}
			else {
				arr[index] = nums2[j];
				j++;
			}
		}
		else if (i < nums1Size) {
			arr[index] = nums1[i];
			i++;
		}
		else {
			arr[index] = nums2[j];
			j++;
		}
		index++;
	}
	// 根据总元素个数的奇和偶来求取中位数
	if (total % 2 == 0) {
		int mid1 = total / 2 - 1;
		int mid2 = total / 2;
		return (arr[mid1] + arr[mid2]) / 2.0;
	}
	else {
		int mid = total / 2;
		return arr[mid] * 1.0;
	}
}
```



## 解法二：把求中位数转换为求第 kth 小的元素

参考网上的解题思路，求一个有序数组的中位数等价于求这个数组中第 kth 小的元素。如果总长度是奇数,则求第`(m + n) / 2`小的数，如果为偶数，则求第`(m + n) / 2 - 1` 小 和 第`(m + n) / 2 `小的平均数。

那么现在的问题变成如何求解两个有序数组的第 kth 小数，如果我们从 1~m 开始遍历，那么还是需要 `O(max(m + n))`的时间复杂度，能不能更快一些？

网上有有一种二分求解法，他的思路如下：

我们可以先比较 `A[kth / 2]` 和 `B[kth / 2]`的大小，如果 `A[kth / 2] =< B[kth / 2]`，则 我们可以将 `A[begin]~A[kth / 2-1]`这些元素排除掉，为什么？

因为 `B[kth / 2]`  >= `A[kth /2]`,则 `B[kth / 2]` 小的元素有`A`中的`kth / 2- 1` 和 B 中的 `kth / 2 -1`，共有`k-2`个，所有 `B[kth / 2]` 最多是第`k-1`位小数，比`B[kth / 2]`还小的数自然要排除掉。

具体的演示可以参考[根据 kth求解——解法三](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-2/)，里面有对应的图例演示，这里我就不画了，直接贴代码吧：

```c
int getMin(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

/** 获取两个有序数组中第 k 小的数
* @param b1 第一个有序数组的起始元素地址
* @param e1 第一个有序数组的终止元素地址
* @param b2 第二个有序数组的起始元素地址
* @param e2 第二个有序数组的终止元素地址
* 若数组为空，请将 b 和 e 都置为 NULL
* @param kths 第 k 小的数,k 从 1 开始
* @return 返回第 k 小的数
*/
int getKthMin(
	int* b1,
	int* e1,
	int* b2,
	int* e2,
	int kths) {
	// kths 为 1，表示找最小的元素，直接在 b1 和 b2 中找最小的元素即可
	if (kths == 1) {
		if (b1 != NULL && b2 != NULL) {
			return getMin(*b1, *b2);
		}
		else if (b1 == NULL) {
			return *b2;
		}
		else {
			return *b1;
		}
	}
	else {
		if (b1 != NULL && b2 != NULL) {
			int mid = kths / 2 - 1;
			int midV1 = 0;
			int midV2 = 0;
			// 如果 mid 已经越界，直接拿 e1 的值
			if (b1 + mid > e1) {
				midV1 = *e1;
			}
			else {
				midV1 = *(b1 + mid);
			}

			// get b mid value
			if (b2 + mid > e2) {
				midV2 = *e2;
			}
			else {
				midV2 = *(b2 + mid);
			}

			if (midV1 >= midV2) {
				// 将 b2 ~ mid 截取
				int *newB2 = NULL;
				int discardNumber = mid + 1;
				if (e2 - b2 < mid + 1) { // 如果 mid 越界，直接将 b2 置为 NULL
					newB2 = NULL;
					discardNumber = (e2 - b2) + 1;
				}
				else {
					newB2 = b2 + mid + 1;
				}
				return getKthMin(b1, e1, newB2, e2, kths - discardNumber);
			}
			else {
				// 将 b1 ~ mid 截取
				int *newB1 = NULL;
				int discardNumber = mid + 1;
				if (e1 - b1 < mid + 1) { // 如果 b1 越界，直接将 b1 置为 NULL
					newB1 = NULL;
					discardNumber = (e1 - b1) + 1;
				}
				else {
					newB1 = b1 + mid + 1;
				}
				return getKthMin(newB1, e1, b2, e2, kths - discardNumber);
			}
		}
		else if (b1 == NULL) {
			return *(b2 + kths - 1);
		}
		else {
			return *(b1 + kths - 1);
		}
	}

}

// 测试获取第 k 小元素的值
void getKthMinSpec() {
	int arr1[] = { 1,3,4,9 };
	int arr2[] = { 1,2,3,4,5,6,7,8,9,10 };
	int arr1Size = (sizeof(arr1) / sizeof(int));
	int arr2Size = (sizeof(arr2) / sizeof(int));
	int kths = 7;
	int r = getKthMin(arr1, arr1 + arr1Size - 1, arr2, arr2 + arr2Size - 1, kths);
	printf("%d ths is %d", kths, r);
}
```

上面的代码是求两个有序数组中第 kth 小元素的值，由于每次都会将 `kth / 2` 个元素排除，所以时间复制度为 `O(Log(m + n))`

下面是解题的代码：

```c
double findMedianSortedArraysWithKthMin(
	int* nums1,
	int nums1Size,
	int* nums2,
	int nums2Size) {
	int* b1 = NULL;
	int* e1 = NULL;
	int* b2 = NULL;
	int* e2 = NULL;
    // 对于元素非空的数组指针赋值，否则让其 begin 和 end 都为 NULL
	if (nums1Size > 0) {
		b1 = nums1;
		e1 = nums1 + nums1Size - 1;
	}
	if (nums2Size > 0) {
		b2 = nums2;
		e2 = nums2 + nums2Size - 1;
	}
	int total = (nums1Size + nums2Size);
	if (total % 2 == 0) {
		int mid1 = total / 2;
		int mid2 = total / 2 + 1;
		int r1 = getKthMin(b1, e1, b2, e2, mid1);
		int r2 = getKthMin(b1, e1, b2, e2, mid2);
		return (r1 + r2) / 2.0;
	}
	else {s
		int mid = total / 2 + 1;
		int r = getKthMin(b1, e1, b2, e2, mid);
		return r * 1.0;
	}
}
```

