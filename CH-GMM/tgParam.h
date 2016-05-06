#ifndef ___tgParam___
#define ___tgParam___

#include "tgVariant.h"
#include <unordered_map>

namespace tg
{

class Param
{
public:
	static Param* Instance();

	void Set(	const std::string& i_strKey,
				const tg::Variant& i_oValue);
	
	tg::Variant Get(const std::string& i_strKey,
					const tg::Variant& i_oValue);

	void Clear();

	std::vector<char> Serialization() const;

	void Deserialization(const std::vector<char>& i_lstArchive);

private:
	Param();

	~Param();

	Param(const Param &);

	Param & operator = (const Param &);

	std::unordered_map<std::string, tg::Variant>		m_oUnorderedMap;	// hash table: key is a string, value is a tg::Variant

	struct ObjectCreator
	{
		ObjectCreator()
		{
			Param::Instance();
		}
	};
	static ObjectCreator m_stuObjectCreator;

};

}

#endif