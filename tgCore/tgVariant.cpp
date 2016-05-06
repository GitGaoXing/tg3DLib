#include "tgVariant.h"
#include <array>
#include <sstream>

namespace tg
{
namespace Core
{

Variant::Variant() : m_strValue(""), m_sLength(0)
{

}

Variant::~Variant()
{

}

Variant::Variant(const char* i_cInput, const int& i_nSize)
{
	if(i_nSize == -1)
	{
		this->m_strValue = i_cInput;
		this->m_sLength = this->m_strValue.length();
	}
	else
	{
		this->m_strValue = std::string(i_cInput, i_nSize);
		this->m_sLength = i_nSize;
	}
}

Variant::Variant(const std::string& i_strInput)
{
	this->m_strValue = i_strInput;
	this->m_sLength = this->m_strValue.length();
}

Variant::Variant(const int& i_nInput)
{
	char l_cTmp[MAX_PARAM_LENGTH];
	_snprintf_s (l_cTmp, _TRUNCATE, "%d", i_nInput);
	this->m_strValue = l_cTmp;
	this->m_sLength = this->m_strValue.length();
}

Variant::Variant(const unsigned int& i_unInput)
{
	char l_cTmp[MAX_PARAM_LENGTH];
	_snprintf_s (l_cTmp, _TRUNCATE, "%u", i_unInput);
	this->m_strValue = l_cTmp;
	this->m_sLength = this->m_strValue.length();
}

Variant::Variant(const long long& i_llInput)
{
	char l_cTmp[MAX_PARAM_LENGTH];
	_snprintf_s (l_cTmp, _TRUNCATE, "%I64d", i_llInput);
	this->m_strValue = l_cTmp;
	this->m_sLength = this->m_strValue.length();
}

Variant::Variant(const unsigned long long& i_ullInput)
{
	char l_cTmp[MAX_PARAM_LENGTH];
	_snprintf_s (l_cTmp, _TRUNCATE, "%I64u", i_ullInput);
	this->m_strValue = l_cTmp;
	this->m_sLength = this->m_strValue.length();
}

Variant::Variant(const bool& i_bInput)
{
	int l_nTmp = i_bInput;

	char l_cTmp[MAX_PARAM_LENGTH];
	_snprintf_s (l_cTmp, _TRUNCATE, "%d", l_nTmp);
	this->m_strValue = l_cTmp;
	this->m_sLength = this->m_strValue.length();
}

Variant::Variant(const float& i_fInput)
{
	char l_cTmp[MAX_PARAM_LENGTH];
	_snprintf_s (l_cTmp, _TRUNCATE, "%f", i_fInput);
	this->m_strValue = l_cTmp;
	this->m_sLength = this->m_strValue.length();
}

Variant::Variant(const double& i_dInput)
{
	char l_cTmp[MAX_PARAM_LENGTH];
	_snprintf_s (l_cTmp, _TRUNCATE, "%lf", i_dInput);
	this->m_strValue = l_cTmp;
	this->m_sLength = this->m_strValue.length();
}

///////////////////////////////////////////////////

const char* Variant::toByteArray(const int& i_nSize) const
{
	static char l_cTmp[MAX_PARAM_LENGTH];
	if(i_nSize == -1)
	{
		this->m_strValue._Copy_s(l_cTmp, MAX_PARAM_LENGTH, this->m_sLength, std::string::size_type(0));
	}
	else
	{
		std::string::size_type l_sTmp = i_nSize < this->m_sLength? i_nSize : this->m_sLength;
		this->m_strValue._Copy_s(l_cTmp, MAX_PARAM_LENGTH, l_sTmp, std::string::size_type(0));
	}
	return l_cTmp;
}

std::string Variant::toString() const
{
	return this->m_strValue;
}

int Variant::toInt() const
{
	int l_nOuput;
	std::stringstream l_ssTmp;
	l_ssTmp << this->m_strValue;
	l_ssTmp >> l_nOuput;
	l_ssTmp.clear();
	return l_nOuput;
}

unsigned int Variant::toUInt() const
{
	unsigned int l_unOuput;
	std::stringstream l_ssTmp;
	l_ssTmp << this->m_strValue;
	l_ssTmp >> l_unOuput;
	l_ssTmp.clear();
	return l_unOuput;
}

long long Variant::toLongLong() const
{
	long long l_llOuput;
	std::stringstream l_ssTmp;
	l_ssTmp << this->m_strValue;
	l_ssTmp >> l_llOuput;
	l_ssTmp.clear();
	return l_llOuput;
}

unsigned long long Variant::toULongLong() const
{
	unsigned long long l_ullOuput;
	std::stringstream l_ssTmp;
	l_ssTmp << this->m_strValue;
	l_ssTmp >> l_ullOuput;
	l_ssTmp.clear();
	return l_ullOuput;
}

bool Variant::toBool() const
{
	bool l_bOuput;
	std::stringstream l_ssTmp;
	l_ssTmp << this->m_strValue;
	l_ssTmp >> l_bOuput;
	l_ssTmp.clear();
	return l_bOuput;
}

float Variant::toFloat() const
{
	float l_fOuput;
	std::stringstream l_ssTmp;
	l_ssTmp << this->m_strValue;
	l_ssTmp >> l_fOuput;
	l_ssTmp.clear();
	return l_fOuput;
}

double Variant::toDouble() const
{
	double l_dOuput;
	std::stringstream l_ssTmp;
	l_ssTmp << this->m_strValue;
	l_ssTmp >> l_dOuput;
	l_ssTmp.clear();
	return l_dOuput;
}

size_t Variant::GetLength()
{
	return this->m_sLength;
}

};
};
