# Data Structures with C++

This is an educational data-structure library. I began writing it while learning data structures and modern C++ in parallel—an endeavour still in progress. The code therefore makes extensive use of recent C++ features such as `std::expected` and `std::function`, inevitably with some rough edges. Any clumsiness in design or style is owed to my limited experience; your indulgence is appreciated.

这是一个用于学习的数据结构库，由于我在学习数据结构的同时，也在同步学习 C++，因此代码中尝试了大量 C++ 新特性（如 `std::expected` `std::function` 等），受限于个人经验，实现与风格难免生疏，尚祈海涵。

在这两个月时间里我确实发现了 c++ 的一些问题，"泛型 + 内联"本身可以可以提供零成本抽象是很好的一件事，但是 c++ 把 cpp 和 hpp 区分开，导致了一些很麻烦的问题，也造就了这是个 Header-only 仓库，因为我使用了大量的模板。Rust 有很好的解决这些问题，因此在后续的项目中我会考虑用 RUST 来写。

```
 data-structures-with-cpp
├── CMakeLists.txt
├── README.md
├── build\
├── tests\
│   ├── test_error.cpp
│   ├── test_graph.cpp
│   ├── test_linear_list.cpp
│   ├── test_queue.cpp
│   ├── test_stack.cpp
│   ├── test_tree.cpp
│   └── test_union_find_set.cpp
└── src\
    ├── error\
    │   └── error.hpp
    ├── linear_list\
    │   ├── circular_double_linked_list.hpp
    │   ├── circular_linked_list.hpp
    │   ├── double_linked_list.hpp
    │   ├── linked_list.hpp
    │   ├── sequential_list.hpp
    │   └── static_linked_list.hpp
    ├── queue\
    │   ├── circular_dequeue.hpp
    │   ├── circular_queue.hpp
    │   ├── list_dequeue.hpp
    │   └── list_queue.hpp
    ├── stack\
    │   ├── list_stack.hpp
    │   └── vector_stack.hpp
    ├── tree\
    │   ├── avl_tree.hpp
    │   ├── binary_search_tree.hpp
    │   ├── binary_tree.hpp
    │   └── red_black_tree.hpp
    ├── graph\
    │   └── adjacency_matrix_graph.hpp
    ├── set\
    │   └── union_find_set.hpp
    ├── hash\
    ├── sorting_algorithms\
    │   └── sorting_algorithms.hpp
    └── string\(empty)
```

```bash
git clone https://github.com/xiaoze-xiaoze/data-structures-with-cpp.git
```
