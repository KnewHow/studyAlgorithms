# SuperSet

传统的C++的`set`、`unordered_set` 只能存放一些基本类型，如果要存放例如`std::unordered_set<std::vector<int>>` 这样的类型就有些犯难，今天我们就来研究一些如果写一个可以粗放高等类型的set

```c++
#pragma once
#include<unordered_set>
#include<vector>

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

using MySet = std::unordered_set<std::vector<int>, VectorHash>;
```

我们实现其Hash算法即可