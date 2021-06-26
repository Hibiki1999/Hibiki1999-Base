#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Parent/GameObject.h"
#include "../../../Library/Animation/Animation.h"
#include "../../../Library/StateMachine/StateMachine.h"
#include "../../../Library/GameManager/GameManager.h"

enum Anim {
	Walk,
	Idle,
};

class Player :public GameObject
{
public:
	Player(const Vec3 position);

	virtual void update() override;

	virtual void draw() const override;

	virtual void react(std::shared_ptr<GameObject> other)override;

	//animStateMachinenÇÃä÷êî====================

	int anim_state();

	void set_anim(int anim);

	StateMachine<Player>* get_anim_state_machine() const;

	Animation* animclass();

	//===========================================

private:
	GameManager& gm = GameManager::GetInstance();

	StateMachine<Player>* anim_state_machine_;

	Animation anim = Animation(Image::ModelHandle);

	int anim_state_ = -1;

	void InputHandle();

};
#endif // !PLAYER_H_

