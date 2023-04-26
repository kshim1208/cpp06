#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

class ScalarConverter
{
	private:
		static char			c;
		static bool			char_imp;
		static int			i;
		static bool			int_imp;
		static float		f;
		static bool			float_imp;
		static double		d;
		static bool			double_imp;

		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& source);
		ScalarConverter& operator=(const ScalarConverter& source);

		static void	convertTypeSpecify(std::string& string);
		static bool	ft_isnanf(float	f);
		static bool	ft_isinff(float f);
		static bool ft_isnan(double d);
		static bool ft_isinf(double d);
		static bool	ft_isposinff(float f);

		class ScalarConvertNonDisplayable : public std::exception
		{
			public:
				const char* what() const throw();
		};
		class ScalarConvertImpossible : public std::exception
		{
			public:
				const char* what() const throw();
		};
	public:
		static void	convert(std::string string);
};

#endif