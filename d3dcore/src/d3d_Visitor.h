#pragma once

namespace d3dcore {
	class LeafContainer;
	class ComplexContainer;

	class D3DVisitor
	{
	public:
		D3DVisitor();
		~D3DVisitor();
		virtual void Visit( ComplexContainer &) = 0;
		virtual void Visit(LeafContainer &) = 0;
	};
}



