#include <iostream>

using namespace std;

void process(const int& par) {
	cout << "const int & " << par << endl;
}

void process(const int&& par) {
	cout << "int && " << par << endl;
}

void forward(const int&& par) {
	cout << "forward int && " << endl;
	process(par);
}

void process(int& par) {
	cout << "int& " << par << endl;
}

int main(int argc, char* argv[]) {
	
	int a = 0;
	
	const int& b = 5;
	process(b);

	process(0);
	process(a);
	
	process(move(a));

	forward(0);
	forward(move(a));

	return 0;
}
