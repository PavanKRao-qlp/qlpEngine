#include "Renderer.h"
#include "../../DummyCube.h"

Renderer::Renderer()
{
	Init();
}

Renderer::~Renderer()
{
}

bool Renderer::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glGenBuffers(1, &lightsUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);

	RenderViewShader = std::make_unique<Shader>("Assets/Shader/RenderView.vert", "Assets/Shader/RenderView.frag");
	frameBuffer_clr = std::make_unique<Framebuffer>(1024, 720, 4, true, true);

	DrawQuad1 = std::make_unique<Mesh>();
	DrawQuad1->V = new std::vector<Mesh::Vertex>();
	DrawQuad1->I = new std::vector<unsigned int>();
	DrawQuad1.get()->V->push_back(Mesh::Vertex(glm::vec3(-1,-1,0), glm::vec2(0,0), glm::vec3(0)));
	DrawQuad1.get()->V->push_back(Mesh::Vertex(glm::vec3(1,-1,0), glm::vec2(1,0), glm::vec3(0)));
	DrawQuad1.get()->V->push_back(Mesh::Vertex(glm::vec3(1,1,0), glm::vec2(1,1), glm::vec3(0)));
	DrawQuad1.get()->V->push_back(Mesh::Vertex(glm::vec3(-1,1,1), glm::vec2(0,1), glm::vec3(0)));
	unsigned int index[6] = {0,1,2,2,3,0};
	DrawQuad1.get()->I->insert(DrawQuad1.get()->I->end(), std::begin(index) , std::end(index));
	DrawQuad1.get()->Mat.Shader = RenderViewShader.get();
	DrawQuad1.get()->InitializeBuffer();

	return false;
}

void Renderer::Update()
{
	//GET SCENE 

}

void Renderer::RenderGrapgh(SceneGraph* SG)
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	activeMesh.clear();
	activeLight.clear();
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

	glBufferData(GL_UNIFORM_BUFFER, 48 * activeLight.size(), NULL, GL_DYNAMIC_DRAW);
	for (int i = 0; i < activeLight.size(); i++)
	{
		auto params = activeLight[i]->GetRendParams();
		glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(params), sizeof(params), &params);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsUBO);

	for (Mesh* node : activeMesh) {
		node->Mat.Shader->Use();
		node->SubmitRender();
	}

	DoTestPass();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderViewShader.get()->Use();
	for (int texIdx = 0; texIdx < frameBuffer_clr.get()->texSize; texIdx++) {
		glActiveTexture(GLenum(GL_TEXTURE0 + texIdx));
		glBindTexture(GL_TEXTURE_2D, frameBuffer_clr.get()->GetColorAttachment(texIdx));
	}
	RenderViewShader.get()->setInt("u_diffuse", 0);
	RenderViewShader.get()->setInt("u_position", 1);
	RenderViewShader.get()->setInt("u_normal", 2);
	DrawQuad1.get()->SubmitRender();
}

void Renderer::RenderNode(SceneNode* node) {
	if (node->IsVisible()) {
		for (auto component : node->GetComponents()) {
			//temp ugly  sort
			if (dynamic_cast<Mesh*>(component)) {
				activeMesh.push_back(dynamic_cast<Mesh*>(component));
			} else if (dynamic_cast<Light*>(component)) {
			  activeLight.push_back(dynamic_cast<Light*>(component));
			}
			/*else
			{
				DummyCube* D = dynamic_cast<DummyCube*>(node->GetComponents()[0]);
				if (D) D->SubmitRender();
			}*/
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

void Renderer::DoTestPass()
{
	frameBuffer_clr.get()->StartWriting();
	frameBuffer_clr.get()->ClearBuffer();	
	for (Mesh* node : activeMesh) {
		node->Mat.Shader->Use();
		node->SubmitRender();
	}
	frameBuffer_clr.get()->EndWriting();

}
