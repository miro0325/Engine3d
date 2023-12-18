#pragma once

class olcEngine3D
{
public:
	olcEngine3D();
	

private:
	mesh meshCube;
	mat4x4 matProj;
	float fTheta;

	void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m);
public:
	bool OnUserCreate(HDC hdc);

	bool OnUserUpdate(HDC hdc, float elapsedTime);

};

