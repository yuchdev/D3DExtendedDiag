#pragma once

namespace system3d_info {

	class GraphicContainer;

	///
	/// GraphicVisitor: Visitor Design pattern for GraphicContainer
	///
	class GraphicVisitor
	{
	public:
		GraphicVisitor();
		virtual ~GraphicVisitor();
		virtual void visit(GraphicContainer &) = 0;

	};
}



