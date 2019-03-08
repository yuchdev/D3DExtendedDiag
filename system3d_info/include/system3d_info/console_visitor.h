#pragma once

#include "graphic_visitor.h"

namespace system3d_info {

	class GraphicContainer;


	class ConsoleVisitor :public GraphicVisitor
	{
	public:
		ConsoleVisitor();
		~ConsoleVisitor();

		// Inherited via GraphicVisitor
		virtual void visit(GraphicContainer &) override;



	};
}

