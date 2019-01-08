#pragma once
#include <iostream>
#include <vector>

#include "Component.h"
#include "Transform.h"


class GameObject
{
public:
	GameObject(const std::string & name);
	~GameObject();

	virtual void Start();
	virtual void Update();

	void AddChild(GameObject *child);
	void AddComponent(Component *component);

	inline std::string & GetName() { return m_Name; };
	inline std::vector<GameObject*> * getGameObjects() { return &m_ChildObjects; }

	inline std::vector<Component*> * getComponents() { return &m_Components; }

	template <class component_type>
	component_type* GetComponent()
	{
		for(auto comp: m_Components)
		if (component_type* c = dynamic_cast<component_type*>(comp))
			return c;
		return NULL;
	}
	

private:
	std::string m_Name;
	std::vector<GameObject *> m_ChildObjects;
	std::vector<Component *> m_Components;
};

