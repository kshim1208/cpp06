#include "Serializer.hpp"

#include <iostream>

Serializer::Serializer(/* args*/){}

Serializer::~Serializer(){}

Serializer::Serializer(const Serializer& source)
{
	Serializer	tmp;

	tmp = source;
}

Serializer& Serializer::operator=(const Serializer& source)
{
	Serializer	tmp = source;
	return (*this);
}

uintptr_t	Serializer::serialize(Data* ptr)
{
	std::cout << "in serialize - Data* ptr's address: "<< &ptr << std::endl;
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*		Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
