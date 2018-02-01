#include <bitset>
#include <iostream>

using namespace std;

void print() {
	cout << "call end" << endl;
}

template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
	cout << firstArg << " "<< sizeof...(args) << sizeof...(Types) << endl;
	print(args...);
} 

int main(int argc, char* argv[]) {
	
	print(7.5, "hello", 42, bitset<16>(4444));
	return 0;
}
