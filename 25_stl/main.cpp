#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

//C++的标准模板库（STL）提供了多种通用容器，用于存储和管理数据。这些容器各有特点，适用于不同的应用场景。
//理解每种容器的用法和内部实现原理，对于编写高效且可维护的代码至关重要。
//本教案将详细介绍几种常用的STL容器，包括vector、list、deque、map、unordered_map、set、unordered_set以及容器适配器如stack、queue和priority_queue。

//vector：动态数组
//vector是STL中最常用的序列容器之一，提供了动态大小的数组功能。它支持随机访问，允许在末尾高效地添加和删除元素。
//vector在内部使用动态数组（通常是连续的内存块）来存储元素。
//当需要扩展容量时，它会分配一块更大的内存，将现有元素复制到新内存中，然后释放旧内存。这种策略在平均情况下保证了push_back的常数时间复杂度。
//性能特性
//  随机访问：支持常数时间的随机访问（O(1)）。
//  末尾插入/删除：push_back和pop_back操作在摊销分析下是常数时间（O(1)）。
//  中间插入/删除：在中间位置插入或删除元素需要移动后续元素，时间复杂度为线性时间（O(n)）。
//应用场景
//  需要频繁随机访问元素。
//  主要在容器末尾进行插入和删除操作。
//  当容器大小不需要频繁调整（避免频繁的内存重新分配）。
void vector_test() {
    vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    // 通过索引访问元素
    cout << v[0] << endl;

    // 遍历vector
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }

    v.pop_back();

    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

//list：双向链表
//list是一个实现了双向链表的数据结构，适合在容器中间频繁插入和删除元素。与vector不同，list不支持随机访问，但在任何位置的插入和删除操作都是常数时间。
//list在内部使用双向链表，每个元素包含指向前一个和后一个元素的指针。这使得在已知位置插入或删除元素时，无需移动其他元素，只需更新指针即可。
//性能特性
//  随机访问：不支持随机访问，访问第n个元素需要线性时间（O (n)）。
//  中间插入/删除：已知位置的插入和删除操作是常数时间（O (1)）。
//  遍历：顺序遍历，适合需要频繁遍历但不需要随机访问的场景。
//应用场景
//  需要在容器中间频繁插入或删除元素。
//  不需要进行随机访问。
//  对内存的局部性要求不高（链表元素在内存中不连续）。
void list_test() {
    list<int> l;
    // 向list末尾添加元素
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    // 向list前端添加元素
    l.push_front(99);
    // 遍历list
    for (auto it = l.begin(); it != l.end(); it++) {
        cout << *it << endl;
    }
    // 插入元素
    l.insert(++l.begin(), 88);

    for (auto it = l.begin(); it != l.end(); it++) {
        cout << *it << endl;
    }
    // 删除元素
    l.remove(99);

    for (auto it = l.begin(); it != l.end(); it++) {
        cout << *it << endl;
    }
}

//模拟实现一个简化版的 List
//节点结构体
template<typename T>
struct Node {
    T data;
    Node *prev;
    Node *next;

    Node(const T &data = T()) : data(data), prev(nullptr), next(nullptr) {
    }
};

//迭代器实现
template<typename T>
class MyList;

template<typename T>
class Iter {
public:
    using self_type = Iter<T>;
    using value_type = T;
    using ref = T &;
    using pointer = T *;
    using iter_cate = std::bidirectional_iterator_tag;
    using diff_type = std::ptrdiff_t;

    Iter(Node<T> *ptr = nullptr) : ptr(ptr) {
    }

    //解引用
    ref operator*() const { return ptr->data; }

    //指针调用
    pointer operator->() const { return &(ptr->data); }

    //前++
    self_type &operator++() {
        if (ptr) {
            ptr = ptr->next;
        }
        return *this;
    }

    //后++
    self_type operator++(int) {
        self_type tmp = *this;
        ++(*this);
        return tmp;
    }

    //前--
    self_type &operator--() {
        if (ptr) {
            ptr = ptr->prev;
        }
        return *this;
    }

    //后--
    self_type operator--(int i) {
        self_type tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const self_type &other) const {
        return ptr == other.ptr;
    }

    bool operator!=(const self_type &other) const {
        return ptr != other.ptr;
    }

private:
    Node<T> *ptr;

    friend class MyList<T>;
};

template<typename T>
class MyList {
public:
    using iter = Iter<T>;
    using const_iter = Iter<T>;

    MyList() {
        head = new Node<T>;
        tail = new Node<T>;
        head->next = tail;
        tail->prev = head;
    }

    ~MyList() {
        clear();
        delete head;
        delete tail;
    }

    // 禁止拷贝构造和赋值操作（简化实现）
    MyList(const MyList &other) = delete;

    MyList &operator=(const MyList &other) = delete;

    // 插入元素到迭代器位置之前
    iter insert(iter pos, const T &data) {
        Node<T> *cur = pos.ptr;
        Node<T> *new_node = new Node<T>(data);

        Node<T> *pre = cur->prev;

        new_node->next = cur;
        new_node->prev = pre;

        pre->next = new_node;
        cur->prev = new_node;

        return iter(new_node);
    }

