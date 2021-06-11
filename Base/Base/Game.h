#ifndef GAME_H_
#define GAME_H_

#include <DxLib.h>

#include "Scene/Parent/Scene.h"
#include "Resource/Image/Image.h"
#include "Resource/Sound/Sound.h"
#include "Library/Input/Input.h"
#include "Library/MyRandom/MyRandom.h"
#include "Library/GameManager/GameManager.h"

class Title;
class Play;
class Ending;

class Game
{
public:
	Game();

	void Init();

	void Update();

	void Draw();

	static void ChangeScene(Scene* newScene);

	//í«â¡ÇµÇΩÉVÅ[ÉìÇÕÇ±ÇÃâ∫Ç…íËã`
	Scene* m_title;

	Scene* m_play;

	Scene* m_ending;

private:
	GameManager& gm = GameManager::GetInstance();
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