#include "ScalarConverter.hpp"
#include <climits>

// ── Detección de tipo ─────────────────────────────────────────────────────────

static bool isPseudoLiteral(const std::string& s) {
	return (s == "nan" || s == "nanf"
		|| s == "inf" || s == "+inf" || s == "-inf"
		|| s == "inff" || s == "+inff" || s == "-inff");
}

static bool isCharLiteral(const std::string& s) {
	return (s.length() == 1 && !std::isdigit(s[0]));
}

static bool isIntLiteral(const std::string& s) {
	size_t i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (i == s.length())
		return false;
	while (i < s.length()) {
		if (!std::isdigit(s[i]))
			return false;
		i++;
	}
	return true;
}

static bool isFloatLiteral(const std::string& s) {
	if (s.empty() || s[s.length() - 1] != 'f')
		return false;
	std::string trimmed = s.substr(0, s.length() - 1);
	if (trimmed.empty())
		return false;
	size_t i = 0;
	bool hasPoint = false;
	if (trimmed[i] == '+' || trimmed[i] == '-')
		i++;
	if (i == trimmed.length())
		return false;
	while (i < trimmed.length()) {
		if (trimmed[i] == '.') {
			if (hasPoint)
				return false;
			hasPoint = true;
		} else if (!std::isdigit(trimmed[i])) {
			return false;
		}
		i++;
	}
	return hasPoint;
}

static bool isDoubleLiteral(const std::string& s) {
	size_t i = 0;
	bool hasPoint = false;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (i == s.length())
		return false;
	while (i < s.length()) {
		if (s[i] == '.') {
			if (hasPoint)
				return false;
			hasPoint = true;
		} else if (!std::isdigit(s[i])) {
			return false;
		}
		i++;
	}
	return hasPoint;
}

// ── Helpers de impresión ──────────────────────────────────────────────────────

static void printChar(double value) {
	if (std::isnan(value) || std::isinf(value)
		|| value < 0 || value > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(value)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
}

static void printInt(double value) {
	if (std::isnan(value) || std::isinf(value)
		|| value < static_cast<double>(INT_MIN)
		|| value > static_cast<double>(INT_MAX))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;
}

static void printFloat(double value) {
	float f = static_cast<float>(value);
	std::cout << "float: " << f;
	if (!std::isinf(f) && !std::isnan(f) && f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;
}

static void printDouble(double value) {
	std::cout << "double: " << value;
	if (!std::isinf(value) && !std::isnan(value)
		&& value == static_cast<int>(value))
		std::cout << ".0";
	std::cout << std::endl;
}

// ── Conversiones por tipo ─────────────────────────────────────────────────────

static void fromChar(char c) {
	double value = static_cast<double>(c);
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}

static void fromInt(const std::string& literal) {
	char *end;
	long lval = std::strtol(literal.c_str(), &end, 10);
	if (*end != '\0' || lval < INT_MIN || lval > INT_MAX) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	double value = static_cast<double>(lval);
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}

static void fromFloat(const std::string& literal) {
	std::string trimmed = literal.substr(0, literal.length() - 1);
	char *end;
	double value = std::strtod(trimmed.c_str(), &end);
	if (*end != '\0') {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}

static void fromDouble(const std::string& literal) {
	char *end;
	double value = std::strtod(literal.c_str(), &end);
	if (*end != '\0') {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}

static void fromPseudo(const std::string& literal) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (literal == "nan" || literal == "nanf") {
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	} else if (literal == "inf" || literal == "inff"
		|| literal == "+inf" || literal == "+inff") {
		std::cout << "float: inff" << std::endl;
		std::cout << "double: inf" << std::endl;
	} else {
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}

// ── Punto de entrada ──────────────────────────────────────────────────────────

void ScalarConverter::convert(const std::string& literal) {
	if (literal.empty()) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	} else if (isPseudoLiteral(literal)) {
		fromPseudo(literal);
	} else if (isCharLiteral(literal)) {
		fromChar(literal[0]);
	} else if (isIntLiteral(literal)) {
		fromInt(literal);
	} else if (isFloatLiteral(literal)) {
		fromFloat(literal);
	} else if (isDoubleLiteral(literal)) {
		fromDouble(literal);
	} else {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}
