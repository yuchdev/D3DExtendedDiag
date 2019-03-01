#pragma once
#include "d3d_Container.h"

namespace d3dcore {
	class D3DVisitor;

	class LeafContainer : public D3DContainer
	{
	public:
		LeafContainer(std::string name);
		~LeafContainer();


		// Inherited via D3DContainer
		virtual void Accept(D3DVisitor &) override;

	};
}


