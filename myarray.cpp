#include<iostream>
#include<string.h>
using namespace std;

template<class T,size_t N>
class My_Array {
private:
	using value_type = T;
	using pointer=T*;
    using reference=T&;
    using iterator=T*;
    using const_iterator = const T*;
    T _elem[N];
public:
    //迭代器接口
    iterator begin()noexcept {
        return _elem;
    }
    iterator end()noexcept {
        return _elem + N;
    }
    //元素访问
    reference operator[](size_t i) {
        if (i < 0 || i >= N) {
            exit(EXIT_FAILURE);
        }
        return _elem[i];
    }
    reference at(size_t i) {
        if (i < 0 || i >= N) {
            exit(EXIT_FAILURE);
        }
        return _elem[i];
    }
    reference front() {
        return _elem[0];
    }
    reference back() {
        return _elem[N - 1];
    }
    reference data() noexcept {
        return _elem;
    }
    //容量
    constexpr size_t size() noexcept {
        return N;
    }
    constexpr bool empty() noexcept {
        return N == 0;
    }
    //操作
    void fill(const T& value) {
        for (size_t i = 0; i < N; ++i) {
            _elem[i] = value;
        }
    }
    void swap(My_Array& other) noexcept {
        for (size_t i = 0; i < N; ++i) {
            std::swap(_elem[i], other._elem[i]);
        }
    }
};
template<class T,size_t N>
void swap(My_Array<T,N>& a, My_Array<T,N>& b) noexcept {
    a.swap(b);
}
int main() {
    My_Array<int,5> arr;
    arr.fill(10);
    for(auto it=arr.begin();it!=arr.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<"Size: "<<arr.size()<<endl;
    cout<<"Front: "<<arr.front()<<endl;
    cout<<"Back: "<<arr.back()<<endl;
    return 0;
}
