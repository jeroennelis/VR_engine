#pragma once
#include "FrameBuffer.h"
#include "Scene.h"
#include <imgui_impl_glfw_gl3.h>
#include <imgui.h>
#include <ImGuizmo.h>

class EditorUiRenderer
{
public:
	EditorUiRenderer();
	~EditorUiRenderer();

	void Render(FrameBuffer & frameBuffer, Scene* scene);

private:
	void RenderTreeNode(GameObject * gameObject);
	void SetCurrentGameObject(GameObject * gameobject);

	void EditTransform(const float *CamView, float *CamProjection, float* matrix);

private:
	GameObject * m_CurrentGameObject;




};

