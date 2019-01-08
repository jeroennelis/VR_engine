#include "EditorUiRenderer.h"



EditorUiRenderer::EditorUiRenderer()
{
}


EditorUiRenderer::~EditorUiRenderer()
{
}

void EditorUiRenderer::Render(FrameBuffer & frameBuffer, Scene * scene)
{
	ImGui_ImplGlfwGL3_NewFrame();
	ImGui::Begin("Game");

	ImVec2 startPos = ImGui::GetCursorScreenPos();
	ImVec2 size = ImGui::GetWindowSize();
	ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);
	ImGui::GetWindowDrawList()->AddImage(
		(void *)frameBuffer.GetTexture(), startPos,
		endPos, ImVec2(0, 1), ImVec2(1, 0));
	//ImGui::Text("frame rate: ");
	ImGui::End();

	ImGui::Begin("Hierarchy");
	std::vector<GameObject*> * gameObjects = scene->getGameObjects();
	for (GameObject *gameObject : *gameObjects)
	{
		RenderTreeNode(gameObject);
	}

	ImGui::End();

	ImGui::Begin("Inspector");

	if (m_CurrentGameObject)
	{
		for (Component * component : *m_CurrentGameObject->getComponents())
		{
			component->ShowInpectorInfo();
		}
	}
		

	ImGui::End();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUiRenderer::RenderTreeNode(GameObject * gameObject)
{
	std::string name = gameObject->GetName();

	if (ImGui::TreeNode(name.c_str()))
	{
		char label[] = "this";
		ImGui::Bullet(); ImGui::Selectable(label, false);
		if ((ImGui::IsItemHovered() || ImGui::IsItemFocused()) && ImGui::IsMouseClicked(0))
			SetCurrentGameObject(gameObject);
		std::vector<GameObject*> * childObjects = gameObject->getGameObjects();
		for (GameObject* child : *childObjects)
		{
			RenderTreeNode(child);
		}
		ImGui::TreePop();
	}


}

void EditorUiRenderer::SetCurrentGameObject(GameObject * gameobject)
{
	m_CurrentGameObject = gameobject;
}

void EditorUiRenderer::EditTransform(const float *CamView, float *CamProjection, float* matrix)
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;

	if (ImGui::IsKeyPressed(90))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82)) // r Key
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
	ImGui::InputFloat3("Tr", matrixTranslation, 3);
	ImGui::InputFloat3("Rt", matrixRotation, 3);
	ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

	if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	{
		if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
			mCurrentGizmoMode = ImGuizmo::LOCAL;
		ImGui::SameLine();
		if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
			mCurrentGizmoMode = ImGuizmo::WORLD;
	}
	if (ImGui::IsKeyPressed(83))
		useSnap = !useSnap;
	ImGui::Checkbox("", &useSnap);
	ImGui::SameLine();

	switch (mCurrentGizmoOperation)
	{
	case ImGuizmo::TRANSLATE:
		ImGui::InputFloat3("Snap", &snap[0]);
		break;
	case ImGuizmo::ROTATE:
		ImGui::InputFloat("Angle Snap", &snap[0]);
		break;
	case ImGuizmo::SCALE:
		ImGui::InputFloat("Scale Snap", &snap[0]);
		break;
	}
	ImGui::Checkbox("Bound Sizing", &boundSizing);
	if (boundSizing)
	{
		ImGui::PushID(3);
		ImGui::Checkbox("", &boundSizingSnap);
		ImGui::SameLine();
		ImGui::InputFloat3("Snap", boundsSnap);
		ImGui::PopID();
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(CamView, CamProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
}


