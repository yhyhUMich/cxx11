#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <typeinfo>
#include <cstring>

using namespace std;

class MyString {
public:
	static size_t DCtor;
	static size_t Ctor;
	static size_t CCtor;
	static size_t CAsgn;
	static size_t MCtor;
	static size_t MAsgn;
	static size_t Dtor;
private:
	char* _data;
	size_t _len;
	
	void _init_data(const char* s) {
		_data = new char[_len+1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

public:
	MyString() : _data(nullptr), _len(0) {
		DCtor++;
	}

	MyString(const char* p) : _len(strlen(p)) {
		Ctor++;
		_init_data(p);
	}
	
	MyString(const MyString& str) : _len(str._len) {
		CCtor++;
		_init_data(str._data);
	}

	MyString(MyString&& str) noexcept 
		: _data(str._data), _len(str._len) {
		MCtor++;
		str._len = 0;
		str._data = nullptr;
	}

	MyString& operator=(const MyString& str) {
		CAsgn++;
		if(this != &str) {
			if(_data) {
				delete _data;
			}

			_len = str._len;
			_init_data(str._data);
		}
		return *this;
	}

	MyString& operator=(MyString&& str) noexcept {
		MAsgn++;
		if(this != &str) {
			if(_data) {
				delete(_data);
			}

			_len = str._len;
			_data = str._data;
			str._data = nullptr;
			str._len = 0;
		}

		return *this;
	}

	virtual ~MyString() {
		Dtor++;
		if(_data) {
			delete _data;
		}
	}

	bool operator < (const MyString& rhs) const {
		return string(this->_data) < string(rhs._data);
	}

	bool operator == (const MyString& rhs) const {
		return string(this->_data) == string(rhs._data);
	}

	char* get() const {
		return _data;
	}
};

size_t MyString::DCtor = 0;
size_t MyString::Ctor = 0;
size_t MyString::CCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MAsgn = 0;
size_t MyString::MCtor = 0;
size_t MyString::Dtor = 0;

namespace std {
template<>
struct hash<MyString> {
	size_t operator() (const MyString& s) const noexcept {
		return hash<string>() (string(s.get()));
	}
};
}


class MyStrNoMove {
public:
	static size_t DCtor;
	static size_t Ctor;
	static size_t CCtor;
	static size_t CAsgn;
	static size_t Dtor;
	static size_t MAsgn;
	static size_t MCtor;
private:
	char* _data;
	size_t _len;
	
	void _init_data(const char* s) {
		_data = new char[_len+1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

public:
	MyStrNoMove() : _data(nullptr), _len(0) {
		DCtor++;
	}

	MyStrNoMove(const char* p) : _len(strlen(p)) {
		Ctor++;
		_init_data(p);
	}
	
	MyStrNoMove(const MyStrNoMove& str) : _len(str._len) {
		CCtor++;
		_init_data(str._data);
	}

	MyStrNoMove& operator=(const MyStrNoMove& str) {
		CAsgn++;
		if(this != &str) {
			if(_data) {
				delete _data;
			}

			_len = str._len;
			_init_data(str._data);
		}
		return *this;
	}

	virtual ~MyStrNoMove() {
		Dtor++;
		if(_data) {
			delete _data;
		}
	}

	bool operator < (const MyStrNoMove& rhs) const {
		return string(this->_data) < string(rhs._data);
	}

	bool operator == (const MyStrNoMove& rhs) const {
		return string(this->_data) == string(rhs._data);
	}

	char* get() const {
		return _data;
	}
};

size_t MyStrNoMove::DCtor = 0;
size_t MyStrNoMove::Ctor = 0;
size_t MyStrNoMove::CCtor = 0;
size_t MyStrNoMove::CAsgn = 0;
size_t MyStrNoMove::Dtor = 0;
size_t MyStrNoMove::MCtor= 0;
size_t MyStrNoMove::MAsgn = 0;

namespace std {
template<>
struct hash<MyStrNoMove> {
	size_t operator() (const MyStrNoMove& s) const noexcept {
		return hash<string>() (string(s.get()));
	}         
};             
}             

template<typename T>
void output_static_data(const T& myStr) {
	cout << typeid(myStr).name() << "--" << endl;
	cout << "CCtor = " << T::CCtor;
	cout << "MCtor = " << T::MCtor;
	cout << "CAsng = " << T::CAsgn;
	cout << "MAsgn = " << T::MAsgn;
	cout << "Dtor = " << T::Dtor;
	cout << "Ctor = " << T::Ctor;
	cout << "DCtor = " << T::DCtor;
	cout << endl;
}

template<typename M, typename NM>
void test_moveable(M c1, NM c2, long& value) {

	char buf[10];

	typedef typename iterator_traits<typename M::iterator>::value_type V1type;

	clock_t timeStart = clock();
	
	for(long i = 0; i < value; i++) {
		snprintf(buf, 10, "%d", rand());
		auto ite = c1.end();
		c1.insert(ite, V1type(buf));
	}
	
	cout << "construction, milli-second : " <<(clock() - timeStart) << endl;
	cout << "size() = " << c1.size() << endl;
	output_static_data(*(c1.begin()));

	timeStart = clock();
	M c11(c1);
	cout << "copy, milli-second : " << (clock() - timeStart) << endl;
	
	timeStart = clock();
	M c12(move(c1));
	cout << "move copy, milli-second : " << (clock() - timeStart) << endl;
	
	timeStart = clock();
	c11.swap(c12);
	cout << "swap, milli-second : " << (clock() - timeStart) << endl;
	
	cout << endl << endl;
	//NM
	typedef typename iterator_traits<typename NM::iterator>::value_type V2type;

	timeStart = clock();

	for(long i = 0; i < value; i++) {
	
		snprintf(buf, 10, "%d", rand());
		auto ite = c2.end();
		c2.insert(ite, V2type(buf));
	}
	
	cout << "construction, milli-second : " << clock() - timeStart << endl;
	cout << "size() = " << c2.size() << endl;
	output_static_data(*(c2.begin()));
	
	timeStart = clock();
	NM c21(c2);
	cout << "copy, milli-second : " << (clock() - timeStart) << endl;
	
	timeStart = clock();
	NM c22(move(c2));
	cout << "move copy, milli-second : " << (clock() - timeStart) << endl;
	
	timeStart = clock();
	c21.swap(c22);
	cout << "swap, milli-second : " << (clock() - timeStart) << endl;
	cout << endl << endl;
}

int main(int argc, char* argv[]) {

	long value = 3000000;

	test_moveable(deque<MyString>(), list<MyStrNoMove>(), value);
	
	return 0;
}

