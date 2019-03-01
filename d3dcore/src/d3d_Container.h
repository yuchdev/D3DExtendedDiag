#pragma once

#include <string>
#include <map>
//#include <any>
namespace d3dcore {

	class D3DVisitor;

	class D3DContainer
	{
	public:
		D3DContainer(std::string name);
		~D3DContainer();
		virtual void Accept(D3DVisitor &) = 0;
		void AddProperty(std::string key, std::string value);

	private:
		std::string m_name; //Name of container
		std::map<std::string, std::string> m_properties;//todo: using std::any
	};
}


