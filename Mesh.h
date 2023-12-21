#pragma once

#define _SILENCE_CXX17_STRSTREAM_DEPRECATION_WARNINGS


struct vec3d
{
	float x, y, z;
};

struct triangle
{
	vec3d p[3];
	float alpha;
};

struct mesh
{
	
	vector<triangle> triangles;

	bool LoadFromObjFile(string fileName) {
		ifstream f(fileName);
		//triangles->shrink_to_fit();
		//triangles->resize((int)f.tellg());
		if (!f.is_open()) {
			return false;
		}
		vector<vec3d> verts;
		while (!f.eof())
		{
			char line[128];
			f.getline(line, 128);
			stringstream s;
			
			s << line;
			char junk;
			if (line[0] == 'v') {
				vec3d v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}
			if (line[0] == 'f') {
				string fIndex[3];
				int fs[3];
				
				s >> junk >> fIndex[0] >> fIndex[1] >> fIndex[2];
				for (int i = 0; i < 3; i++) {
					if (fIndex[i].find('/') != string::npos) {
						vector<string> split = Utils::Split(fIndex[i],'/');
						fs[i] = atoi(split[0].c_str());
					}
					fs[i] = atoi(fIndex[i].c_str());
				}
				triangles.push_back({verts[fs[0]-1],verts[fs[1]-1],verts[fs[2]-1]});
			}
		}
		return true;
	}
};

struct mat4x4 {
	float m[4][4] = { 0 };
};