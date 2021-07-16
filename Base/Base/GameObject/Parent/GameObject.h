#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/MyDraw/MyDraw.h"
#include "../../Library/Collision/SphereCollision/SphereCollision.h"
#include "../../Library/Collision/CubeCollision/CubeCollision.h"
#include "../../Library/Screen/Screen.h"
#include "../../Library/GameManager/GameManager.h"
#include"../../Resource/Image/Image.h"
#include "../../Library/MyRandom/MyRandom.h"
#include "../../Library/Transform/Transform.h"

class GameObject :public std::enable_shared_from_this<GameObject>
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
	virtual void react(std::shared_ptr<GameObject> other);
	//衝突判定
	void collide(std::shared_ptr<GameObject> other);
	//死亡する
	void die();
	//衝突しているか？
	bool is_collide(const std::shared_ptr<GameObject> other);
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
	SphereCollision collider();

	float height();
	//壁の衝突判定
	void WallCollide();
	//重力
	void gravity();
	//発射する物の重力
	void projectile_gravity();
	//地面にいるか？
	void grounded();
	//空中にいるのか？
	bool isAir();
	//今のｙで加速
	Vec3 gravity_velo();
	//今のｙを-1を掛ける
	void minus_gravity_velo();
	//重力に影響を受けるかを調べる
	bool is_gravity();
	//壁に当たり判定あるかどうか
	bool is_wallcollide();

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
	bool enable_wall_collider_{ false };
	//衝突判定
	SphereCollision collider_;
	CubeCollision cube_collider_;
	//死亡フラグ
	bool dead_{ false };
	//ジャンプ
	void Jump(float jumpPower);
	//重力に適用するか
	bool enable_gravity_{ true };
	//重力
	float gravity_power_{ -3.1f };
	//重力の強さ
	float max_gravity_power_ = -30.0f;

private:

	GameManager& gm = GameManager::GetInstance();

	Vec3 gravity_velocity_{ 0.0f,0.0f,0.0f };

};

#endif // !GAMEOBJECT_H_

