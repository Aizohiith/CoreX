#include "corex/simply3d/node/node.hpp"

namespace CoreX
{
	namespace Simply3D
	{
		class Root : public CoreX::Simply3D::Node
		{
			public:
				Root(const std::string& Name) : CoreX::Simply3D::Node(Name, "Root") {};

				bool Initilize() override
				{
					return true;
				}

				bool Setup() override
				{
					return false;
				}
				void Update() override
				{

				}

				void Render() override
				{

				}
		};
	}
}