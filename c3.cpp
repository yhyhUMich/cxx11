//variadic template fits the most specific template function

#include <iostream>
#include <functional>
#include <string>

using namespace std;

class Customer {
public:
	string fname;
	string lname;
	int no;
};

template<typename T>
inline void hash_combine(size_t& seed, const T& val) {
	seed ^= hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(size_t& seed, const T& val) {
	hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args) {
	cout << sizeof...(args) << endl;
	hash_combine(seed, val);
	hash_val(seed, args...);
}

template<typename... Types>
inline size_t hash_val(const Types&... args) {
	size_t seed = 0;
	cout << sizeof...(args) << endl;
	hash_val(seed, args...);
	return seed;
}

class CustomerHash {
public:
	size_t operator() (const Customer& c) const {
		return hash_val(c.fname, c.lname, c.no);
	}
};

int main(int argc, char* argv[]) {

	Customer c {"hang", "yuan", 10};
	
    cout <<	CustomerHash()(c) << endl;

	return 0;
}

