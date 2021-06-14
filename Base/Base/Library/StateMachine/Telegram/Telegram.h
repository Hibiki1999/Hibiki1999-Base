#ifndef TELEGRAM_H_
#define TELEGRAM_H_

enum
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
};

#include <string>

struct Telegram
{

	std::string Sender;

	int Receiver;

	int Msg;

	void* ExtraInfo;
};

#endif // !TELEGRAM_H_