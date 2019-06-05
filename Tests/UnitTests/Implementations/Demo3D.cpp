#include <Boxes/Demo3D.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Demo3D::Demo3D(void)
:
_useOrbit(true),
_crate1(),
_crate2(),
_floor(),
_robot(),
_bowlingPin(),
_bunny(),
_light(),
_lightMovAngle(0.0f),
_orbitCamera(),
_fpsCamera()
{

}

Demo3D::~Demo3D(void)
{  }

void Demo3D::v_InitLevel(U32 id, S32 w, S32 h, const KE::Color& c)
{
	Level::SetID(id);
	Level::SetLevelWidth(w);
	Level::SetLevelHeight(h);
	Level::SetBackgroundColor(c);

	//Set up Cameras
	F32 left = -25.0f;
	F32 right = 25.0f;
	F32 bottom = -25.0f;
	F32 top = 25.0f;

	//Load Light Shader
	//Light
	std::vector<KE::ShaderData> shaderData;
	KE::ShaderData vs;
	vs.filePath = "../Assets/Shaders/light_vertex.glsl";
	vs.type = KE::ShaderType::VERTEX;
	shaderData.push_back(vs);

	KE::ShaderData fs;
	fs.filePath = "../Assets/Shaders/light_fragment.glsl";
	fs.type = KE::ShaderType::FRAGMENT;
	shaderData.push_back(fs);

	U32 ligthShaderID = 102;

	KE::ShaderManager::Instance()->LoadShader(ligthShaderID, shaderData);

	_orbitCamera.SetPerspective(45.0f, static_cast<F32>(w) / static_cast<F32>(h), 0.1f, 100.0f);
	//_orbitCamera.SetOrthographic(left, right, bottom, top, 0.01f, 100.0f);
	_orbitCamera.SetPosition(0.0f, 0.0f, 0.0f);
	//Offset for robot to look right
	KM::Vector4 targetPos {};
	targetPos = _robot.GetPosition();
	_orbitCamera.SetTarget(targetPos[0], targetPos[1] + 3.0f, targetPos[2]);
	_orbitCamera.SetUpVector(0.0f, 1.0f, 0.0f);
	_orbitCamera.SetMouseSensitivity(0.25f);

	_fpsCamera.SetPerspective(45.0f, static_cast<F32>(w) / static_cast<F32>(h), 0.1f, 100.0f);
	//_fpsCamera.SetOrthographic(left, right, bottom, top, -100.0f, 100.0f);
	_fpsCamera.SetPosition(0.0f, 0.0f, 0.0f);
	_fpsCamera.SetMoveSpeed(10.0f);
	_fpsCamera.SetMouseSensitivity(0.1f);
	_fpsCamera.SetDeadZone(0.2f);

	Level::SetCamera(&_orbitCamera);

	//Crate1	
	_crate1.InitCube("../Assets/Models/Course/crate.obj");
	_crate1.SetPosition(-5.0f, 0.0f, 0.0f);
	_crate1.SetTexture(KE::TextureManager::Instance()->GetTexture(500));
	_crate1.SetColor(1.0f, 0.0f, 0.0f);
	Level::AddObjectToLevel(_crate1);

	//Crate2
	_crate2.InitCube("../Assets/Models/Course/crate.obj");
	_crate2.SetPosition(5.0f, 0.0f, 0.0f);
	_crate2.SetTexture(KE::TextureManager::Instance()->GetTexture(501));
	_crate2.SetColor(0.0f, 1.0f, 0.0f);
	//_crate2.SetActive(false);
	Level::AddObjectToLevel(_crate2);

	//Robot	
	_robot.InitCube("../Assets/Models/Course/robot.obj");
	_robot.SetPosition(0.0f, -1.0f, -2.0f);
	_robot.SetTexture(KE::TextureManager::Instance()->GetTexture(502));
	_robot.SetColor(0.5f, 0.5f, 0.5f);
	//_robot.SetActive(false);
	Level::AddObjectToLevel(_robot);

	//Bowling Pin
	_bowlingPin.InitCube("../Assets/Models/Course/bowling_pin.obj");
	_bowlingPin.SetPosition(0.0f, 0.0f, 4.0f);
	_bowlingPin.SetScale(0.1f, 0.1f, 0.1f);
	_bowlingPin.SetActive(false);
	//_bowlingPin.SetTexture(pinTexture);
	Level::AddObjectToLevel(_bowlingPin);
	
	//Bunny
	_bunny.InitCube("../Assets/Models/Course/bunny.obj");
	_bunny.SetPosition(-2.0f, 0.0f, 0.0f);
	_bunny.SetScale(0.7f, 0.7f, 0.7f);
	//_bunny.SetActive(false);
	//_bunny.SetTexture(KE::TextureManager::Instance()->GetTexture(503));
	Level::AddObjectToLevel(_bunny);

	//Floor
	_floor.InitCube("../Assets/Models/Course/floor.obj");
	_floor.SetPosition(0.0f, -1.0f, 0.0f);
	_floor.SetScale(10.0f, 0.1f, 10.0f);
	_floor.SetTexture(KE::TextureManager::Instance()->GetTexture(504));
	//_floor.SetActive(false);
	Level::AddObjectToLevel(_floor);

	

	_light.InitCube("../Assets/Models/Course/light.obj", ligthShaderID);
	_light.SetPosition(0.0f, 2.0f, 8.0f);
	_light.SetActiveUpdate(false);
	_light.SetActive(false);
	Level::AddObjectToLevel(_light);	

	KE::Color lightColor(1.0f, 1.0f, 1.0f);	
	lightColor.UseAlpha(false);
	KM::Point lightPos = _light.GetPosition();
	KM::Vector3 lightDirection{ 0.0f, -0.9f, -0.17f };
	KE::Color ambient{ 1.0f, 1.0f, 1.0f };
	ambient.UseAlpha(false);
	KE::Color specular{ 1.0f, 1.0f, 1.0f };
	specular.UseAlpha(false);

	//Add the following: 
	// point:
	// set uniform name = light.constant = 1.0f
	// set uniform name = light.linear = 0.07f
	// set uniform name = light.exponent = 0.017f
	//
	// spot:
	// set uniform name = light.cosInnerCone = cos(Randian(15.0f))
	// set uniform name = light.cosOuterCone = cos(Radian(20.0f))
	// set uniform name = light.on = bool flashLightOn. Use F key to toggle on and off. 

	Level::SetObjectUniforms("light.ambient", ambient);
	Level::SetObjectUniforms("light.diffuse", lightColor);
	Level::SetObjectUniforms("light.specular", specular);
	Level::SetObjectUniforms("light.position", lightPos);
	Level::SetObjectUniforms("light.direction", lightDirection);


	_light.SetUniform("lightColor", lightColor);


	KE::Color ambientMat{ 0.1f, 0.1f, 0.1f };
	ambientMat.UseAlpha(false);
	KE::Color specularMat{ 0.5f, 0.5f, 0.5f };
	specularMat.UseAlpha(false);
	F32 shininess = 150.0f;
	
	Level::SetObjectUniforms("material.ambient", ambientMat);
	Level::SetObjectUniforms("material.specular", specularMat);
	Level::SetObjectUniforms("material.shininess", shininess);

	_crate1.SetUniformSampler("material.diffuseMap", 0); //Texture slot 0
	_crate2.SetUniformSampler("material.diffuseMap", 0); //Texture slot 0
	_robot.SetUniformSampler("material.diffuseMap", 0); //Texture slot 0
	_bowlingPin.SetUniformSampler("material.diffuseMap", 0); //Texture slot 0
	_bunny.SetUniformSampler("material.diffuseMap", 0); //Texture slot 0
	_floor.SetUniformSampler("material.diffuseMap", 0); //Texture slot 0

}

