#include "Explo.h"
#include "../../../Image/Image.h"
#include "../../../../Library/MyDraw/MyDraw.h"

void Explo::Update()
{
	int max = Image::Explo.AllNum;
	count++;
	if (count == 5) {
		num++;
		count = 0;
	}
	if (num >= max) {
		isDead = true;
	}
}

void Explo::Draw()
{
	MyDraw::DrawPlaneDivCharaRotaGraphF3D(position, 1, 0, Image::Explo, num);
}
