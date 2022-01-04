#include "Hud.h"

Hud::Hud(void* windowPtr)
{
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)windowPtr, true);
}

Hud::~Hud()
{
}

void Hud::UpdateUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Begin("Model",0,window_flags);
    //ImGui::("Camera Pos : %s", sg_->MainCamera.Position);
    ImGui::Separator();
    ImGui::Text("Camera");
    ImGui::InputFloat3("Position", &sg_->MainCamera.Position[0], "%.3f", 0);
    ImGui::Separator();
    ImGui::Text("Hierarchy");
    for (auto node : sg_->RootObjects) {
        DrawHierarchyNode(node);
    }
    ImGui::End();
    if (selectedNode != nullptr) {
        ImGui::SetNextWindowBgAlpha(0.35f);
        ImGui::SetNextWindowPos(ImVec2(1024, 0), 0, ImVec2(1, 0));
        ImGui::Begin("Info", 0, window_flags);
        DrawnNodeInfo(selectedNode);
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Hud::SetSceneGrapgh(SceneGraph* SG)
{
	this->sg_ = SG;
}

void Hud::DrawHierarchyNode(SceneNode* node)
{
    ImGuiTreeNodeFlags flags = ((selectedNode == node) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    if (node->GetChildren().size() == 0)  flags |= ImGuiTreeNodeFlags_Leaf;
    bool isTreeExpanded = ImGui::TreeNodeEx((void*)node, flags, node->Name.c_str());
    bool isTreeClicked = ImGui::IsItemClicked();
    if (isTreeClicked) selectedNode = node;
    if (isTreeExpanded)
    {
        if (node->GetChildren().size() > 0) {
            for (auto node : node->GetChildren()) {
                DrawHierarchyNode(node);
            }
        }
        ImGui::TreePop();
    }

}

void Hud::DrawnNodeInfo(SceneNode* node) {
    ImGui::Checkbox("", &node->Visible);
    ImGui::SameLine();
    ImGui::Text("%s", node->Name.c_str());
    ImGui::Separator();
    if (ImGui::CollapsingHeader("Tranform", ImGuiTreeNodeFlags_OpenOnArrow|ImGuiTreeNodeFlags_DefaultOpen ))
    {
        ImGui::InputFloat3("Position", &node->LocalTranform.Position[0], "%.3f", ImGuiInputTextFlags_None);
        ImGui::InputFloat3("Rotation", &node->LocalTranform.Rotation[0], "%.3f", ImGuiInputTextFlags_None);
        ImGui::InputFloat3("Scale", &node->LocalTranform.Scale[0], "%.3f", ImGuiInputTextFlags_None);

    }
    for (auto component : node->GetComponents()) {
        DrawComponent(component);
        ImGui::Separator();
    }
    // if()
}

void Hud::DrawComponent(IComponent* component)
{
    if (ImGui::CollapsingHeader(component->GetComponentName(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen)) {
#pragma region Mesh
        Mesh* mesh = dynamic_cast<Mesh*>(component);
        if (mesh) {
            ImGui::Text("Vertices %d", mesh->V->size());
            ImGui::Separator();
            ImGui::Image((void*)(intptr_t)mesh->Mat.DiffuseTex->TexId, ImVec2(32, 32));
            if (ImGui::IsItemHovered()) {
                ImGui::BeginTooltip();
                ImGui::Image((void*)(intptr_t)mesh->Mat.DiffuseTex->TexId, ImVec2(256, 256));
                ImGui::EndTooltip();
            }
            ImGui::SameLine();
            ImGui::ColorEdit3("Ambient", &mesh->Mat.AmbientColor[0]);
        }
#pragma endregion
        Light* light = dynamic_cast<Light*>(component);
        if (light) {
            ImGui::ColorEdit3("Color", &light->Color[0]);
            ImGui::DragFloat("Intensity",&light->Intensity ,0.25f,0 , 20, "%.3f");
        }
    }
}


