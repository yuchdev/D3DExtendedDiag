#pragma once
#include "d3d_Container.h"

#include <vector>
#include <memory>

namespace d3dcore {

	class D3DVisitor;

	using D3DContainerPtr = std::shared_ptr<D3DContainer>;

	class ComplexContainer : public D3DContainer
	{		
	public:
		ComplexContainer(std::string name);
		~ComplexContainer();

		std::vector<D3DContainerPtr> GetChildrenContainers();
		void AddChildContainer(D3DContainerPtr child);

	private:
		std::vector<D3DContainerPtr> m_childrenContainers;

		// Inherited via D3DContainer
		virtual void Accept(D3DVisitor &) override;
	};

}

