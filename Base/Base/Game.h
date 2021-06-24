#ifndef GAME_H_
#define GAME_H_

#include "Library/GameManager/GameManager.h"
#include "Scene/SceneManager.h"

class Game
{
public:
	Game();

	void Init();

	void Update();

	void Draw();

private:
	GameManager& gm = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	void RegisterButton();
};
#endif // !GAME_H_

//////////////
//enum StateType
//{
//	RunAway,
//	Patrtol,
//	Attack,
//};
//
//void Agent::UpdateState(StateType CurrentState) {
//	switch (CurrentState) {
//	case state_RunAway:
//		EvadeEnemy();
//		if (Safe()) {
//			ChangeState(state_Patrol);
//		}
//		break;
//
//	case state_Patrol:
//		FollowPatrolPath();
//		if (Threatened()) {
//			if (StrongerThanEnemy()) {
//				ChangeState(state_Attack);
//			}
//			else {
//				ChangeState(state_RunAway);
//			}
//		}
//		break;
//
//	case state_Attack:
//
//		if (WeakerThanEnemy()) {
//			ChanegState(state_RunAway);
//		}
//		else {
//			BAshEnemyOverHead();
//		}
//		break;
//	}
//}