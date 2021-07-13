#ifndef STAGE_H_
#define STAGE_H_

#include <vector>
#include <string>
#include "../../Library/Transform/Transform.h"

class GameObject;

class Stage
{
public:
	Stage(std::string stageName);

	~Stage();

	Vec3 check_colli(std::shared_ptr<GameObject> obj);

	void draw() const;

	int MoveFlag = 0;
private:
	int model_ = 0;

	Transform transform_;
	//int coll_obj_base_model_handle_;
	//std::vector<int> coll_obj_model_handle_;
	//int coll_obj_num;

};

#endif // !STAGE_H_
