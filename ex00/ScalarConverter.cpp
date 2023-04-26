#include "ScalarConverter.hpp"
#include "ScalarConverter.h"

#include <string>
#include <cstdlib>
#include <limits.h>
#include <float.h>
#include <cerrno>

#include <iostream>
#include <iomanip>

char	ScalarConverter::c = 0;
bool	ScalarConverter::char_imp = false;
int		ScalarConverter::i = 0;
bool	ScalarConverter::int_imp = false;
float	ScalarConverter::f = 0;
bool	ScalarConverter::float_imp = false;
double	ScalarConverter::d = 0;
bool	ScalarConverter::double_imp = false;

ScalarConverter::ScalarConverter(/* args*/){}

ScalarConverter::~ScalarConverter(){}

ScalarConverter::ScalarConverter(const ScalarConverter& source)
{
	ScalarConverter tmp;

	tmp = source;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& source)
{
	ScalarConverter tmp = source;
	return (*this);
}

const char* ScalarConverter::ScalarConvertNonDisplayable::what() const throw()
{
	return ("Non displayable");
}

const char*	ScalarConverter::ScalarConvertImpossible::what() const throw()
{
	return ("impossible");
}

bool	ScalarConverter::ft_isnanf(float f)
{
	return (f != f);
}

bool	ScalarConverter::ft_isinff(float f)
{
	return (f != 0 && f * 2 == f);
}

bool	ScalarConverter::ft_isnan(double d)
{
	return (d != d);
}

bool	ScalarConverter::ft_isinf(double d)
{
	return (d != 0 && d * 2 == d);
}

bool	ScalarConverter::ft_isposinff(float f)
{
	u_ftoi_bitwise	cast_union;
	int				tmp;
	int				sign_bit = std::numeric_limits<float>::signaling_NaN();

	cast_union.f = f;
	tmp = cast_union.i;
	return ((tmp & sign_bit) == 0);
}

