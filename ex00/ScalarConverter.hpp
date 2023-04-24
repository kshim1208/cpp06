#ifndef ScalarConverter_HPP
# define ScalarConverter_HPP

class ScalarConverter
{
	private:
		static	char	c;
		static	int		i;
		static	float	f;
		static	double	d;

		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& source);
		ScalarConverter& operator=(const ScalarConverter& source);
	public:

};

#endif