## 一、实验目的：

（1）掌握回溯法算法设计思想
（2）掌握地图填色问题的回溯法解法

## 二、实验内容

我们可以将地图转换为平面图，每个地区变成一个节点，相邻地区用边连接，我们要为这个图形的顶点着色，并且两个顶点通过边连接时必须具有不同的颜色。附件是给出的地图数据，请针对三个地图数据尝试分别使用 5 个（le450_5a），15 个（le450_15b），25 个（le450_25a）颜色为地图着色。

## 三、实验内容及过程

### 问题建模

这是一个图论模型，所以考虑对一个地图抽象成一张图。其中的点表示地图中的区域，边表示两块区域相邻。

那么原问题就转化成了：构造一个数组 $col$ 满足对任意一条边 $(u, v)$ 满足 $col(u) \neq col(v)$。

### 算法设计

#### 朴素的暴力

由于是需要构造一个数组，并且值域为 $[1, count]$，那么不妨考虑如果枚举所有的数组，显然可以想到有这样的算法。

```cpp
// dfs(i) 表示正在处理数组的第 i 个元素
def dfs(int i) -> void {
    // 处理第 n + 1 个元素表示已经完成了数组的构造
    if (i == n + 1) {
        // 如果数组通过了检测，那么方案数+1
        if (check(col)) {
            ans <- ans + 1
        }
        return;
    }
    // 枚举数组第 i 个元素的值（颜色）
    for c in [1, count] {
        col[i] <- c;
        dfs(i + 1);
    }
}
```

这个算法的时间复杂度是稳定的 $O(count^n)$，也就是所有涂色方案（包括不可行）的方案数。

#### 可行性剪枝

注意到朴素算法的求解过程中，需要完成数组的构造才测试数组的可行性。但是事实上，可以在每次涂色完成后，都检测一次新填入的颜色是否可行，如果不可行就不需要再继续后面的搜索了。

```cpp
def dfs(int i) -> void {
    if (i == n + 1) {
        ans <- ans + 1;
        return;
    }
    for c in [1, count] {
        // 如果当且点颜色为 c 的时候不合法，那么直接跳过后续的搜索。
        if (check(i, c) == false) {
            continue;
        }
        col[i] <- c;
        dfs(i + 1);
    }
}
```

#### 基于度数优化

上面的算法都没有考虑到图的结构来进行优化，也就是无论图的结构如何都是从第一个点开始构造数组的，那么可以考虑根据图的结构来进行优化。

如果一个点的度数比较大，说明它存在更多的约束限制。所以让度数更大的点优先构造，可以让问题尽早地暴露，从而使可行性剪枝发挥更大的效果。

```cpp
// 先预处理得到处理点的顺序
vertex = [1, 2, ..., n];
sort(vertex, by_degree);

def dfs(int i) -> void {
    if (i == n + 1) {
        ans <- ans + 1;
        return;
    }
    // 表示当前填第 i 个点 vertex[i] 的颜色
    u = vertex[i]
    for c in [1, count] {
        if (check(u, c) == false) {
            continue;
        }
        col[u] <- c;
        dfs(i + 1);
    }
}
```

#### 向前探测法

可以发现，填完点 $u$ 的颜色之后，所有与 $u$ 相邻的点 $v$ 的颜色选择数量全部都会减少一种。按照上面的解法，如果 $v$ 已经没有颜色可涂了，需要等到给 $v$ 涂色的时候才能发现。

那么考虑在给 $u$ 涂色的时候，向前一步测试 $v$ 的可选颜色数量。如果发现 $v$ 已经没有颜色可以选择了，那么说明 $u$ 不能选择这种颜色。

```cpp
vertex = [1, 2, ..., n];
sort(vertex, by_degree);

def check(int u, int c) -> bool {
    for v in adjacent_vertex_of_u {
        if (c == col[v]) return false;
        if ((color_set(v) - {c}) is empty) return false;
    }
    return true;
}

def dfs(int i) -> void {
    if (i == n + 1) {
        ans <- ans + 1;
        return;
    }
    // 表示当前填第 i 个点 vertex[i] 的颜色
    u = vertex[i]
    for c in [1, count] {
        if (check(u, c) == false) {
            continue;
        }
        col[u] <- c;
        dfs(i + 1);
    }
}
```

#### 另外一种处理涂色顺序的方式

之前是按照度数的顺序来填涂颜色，现在考虑另外一种处理颜色顺序的方式：每次选择未选择的点中，可选择颜色数量更小的点。这和按度数顺序处理是类似的原理，都是优先给最容易出问题点填涂颜色。

虽然优先考虑可填涂颜色最少的点，但是依旧可以加上按度数排序的优化，把它作为第二关键字即可。

```cpp
vertex = [1, 2, ..., n];
sort(vertex, by_degree);

def check(int u, int c) -> bool {
    for v in adjacent_vertex_of_u {
        if (c == col[v]) return false;
        if ((color_set(v) - {c}) is empty) return false;
    }
    return true;
}

def dfs(int i) -> void {
    if (i == n + 1) {
        ans <- ans + 1;
        return;
    }
    u = find_vertex();
    for c in [1, count] {
        if (check(u, c) == false) {
            continue;
        }
        col[u] <- c;
        dfs(i + 1);
    }
}
```

#### 基于对称性的优化

注意到一个点具体涂什么颜色是不重要的，重要的是相对于其他点不同。更具体地，第一个点填任意一种颜色，对应的方案数都是一样的。那么我们可以固定第一个点的颜色选择，在最后统计方案的时候，乘上本次涂色使用的颜色数量即可。

```cpp
vertex = [1, 2, ..., n];
sort(vertex, by_degree);

def check(int u, int c) -> bool {
    for v in adjacent_vertex_of_u {
        if (c == col[v]) return false;
        if ((color_set(v) - {c}) is empty) return false;
    }
    return true;
}

def dfs(int i) -> void {
    if (i == n + 1) {
        ans <- ans + used_colors;
        return;
    }

    u = find_vertex();
    if (i == 1) {
        col[u] <- c;
        dfs(i + 1);
    } else {
        for c in [1, count] {
            if (check(u, c) == false) {
                continue;
            }
            col[u] <- c;
            dfs(i + 1);
        }
    }
}
```

## 四、实验结果与分析

运行上述的代码并得到以下的运行效率：

## 五、实验结论
