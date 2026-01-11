#include<iostream>
#include<string.h>
using namespace std;
template<class T>
class My_vector {
private:
	T* _start;
	T* _finish;
	T* _end;
public:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef pointer iterator;
	My_vector() {
		_start = nullptr;
		_finish = nullptr;
		_end = nullptr;
	}
	~My_vector() {
		if (_start != nullptr)delete _start;
	}
	My_vector(const My_vector& vec) {
		long len = vec._end - vec._start;
		_start = (pointer) operator new(sizeof(value_type) * len);
		memmove(_start, vec._start, sizeof(value_type) * len);
		_end = _start + len;
		_finish = _start + (vec._finish - vec._start);
	}

	My_vector& operator=(const My_vector& vec) {
		if (this == &vec) {
			return *this;
		}
		if (_start != nullptr)delete _start;
		long len = vec._end - vec._start;
		pointer new_start = (pointer) operator new(sizeof(value_type) * len);
		memmove(new_start, vec._start, sizeof(value_type) * len);
		delete _start;
		_start = new_start;
		_end = _start + len;
		_finish = _start + (vec._finish - vec._start);
		return *this;
	}

	value_type operator[](size_t i) {
		int size = _end - _start;
		if (i < 0 || i >= size) {
			exit(EXIT_FAILURE);
		}
		return *(_start + i);    
	}

	value_type at(size_t i) {
		int size = _end - _start;
		if (i < 0 || i >= size) {
			exit(EXIT_FAILURE);
		}
		return *(_start + i);
	}

	iterator begin() {
		return _start;
	}
	iterator end() {
		return _finish;
	}

	bool empty() {
		return begin() == end();
	}

	void push_back(value_type value){
		if (empty()) {
			_start = (pointer) operator new(1 * sizeof(T));
			_finish = _start;
			_end = _start + 1;
		}
		else {
			if (end() >= _end) {  // 扩容 
				long len = end() - begin();
				pointer new_start = (pointer) operator new(len * 2 * sizeof(T));
				memmove(new_start, begin(), len * sizeof(T));
				// 释放之前空间
				delete _start;

				_start = new_start;
				_finish = _start + len;
				_end = _start + 2 * len;
			}
		}
	*_finish++ = value;
}
};

template<typename Iter>
void forEach(Iter begin, Iter end) {
	Iter p = begin;
	while (p < end) {
		cout << *p++ << "  ";
	}
	cout << endl;
}
int main() {
	My_vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	cout << v[0] << endl;
	cout << v.at(0) << endl;

	My_vector<int> v2;
	v2 = v;

	forEach<My_vector<int>::iterator>(v.begin(), v.end());
	forEach<My_vector<int>::iterator>(v2.begin(), v2.end());
	return 0;
}