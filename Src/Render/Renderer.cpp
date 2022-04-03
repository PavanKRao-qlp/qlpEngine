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
	frameBuffer_DepthPre = std::make_unique<Framebuffer>(1024, 720, 0, true, true);
	frameBuffer_Gbuffer = std::make_unique<Framebuffer>(1024, 720, 4, true, true);

	RenderLayer_1 = std::make_unique<Mesh>();
	RenderLayer_1->V = new std::vector<Mesh::Vertex>();
	RenderLayer_1->I = new std::vector<unsigned int>();
	RenderLayer_1.get()->V->insert(RenderLayer_1.get()->V->end(), {
		Mesh::Vertex(glm::vec3(-1,-1,0), glm::vec2(0,0), glm::vec3(0)),
		Mesh::Vertex(glm::vec3(1,-1,0), glm::vec2(1,0), glm::vec3(0)),
		Mesh::Vertex(glm::vec3(1,1,0), glm::vec2(1,1), glm::vec3(0)),
		Mesh::Vertex(glm::vec3(-1,1,1), glm::vec2(0,1), glm::vec3(0))
		});
	RenderLayer_1.get()->I->insert(RenderLayer_1.get()->I->end(), { 0,1,2,2,3,0 });
	RenderLayer_1.get()->Mat.Shader = RenderViewShader.get();
	RenderLayer_1.get()->InitializeBuffer();

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
	// find all renderables and lighting infos
	for (SceneNode* node : SG->RootObjects) {
		IterateNode(node);
	}
	//scene data UBO
	glBufferData(GL_UNIFORM_BUFFER, 48 * activeLight.size(), NULL, GL_DYNAMIC_DRAW);
	for (int i = 0; i < activeLight.size(); i++)
	{
		auto params = activeLight[i]->GetRendParams();
		glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(params), sizeof(params), &params);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsUBO);

	//for (Mesh* node : activeMesh) { // staight forward forward-rendering
	//	node->Mat.Shader->Use();
	//	node->SubmitRender();
	//}

	DoDepthPass();
	frameBuffer_DepthPre.get()->BlitToFrameBuffer(*frameBuffer_Gbuffer, GL_DEPTH_BUFFER_BIT); //copy depth buffer to reduce overdraw
	DoGbufferPass();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderViewShader.get()->Use();
	for (int texIdx = 0; texIdx < frameBuffer_Gbuffer.get()->texSize; texIdx++) {
		glActiveTexture(GLenum(GL_TEXTURE0 + texIdx));
		glBindTexture(GL_TEXTURE_2D, frameBuffer_Gbuffer.get()->GetColorAttachment(texIdx));
	}
	RenderViewShader.get()->setInt("u_diffuse", 0);
	RenderViewShader.get()->setInt("u_position", 1);
	RenderViewShader.get()->setInt("u_normal", 2);
	RenderLayer_1.get()->SubmitRender();
}

void Renderer::IterateNode(SceneNode* node) {
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
				IterateNode(node);
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

void Renderer::DoDepthPass()
{
	frameBuffer_DepthPre.get()->StartWriting();
	frameBuffer_DepthPre.get()->ClearBuffer();
	for (Mesh* node : activeMesh) {
		node->Mat.Shader->Use();
		node->SubmitRender();
	}
	frameBuffer_DepthPre.get()->StopWriting();

}

void Renderer::DoGbufferPass()
{
	frameBuffer_Gbuffer.get()->StartWriting();
	frameBuffer_Gbuffer.get()->ClearBuffer();	
	for (Mesh* node : activeMesh) {
		node->Mat.Shader->Use();
		node->SubmitRender();
	}
	frameBuffer_Gbuffer.get()->StopWriting();

}
