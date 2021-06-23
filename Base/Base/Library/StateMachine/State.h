#ifndef STATE_H_
#define STATE_H_

template <class T>
class State
{
public:
	virtual ~State() {}
	//ステート開始の時だけ実行
	virtual void start(T* owner) = 0;
	//ステートの毎フレーム更新
	virtual void update(T* owner) = 0;
	//ステート変える瞬間実行
	virtual void end(T* owner) = 0;

	//virtual void on_message(T*, const Telegram&) = 0;
};

#endif // !STATE_H_
