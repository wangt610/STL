#include<iostream>
#include<string.h>
#include<memory>
using namespace std;
template<class T>
class My_deque {
private:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator = T*;
    using const_iterator = const T*;
    pointer _start;
    pointer _finish;
    size_t _size;
    size_t _capacity;
public:
//===================构造与析构==================
    My_deque() {
       _start = nullptr;
         _finish = nullptr;
        _size = 0;
        _capacity = 0;
    }
    My_deque(size_t n) {
        _capacity = n;
        _size = n;
        _start = (pointer)operator new(sizeof(value_type) * _capacity);//new运算符
        _finish = _start + _size;
        for (size_t i = 0; i < n; ++i) {
            new (_start + i) T();//定位 new
        }
    }
    My_deque(size_t n, const T& value) {
        _capacity = n;
        _size = n;
        _start = (pointer)operator new(sizeof(value_type) * _capacity);//new运算符
        _finish = _start + _size;
        for (size_t i = 0; i < n; ++i) {
            new (_start + i) T(value);//定位 new
        }
    }
    My_deque(const My_deque& dq) {
        _capacity = dq._capacity;
        _size = dq._size;
        _start = (pointer)operator new(sizeof(value_type) * _capacity);
        _finish = _start + _size;
        for (size_t i = 0; i < _size; ++i) {
            new (_start + i) T(dq._start[i]);
        }
    }
    My_deque(initializer_list<T> ilist) {
        _capacity = ilist.size();
        _size = ilist.size();
        _start = (pointer)operator new(sizeof(value_type) * _capacity);
        _finish = _start + _size;
        size_t i = 0;
        for (const auto& elem : ilist) {
            new (_start + i) T(elem);
            ++i;
        }
    }
    ~My_deque() {
        for (size_t i = 0; i < _size; ++i) {
            _start[i].~T(); // 显式调用析构函数
        }
        operator delete(_start); // 释放内存
    }
    // Additional member functions to be implemented
    //===================迭代器接口==================
    iterator begin() noexcept {
        return _start;
    }
    iterator end() noexcept {
        return _finish;
    }   
    iterator cbegin() noexcept {
        return _start;
    }
    iterator cend() noexcept {
        return _finish;
    }
    //===================元素访问==================
    reference operator[](size_t i) {
        if (i < 0 || i >= _size) {
            exit(EXIT_FAILURE);
        }
        return _start[i];
    }
    reference at(size_t i) {
        if (i < 0 || i >= _size) {
            exit(EXIT_FAILURE);
        }
        return _start[i];   
    }
    reference front() {
        return _start[0];
    }
    reference back() {
        return _finish[-1];
    }
    pointer data() noexcept {
        return _start;
    }
    //===================容量==================
    size_t size() noexcept {
        return _size;
    }
    size_t capacity() noexcept {
        return _capacity;
    }
    bool empty() noexcept {
        return _size == 0;
    }
    //===================操作==================
    void push_back(const T& value) {
        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            pointer new_start = (pointer)operator new(sizeof(value_type) * new_capacity);
            for (size_t i = 0; i < _size; ++i) {
                new (new_start + i) T(std::move(_start[i]));
                _start[i].~T();
            }
            operator delete(_start);
            _start = new_start;
            _capacity = new_capacity;
        }
        new (_start + _size) T(value);
        ++_size;
        _finish = _start + _size;
    }
    void pop_back() {
        if (_size == 0) {
            exit(EXIT_FAILURE);
        }
        --_size;
        _finish = _start + _size;
        _start[_size].~T();
    }
    void push_front(const T& value) {
        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            pointer new_start = (pointer)operator new(sizeof(value_type) * new_capacity);
            for (size_t i = 0; i < _size; ++i) {
                new (new_start + i + 1) T(std::move(_start[i]));
                _start[i].~T();
            }
            operator delete(_start);
            _start = new_start;
            _capacity = new_capacity;
        } else {
            for (size_t i = _size; i > 0; --i) {
                new (_start + i) T(std::move(_start[i - 1]));
                _start[i - 1].~T();
            }
        }
        new (_start) T(value);
        ++_size;
        _finish = _start + _size;
    }
    void pop_front() {
        if (_size == 0) {
            exit(EXIT_FAILURE);
        }
        _start[0].~T();
        for (size_t i = 1; i < _size; ++i) {
            new (_start + i - 1) T(std::move(_start[i]));
            _start[i].~T();
        }
        --_size;
        _finish = _start + _size;
    }
    void insert(size_t index, const T& value) {
        if (index < 0 || index > _size) {
            exit(EXIT_FAILURE);
        }
        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            pointer new_start = (pointer)operator new(sizeof(value_type) * new_capacity);
            for (size_t i = 0; i < index; ++i) {
                new (new_start + i) T(std::move(_start[i]));
                _start[i].~T();
            }
            new (new_start + index) T(value);
            for (size_t i = index; i < _size; ++i) {
                new (new_start + i + 1) T(std::move(_start[i]));
                _start[i].~T();
            }
            operator delete(_start);
            _start = new_start;
            _capacity = new_capacity;
        } else {
            for (size_t i = _size; i > index; --i) {
                new (_start + i) T(std::move(_start[i - 1]));
                _start[i - 1].~T();
            }
            new (_start + index) T(value);
        }
        ++_size;
        _finish = _start + _size;
    }
    void erase(size_t index) {
        if (index < 0 || index >= _size) {
            exit(EXIT_FAILURE);
        }
        _start[index].~T();
        for (size_t i = index + 1; i < _size; ++i) {
            new (_start + i - 1) T(std::move(_start[i]));
            _start[i].~T();
        }
        --_size;
        _finish = _start + _size;
    }
    void clear() noexcept {
        for (size_t i = 0; i < _size; ++i) {
            _start[i].~T();
        }
        _size = 0;
        _finish = _start;
    }
    void swap(My_deque& other) noexcept {
        std::swap(_start, other._start);
        std::swap(_finish, other._finish);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }
    void resize(size_t new_size, const T& value = T()) {
        if (new_size < _size) {
            for (size_t i = new_size; i < _size; ++i) {
                _start[i].~T();
            }
        } else if (new_size > _size) {
            if (new_size > _capacity) {
                size_t new_capacity = new_size;
                pointer new_start = (pointer)operator new(sizeof(value_type) * new_capacity);
                for (size_t i = 0; i < _size; ++i) {
                    new (new_start + i) T(std::move(_start[i]));
                    _start[i].~T();
                }
                operator delete(_start);
                _start = new_start;
                _capacity = new_capacity;
            }
            for (size_t i = _size; i < new_size; ++i) {
                new (_start + i) T(value);
            }
        }
        _size = new_size;
        _finish = _start + _size;
    }
};
int main(){
    //初始化测试
    My_deque<int> dq1;
    My_deque<int> dq2(5);
    My_deque<int> dq3(5, 10);
    My_deque<int> dq4 = {1, 2, 3, 4, 5};
    //元素访问测试
    dq3[2] = 20;
    cout << "dq3[2]: " << dq3.at(2) << endl;
    cout << "dq4 front: " << dq4.front() << ", back: " << dq4.back() << endl;
    //容量测试
    cout << "dq4 size: " << dq4.size() << ", empty: " << dq4.empty() << endl;
    //操作测试
    dq4.push_back(6);
    dq4.push_front(0);
    cout << "After push_back and push_front, dq4: ";
    for (auto it = dq4.begin(); it != dq4.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    dq4.pop_back();
    dq4.pop_front();
    cout << "After pop_back and pop_front, dq4: ";
    for (auto it = dq4.begin(); it != dq4.end(); ++it) {
        cout << *it << " ";
    }   
    cout << endl;
    dq4.insert(2, 15);
    cout << "After insert 15 at index 2, dq4: ";
    for (auto it = dq4.begin(); it != dq4.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    dq4.erase(2);
    cout << "After erase at index 2, dq4: ";
    for (auto it = dq4.begin(); it != dq4.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    dq4.resize(10, 100);
    cout << "After resize to 10 with fill value 100, dq4: ";
    for (auto it = dq4.begin(); it != dq4.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    dq4.clear();
    cout << "After clear, dq4 size: " << dq4.size() <<  " empty: " << dq4.empty() << endl;
    return 0;
}
