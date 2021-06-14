#ifndef WALK_ANIM_H_
#define WALK_ANIM_H_

#include "../../../../../Library/StateMachine/State.h"

class Player;

class WalkAnim:public State<Player>
{
public:
	static WalkAnim* Instance();

	virtual void start(Player* owner);

	virtual void update(Player* owner);

	virtual void end(Player* owner);

private:
	WalkAnim() {}

	WalkAnim(const WalkAnim&);
	WalkAnim& operator=(const WalkAnim&);
};

#endif // !WALK_ANIM_H_
