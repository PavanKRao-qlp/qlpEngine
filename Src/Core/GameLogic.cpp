#include "GameLogic.h"
GameLogic::GameLogic()
{
	//Load Scenefile
	//Pre Cache
	TempColor = new Shader("Assets/Shader/Lambert.vert", "Assets/Shader/Lambert.frag");
	//TempColor = new Shader("Assets/Shader/LambertDeffered.vert", "Assets/Shader/LambertDeffered.frag");
	TempColor->Use();
	CurrScene = std::make_unique<SceneGraph>();
	light = std::make_unique<Light>();
	light2 = std::make_unique<Light>();
	
	ResourceLoader res;
	res.CurrShader = TempColor;

	/*cube = std::make_unique<DummyCube>();
	cube.get()->Mat->Shader = TempColor;
	auto sn = new SceneNode();
	sn->Name = "Dummy";
	sn->AddComponent(cube.get());
	CurrScene->AddNode(sn);*/

	//auto sn = res.Load3DFile("Assets/3D/Sponza/Sponza.obj");
	//auto sn = res.Load3DFile("Assets/3D/legitTesting/Girl_1.obj");
	//	auto sn = res.Load3DFile("Assets/3D/suzanne.obj");
	auto sn = res.Load3DFile("Assets/3D/Gene/Gene.obj");

	//auto sn = res.Load3DFile("Assets/3D/suzanne.obj");
	sn->LocalTranform.Scale = glm::vec3(1);
	CurrScene->AddNode(sn);

	sn = res.Load3DFile("Assets/3D/cube.obj");
	sn->LocalTranform.Scale = glm::vec3(1);
	CurrScene->AddNode(sn);

	sn = new SceneNode();
	sn->Name = "light1";
	sn->AddComponent(light.get());
	CurrScene->AddNode(sn);

	//sn = new SceneNode();
	//sn->Name = "light2";
	//sn->AddComponent(light2.get());
	//CurrScene->AddNode(sn);

	mainCam = &CurrScene.get()->MainCamera;
	mainCam->SetClipping(0.25f, 3000);
	mainCam->SetProjection(120);
	mainCam->SetPosition(glm::vec3(0, 0, 50));
	mainCam->SetLookAt(glm::vec3(0));

	TempColor->setMat4("u_PV", mainCam->GetProjectionMatrix() * mainCam->GetViewMatrix());

	yaw = -90;
	pitch = 0;
}

GameLogic::~GameLogic()
{
}

void GameLogic::Update()
{
	float time = glfwGetTime();
	float light1X = glm::sin(time) * 5;
	float light1Z = glm::cos(time) * 5;
	CurrScene.get()->RootObjects[1]->LocalTranform.Position = glm::vec3(light1X, CurrScene.get()->RootObjects[1]->LocalTranform.Position.y, light1Z);
	light.get()->GetSceneNode()->LocalTranform.Position = glm::vec3(light1X, light.get()->GetSceneNode()->LocalTranform.Position.y, light1Z);
	//light2.get()->GetSceneNode()->LocalTranform.Position = glm::vec3(light1X + 1, 5, light1Z + 1);

	float camSpeed = 1;
	if (inputWeak->IsKeyPressed(GLFW_KEY_W)) {
		mainCam->Position += mainCam->Forward * camSpeed;
	}
	if (inputWeak->IsKeyPressed(GLFW_KEY_S)) {
		mainCam->Position += mainCam->Forward * -camSpeed;
	}
	if (inputWeak->IsKeyPressed(GLFW_KEY_A)) {
		mainCam->Position += glm::normalize(glm::cross(mainCam->Forward, mainCam->Up)) * -camSpeed;
	}
	if (inputWeak->IsKeyPressed(GLFW_KEY_D)) {
		mainCam->Position += glm::normalize(glm::cross(mainCam->Forward, mainCam->Up)) * camSpeed;
	}
	if (inputWeak->IsKeyPressed(GLFW_KEY_E)) {
		mainCam->Position += mainCam->Up * camSpeed;
	}
	if (inputWeak->IsKeyPressed(GLFW_KEY_Q)) {
		mainCam->Position += mainCam->Up * -camSpeed;
	}
	if (inputWeak->IsKeyPressed(GLFW_KEY_ESCAPE)) {
		takeMouseInput = !takeMouseInput;
		inputWeak->ToggleMouse();
	}


	if (takeMouseInput) {
		MousePos pos = inputWeak->GetMousePos();
		int xpos = pos.X; int ypos = pos.Y;
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		if (inputWeak->IsKeyPressed(GLFW_KEY_UP)) {
			pitch += 0.25f;
		}if (inputWeak->IsKeyPressed(GLFW_KEY_DOWN)) {
			pitch -= 0.25f;
		}if (inputWeak->IsKeyPressed(GLFW_KEY_LEFT)) {
			yaw -= 0.25f;
		}if (inputWeak->IsKeyPressed(GLFW_KEY_RIGHT)) {
			yaw += 0.25f;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;
		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;



		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		mainCam->Forward = glm::normalize(front);
	}
	mainCam->SetPosition(mainCam->Position);
	TempColor->Use();
	TempColor->setMat4("u_PV", mainCam->GetProjectionMatrix() * mainCam->GetViewMatrix());
}
