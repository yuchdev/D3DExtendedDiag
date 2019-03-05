#include <iostream>
#include <string>

#include "system3d_info/console_visitor.h"
#include "system3d_info/graphic_container.h"



using namespace system3d_info;

ConsoleVisitor::ConsoleVisitor()
{
}


ConsoleVisitor::~ConsoleVisitor()
{
}

void ConsoleVisitor::visit(GraphicContainer & parent_container)
{
	auto children_containers = parent_container.GetChildrenContainers();
	auto properties = parent_container.getProperties();
	std::cout << parent_container.get_name() << std::endl;
	std::cout << "--Properties:" << std::endl;
	for (const auto& kv : properties) {
		std::cout << "---"<<kv.first << ":" << kv.second << std::endl;
	}
	
}


