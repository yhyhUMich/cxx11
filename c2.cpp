#include <bitset>
#include <iostream>

using namespace std;

void print() {}

template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
	cout << firstArg << endl;
	print(args...);
} 

int main(int argc, char* argv[]) {
	
	print(7.5, "hello", 42, bitset<16>(377));
	return 0;
}
