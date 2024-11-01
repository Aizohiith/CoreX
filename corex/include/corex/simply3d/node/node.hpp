#include "corex/core/hierarchy.hpp"


namespace CoreX
{
	namespace Simply3D
	{
		class Node : public CoreX::Hierarchy::Node
		{
			protected:
				virtual bool Initilize() = 0;;
				virtual bool Setup() = 0;
				virtual void Update() = 0;
				virtual void Render() = 0;

				Node(const std::string& Name, const std::string& Type) : CoreX::Hierarchy::Node(Name, Type) {};

		};
	}
}