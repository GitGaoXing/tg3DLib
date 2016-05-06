#include "tgParam.h"
#include <assert.h>
#include <Windows.h>

namespace tg
{
namespace Core
{
Param::ObjectCreator Param::m_stuObjectCreator;

Param* Param::Instance()
{
	static Param l_oParam;
	return &l_oParam;
}

Param::Param() : m_strVersion("20160506-NIGHTLY")
{
	
}

Param::~Param()
{

}

void Param::Set(const std::string&	i_strKey,
				const Variant&		i_oValue)
{
	this->m_oUnorderedMap[i_strKey] = i_oValue;
}
	
Variant Param::Get(	const std::string&	i_strKey,
					const Variant&		i_oValue)
{
	auto l_oOutput = i_oValue;
	auto iterator = this->m_oUnorderedMap.find(i_strKey);
	if(iterator != this->m_oUnorderedMap.end())
		l_oOutput = (*iterator).second;
	else
		this->m_oUnorderedMap[i_strKey] = l_oOutput;

	return l_oOutput;
}

void Param::Clear()
{
	this->m_oUnorderedMap.clear();
}

std::vector<char> Param::Serialization() const
{
	std::vector<char> l_lstArchive;
	// size
	auto l_sSize = this->m_oUnorderedMap.size();
	for(auto i = 0; i < sizeof(l_sSize); ++i)
	{
		l_lstArchive.push_back(char((l_sSize >> (i * 8)) & 0xff));
	}
	// context
	for(auto iter : this->m_oUnorderedMap)
	{
		// key
		auto l_sKeyLen = iter.first.length();
		for(int i = 0; i < sizeof(l_sKeyLen); ++i)
		{
			l_lstArchive.push_back(char((l_sKeyLen >> (i * 8)) & 0xff));
		}
		for(int i = 0; i < l_sKeyLen; ++i)
		{
			l_lstArchive.push_back(iter.first.at(i));
		}

		// val
		auto l_sValLen = iter.second.GetLength();
		for(int i = 0; i < sizeof(l_sValLen); ++i)
		{
			l_lstArchive.push_back(char((l_sValLen >> (i * 8)) & 0xff));
		}
		for(int i = 0; i < l_sValLen; ++i)
		{
			l_lstArchive.push_back(iter.second.toByteArray()[i]);
		}
	}

	return l_lstArchive;
}

void Param::Deserialization(const std::vector<char>& i_lstArchive)
{
	size_t l_nCount = 0;
	// size
	size_t l_sSize(0);
	assert(i_lstArchive.size() - l_nCount >= sizeof(l_sSize));
	for(int i = 0; i < sizeof(l_sSize); ++i)
	{
		l_sSize |= size_t(i_lstArchive[l_nCount]) << (i * 8);
		++l_nCount;
	}
	// context
	for(size_t i = 0; i < l_sSize; ++i)
	{
		// key
		size_t l_sKeyLen = 0;
		assert(i_lstArchive.size() - l_nCount >= sizeof(l_sKeyLen));
		for(int j = 0; j < sizeof(l_sKeyLen); ++j)
		{
			l_sKeyLen |= size_t(i_lstArchive[l_nCount]) << (j * 8);
			++l_nCount;
		}
		assert(i_lstArchive.size() - l_nCount >= l_sKeyLen);
		std::string l_strKey(&i_lstArchive[l_nCount], l_sKeyLen);
		l_nCount += l_sKeyLen;
		// val
		size_t l_sValLen = 0;
		assert(i_lstArchive.size() - l_nCount >= sizeof(l_sValLen));
		for(int j = 0; j < sizeof(l_sValLen); ++j)
		{
			l_sValLen |= size_t(i_lstArchive[l_nCount]) << (j * 8);
			++l_nCount;
		}
		assert(i_lstArchive.size() - l_nCount >= l_sValLen);
		std::string l_strVal(&i_lstArchive[l_nCount], l_sValLen);
		l_nCount += l_sValLen;

		this->m_oUnorderedMap[l_strKey] = l_strVal;
	}
	assert(i_lstArchive.size() == l_nCount);
}

std::string Param::GetVersion()
{
	return this->m_strVersion;
}

/////////////////////////////////////////////////////////////
// Exe dir
std::string Param::GetExeDir()
{
	char l_cPath[MAX_PATH];
	GetModuleFileNameA(NULL, l_cPath, MAX_PATH);
	std::string l_strPath = l_cPath;
	l_strPath = l_strPath.substr(0, l_strPath.find_last_of("/\\") + 1);
	return l_strPath;
}

void SetParam(	const std::string&	i_strKey,
				const Variant&		i_oValue)
{
	Param::Instance()->Set(i_strKey, i_oValue);
}
	
Variant GetParam(	const std::string&	i_strKey,
					const Variant&		i_oValue)
{
	return Param::Instance()->Get(i_strKey, i_oValue);
}

// Version
std::string GetVersion()
{
	return Param::Instance()->GetVersion();
}

// exe dir
std::string GetExeDir()
{
	return Param::Instance()->GetExeDir();
}

}
}
#if(0)
/////////////////////////////////////////////////////////
// test for set get

