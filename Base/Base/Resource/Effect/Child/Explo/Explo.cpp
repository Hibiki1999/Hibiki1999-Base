#include "Explo.h"
#include "../../../Image/Image.h"
#include "../../../../Library/MyDraw/MyDraw.h"

void Explo::Update()
{
	int max = Image::Explo.AllNum;
	count++;
	if (count == 6) {
		num++;
		count = 0;
	}
	if (num >= max) {
		isDead = true;
	}
}

void Explo::Draw()
{
	MyDraw::DrawEffect3D(position, 80.0f, 256.0f, 0.0f, Image::Explo.HandleArray[num]);
}
