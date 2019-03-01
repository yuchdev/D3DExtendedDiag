#include "d3d_Container.h"

namespace d3dcore {

	D3DContainer::D3DContainer(std::string name)
		: m_name{name}
	{
	}


	D3DContainer::~D3DContainer()
	{
	}
	void D3DContainer::AddProperty( std::string key, std::string value)
	{
		m_properties.insert({ key, value });
	}
}


