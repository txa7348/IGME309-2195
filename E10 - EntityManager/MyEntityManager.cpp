#include "MyEntityManager.h"
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
}
void MyEntityManager::Release(void)
{
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
}
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{
	return -1;
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{
	return nullptr;
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{
	return nullptr;
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{
	return nullptr;
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	return nullptr;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{
	return IDENTITY_M4;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{
	return IDENTITY_M4;
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{

}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{

}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{

}
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	m_entityList.push_back(new MyEntity(a_sFileName, a_sUniqueID)); //Adds new Entity to list
	m_uEntityCount++; //Updates Entity count
}
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{
	if (a_uIndex >= 0 && a_uIndex < m_uEntityCount) //Ensures valid index
	{
		m_entityList.erase(m_entityList.begin() + a_uIndex); //Deletes Entity at specified index
		m_uEntityCount--;
	}
}
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	int index = -1;

	for (int i = 0; i < m_uEntityCount; i++) //Checks for an Entity with the specified ID
	{
		if (m_entityList[i]->GetUniqueID() == a_sUniqueID)
			index == i;
	}

	if (index >= 0 && index < m_uEntityCount) //Ensures valid index
	{
		m_entityList.erase(m_entityList.begin() + index); //Deletes Entity at specified index
		m_uEntityCount--;
	}
}
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{
	if (a_uIndex >= 0 && a_uIndex < m_uEntityCount) //Checks for valid index
	{
		return m_entityList[a_uIndex]->GetUniqueID();
	}

	return "";
}
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{
	if (a_uIndex >= 0 && a_uIndex < m_uEntityCount) //Checks for valid index
	{
		return m_entityList[a_uIndex];
	}

	return nullptr;
}
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{

}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{

}