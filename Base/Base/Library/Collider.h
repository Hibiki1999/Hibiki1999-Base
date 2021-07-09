#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Component.h"

#include "Vector3.h"

class GameObject;

class Collider : public Component
{
public:
	static const std::string& Type() { return "Collider"; }
	std::string componentType = "Collider"; // コンポーネントの種類(Colliderなど大まかな種類)

	// 初期化コンストラクタ
	Collider(GameObject* owner) : Component(owner)
	{
	}

	// 仮想デストラクタ
	~Collider()
	{
	}

	//この collider は他の collider に触れたときに OnCollisionEnter は呼び出されます。
	virtual void OnCollisionEnter()
	{

	}
	//この collider が他の collider と触れ合うのをやめたときに OnCollisionExit は呼び出されます。
	virtual void OnCollisionExit()
	{

	}
	//OnCollisionStay は rigidbody / collider が他の rigidbody / collider に触れている間毎フレーム 1 度だけ呼び出されます。
	virtual void OnCollisionStay()
	{

	}
	//GameObjectが他のオブジェクトと collidesしたとき OnTriggerEnterが呼び出されます
	virtual void OnTriggerEnter()
	{

	}
	//Collider が other のトリガーに触れるのをやめたときに OnTriggerExit は呼び出されます。
	virtual void OnTriggerExit()
	{

	}
	virtual void OnTriggerStay()
	{

	}
};


#endif
