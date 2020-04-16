#include "MyOctant.h";

using namespace Simplex;

uint MyOctant::m_uOctantCount = 0;
uint MyOctant::m_uMaxLevel = 3;
uint MyOctant::m_uIdealEntityCount = 5;

//Constructor, will create an octant containing all MagnaEntities Instances in the Mesh manager currently contains
Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	Init(); //Initialize Values

	//Static Values
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_uOctantCount = 0;

	//Default Values
	m_uID = m_uOctantCount;
	m_pRoot = this;
	m_lChild.clear();

	//Used to determine size of Octant
	std::vector<vector3> lMinMax; 

	uint nObjects = m_pEntityMngr->GetEntityCount();
	for (int i = 0; i < nObjects; i++)
	{
		MyEntity* pEntity = m_pEntityMngr->GetEntity(i);
		MyRigidBody* pRigidBody = pEntity->GetRigidBody();
		lMinMax.push_back(pRigidBody->GetMinGlobal());
		lMinMax.push_back(pRigidBody->GetMaxGlobal());
	}
	MyRigidBody* pRigidBody = new MyRigidBody(lMinMax);

	vector3 vHalfWidth = pRigidBody->GetHalfWidth();
	float fMax = vHalfWidth.x;
	for (int i = 0; i < 3; i++)
	{
		if (fMax < vHalfWidth[i])
			fMax = vHalfWidth[i];
	}

	vector3 v3Center = pRigidBody->GetCenterLocal();
	lMinMax.clear();
	SafeDelete(pRigidBody);

	m_
	m_uOctantCount++;

	ConstructTree(m_uMaxLevel);
}

//Constructor
Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	Init(); //Initialize Values

	//Parameterized Values
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	m_v3Min = m_v3Center - vector3(m_fSize / 2.0f);
	m_v3Max = m_v3Center + vector3(m_fSize / 2.0f);

	m_uOctantCount++;
}

//Copy Constructor
Simplex::MyOctant::MyOctant(MyOctant const& other)
{
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_uChildren = other.m_uChildren;

	m_fSize = other.m_fSize;

	m_pMeshMngr = other.m_pMeshMngr;
	m_pEntityMngr = other.m_pEntityMngr;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_pParent = other.m_pParent;
	for (int i = 0; i < other.m_uChildren; i++)
	{
		m_pChild[i] = other.m_pChild[i];
	}

	m_EntityList = other.m_EntityList;

	m_pRoot = other.m_pRoot;
	m_lChild = other.m_lChild;
}

//Copy Assignment Operator
MyOctant& Simplex::MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}

//Destructor
Simplex::MyOctant::~MyOctant(void)
{
	Release();
}

//Changes object contents for other object's
void Simplex::MyOctant::Swap(MyOctant& other)
{
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_uChildren, other.m_uChildren);

	std::swap(m_fSize, other.m_fSize);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
	std::swap(m_pEntityMngr, other.m_pEntityMngr);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_pParent, other.m_pParent);
	std::swap(m_pChild, other.m_pChild);

	std::swap(m_EntityList, other.m_EntityList);

	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);
}

//Gets this octant's size
float Simplex::MyOctant::GetSize(void)
{
	return m_fSize;
}

//Gets the center of the octant in global scape
vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return m_v3Center;
}

//Gets the min corner of the octant in global space 
vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return m_v3Min;
}

//Gets the max corner of the octant in global space
vector3 Simplex::MyOctant::GetMaxGlobal(void)
{
	return m_v3Max;
}

//Asks if there is a collision with the Entity specified by index from the Bounding Object Manager
bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
{
	if (a_uRBIndex > 0 && a_uRBIndex < m_pEntityMngr->GetEntityCount()) //Checks for valid index
	{
		MyRigidBody* other = m_pEntityMngr->GetRigidBody(a_uRBIndex); //Checks collision using Axis Aligned Bounding Box

		if (m_v3Max.x < other->GetMinGlobal().x) //this to the right of other
			return false;
		if (m_v3Min.x > other->GetMaxGlobal().x) //this to the left of other
			return false;

		if (m_v3Max.y < other->GetMinGlobal().y) //this below of other
			return false;
		if (m_v3Min.y > other->GetMaxGlobal().y) //this above of other
			return false;

		if (m_v3Max.z < other->GetMinGlobal().z) //this behind of other
			return false;
		if (m_v3Min.z > other->GetMaxGlobal().z) //this in front of other
			return false;

		return true; //Objects are colliding
	}
	else
	{
		return false;
	}
}

//Displays the Octant volume specified by index including the objects underneath
void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
{
	//Displays this Octant if it matches the ID
	if (m_uID == a_nIndex)
	{
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color);
		return;
	}

	//Checks children for ID to display
	for (int i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_nIndex, a_v3Color);
	}
}

//Displays the Octant volume in the color specified
void Simplex::MyOctant::Display(vector3 a_v3Color)
{
	//Displays Children
	for (int i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_v3Color);
	}
	//Displays this Octant
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color);
}

//Displays the non empty leafs in the octree
void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
{
	if (!IsLeaf()) //Only checks for Octants that are not leaves
	{
		for (int i = 0; i < m_lChild.size(); i++)
		{
			m_lChild[i]->DisplayLeafs(a_v3Color);
		}
	}

	//Displays this Octant
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color);
}

//Clears the Entity list for each node
void Simplex::MyOctant::ClearEntityList(void)
{

	if (!IsLeaf()) //Clears entity list in any children
	{
		for (int i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->ClearEntityList();
		}
	}

	m_EntityList.clear(); //Clears current entity list
}

