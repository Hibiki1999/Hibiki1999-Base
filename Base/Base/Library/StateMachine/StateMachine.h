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

	//���̏�ԁA���ʏ�ԁA�O��̏�Ԃ𑸂�
	void set_current_state(State<T>* s) { current_state_ = s; }
	void set_global_state(State<T>* s) { global_state_ = s; }
	void set_previous_state(State<T>* s) { previous_state_ = s; }
	//���t���[���X�V
	void update()
	{
		if (global_state_)global_state_->update(owner_);

		if (current_state_)current_state_->update(owner_);
	}
	//��Ԃ�ς���
	void change_state(State<T>* new_state)
	{
		assert(new_state && "<StateMachine::ChangeState>: trying to change to a null state");

		previous_state_ = current_state_;

		current_state_->end(owner_);

		current_state_ = new_state;

		current_state_->start(owner_);
	}
	//�O��̏�Ԃɖ߂�
	void revert_to_previous_state()
	{
		change_state(previous_state_);
	}
	//�e��Ԃ̎擾
	State<T>* current_state() const { return current_state_; }
	State<T>* global_state() const { return global_state_; }
	State<T>* previous_state() const { return previous_state_; }
	//���̏�Ԃƈ�v���邩
	bool is_in_state(const State<T>& st)const { return current_state_ = st; }

private:
	T* owner_;

	State<T>* current_state_;

	State<T>* previous_state_;

	State<T>* global_state_;
};

#endif // !STATE_MACHINE_H_
