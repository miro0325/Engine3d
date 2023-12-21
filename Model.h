#pragma once

class Model : public Scene
{
public:
	Model();
	

private:
	mesh model;
	mat4x4 matProj;
	float fTheta;

	vec3d vCamera;

	void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m);
public:
	bool OnUserCreate();

	bool OnUserUpdate(HDC hdc, float elapsedTime);

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

};

