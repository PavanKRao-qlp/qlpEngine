#include "Renderer.h"
#include "../../DummyCube.h"

Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST );
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Renderer::~Renderer()
{
}

bool Renderer::Init()
{
	return false;
}

void Renderer::Update()
{
	//GET SCENE 

}

void Renderer::RenderGrapgh(SceneGraph* SG)
{
	rendGraph.clear();
	curSG = SG;
	for (SceneNode* node : SG->RootObjects) {
		RenderNode(node);
	}

	//std::sort(rendGraph.begin(), rendGraph.end(), &Renderer::IcompareCloserToCamera);
	/* std::sort(rendGraph.begin(), rendGraph.end(), [SG](const auto& l, const auto& r) {
		glm::vec3  Ipos = l->GetWorldTranform()[3];
		glm::vec3  Jpos = r->GetWorldTranform()[3];
		glm::vec3  camPos = SG->MainCamera.Position;
		float I = glm::distance(Ipos, camPos);
		float J = glm::distance(Ipos, camPos);
		return(Ipos.z > Jpos.z);
		}); */

	for (Mesh* node : rendGraph) {
		node->SubmitRender();
	}

}

void Renderer::RenderNode(SceneNode* node) {
	if (node->IsVisible()) {
		for (auto component : node->GetComponents()) {
			Mesh* mesh = dynamic_cast<Mesh*>(component);
			//temp ugly  sort
			if (mesh)  rendGraph.push_back(mesh);
			else
			{
				DummyCube* D = dynamic_cast<DummyCube*>(node);
				if (D) D->SubmitRender();
			}
		}
		//}
		if (node->GetChildren().size() > 0) {
			for (SceneNode* node : node->GetChildren()) {
				RenderNode(node);
			}
		}

	}
}

bool Renderer::IcompareCloserToCamera(Mesh* i, Mesh* j)
{
	//glm::vec3  Ipos = i->GetWorldTranform()[3];
//	glm::vec3  Jpos = j->GetWorldTranform()[3];
//	glm::vec3  camPos  = curSG->MainCamera.Position;
	//float I = glm::distance(Ipos, camPos);
	//float J = glm::distance(Ipos, camPos);
	//return(I > J);
	return false;
}
