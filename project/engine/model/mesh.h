#pragma once

#include "engine/namespace.h"

class				engine::mesh
{
public:
					mesh();
					mesh(const string& Filename);
					~mesh();

	void			render();

private:

//	bool			InitFromScene(const aiScene* pScene, const std::string& Filename);
//	void			InitMesh(unsigned int Index, const aiMesh* paiMesh);
//	bool			InitMaterials(const aiScene* pScene, const std::string& Filename);
	void			Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	struct MeshEntry {
		MeshEntry();

		~MeshEntry();

//		bool Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices);

		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

//	std::vector<MeshEntry> m_Entries;
//	std::vector<Texture*> m_Textures;
};


