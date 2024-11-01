#pragma once

#include "../config.hpp"

#include "corex/simply3d/node/root.hpp"

#include "../glew/shader.h" //for now, needs to be fixed
#include "../glew/mesh.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "primitives.hpp"

namespace CoreX
{
	namespace Simply3D
	{
		class  Engine
		{
			public:
				 
				Engine(const Engine&) = delete;
				Engine& operator=(const Engine&) = delete;
				static Engine& Get() { static Engine ll_Instance; return ll_Instance; }

				//Returns the root node of the engine
				static const CoreX::Simply3D::Root& Root() { return Get().gg_Root; };
				//Returns the last error loged (Empty is no error)
				static const std::string& Error_Text() { return Get().gs_Error_Text; };

				static bool Initilize() 
				{
					if (not Get().gg_Root.Initilize())
					{
						Get().gs_Error_Text = "Failed: Initilize of: " + Get().gg_Root.Name() + " of Type: " + Get().gg_Root.Type();
						return false;
					}

					return true;
				};

				static bool Setup()
				{
					if (not Get().gg_Root.Setup())
					{
						Get().gs_Error_Text = "Failed: Setup of: " + Get().gg_Root.Name() + " of Type: " + Get().gg_Root.Type();
						return false;
					}
					return true;
				};

				static void Start()
				{
					Get().gg_Root.Update();
				};
				

			private:
				Engine() : gg_Root("Engine-Root"), gs_Error_Text("") {}
				CoreX::Simply3D::Root gg_Root;
				std::string gs_Error_Text;
				
		};
	}
}
