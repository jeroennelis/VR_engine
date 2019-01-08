#pragma once
#include "Component.h"
#include "TexturedModel.h"
class MeshRenderer :
	public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	// Inherited via Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void ShowInpectorInfo() override;

	inline TexturedModel * GetModel() { return m_Model; }
	inline void SetModel(TexturedModel * model) { m_Model = model; }

private:
	TexturedModel * m_Model;
};

