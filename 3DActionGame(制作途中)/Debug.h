#pragma once

class ObjectManager;
class Input;
class CameraBase;
class Character;

class Debug
{
public:
	void SetObjectManager(const std::shared_ptr<ObjectManager>& objectMgrPtr);
	void Draw();

private:
	std::shared_ptr<ObjectManager>objMgr = nullptr;

	void DrawCapsule(const std::shared_ptr<Character>& character);
};