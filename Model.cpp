#include "framework.h"
#include "Model.h"


extern HWND g_hWnd;

Model::Model() {
	OnUserCreate();
}

void Model::Init() {
	OnUserCreate();
}

void Model::Update(float deltaTime) {
	this->deltaTime = deltaTime;
}

void Model::Render(HDC hdc) {
	//float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();
	wstring str = std::format(L"DT({0} ms)", OnUserUpdate(hdc, deltaTime));
	::TextOut(hdc, 100, 10, str.c_str(), static_cast<int32>(str.size()));
	
}

bool Model::OnUserCreate() {
	model.LoadFromObjFile("azusaFix.obj");

	//Projection Matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	RECT rtTemp;
	GetClientRect(g_hWnd, &rtTemp);
	int w = rtTemp.right - rtTemp.left;
	int h = rtTemp.bottom - rtTemp.top;
	float fAspectRatio = (float)h / (float)w;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;
	return true;
}

bool Model::OnUserUpdate(HDC hdc, float elapsedTime) {

	//float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();
	RECT rtTemp;
	GetClientRect(g_hWnd, &rtTemp);
	int w = rtTemp.right - rtTemp.left;
	int h = rtTemp.bottom - rtTemp.top;
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();
	mat4x4 matRotZ, matRotX;
	fTheta += 1.0f * deltaTime;

	matRotZ.m[0][0] = cosf(fTheta);
	matRotZ.m[0][1] = sinf(fTheta);
	matRotZ.m[1][0] = -sinf(fTheta);
	matRotZ.m[1][1] = cosf(fTheta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(fTheta * 0.5f);
	matRotX.m[1][2] = sinf(fTheta * 0.5f);
	matRotX.m[2][1] = -sinf(fTheta * 0.5f);
	matRotX.m[2][2] = cosf(fTheta * 0.5f);
	matRotX.m[3][3] = 1;
	vector<triangle> rasterTris;

	//vector<triangle>* tris = model.triangles;
	for (auto tri : model.triangles) {
		triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

		MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
		MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
		MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

		MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
		MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
		MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

		triTranslated = triRotatedZX;
		triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
		triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
		triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

		vec3d normal, line1, line2;
		line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
		line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
		line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

		line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
		line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
		line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

		normal.x = line1.y * line2.z - line1.z * line2.y;
		normal.y = line1.z * line2.x - line1.x * line2.z;
		normal.z = line1.x * line2.y - line1.y * line2.x;

		float l = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal.x /= l; normal.y /= l; normal.z /= l;

		//if (normal.z < 0)
		//Draw Triangles
		if (normal.x * (triTranslated.p[0].x - vCamera.x) +
			normal.y * (triTranslated.p[0].y - vCamera.y) +
			normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f)
		{
			//Lighting
			vec3d light_Dirction = { 0.0f, 0.0f, -1.0f };
			float l = sqrtf(light_Dirction.x * light_Dirction.x + light_Dirction.y * light_Dirction.y + light_Dirction.z * light_Dirction.z);
			light_Dirction.x /= l; light_Dirction.y /= l; light_Dirction.z /= l;

			float dp = normal.x * light_Dirction.x + normal.y * light_Dirction.y + normal.z * light_Dirction.z;
			triTranslated.alpha = dp;

			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);
			triProjected.alpha = triTranslated.alpha;

			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;

			triProjected.p[0].x *= 0.5f * (float)w;
			triProjected.p[0].y *= 0.5f * (float)h;
			triProjected.p[1].x *= 0.5f * (float)w;
			triProjected.p[1].y *= 0.5f * (float)h;
			triProjected.p[2].x *= 0.5f * (float)w;
			triProjected.p[2].y *= 0.5f * (float)h;

			rasterTris.push_back(triProjected);

			
		}
	}
	sort(rasterTris.begin(), rasterTris.end(), [](triangle& t1, triangle& t2) {
		float z1 = (t1.p[0].z, t1.p[1].z, t1.p[2].z) / 3.0f;
		float z2 = (t2.p[0].z, t2.p[1].z, t2.p[2].z) / 3.0f;
		return z1 > z2;
		});


	for (auto& triProjected : rasterTris) {
		Utils::FillTriangle(hdc, Pos(triProjected.p[0].x, triProjected.p[0].y)
			, Pos(triProjected.p[1].x, triProjected.p[1].y)
			, Pos(triProjected.p[2].x, triProjected.p[2].y)
			, RGB(triProjected.alpha * 255, triProjected.alpha * 255, triProjected.alpha * 255), RGB(triProjected.alpha * 255, triProjected.alpha * 255, triProjected.alpha * 255)
		);
		
	}
	return true;
}

void Model::MultiplyMatrixVector(vec3d& i, vec3d& o, mat4x4& m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
}

