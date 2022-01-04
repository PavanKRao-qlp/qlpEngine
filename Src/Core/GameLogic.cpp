#include "GameLogic.h"
GameLogic::GameLogic()
{
	//Load Scenefile
	//Pre Cache
	TempColor = new Shader("Assets/Shader/Lambert.vert", "Assets/Shader/Lambert.frag");
	TempColor->Use();
	CurrScene = std::make_unique<SceneGraph>();
	light = std::make_unique<Light>();

	//cube = std::make_unique<DummyCube>();
	//cube.get()->Mat->Shader = TempColor;
	//CurrScene->AddNode(cube.get());
	ResourceLoader res;
	res.CurrShader = TempColor;
	//auto sn = dynamic_cast<SceneNode*>(cube.get());
	//auto sn = res.Load3DFile("Assets/3D/Sponza/Sponza.obj");
	//auto sn = res.Load3DFile("Assets/3D/legitTesting/Girl_1.obj");
	auto sn = res.Load3DFile("Assets/3D/suzanne.obj");
	//auto sn = res.Load3DFile("Assets/3D/Gene/Gene.obj");
	sn->LocalTranform.Scale = glm::vec3(1);
	CurrScene->AddNode(sn);

	sn = res.Load3DFile("Assets/3D/cube.obj");
	sn->LocalTranform.Position.x = 5;
	CurrScene->AddNode(sn);

	sn = new SceneNode();
	sn->Name = "light1";
	sn->AddComponent(light.get());
	CurrScene->AddNode(sn);

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
	float light1X = glm::sin(time) * 10;
	float light1Z = glm::cos(time) * 10;
	CurrScene.get()->RootObjects[1]->LocalTranform.Position = glm::vec3(light1X, 0, light1Z);
	light.get()->GetSceneNode()->LocalTranform.Position = glm::vec3(light1X, 0, light1Z);

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
	TempColor->setMat4("u_PV", mainCam->GetProjectionMatrix() * mainCam->GetViewMatrix());
}
