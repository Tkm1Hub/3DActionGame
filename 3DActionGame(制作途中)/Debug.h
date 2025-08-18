#pragma once

class ObjectManager;
class Input;
class CameraBase;
class Character;

class Debug
{
public:
	void SetObjectManager(ObjectManager* mgr);
	void SetInput(const std::shared_ptr<Input>& inputPtr);
	void SetCamera(CameraBase* camera);
	void Draw();

private:
	ObjectManager* objMgr = nullptr;
	//Input* input = nullptr;
	std::shared_ptr<Input>input = std::make_shared<Input>();
	CameraBase* camera = nullptr;

	void DrawCapsule(const Character* character);
};