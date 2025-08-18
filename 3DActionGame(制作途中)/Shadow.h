#pragma once

class Shadow
{
public:
	Shadow();
	~Shadow();

	void Init();
	void Update(const VECTOR& pos);

	int GetShadowMapHandle() const { return shadowMapHandle; }
	VECTOR GetLightDir()const { return lightDirection; }

private:
	int shadowMapHandle;
	VECTOR lightDirection;

	static constexpr int SHADOW_QUALITY = 2048;	// �e�̃N�I���e�B

};