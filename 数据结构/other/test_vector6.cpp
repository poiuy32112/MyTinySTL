#include "vector6.h"

int main() {
	mystl::vector v1(4);
	v1[0] = 1, v1[1] = 2, v1[2] = 3, v1[3] = 4;

	std::cout << v1.size() << '\n'; //4
	std::cout << v1.front() << '\n'; //1
	std::cout << v1.back() << '\n'; //4
	std::cout << v1[1] << '\n'; //2
	v1.insert(v1.begin() + 3, 222);
	v1.insert(v1.begin() + 5, 1);
	v1.push_back(5);
	v1.push_back(6);
	v1.pop_back();
	v1.printVector(); //1 2 3 222 4 5

	v1.insert(v1.begin(), -1);
	v1.erase(v1.begin() + 7);
	v1.erase(v1.begin() + 1);
	v1.insert(v1.begin(), -2); //-2 -1 2 3 222 4 5
	v1.erase(v1.begin() + 5); //-2 -1 2 3 222 5
	v1.printVector(); //-2 -1 2 3 222 5

	std::cout << v1.empty() << '\n'; //0
	v1.resize(9, 33);
	v1.printVector(); //-2 -1 2 3 222 5 33 33 33
	std::cout << "----------------------\n";

	mystl::vector v2{ 1,11,23,4,7 };
	v2.printVector(); //1 11 23 4 7

	mystl::vector v3(v2);
	v3.printVector(); //1 11 23 4 7

	return 0;
}