#ifndef MESSAGE_DISPATCHER_H_
#define MESSAGE_DISPATCHER_H_

#include "../../../Library/GameManager/GameManager.h"

#include <string>

struct Telegram;
class GameObject;

class MessageDispatcher
{
public:
	static MessageDispatcher* Instance();
	void dispatch_message(std::string sender, int receiver, int msg, void* ExtraInfo);

private:
	
	GameManager& gm = GameManager::GetInstance();

	void Discharge(std::shared_ptr<GameObject> receiver, const Telegram& msg);

	MessageDispatcher() {}
};

#endif // !MESSAGE_DISPATCHER_H_
