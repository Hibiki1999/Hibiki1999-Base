#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Vector3.h"

class GameObject; //前方宣言


class Component
{
public:
	static const std::string& Type() { return "Component"; } // GetComponentに使う

	union { // ★共用体unionテクニック https://inemaru.hatenablog.com/entry/2016/03/02/005408
		Vector3 position; // 座標
		struct { 
			float x;
			float y;
			float z;
		}; // XYZ座標  [匿名共用体とは] https://code.i-harness.com/ja-jp/q/4d437c
		std::array<float, 3> xyz; // float xyz[3];と同じ意味 float 3個ぶんのデータサイズでx,y,z 3個ぶんと一致するので★unionで共用
	}; // unionは異なる複数のものをメモリ上の同一の番地に割り当てられる⇒x,y,z分けて記述するの面倒なとき配列xyz[3]をfor文i=0～3で回せる

	GameObject* gameObject; //自身を所有するーオーナーのGameObjectへのポインタ
	std::string tag = ""; //タグ
	std::string componentType = ""; // コンポーネントの種類(Colliderなど大まかな種類)
	
	// コンポーネントをゲットする
	template<typename GameObjectType>
	GameObjectType *GetComponent();

	// 初期化コンストラクタ
	Component(GameObject* owner) : gameObject{ owner }
	{
	}

	// 仮想デストラクタ
	~Component()
	{
	}
	// 更新処理
	virtual void Update()
	{
	}
};


#endif
