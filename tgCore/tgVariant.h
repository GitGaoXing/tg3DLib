#ifndef ___tgVariant___
#define ___tgVariant___

#include "tgPrecompile.h"
#include <string>

namespace tg
{
namespace Core
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

	TG_EXPORT Variant();

	TG_EXPORT ~Variant();

	TG_EXPORT Variant(const char* i_cInput, const int& i_nSize = -1);
	TG_EXPORT Variant(const std::string& i_strInput);
	TG_EXPORT Variant(const int& i_nInput);
	TG_EXPORT Variant(const unsigned int& i_unInput);
	TG_EXPORT Variant(const long long& i_llInput);
	TG_EXPORT Variant(const unsigned long long& i_ullInput);
	TG_EXPORT Variant(const bool& i_bInput);
	TG_EXPORT Variant(const float& i_fInput);
	TG_EXPORT Variant(const double& i_dInput);

	///////////////////////////////////////
	// public member functions

	TG_EXPORT const char* toByteArray(const int& i_nSize = -1) const;
	TG_EXPORT std::string toString() const;
	TG_EXPORT int toInt() const;
    TG_EXPORT unsigned int toUInt() const;
    TG_EXPORT long long toLongLong() const;
    TG_EXPORT unsigned long long toULongLong() const;
    TG_EXPORT bool toBool() const;
    TG_EXPORT float toFloat() const;
    TG_EXPORT double toDouble() const;

	TG_EXPORT size_t GetLength();

private:
	///////////////////////////////////////
	// private variables

	std::string m_strValue;
	std::string::size_type m_sLength;

};

};
};
#endif