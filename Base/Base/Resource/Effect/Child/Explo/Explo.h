#ifndef SHISYOTRANSFORM_H_
#define SHISYOTRANSFORM_H_

#include "../../Parents/EffectParent.h"

class Explo: public EffectParent
{
public:
	Explo(Vec3 Effectposition)
	{
		this->tag = "Explo"; 
		this->position = Effectposition;
	}
	
	~Explo(){}

	void Update() override;

	void Draw() override;

private:
	Vec3 position;
	int num = 0;
	int count = 0;
};
#endif