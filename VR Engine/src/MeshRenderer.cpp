#include "MeshRenderer.h"



MeshRenderer::MeshRenderer()
{
	name = "MeshRenderer";
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Start()
{
}

void MeshRenderer::Update()
{
}

void MeshRenderer::ShowInpectorInfo()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::TreePop();
	}
}
