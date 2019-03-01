#include "leafContainer.h"

#include "d3d_Visitor.h"

namespace d3dcore {
	LeafContainer::LeafContainer(std::string name)
		: D3DContainer(name)
	{
	}


	LeafContainer::~LeafContainer()
	{
	}

	//override the Accept method: refer Vistor Pattern
	void LeafContainer::Accept(D3DVisitor & visitor)
	{   //doing some implementation
		visitor.Visit(*this);
	}
}


