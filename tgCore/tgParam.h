#ifndef ___tgParam___
#define ___tgParam___

#include "tgPrecompile.h"
#include "tgVariant.h"
#include <unordered_map>

const int MAX_PATH_SIZE = 1024;
namespace tg
{
namespace Core
{

class Param
{
public:
	TG_EXPORT static Param* Instance();

	TG_EXPORT void Set(	const std::string&	i_strKey,
						const Variant&		i_oValue);
	
	TG_EXPORT Variant Get(	const std::string&	i_strKey,
							const Variant&		i_oValue);

	TG_EXPORT void Clear();

	TG_EXPORT std::vector<char> Serialization() const;

	TG_EXPORT void Deserialization(const std::vector<char>& i_lstArchive);

	// Version
	TG_EXPORT std::string GetVersion(); 

	// exe dir
	TG_EXPORT std::string GetExeDir();

private:
	Param();

	~Param();

	Param(const Param &);

	Param & operator = (const Param &);

	std::unordered_map<std::string, Variant>		m_oUnorderedMap;	// hash table: key is a string, value is a tg::Variant
	std::string m_strVersion;

	struct ObjectCreator
	{
		ObjectCreator()
		{
			Param::Instance();
		}
	};
	static ObjectCreator m_stuObjectCreator;

};

TG_EXPORT void SetParam(const std::string&	i_strKey,
						const Variant&		i_oValue);
	
TG_EXPORT Variant GetParam(	const std::string&	i_strKey,
							const Variant&		i_oValue);

// Version
TG_EXPORT std::string GetVersion(); 

// exe dir
TG_EXPORT std::string GetExeDir();

};
};
#endif