    // 删除迭代器指向的元素
    iter erase(iter pos) {
        Node<T> *cur = pos.ptr;
        if (cur == head || cur == tail) {
            return pos;
        }

        Node<T> *pre = cur->prev;
        Node<T> *next = cur->next;

        pre->next = next;
        next->prev = pre;

        delete cur;

        return iter(next);
    }

    // 在头部插入元素
    void push_front(const T &data) {
        insert(begin(), data);
    }

    // 在尾部插入元素
    void push_back(const T &data) {
        insert(end(), data);
    }

    // 在头部删除元素
    void pop_front() {
        if (!empty()) {
            erase(begin());
        }
    }

    // 在尾部删除元素
    void pop_back() {
        if (!empty()) {
            iter tmp = end();
            --tmp;
            erase(tmp);
        }
    }

    // 获取头元素引用
    T &front() {
        return head->next->data;
    }

    // 获取尾元素引用
    T &back() {
        return tail->prev->data;
    }

    // 判断是否为空
    bool empty() const {
        return head->next == tail;
    }

    // 获取链表大小（O(n)复杂度）
    size_t size() const {
        size_t count = 0;
        for (auto it = begin(); it != end(); ++it) {
            ++count;
        }
        return count;
    }

    // 获取开始迭代器
    iter begin() {
        return iter(head->next);
    }

    // 获取结束迭代器
    iter end() {
        return iter(tail);
    }

    // 清空链表
    void clear() {
        Node<T> *cur = head->next;
        while (cur != tail) {
            Node<T> *temp = cur;
            cur = cur->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
    }

    // 打印链表（辅助函数）
    void print() const {
        Node<T> *cur = head->next;
        while (cur != tail) {
            std::cout << cur->data << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }

private:
    Node<T> *head;
    Node<T> *tail;
};

void mylist_test() {
    MyList<int> l;

    l.push_back(1);
    l.push_front(5);
    l.push_front(2);
    l.insert(++l.begin(), 3);

    l.print();

    l.pop_front();
    l.pop_back();

    l.print();

    l.insert(l.begin(), 2);
    l.erase(++l.begin());

    l.print();

    l.clear();
    l.print();
    cout << l.empty() << endl;
}

//迭代器类别（Iterator Categories）
//输入迭代器（Input Iterator）
//输出迭代器（Output Iterator）
//前向迭代器（Forward Iterator）
//双向迭代器（Bidirectional Iterator）
//随机访问迭代器（Random Access Iterator）
//无效迭代器（Contiguous Iterator）（C++20 引入）

//为什么需要 iterator_category
//标准库中的算法（如 std::sort、std::find 等）需要知道迭代器支持哪些操作，以便选择最优的实现方式。例如：
//  对于随机访问迭代器，可以使用快速的随机访问算法（如快速排序）。
//  对于双向迭代器，只能使用适用于双向迭代的算法（如归并排序）。
//  对于输入迭代器，只能进行单次遍历，许多复杂算法无法使用。
//通过指定 iterator_category，你可以让标准算法了解你自定义迭代器的能力，从而选择合适的方法进行操作。

//iterator_category 的声明
//在你的自定义迭代器类中，通过以下方式声明迭代器类别：
//using iterator_category = std::bidirectional_iterator_tag;

//std::bidirectional_iterator_tag 详解
//std::bidirectional_iterator_tag 是一个标签（Tag），用于标识迭代器类别。C++ 标准库中有多个这样的标签，分别对应不同的迭代器类别：
//std::input_iterator_tag
//std::output_iterator_tag
//std::forward_iterator_tag
//std::bidirectional_iterator_tag
//std::random_access_iterator_tag
//std::contiguous_iterator_tag（C++20）

//迭代器特性（Iterator Traits）详解
//C++ 提供了 迭代器特性（Iterator Traits），通过模板类 std::iterator_traits 来获取迭代器的相关信息。通过这些特性，标准算法可以泛化地处理不同类型的迭代器。
//std::iterator_traits 提供以下信息：
//  iterator_category：迭代器类别标签。
//  value_type：迭代器指向的元素类型。
//  difference_type：迭代器间的距离类型（通常是 std::ptrdiff_t）。
//  pointer：指向元素的指针类型。
//  reference：对元素的引用类型。

//自定义迭代器与 iterator_traits
//当你定义自己的迭代器时，确保提供这些类型别名，以便标准库算法能够正确识别和使用你的迭代器。例如：
template<typename T>
class Iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    // 其他成员函数...
};

//使用 std::iterator_traits<Iterator<T>> 时，就能正确获取迭代器的特性。

//deque：双端队列
//deque（双端队列）是一种支持在两端高效插入和删除元素的序列容器。与vector相比，deque支持在前端和后端均以常数时间进行插入和删除操作。
void deque_test() {
    deque<string> dq;

    dq.push_back("end1");
    dq.push_back("end2");

    dq.push_front("head1");
    dq.push_front("head2");

    for (auto it = dq.begin(); it != dq.end(); ++it) {
        cout << *it << endl;
    }
    // 访问首尾元素
    cout << dq.front() << endl;
    cout << dq.back() << endl;

    dq.pop_front();

    dq.pop_back();

    for (auto num: dq) {
        cout << num << endl;
    }
}

//map和unordered_map：关联数组
//map是一个关联容器，用于存储键值对（key-value）。它基于键自动排序，且每个键都是唯一的。map提供了快速的查找、插入和删除操作。
//unordered_map也是一种关联容器，用于存储键值对，但它不保证元素的顺序。unordered_map基于哈希表实现，提供了平均常数时间（O(1)）的查找、插入和删除操作。
void map_test() {
    map<string, int> ages;

    ages["xiaomi"] = 33;
    ages["xiaozhang"] = 44;
    ages["xiaowang"] = 55;

    if (ages.find("xiaozhang") != ages.end()) {
        cout << ages["xiaozhang"] << endl;
    } else {
        cout << "未找到" << endl;
    }

    for (auto it = ages.begin(); it != ages.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    ages.erase("xiaozhang");

    for (auto &[key, value]: ages) {
        cout << key << " " << value << endl;
    }
}

void unordered_map_test() {
    unordered_map<string, double> prices;

    prices["apple"] = 1.23;
    prices["banana"] = 4.56;
    prices["orange"] = 7.23;

    if (prices.find("banana") != prices.end()) {
        cout << prices["banana"] << endl;
    } else {
        cout << "未找到" << endl;
    }

    for (auto &[key, value]: prices) {
        cout << key << " " << value << endl;
    }

    prices.erase("apple");

    for (auto &[key, value]: prices) {
        cout << key << " " << value << endl;
    }
}

//set和unordered_set：集合
//set是一个关联容器，用于存储唯一的、有序的元素。set基于键自动排序，且每个元素都是唯一的。
//unordered_set也是一种集合容器，用于存储唯一的元素，但它不保证元素的顺序。unordered_set基于哈希表实现，提供了平均常数时间（O(1)）的查找、插入和删除操作。
void set_test() {
    set<int> numbers;
    // 插入元素
    numbers.insert(10);
    numbers.insert(20);
    numbers.insert(30);
    numbers.insert(10); //重复元素，不会被插入

    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << endl;
    }

    if (numbers.find(10) != numbers.end()) {
        cout << "存在" << endl;
    } else {
        cout << "不存在" << endl;
    }

    numbers.erase(10);

    for (auto num: numbers) {
        cout << num << endl;
    }
}

void unordered_set_test() {
    unordered_set<int> numbers;
    // 插入元素
    numbers.insert(10);
    numbers.insert(20);
    numbers.insert(30);
    numbers.insert(10);
    // 遍历unordered_set
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << endl;
    }
    // 查找元素
    if (numbers.find(10) != numbers.end()) {
        cout << "找到" << endl;
    } else {
        cout << "未找到" << endl;
    }

