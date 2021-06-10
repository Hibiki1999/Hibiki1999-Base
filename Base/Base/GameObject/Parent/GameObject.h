#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/Collision/SphereCollision/SphereCollision.h"
#include "../../Library/Screen/Screen.h"
#include "../../Library/Input/Input.h"
#include "../../Library/GameManager/GameManager.h"
#include"../../Resource/Image/Image.h"
#include "../../Library/MyRandom/MyRandom.h"
#include "../../Library/Transform/Transform.h"

class GameObject
{
public:

public:
	//コンストラクタ
	GameObject() = default;
	//仮想デストラクタ
	virtual ~GameObject() = default;
	//更新
	virtual void update();
	//描画
	virtual void draw() const;
	//半透明の描画
	virtual void draw_transparent() const;
	//GUIの描画
	virtual void draw_gui() const;
	//衝突リアクション
	virtual void react(GameObject& other);
	//衝突判定
	void collide(GameObject& other);
	//死亡する
	void die();
	//衝突しているか？
	bool is_collide(const GameObject& other) const;
	//死亡しているか？
	bool is_dead() const;
	//名前を取得
	const std::string& name() const;
	//タグ名を取得
	const std::string& tag() const;
	//トランスフォームを取得(Const版)
	const Transform& transform() const;
	//トランスフォームを取得
	Transform& transform();
	//移動量を取得
	Vec3 velocity() const;
	//衝突判定データを取得
	SphereCollision collider() const;

	//コピー禁止
	GameObject(const GameObject& other) = delete;
	GameObject& operator = (const GameObject& other) = delete;

protected:
	
	//タグ名
	std::string tag_;
	//名前
	std::string name_;
	//トランスフォーム
	Transform transform_;
	//移動量
	Vec3 velocity_{ 0.0f,0.0f,0.0f };
	//衝突判定が有効か?
	bool enable_collider_{ true };
	//衝突判定
	SphereCollision collider_;
	//死亡フラグ
	bool dead_{ false };

};

#endif // !GAMEOBJECT_H_

