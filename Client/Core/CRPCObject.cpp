#include "stdafx.h"

void CRPCObject::Create(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCObject::Create" << std::endl;
	int entity;
	int hash = 0;
	RakWString model;
	CVector3 position;
	CVector3 rotation;
	bool dynamic, isHash;

	bitStream->Read(entity);
	bitStream->Read(isHash);
	if(isHash)
		bitStream->Read(hash);
	else
		bitStream->Read(model);
	bitStream->Read(position.x);
	bitStream->Read(position.y);
	bitStream->Read(position.z);
	bitStream->Read(rotation.x);
	bitStream->Read(rotation.y);
	bitStream->Read(rotation.z);
	bitStream->Read(dynamic);

	CObjectEntity newObject;

	if (!isHash)
		hash = GAMEPLAY::GET_HASH_KEY((char*)CString::utf16ToUtf8(model.C_String()).c_str());

	if (newObject.Create(entity, hash, position, rotation, dynamic))
		g_Objects.push_back(newObject);
}

void CRPCObject::SetTextureVariation(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCObject::SetTextureVariation" << std::endl;
	int entity, textureindex;

	bitStream->Read(entity);
	bitStream->Read(textureindex);

	for (int i = 0; i < g_Objects.size(); i++) {
		if (g_Objects[i].GetId() == entity) {
			g_Objects[i].SetTextureVariation(textureindex);
			break;
		}
	}
}