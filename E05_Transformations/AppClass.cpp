#include "AppClass.h"
void Application::InitVariables(void)
{
	m_pCameraMngr->SetCameraMode(CAM_ORTHO_Z);

	//Make MyMesh object
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLACK);

	//Green Cube
	m_pMeshG = new MyMesh();
	m_pMeshG->GenerateCube(1.0f, vector3(0.6f, 0.9f, 0.0f));
	//Brown Cube
	m_pMeshB = new MyMesh();
	m_pMeshB->GenerateCube(1.0f, vector3(0.75f, 0.44f, 0.0f));
	//Orange Cube
	m_pMeshO = new MyMesh();
	m_pMeshO->GenerateCube(1.0f, vector3(1.0f, 0.63f, 0.0f));

	m_fXValue = -28;

}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Model = ToMatrix4(m_qArcBall);
	//
	//*
	vector4 v4C0 = m4Model[0];
	vector4 v4C1 = m4Model[1];
	vector4 v4C2 = m4Model[2];
	vector4 v4C3 = m4Model[3];

	/*v4C0[0] = 2;
	v4C1[1] = 4;
	v4C2[2] = 1;*/
	v4C3 = vector4(m_fXValue, 8, 0, 1);

	m_fXValue += 0.1f;
	if (m_fXValue > 23)
	{
		m_fXValue = -28;
	}

	/*m4Model[0] = v4C0;
	m4Model[1] = v4C1;
	m4Model[2] = v4C2;
	m4Model[3] = v4C3;*/

	m4Model = glm::translate(m4Model, vector3(v4C3));
	//m4Model = glm::scale(m4Model, vector3(2.0, 4, 1));


	//------Green Cubes------
	//1st Row
	m_pMeshG->Render(m4Projection, m4View, m4Model);
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, 0, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, 0, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, 0, 0)));
	//2nd Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -1, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -1, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -1, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -1, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -1, 0)));
	//3rd Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4, -2, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -2, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -2, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -2, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -2, 0)));
	//4th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-5, -3, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4, -3, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -3, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -3, 0)));
	//5th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-5, -4, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -4, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -4, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -4, 0)));
	//6th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -5, 0)));
	//7th Row
	//8th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -7, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -7, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -7, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -7, 0)));
	//9th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -8, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -8, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -8, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -8, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -8, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -8, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -8, 0)));
	//10th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -9, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -9, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -9, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -9, 0)));
	//11th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -10, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -10, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -10, 0)));
	//12th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -11, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -11, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -11, 0)));
	//13th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -12, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -12, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -12, 0)));
	//14th Row
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -13, 0)));
	m_pMeshG->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -13, 0)));


	//------Brown Cubes------
	//2nd Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -1, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -1, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -1, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -1, 0)));
	//3rd Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -2, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -2, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -2, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -2, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -2, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(7, -2, 0)));
	//4th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -3, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -3, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -3, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -3, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -3, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -3, 0)));
	//5th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -4, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -4, 0)));
	//6th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -5, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -5, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -5, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -5, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -5, 0)));
	//7th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -6, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -6, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -6, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -6, 0)));
	//8th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -7, 0)));
	//9th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -8, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -8, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -8, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(7, -8, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -8, 0)));
	//10th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4, -9, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -9, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -9, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -9, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(7, -9, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -9, 0)));
	//11th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4, -10, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -10, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -10, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -10, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -10, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(7, -10, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -10, 0)));
	//12th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4, -11, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3, -11, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -11, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -11, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -11, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -11, 0)));
	//13th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2, -12, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -12, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -12, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -12, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -12, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -12, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(9, -12, 0)));
	//14th Row
	//15th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -14, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -14, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -14, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -14, 0)));
	//16th Row
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -15, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -15, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -15, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -15, 0)));
	m_pMeshB->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -15, 0)));

	//------Orange Cubes------
	//3rd Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -2, 0)));
	//4th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -3, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -3, 0)));
	//5th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1, -4, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -4, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -4, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -4, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -4, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -4, 0)));
	//6th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -5, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -5, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -5, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -5, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -5, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(7, -5, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(8, -5, 0)));
	//7th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -6, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -6, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -6, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -6, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -6, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -6, 0)));
	//8th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3, -7, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4, -7, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5, -7, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(6, -7, 0)));
	//9th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(8, -8, 0)));
	//10th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -9, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -9, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -9, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(8, -9, 0)));
	//11th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -10, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -10, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2, -10, 0)));
	//12th Row
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0, -11, 0)));
	m_pMeshO->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1, -11, 0)));


	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	m_pMeshMngr->AddGridToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	
	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	if (m_pMeshG != nullptr)
	{
		delete m_pMeshG;
		m_pMeshG = nullptr;
	}
	if (m_pMeshB != nullptr)
	{
		delete m_pMeshB;
		m_pMeshB = nullptr;
	}
	if (m_pMeshO != nullptr)
	{
		delete m_pMeshO;
		m_pMeshO = nullptr;
	}
	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}