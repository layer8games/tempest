#pragma once
//===== Prcompiled Headers =====
//=====Windows Includes=====
#include <Windows.h>

//=====STD Includes=====
#include <string>
#include <memory>

using std::string;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
#include <Engine/Point2.h>
#include <Engine/Point3.h>
#include <Engine/Point4.h>
#include <Engine/Quaternion.h>
#include <Engine/Matrix3.h>
#include <Engine/Matrix4.h>
#include <Engine/Timer.h>
#include <Engine/Random.h>

#include <Engine/AudioManager.h>
#include <Engine/ErrorManager.h>
#include <Engine/EventManager.h>
#include <Engine/FontManager.h>
#include <Engine/ShaderManager.h>
#include <Engine/LevelManager.h>

#include <Engine/Shader.h>
#include <Engine/GameWindow.h>
#include <Engine/Font.h>
#include <Engine/Input.h>
#include <Engine/Color.h>
#include <Engine/AudioClip.h>
#include <Engine/AudioListener.h>

#include <Engine/Keys.h>
#include <Engine/CharacterData.h>
#include <Engine/BufferData.h>
#include <Engine/Vertex.hpp>
#include <Engine/Factory.h>

#include <Engine/Driver.h>
#include <Engine/CollisionDetector.h>
#include <Engine/GameObject2D.h>
#include <Engine/CameraController.h>