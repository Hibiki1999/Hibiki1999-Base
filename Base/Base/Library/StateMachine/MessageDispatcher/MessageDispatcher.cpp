#include "MessageDispatcher.h"
#include "../../../GameObject/Parent/GameObject.h"
#include "../Telegram/Telegram.h"
#include "../../../Library/GameManager/GameObjectManeger/GameObjectManager.h"


MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;
	return &instance;
}

void MessageDispatcher::dispatch_message(std::string sender, int receiver, int msg, void* ExtraInfo)
{
	std::shared_ptr<GameObject> pReveicer = gm.game_object_manager_->find(sender); //EntityMgr->GetEntityFromID(receiver);

	Telegram telegram{ sender, receiver, msg, ExtraInfo };

	Discharge(pReveicer, telegram);
}

void MessageDispatcher::Discharge(std::shared_ptr<GameObject> receiver, const Telegram& msg)
{
	
}
