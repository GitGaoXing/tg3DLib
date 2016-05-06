#ifndef ___tgVariant___
#define ___tgVariant___

#include <string>

namespace tg
{

/*

Store different kind of variables in std::string

*/
const int MAX_PARAM_LENGTH = 2048;
class Variant
{
public:
	///////////////////////////////////////
	// constructors and destructor

	Variant();

	~Variant();

	Variant(const char* i_cInput, const int& i_nSize = -1);
	Variant(const std::string& i_strInput);
	Variant(const int& i_nInput);
	Variant(const unsigned int& i_unInput);
	Variant(const long long& i_llInput);
	Variant(const unsigned long long& i_ullInput);
	Variant(const bool& i_bInput);
	Variant(const float& i_fInput);
	Variant(const double& i_dInput);

	///////////////////////////////////////
	// public member functions

	const char* toByteArray(const int& i_nSize = -1) const;
	std::string toString() const;
	int toInt() const;
    unsigned int toUInt() const;
    long long toLongLong() const;
    unsigned long long toULongLong() const;
    bool toBool() const;
    float toFloat() const;
    double toDouble() const;

	size_t GetLength();

private:
	///////////////////////////////////////
	// private variables

	std::string m_strValue;
	size_t m_sLength;

};

};
#endif