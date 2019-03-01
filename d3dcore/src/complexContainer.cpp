#include "complexContainer.h"

#include "d3d_Visitor.h"

namespace d3dcore {

	ComplexContainer::ComplexContainer(std::string name)
		: D3DContainer(name)
	{
	}


	ComplexContainer::~ComplexContainer()
	{
	}

	std::vector<D3DContainerPtr> ComplexContainer::GetChildrenContainers()
	{
		return m_childrenContainers;
	}

	void ComplexContainer::AddChildContainer(D3DContainerPtr child)
	{
		m_childrenContainers.push_back(child);
	}

	void ComplexContainer::Accept(D3DVisitor & visitor)
	{
		visitor.Visit(*this);
		//for (const auto & child : m_childrenContainers) {
	//		visitor.Visit(child.get());
	//	}
	}
}


