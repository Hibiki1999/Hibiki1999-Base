#ifndef STATE_H_
#define STATE_H_

template <class T>
class State
{
public:
	virtual ~State() {}
	//�X�e�[�g�J�n�̎��������s
	virtual void start(T* owner) = 0;
	//�X�e�[�g�̖��t���[���X�V
	virtual void update(T* owner) = 0;
	//�X�e�[�g�ς���u�Ԏ��s
	virtual void end(T* owner) = 0;

	//virtual void on_message(T*, const Telegram&) = 0;
};

#endif // !STATE_H_
