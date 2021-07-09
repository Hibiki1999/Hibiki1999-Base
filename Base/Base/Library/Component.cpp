#include "Component.h"

#include "GameObjects/GameObject.h"

template<typename GameObjectType>
GameObjectType* Component::GetComponent()
{
	return  gameObject->GetComponent<GameObjectType>();
};