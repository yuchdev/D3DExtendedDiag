#pragma once

namespace system3d_info {

	class GraphicContainer;

	class GraphicVisitor
	{
	public:
		GraphicVisitor();
		~GraphicVisitor();
		virtual void visit(GraphicContainer &) = 0;
		//virtual void Visit(LeafContainer &) = 0;
	};
}



