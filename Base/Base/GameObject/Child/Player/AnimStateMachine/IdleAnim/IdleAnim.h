#ifndef IDLE_ANIM_H_
#define IDLE_ANIM_H_

#include "../../../../../Library/StateMachine/State.h"

class Player;

class IdleAnim:public State<Player>
{
public:
	static IdleAnim* Instance();

	virtual void start(Player* owner);

	virtual void update(Player* owner) ;

	virtual void end(Player* owner) ;

private:
	IdleAnim() {}

	IdleAnim(const IdleAnim&);
	IdleAnim& operator=(const IdleAnim&);
};

#endif // !IDLE_ANIM_H_
