#pragma once


#include <vector>
#include <memory>
#include <map>

namespace system3d_info {

	class GraphicVisitor;

	

	class GraphicContainer 
	{		
	public:
		GraphicContainer(std::string name);
		~GraphicContainer();

		std::vector<std::shared_ptr<GraphicContainer>> GetChildrenContainers();
		void add_child_container(std::shared_ptr<GraphicContainer> child);
		virtual void accept(GraphicVisitor &) ;
		void add_property(std::string key, std::string value);
		std::string const& get_name() const;
		std::map<std::string, std::string> getProperties();

	private:
		std::vector<std::shared_ptr<GraphicContainer>> m_children_containers;
		std::map<std::string, std::string> m_properties;//todo: using std::any
		std::string m_name;

		
		
	};

}