    numbers.erase(10);

    for (auto num: numbers) {
        cout << num << endl;
    }
}

//stack、queue和priority_queue：容器适配器
//STL中的容器适配器（stack、queue、priority_queue）提供了特定的数据结构接口，这些适配器在内部使用其他容器来存储元素（默认使用deque或vector）。
//stack：后进先出（LIFO）数据结构，通常使用deque或vector作为底层容器，通过限制操作接口来实现。
//queue：先进先出（FIFO）数据结构，通常使用deque作为底层容器，通过限制操作接口来实现。
//priority_queue：基于堆的数据结构，通常使用vector作为底层容器，并通过堆算法（如std::make_heap、std::push_heap、 std::pop_heap）维护元素的优先级顺序。
void stack_test() {
    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << s.top() << endl;

    s.pop(); //弹出
    cout << s.top() << endl;

    if (s.empty()) {
        cout << "为空" << endl;
    } else {
        cout << "不为空" << s.size() << endl;
    }
}

void queue_test() {
    queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);
    // 访问队首元素
    cout << q.front() << endl;
    // 访问队尾元素
    cout << q.back() << endl;
    // 出队元素
    q.pop();
    cout << q.front() << endl;

    if (q.empty()) {
        cout << "为空" << endl;
    } else {
        cout << "不为空" << q.size() << endl;
    }
}

void priority_queue_test() {
    // 创建一个空的priority_queue，默认是最大堆
    priority_queue<int> q;

    q.push(10);
    q.push(40);
    q.push(30);
    q.push(20);
    // 访问堆顶元素
    cout << q.top() << endl;

    q.pop();
    cout << q.top() << endl;

    // 遍历priority_queue（需要复制，因为无法直接遍历）
    priority_queue<int> copy = q;
    while (!copy.empty()) {
        cout << copy.top() << endl;
        copy.pop();
    }
}

int main() {
    vector_test();
    list_test();
    mylist_test();
    deque_test();
    map_test();
    unordered_map_test();
    set_test();
    unordered_set_test();
    stack_test();
    queue_test();
    priority_queue_test();
    return 0;
}
