#include <iostream>

#include "system3d_info/graphic_container.h"
#include "system3d_info/graphic_visitor.h"



using namespace system3d_info;

	GraphicContainer::GraphicContainer(std::string name)
		: m_name{ name }
	{
	}


	GraphicContainer::~GraphicContainer()
	{
	}

	std::vector<std::shared_ptr<GraphicContainer>> GraphicContainer::GetChildrenContainers()
	{
		return m_children_containers;
	}

	void GraphicContainer::add_child_container(std::shared_ptr<GraphicContainer> child)
	{
		m_children_containers.push_back(child);
	}

	void GraphicContainer::accept(GraphicVisitor & visitor)
	{
		visitor.visit(*this);
		for ( auto &  child : m_children_containers) {
			
			auto child_container = *child.get();
			std::cout << "--Children:" << std::endl;
			std::cout << "    " << std::endl;
			child_container.accept(visitor);

		}
	}

	void GraphicContainer::add_property(std::string key, std::string value)
	{
		m_properties.insert({ key, value });
	}

	std::string const & GraphicContainer::get_name() const
	{
		return m_name;
	}

	std::map<std::string, std::string> GraphicContainer::getProperties()
	{
		return m_properties;
	}



