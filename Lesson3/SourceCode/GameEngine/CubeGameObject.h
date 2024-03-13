#pragma once

#include "GameObject.h"
#include "InputHandler.h"
#include <cmath>

class CubeGameObject : public GameObject
{
public:
	CubeGameObject();
	virtual void Move(float time);
	virtual void Jump(float time);
	virtual void Control(float delta, EInputCommand command);

private:
	
};

class MoveCube final : public CubeGameObject {
public:
	MoveCube();
	void Move(float time) override;
	float start[3] = { std::nanf(""), std::nanf(""), std::nanf("") };
};

class JumpCube final : public CubeGameObject {
public:
	JumpCube();
	void Jump(float time) override;
	float start[3] = { std::nanf(""), std::nanf(""), std::nanf("") };
};

class ControledCube final : public CubeGameObject {
public:
	ControledCube();
	virtual void Control(float delta, EInputCommand command) override;
};

