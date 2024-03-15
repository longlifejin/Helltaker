#pragma once
#include "SpriteGo.h"
class Transition : public SpriteGo
{
protected:
	bool transitionUpDone;

public:
	Transition(const std::string& name = "");
	~Transition() override;

	Animator animator;
	SceneIds scene = SceneIds::CHAPTER;

	void Init() override;

	void RemoveChangeSceneImage();

	void SetChangeScene(SceneIds scn) { scene = scn; }
	void SceneChange();
	
	void PlayTransitionUp();
	void PlayTransitionDown();

	void Reset() override;
	void Update(float dt) override;
};

