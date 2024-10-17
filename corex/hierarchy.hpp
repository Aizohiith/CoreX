#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace CoreX {
	namespace Hierarchy
	{
		class Node : public std::enable_shared_from_this<Node>
		{
			public:


				static void Print(const std::shared_ptr<Node>& Node, int Level = 0)
				{
					std::cout << std::string(Level, '\t') << "- Type: " << Node->Type() << ", Name: " << Node->Name() << std::endl;

					for (size_t C1 = 0; C1 < Node->Children_Count(); ++C1)
						Print(Node->Child(C1), Level + 1);
				}

				virtual ~Node() { Clear(); };

				std::weak_ptr<Node> Parent() { return gg_Parent; }
				std::weak_ptr<const Node> Parent() const { return gg_Parent; }
				void Set_Parent(std::weak_ptr<Node> Parent) { gg_Parent = Parent;  }
				bool Has_Parent() const { return not gg_Parent.expired();  }

				const std::string& Type() const { return gs_Type; }
				const std::string& Name() const { return gs_Name; }
				void Set_Name(const std::string& Name) { gs_Name = Name; }
				
				void Reserve(size_t Amount) { garr_Children.reserve(Amount); }

				const std::vector<std::shared_ptr<Node>>& Children() const  { return garr_Children;  };
				size_t Children_Count() const { return  garr_Children.size(); }
				bool Has_Children() const { return !garr_Children.empty(); }

				std::shared_ptr<Node> Child(size_t Index) { return garr_Children.at(Index); }
				std::shared_ptr<const Node> Child(size_t Index) const { return garr_Children.at(Index); }
				std::shared_ptr<Node> Child(const std::string& Name) { return Find_Child(Name); }
				std::shared_ptr<const Node> Child(const std::string& Name) const { return Find_Child(Name); }

				
				void Add(std::shared_ptr<Node> Child)
				{
					Child->Set_Parent(shared_from_this());
					garr_Children.emplace_back(std::move(Child));
				}

				void Remove(std::shared_ptr<Node> Child)
				{
					for (auto& E1 : garr_Children)
					{ 
						if (E1 == Child)
						{
							Child->Set_Parent({});
							garr_Children.erase(std::remove(garr_Children.begin(), garr_Children.end(), Child), garr_Children.end());
							return;
						}
					}
				}

				void Clear()
				{
					while (Has_Children())
					{
						garr_Children.back()->Clear();
						garr_Children.pop_back();
					}
				}

			protected:
				Node(const std::string& Name, const std::string& Type) : gs_Name(Name), gs_Type(Type) {}

			private:
				std::string gs_Type;
				std::string gs_Name;
				std::weak_ptr<Node> gg_Parent;
				std::vector<std::shared_ptr<Node>> garr_Children;

				std::shared_ptr<Node> Find_Child(const std::string& ps_Name) const
				{
					for (auto& E1 : garr_Children)
					{
						if (E1->Name() == ps_Name)
							return E1;
					}
					return nullptr;
				}
		};

		class Root : public Node
		{
			public:
				Root(const std::string& Name) : Node(Name, "Root") { }
		};
	}
}