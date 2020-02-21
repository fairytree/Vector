#include "Vector.h"		

int main()
{
	size_t size1 = 4;
	size_t size2 = 2;

	Vector<int> vec1(size1);
	std::cout << "vec1:\n" << vec1 << "\nsize = " << vec1.size() << "; capacity = " << vec1.capacity() << '\n' << std::endl;

	Vector<int> vec2;   // cannot use "Vector<int> vec2()" format, as the compilor will mistake it with a regular function call	
	std::cout << "vec2:\n" << vec2 << "\nsize = " << vec2.size() << "; capacity = " << vec2.capacity() << '\n' << std::endl;

	vec2 = vec1;
	std::cout << "vec2:\n" << vec2 << "\nsize = " << vec2.size() << "; capacity = " << vec2.capacity() << '\n' << std::endl;

	vec1.push_back(999);
	std::cout << "vec1:\n" << vec1 << "\nsize = " << vec1.size() << "; capacity = " << vec1.capacity() << '\n' << std::endl;

	vec1.pop_back();
	std::cout << "vec1:\n" << vec1 << "\nsize() = " << vec1.size() << "; capacity() = " << vec1.capacity() << '\n' << std::endl;

	return 0;
}

