#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

typedef boost::variant<int, float, std::string> object_type;

struct equal : boost::static_visitor<bool> {
	bool operator ()(float a, int b) const {
		return a == static_cast<float>(b);
	}
	bool operator ()(std::string const& a, std::string const& b) const {
		return a == b;
	}
	template<typename T>
	bool operator ()(std::string const& str, T const& a) const {
		return str == boost::lexical_cast<std::string>(a);
	}
	template<typename T, typename U>
	bool operator ()(T const& a, U const& b) const {
		return (*this)(b, a);
	}
	template<typename T>
	bool operator ()(T const& a, T const& b) const {
		return a == b;
	}
};

int
main() {
	object_type o1(10);
	object_type o2(10.0f);
	object_type o3("10");

	std::cout << boost::apply_visitor(equal(), o1, o2) << std::endl;
	std::cout << boost::apply_visitor(equal(), o3, o2) << std::endl;
	std::cout << boost::apply_visitor(equal(), o1, o3) << std::endl;

	return 0;
}