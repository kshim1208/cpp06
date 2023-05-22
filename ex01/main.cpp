#include "Serializer.hpp"

#include <iostream>

int	main()
{
	Data	hello;
	Data	*to_hello_ptr;
	uintptr_t	hello_ptr_raw;
	Data	*from_raw_ptr;

	hello.is_any_data = true;
	to_hello_ptr = &hello;
	std::cout << "before serialize - Data* ptr's address: "<< &to_hello_ptr << std::endl;
	hello_ptr_raw = Serializer::serialize(to_hello_ptr);
	from_raw_ptr = Serializer::deserialize(hello_ptr_raw);

	std::cout << to_hello_ptr << std::endl;
	std::cout << hello_ptr_raw << std::endl;
	std::cout << from_raw_ptr << std::endl;
	return (0);
}