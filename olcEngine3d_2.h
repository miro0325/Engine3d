#pragma once

class olcEngine3D_2 : public Scene
{
public:
	olcEngine3D_2();


private:
	mesh meshCube;
	mat4x4 matProj;
	float fTheta;

	void MultiplyMatrixVector(vec3d& i, vec3d& o, mat4x4& m);
public:
	bool OnUserCreate();

	bool OnUserUpdate(HDC hdc, float elapsedTime);

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

};

