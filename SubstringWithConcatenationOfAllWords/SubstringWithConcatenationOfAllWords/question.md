# Substring with Concatenation of All Words

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

 

Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input:
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
Output: []

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一：暴力法

暴力法，找 s 中长度为所有 words 长度之和的子串，然后测试每个子串是否满足。

```java
public List<Integer> findSubstring(String s, String[] words) {
		List<Integer> r = new ArrayList<Integer>();
		if(s.isEmpty() || words.length == 0) {
			return r;
		} else {
			HashMap<String, Integer> standard = new HashMap<String, Integer>();
			for(String word: words) {
				standard.put(word, standard.getOrDefault(word, 0) + 1);
			}
			int sLength = s.length();
			int wordLength = words[0].length();
			int wordsSum = words.length;
			int totalLength = wordLength * wordsSum;
			for(int i = 0; i < sLength - totalLength +1; i++) {
				int counter = 0;
				HashMap<String, Integer> map = new HashMap<String, Integer>();
				while(counter < wordsSum) {
					// 判断子串是否满足条件
					String word = s.substring(
							i + counter * wordLength, i + (counter + 1) * wordLength);
					if(standard.containsKey(word)) {
						counter++;
						map.put(word, map.getOrDefault(word, 0) + 1);
					} else {
						break;
					}
				}
				if(map.equals(standard)) {
					r.add(i);
				}
			}
		}
	
		return r;
    }
```



## 解法二：双指针法

上面的方法可以优化，我们不需要全部扫描 s 的子串，我们可以使用两个指针 left 和 right，分别记录开始的 index 和 当前的 index， 如果元素有重复，我们让 left 移动一个 word 长度，并将 left ~ left + wordLength 的单词舍弃，直到当前 word 的数量和规定的一样。这样就可以利用之前的结果。

```java
public List<Integer> findSubstring2(String s, String[] words) {
		List<Integer> r = new ArrayList<Integer>();
		if(s.isEmpty() || words.length == 0) {
			return r;
		} else {
			HashMap<String, Integer> standard = new HashMap<String, Integer>();
			for(String word: words) {
				standard.put(word, standard.getOrDefault(word, 0) + 1);
			}
			int sLength = s.length();
			int wordLength = words[0].length();
			int wordsSum = words.length;
			// 这里的 for 循环是为了避免前面有非 wordLength 整数倍字符串而导致正好将匹配完全错开
			for(int i = 0; i < wordLength;i++) {
				int left = i;
				int right = i;
				int counter = 0;
				HashMap<String, Integer> map = new HashMap<String, Integer>();
				while(right + wordLength <= sLength) {
					String word = s.substring(right, right + wordLength);
					map.put(word, map.getOrDefault(word, 0) + 1);
					right += wordLength;
					if(standard.containsKey(word)) {
						counter++;
						// 如果当前 word 超出规定，就慢慢的将 left 往 right 方向移动，直到 word 符合规定
						while(map.getOrDefault(word, 0) > standard.getOrDefault(word, 0)) {
							String tempWord = s.substring(left, left+wordLength);
							map.put(tempWord, map.getOrDefault(tempWord, 0) - 1);
							counter--;
							left = left + wordLength;
						}
					} else {
						// 如果 word 不再给定的 word 内，直接从 right 重新开始
						left = right;
						map.clear();
						counter = 0;
					}
					if(counter == wordsSum) {
						r.add(left);
					}
				}
			}
		}
		return r;
    }
```

