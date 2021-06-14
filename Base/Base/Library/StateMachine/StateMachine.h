#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "State.h"

#include <assert.h>

template<class T>
class StateMachine
{
public:
	StateMachine(T* owner)
		:owner_(owner), current_state_(NULL), previous_state_(NULL), global_state_(NULL)
	{
		
	}

	//今の状態、共通状態、前回の状態を尊く
	void set_current_state(State<T>* s) { current_state_ = s; }
	void set_global_state(State<T>* s) { global_state_ = s; }
	void set_previous_state(State<T>* s) { previous_state_ = s; }
	//毎フレーム更新
	void update()
	{
		if (global_state_)global_state_->update(owner_);

		if (current_state_)current_state_->update(owner_);
	}
	//状態を変える
	void change_state(State<T>* new_state)
	{
		assert(new_state && "<StateMachine::ChangeState>: trying to change to a null state");

		previous_state_ = current_state_;

		current_state_->end(owner_);

		current_state_ = new_state;

		current_state_->start(owner_);
	}
	//前回の状態に戻る
	void revert_to_previous_state()
	{
		change_state(previous_state_);
	}
	//各状態の取得
	State<T>* current_state() const { return current_state_; }
	State<T>* global_state() const { return global_state_; }
	State<T>* previous_state() const { return previous_state_; }
	//今の状態と一致するか
	bool is_in_state(const State<T>& st)const { return current_state_ = st; }

private:
	T* owner_;

	State<T>* current_state_;

	State<T>* previous_state_;

	State<T>* global_state_;
};

#endif // !STATE_MACHINE_H_
