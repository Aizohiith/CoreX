#include "corex/simply3d/simply3d.h"

int main()
{
	if (not CoreX::Simply3D::Engine::Initilize())
	{
		std::cerr << CoreX::Simply3D::Engine::Error_Text() << std::endl;
		return -1;
	}

	if (not CoreX::Simply3D::Engine::Setup())
	{
		std::cerr << CoreX::Simply3D::Engine::Error_Text() << std::endl;
		return -1;
	}

	CoreX::Simply3D::Engine::Start();

	return 0;
}