void	ScalarConverter::convertTypeSpecify(std::string& string)
{
	if (string.length() == 1 && isprint(string.front()) != 0 && isdigit(string.front()) == 0)
	{
		ScalarConverter::c = string.front();
		ScalarConverter::i = static_cast<int>(ScalarConverter::c);
		ScalarConverter::f = static_cast<float>(ScalarConverter::c);
		ScalarConverter::d = static_cast<double>(ScalarConverter::c);
		return ;
	}
	else
	{
		char	*end;
		long	tmp_l;
		tmp_l = std::strtol(string.c_str(), &end, 10);
		if (errno != ERANGE
			&& *end != '.'
			&& *end == '\0'
			&& (tmp_l >= INT_MIN
			&& tmp_l <= INT_MAX))
		{
			ScalarConverter::i = static_cast<int>(tmp_l);
			if (ScalarConverter::i < CHAR_MIN
				|| ScalarConverter::i > CHAR_MAX)
				ScalarConverter::char_imp = true;
			ScalarConverter::c = static_cast<char>(ScalarConverter::i);
			ScalarConverter::f = static_cast<float>(ScalarConverter::i);
			ScalarConverter::d = static_cast<double>(ScalarConverter::i);
			return ;
		}

		double	tmp_d;

		tmp_d = std::strtod(string.c_str(), &end);
		if (tmp_d == HUGE_VAL)
		{
			ScalarConverter::char_imp = true;
			ScalarConverter::int_imp = true;
			ScalarConverter::float_imp = true;
			ScalarConverter::double_imp = true;
			return ;
		}
		if (((*end == '\0'|| *end == 'f')
				&& (tmp_d >= FLT_MIN && tmp_d <= FLT_MAX))
			|| ft_isinf(tmp_d) == true
			|| ft_isnan(tmp_d) == true)
		{
			if (*end == 'f' && *(end + 1) != '\0')
			{
				ScalarConverter::char_imp = true;
				ScalarConverter::int_imp = true;
				ScalarConverter::float_imp = true;
				ScalarConverter::double_imp = true;
				return ;
			}
			ScalarConverter::f = static_cast<float>(tmp_d);
			ScalarConverter::d = static_cast<double>(ScalarConverter::f);
			if (ScalarConverter::ft_isnanf(ScalarConverter::f) == true
				|| ScalarConverter::ft_isinff(ScalarConverter::f) == true
				|| ScalarConverter::f < INT_MIN
				|| ScalarConverter::f > INT_MAX)
				ScalarConverter::int_imp = true;
			ScalarConverter::i = static_cast<int>(ScalarConverter::f);
			if (ScalarConverter::ft_isnanf(ScalarConverter::f) == true
				|| ScalarConverter::ft_isinff(ScalarConverter::f) == true
				|| ScalarConverter::f < CHAR_MIN
				|| ScalarConverter::f > CHAR_MAX)
				ScalarConverter::char_imp = true;
			ScalarConverter::c = static_cast<char>(ScalarConverter::f);
			return ;
		}
		else if (*end == '\0')
		{
			ScalarConverter::d = tmp_d;
			if (ScalarConverter::d < FLT_MIN
				|| ScalarConverter::d > FLT_MAX)
				ScalarConverter::float_imp = true;
			ScalarConverter::f = static_cast<float>(ScalarConverter::d);
			if (ScalarConverter::ft_isnan(ScalarConverter::d) == true
				|| ScalarConverter::ft_isinf(ScalarConverter::d) == true
				|| ScalarConverter::d < INT_MIN
				|| ScalarConverter::d > INT_MAX)
				ScalarConverter::int_imp = true;
			ScalarConverter::i = static_cast<int>(ScalarConverter::d);
			if (ScalarConverter::ft_isnan(ScalarConverter::d) == true
				|| ScalarConverter::ft_isinf(ScalarConverter::d) == true
				|| ScalarConverter::d < CHAR_MIN
				|| ScalarConverter::d > CHAR_MAX)
				ScalarConverter::char_imp = true;
			ScalarConverter::c = static_cast<char>(ScalarConverter::d);
			return ;
		}
		else
		{
			ScalarConverter::char_imp = true;
			ScalarConverter::int_imp = true;
			ScalarConverter::float_imp = true;
			ScalarConverter::double_imp = true;
			return ;
		}
	}
}

void	ScalarConverter::convert(std::string string)
{
	ScalarConverter::convertTypeSpecify(string);

	try
	{
		if (ScalarConverter::char_imp == true)
		{
			throw ScalarConverter::ScalarConvertImpossible();
		}
		if (isprint(ScalarConverter::c) != 0)
		{
			std::cout << "char: \'" << ScalarConverter::c << "'" << std::endl;
		}
		else
			throw ScalarConverter::ScalarConvertNonDisplayable();
	}
	catch(const std::exception& e)
	{
		std::cout << "char: " << e.what() << std::endl;
	}
	
	try
	{
		if (ScalarConverter::int_imp == true)
		{
			throw ScalarConverter::ScalarConvertImpossible();
		}
		std::cout << "int: " << ScalarConverter::i << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "int: " << e.what() << '\n';
	}

	std::cout << std::fixed << std::setprecision(1);

	try
	{
		if (ScalarConverter::float_imp == true)
		{
			throw ScalarConverter::ScalarConvertImpossible();
		}
		std::cout << "float: ";
		if (ft_isinff(ScalarConverter::f) == true
			&& ft_isposinff(ScalarConverter::f) == true)
		{
			std::cout << "+";
		}
		std::cout << ScalarConverter::f << "f" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "float: " << e.what() << '\n';
	}

	try
	{
		if (ScalarConverter::double_imp == true)
		{
			throw ScalarConverter::ScalarConvertImpossible();
		}
		std::cout << "double: ";
		if (ft_isinf(ScalarConverter::d) == true
			&& ft_isposinff(static_cast<float>(ScalarConverter::d)) == true)
		{
			std::cout << "+";
		}
		std::cout << ScalarConverter::d << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "double: " << e.what() << '\n';
	}
}