void SetParam()
{
	//tg::Param::Instance()->Set("Test_0", "");							// char*
	tg::Param::Instance()->Set("Test_0", tg::Variant("abc\0def", 7));	// char*
	tg::Param::Instance()->Set("Test_1", std::string("abc"));			// string
	tg::Param::Instance()->Set("Test_2", 1);							// int
	tg::Param::Instance()->Set("Test_3", 1U);							// uint
	tg::Param::Instance()->Set("Test_4", 1LL);							// longlong
	tg::Param::Instance()->Set("Test_5", 1ULL);							// ulonglong
	tg::Param::Instance()->Set("Test_6", 1.0f);							// float
	tg::Param::Instance()->Set("Test_7", 1.0);							// double
	tg::Param::Instance()->Set("Test_8", false);						// bool
}

void GetParam()
{
	printf("########################################################\n");
	// test 0
	printf("Test for byte array:\n");
	const char* l_cTmp_0 = tg::Param::Instance()->Get("Test_0", "").toByteArray();
	for(int i = 0; i < 7; ++i)
	{
		printf("%c", l_cTmp_0[i]);
	}
	printf("\n");
	printf("\n");

	// test 1
	printf("Test for string:\n");
	printf("%s\n\n", tg::Param::Instance()->Get("Test_1", "").toString().c_str());

	// test 2
	printf("Test for int:\n");
	printf("%d\n\n", tg::Param::Instance()->Get("Test_2", "").toInt());

	// test 3
	printf("Test for uint:\n");
	printf("%u\n\n", tg::Param::Instance()->Get("Test_3", "").toUInt());

	// test 4
	printf("Test for longlong:\n");
	printf("%I64d\n\n", tg::Param::Instance()->Get("Test_4", "").toLongLong());

	// test 5
	printf("Test for ulonglong:\n");
	printf("%I64u\n\n", tg::Param::Instance()->Get("Test_5", "").toULongLong());

	// test 6
	printf("Test for float:\n");
	printf("%f\n\n", tg::Param::Instance()->Get("Test_6", "").toFloat());

	// test 7
	printf("Test for double:\n");
	printf("%lf\n\n", tg::Param::Instance()->Get("Test_7", "").toDouble());

	// test 8
	printf("Test for bool:\n");
	if(tg::Param::Instance()->Get("Test_8", "").toBool())
	{
		printf("true\n\n");
	}
	else
	{
		printf("false\n\n");
	}
}

int main(int argc, char *argv[])
{
	SetParam();
	GetParam();

	auto l_lstArchive = tg::Param::Instance()->Serialization();
	tg::Param::Instance()->Clear();
	GetParam();

	tg::Param::Instance()->Deserialization(l_lstArchive);
	GetParam();
	
	system("PAUSE");
	return 0;
}

#endif