//Allocates 8 smaller octants in the child pointers
void Simplex::MyOctant::Subdivide(void)
{
	if (m_uChildren == 0 && m_uLevel < m_uMaxLevel) //Only divides if octant doesn't already have children and max level has not been reached
	{
		m_uChildren = 8; //Set Children

		for (int i = 0; i < 8; i++) //
		{
			float fSize = m_fSize / 2.0f; //Diameter is half the size of the parent

			vector3 v3Center = m_v3Center; //Center starts at parent's center and is adjusted by half the child's size

			if (i < 4)						//Children 0, 1, 2, 3
				v3Center.x += fSize / 2.0f;
			else							//Children 4, 5, 6, 7
				v3Center.x -= fSize / 2.0f;

			if (i < 2 || (i > 3 && i < 6))	//Children 0, 1, 4, 5
				v3Center.y += fSize / 2.0f;
			else							//Children 2, 3, 6, 7
				v3Center.y -= fSize / 2.0f;

			if (i % 2 == 0)					//Children 0, 2, 4, 6
				v3Center.z += fSize / 2.0f;
			else							//Children 1, 3, 5, 7
				v3Center.z -= fSize / 2.0f;

			m_pChild[i] = new MyOctant(v3Center, fSize); //Set Child
			m_pChild[i]->m_pParent == this; //Set Parent
			m_pChild[i]->m_pRoot = this->m_pRoot; //Set Root
			m_pChild[i]->m_uLevel = m_uLevel + 1; //Set Child's level
			if (m_pChild[i]->ContainsMoreThan(m_uIdealEntityCount))
			{
				m_pChild[i]->Subdivide();
			}
		}
	}
}

//Returns the child specified in the index
MyOctant* Simplex::MyOctant::GetChild(uint a_nChild)
{
	if (a_nChild >= 0 && a_nChild < m_uChildren) //Returns specified child if index is valid
		return m_pChild[a_nChild];
	else
		return nullptr;
}

//Returns the parent of the octant
MyOctant* Simplex::MyOctant::GetParent(void)
{
	return m_pParent;
}

//Asks the MyOctant if it does not contain any children (its a leaf)
bool Simplex::MyOctant::IsLeaf(void)
{
	return m_uChildren == 0;
}

//Asks the MyOctant if it contains more than this many Bounding Objects
bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
{
	uint uCount = 0; //Number of entities in the Octant
	uint uObjectCount = m_pEntityMngr->GetEntityCount(); //Number of entities in the manager
	for (int i = 0; i < uObjectCount; i++)
	{
		if (IsColliding(i))
			uCount++;
		if (uCount > a_nEntities)
			return true;
	}
	return false;
}

//Deletes all children and the children of their children
void Simplex::MyOctant::KillBranches(void)
{
	if (!IsLeaf()) //Checks if there are children first
	{
		for (int i = 0; i < m_uChildren; i++) //Goes through all of the octant's children
		{
			m_pChild[i]->KillBranches(); //Deletes the branches of the child
			delete m_pChild[i]; //Deletes the child
			m_pChild[i] = nullptr;
		}

		m_uChildren = 0;
	}
}

//Creates a tree using subdivisions, the max number of objects and levels
void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
{
	if (m_uLevel != 0) //Tree can only be constructed at the root
		return;

	m_uMaxLevel = a_nMaxLevel;
	m_uOctantCount = 1;
	
	m_EntityList.clear(); //Clears current entity list

	KillBranches(); //Deletes existing tree
	m_lChild.clear();
	
	if (ContainsMoreThan(m_uIdealEntityCount)) //Subdivide tree
	{
		Subdivide();
	}

	AssignIDtoEntity(); //Assigns IDs for entities contained in the tree

	ConstructList(); //Contructs list of object containing leafs
}

//Traverse the tree up to the leafs and sets the objects in them to the index
void Simplex::MyOctant::AssignIDtoEntity(void)
{
	//Traverses tree starting at root
	//If octant is leaf, checks main entity list for colliding entities
	//If entity is colliding, adds it to that octant's EntityList

	for (int i = 0; i < m_uChildren; i++) //Searches for leafs in the tree
	{
		m_pChild[i]->AssignIDtoEntity();
	}

	if (IsLeaf()) //If octant is leaf, checks for entities contained within it
	{
		for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++) //Checks main list of entities
		{
			if (IsColliding(i)) //If entity collides with octant, it is added to its entity list
			{
				m_EntityList.push_back(i);
				m_pEntityMngr->AddDimension(i, m_uID);
			}
		}
	}
}

//Gets the total number of octants in the world
uint Simplex::MyOctant::GetOctantCount(void)
{
	return m_uOctantCount;
}

//Deallocates member fields
void Simplex::MyOctant::Release(void)
{
	if (m_uLevel == 0)
	{
		KillBranches();
	}

	m_uChildren = 0;
	m_fSize = 0.0f;
	m_EntityList.clear();
	m_lChild.clear();
	m_pMeshMngr = nullptr;
	m_pEntityMngr = nullptr;
}

//Allocates member fields
void Simplex::MyOctant::Init(void)
{
	m_uChildren = 0;

	m_fSize = 0.0f;

	m_uID = m_uOctantCount;
	m_uLevel = 0;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	m_pRoot = nullptr;
	m_pParent = nullptr;

	for (int i = 0; i < 8; i++)
	{
		m_pChild[i] = nullptr;
	}
}

//creates the list of all leafs that contains objects.
void Simplex::MyOctant::ConstructList(void)
{
	for (int i = 0; i < m_uChildren; i++) //Checks Children to add them to the list
	{
		m_pChild[i]->ConstructList();
	}

	if (m_EntityList.size() > 0) //If octant contains entities, adds it to the list
		m_pRoot->m_lChild.push_back(this);
}
