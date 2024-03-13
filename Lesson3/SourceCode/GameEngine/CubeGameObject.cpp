#include "CubeGameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

CubeGameObject::CubeGameObject()
{
	m_pRenderProxy = new CubeRenderProxy();
}

MoveCube::MoveCube() {}
ControledCube::ControledCube() {}
JumpCube::JumpCube() {}

void CubeGameObject::Move(float time) {}
void CubeGameObject::Jump(float time) {}
void CubeGameObject::Control(float delta, EInputCommand command) {}

void MoveCube::Move(float time)
{
	if (std::isnan(start[0])) {
		start[0] = m_vPosition[0];
		start[1] = m_vPosition[1];
		start[2] = m_vPosition[2];
	}

	SetPosition(start[0], start[1], start[2] + sinf(time) * 2);
}

void JumpCube::Jump(float time)
{
	if (std::isnan(start[0])) {
		start[0] = m_vPosition[0];
		start[1] = m_vPosition[1];
		start[2] = m_vPosition[2];
	}

	
	float change = - (time - floor(time) - 1) * (time - floor(time)) * 30.f;
	SetPosition(start[0], start[1] + change, start[2]);
}

void ControledCube::Control(float delta, EInputCommand command) {
	float speed = 10.f;
	if (command == eIC_GoLeft) {
		SetPosition(m_vPosition[0] - delta * speed, m_vPosition[1], m_vPosition[2]);
	}
	if (command == eIC_GoRight) {
		SetPosition(m_vPosition[0] + delta * speed, m_vPosition[1], m_vPosition[2]);
	}
}