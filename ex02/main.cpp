#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <random>
#include <iostream>

Base*	generate(void)
{
	Base*	tmp;
	int		random = std::rand() % 3;

	if (random == 0)
	{
		tmp = new A();
		std::cout << "generate - the masked_instance is A.... " << tmp << " in secret." << std::endl;
	}
	else if (random == 1)
	{
		tmp = new B();
		std::cout << "generate - the masked_instance is B.... " << tmp << " in secret." << std::endl;
	}
	else
	{
		tmp = new C();
		std::cout << "generate - the masked_instance is C.... " << tmp << " in secret." << std::endl;
	}
	return (tmp);
}

void	identify(Base* p)
{
	A*	is_a;
	B*	is_b;
	C*	is_c;
	
	is_a = dynamic_cast<A*>(p);
	is_b = dynamic_cast<B*>(p);
	is_c = dynamic_cast<C*>(p);
	std::cout << "identify-ptr : is_a is..... " << is_a << std::endl;
	std::cout << "identify-ptr : is_b is..... " << is_b << std::endl;
	std::cout << "identify-ptr : is_c is..... " << is_c << std::endl;
}

void	identify(Base& p)
{
	A	is_a;
	B	is_b;
	C	is_c;
	
	try
	{
		is_a = dynamic_cast<A&>(p);
		std::cout << "is_a was the masked_instance!!!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "is_a was not the masked_instance...... : " << e.what() << '\n';
	}
	try
	{
		is_b = dynamic_cast<B&>(p);
		std::cout << "is_b was the masked_instance!!!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "is_b was not the masked_instance...... : " << e.what() << '\n';
	}
	try
	{
		is_c = dynamic_cast<C&>(p);
		std::cout << "is_c was the masked_instance!!!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "is_c was not the masked_instance...... : " << e.what() << '\n';
	}
}

int main()
{
	Base*	masked_instance;

	masked_instance = generate();
	identify(masked_instance);
	identify(*masked_instance);
}