void Demo3D::v_Update(void)
{
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE))
	{
		KE::Engine::Instance()->SetActiveLevel(2);
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::F11))
	{
		KE::GameWindow::Instance()->ToggleWireFrame();
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::F1))
	{
		_useOrbit = !_useOrbit;

		if(!_useOrbit)
		{
			Level::SetCamera(&_fpsCamera);
			KE::GameWindow::Instance()->DisableMouseCursor();
		}
		else
		{
			Level::SetCamera(&_orbitCamera);
			KE::GameWindow::Instance()->EnableMouseCursor();
		}
	}

	KM::Vector4 viewPos;

	if(_useOrbit)
	{
		viewPos = _orbitCamera.GetPosition();

		if(KE::Controller::Instance()->GetKeyHeld(KE::LEFT_MOUSE))
		{
			_orbitCamera.Orbit();
		}

		if(KE::Controller::Instance()->GetKeyHeld(KE::RIGHT_MOUSE))
		{
			_orbitCamera.Zoom();
		}
	}
	else
	{
		viewPos = _fpsCamera.GetPosition();

		if(KE::Controller::Instance()->GetKeyHeld(KE::W))
		{
			_fpsCamera.v_Move(_fpsCamera.GetLookVector()); //forward
		}
		else if(KE::Controller::Instance()->GetKeyHeld(KE::S))
		{
			_fpsCamera.v_Move(_fpsCamera.GetLookVector() * -1.0f); //back
		}
		
		if(KE::Controller::Instance()->GetKeyHeld(KE::D))
		{
			_fpsCamera.v_Move(_fpsCamera.GetRightVector()); //right
		}
		else if(KE::Controller::Instance()->GetKeyHeld(KE::A))
		{
			_fpsCamera.v_Move(_fpsCamera.GetRightVector() * -1.0f); //left
		}

		if(KE::Controller::Instance()->GetKeyHeld(KE::SPACE))
		{
			_fpsCamera.v_Move(_fpsCamera.GetUpVector()); //up
		}
		else if(KE::Controller::Instance()->GetKeyHeld(KE::LSHIFT))
		{
			_fpsCamera.v_Move(_fpsCamera.GetUpVector() * -1.0f); //down
		}
	}

	//Move Light Code
	_lightMovAngle += KM::Timer::Instance()->DeltaTime() * 50.0f;
	_light.SetPositionX(8.0f * sin(RADIAN(_lightMovAngle)));
	
	KM::Point lightPos = _light.GetPosition();

	//Update view Position
	Level::SetObjectUniforms("view_position", viewPos);

	//Update light Position
	Level::SetObjectUniforms("light.position", lightPos);
}