#pragma once
#include "State.h"
#include "../scene/Scene.h"

class State_Editor : public State
{
public:
	State_Editor();
	~State_Editor();

	//	Scene loading & saving
	Scene currentScene;
	void LoadScene(std::string _path);
	void SaveScene();
	void SaveSceneAs(std::string _path);
	void NewScene();


	EcsEntity * selectedEntity;
	void SelectEntity();
	void DeselectEntity();
	void DeleteSelectedEntity();
	void CopySelectedEntity();


	// Inherited via State
	virtual void HandleEvent	(int _event)			override;
	virtual void HandleInput	(GLFWwindow * _window)	override;
	virtual void Update			(double _deltaTime)		override;
	virtual void FixedUpdate	(double _fixedTime)		override;
	virtual void GuiUpdate		()						override;
	virtual void Render			(GLFWwindow * _target)	override;
};