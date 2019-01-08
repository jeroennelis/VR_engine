#include "GameObject.h"



GameObject::GameObject(const std::string & name)
	:m_Name(name)
{
	Start();
}


GameObject::~GameObject()
{
}

void GameObject::Start()
{
	std::cout << "created: " << m_Name.c_str() << std::endl;
	AddComponent(new Transform());
}

void GameObject::Update()
{
	for(Component *component : m_Components)
	{
		component->Update();
	}

	for (GameObject *child : m_ChildObjects)
	{
		child->Update();
	}
}

void GameObject::AddChild(GameObject * child)
{
	m_ChildObjects.push_back(child);
}

void GameObject::AddComponent(Component * component)
{
	m_Components.push_back(component);
}
