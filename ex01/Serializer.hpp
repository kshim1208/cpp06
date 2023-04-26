#ifndef Serializer_HPP
# define Serializer_HPP

# include "Serializer.h"

class Serializer
{
	private:

		Serializer(/* args*/);
		~Serializer();
		Serializer(const Serializer& source);
		Serializer& operator=(const Serializer& source);
	public:
		static uintptr_t	serialize(Data* ptr);
		static Data*		deserialize(uintptr_t raw);
};

#endif