#pragma once
#include "Component.h"
#include "TexturedModel.h"
class Renderer :
	public Component
{
public:
	Renderer();
	~Renderer();

	// Inherited via Component
	virtual void Start() override;
	virtual void Update() override;

	inline TexturedModel * GetModel() { return m_Model; }
	inline void SetModel(TexturedModel * model) { m_Model = model; }

private:
	TexturedModel * m_Model;
};

