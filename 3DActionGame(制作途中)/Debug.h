#pragma once

class ObjectManager;
class Input;
class CameraBase;
class Character;

class Debug
{
public:
	void SetObjectManager(ObjectManager* mgr);
	void SetInput(Input* inputPtr);
	void SetCamera(CameraBase* camera);
	void Draw();

private:
	ObjectManager* objMgr = nullptr;
	Input* input = nullptr;
	CameraBase* camera = nullptr;

	void DrawCapsule(const Character* character);
};