#include "Stage.h"
#include "../../Library/MyDraw/MyDraw.h"
#include "../../GameObject/Parent/GameObject.h"

#include <DxLib.h>

constexpr int HitDimNum = 1;
constexpr int Max_Hitcoll = 256;
constexpr int Hit_TryNum = 16;

Stage::Stage(std::string stageName)
{
	std::string path = "ResourceFile/StageFile/" + stageName;
	this->model_ = MV1LoadModel(path.c_str());
	transform_.position(Vec3(0, 0, 0));
	transform_.rotation(Quaternion(0, 0, 0));
	transform_.scale(Vec3(0, 0, 0));
}

Stage::~Stage()
{
}

Vec3 Stage::check_colli(std::shared_ptr<GameObject> obj)
{
	Vec3 position = obj->transform().position();
	Vec3 velo = obj->velocity() + obj->gravity_velo();
	float radius = obj->collider().GetRadius();
	float height = obj->height();
	bool isAir = obj->isAir();


	MV1_COLL_RESULT_POLY_DIM HitDim;			// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	HitDim = MV1CollCheck_Sphere(model_, -1, position + velo, 500.0f + velo.Length());

	bool MoveFlag = velo.NotZero() ? true : false;

	int KabeNum = 0;
	int YukaNum = 0;
	int HitFlag = 0;
	MV1_COLL_RESULT_POLY* Kabe[Max_Hitcoll];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* Yuka[Max_Hitcoll];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* Poly;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
	HITRESULT_LINE LineRes;				// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
	Vec3 OldPos;
	Vec3 NowPos;

	OldPos = position - velo;
	NowPos = position;

	for (int i = 0; i < HitDim.HitNum; i++) {

		if (HitDim.Dim[i].Normal.y<0.000001f && HitDim.Dim[i].Normal.y > -0.000001f) {
			// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
			if (HitDim.Dim[i].Position[0].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > OldPos.y + 1.0f)
			{
				// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (KabeNum < Max_Hitcoll)
				{
					// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					Kabe[KabeNum] = &HitDim.Dim[i];

					// �ǃ|���S���̐������Z����
					KabeNum++;
				}
			}
		}
		else
		{
			// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
			if (YukaNum < Max_Hitcoll)
			{
				// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
				Yuka[YukaNum] = &HitDim.Dim[i];

				// ���|���S���̐������Z����
				YukaNum++;
			}
		}

	}

	if (KabeNum != 0) {
		HitFlag = 0;

		if (MoveFlag) {
			// �ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < KabeNum; i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Kabe[i];

				// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

				// �����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1;

				// �ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
				{
					VECTOR SlideVec;	// �v���C���[���X���C�h������x�N�g��

					// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
					SlideVec = VCross(velo, Poly->Normal);

					// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
					// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
					SlideVec = VCross(Poly->Normal, SlideVec);

					// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
					NowPos = VAdd(OldPos, SlideVec);
				}
				int j = 0;
				// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				for (j = 0; j < KabeNum; j++)
				{
					// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Kabe[j];

					// �������Ă����烋�[�v���甲����
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
				}

				// j �� KabeNum �������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
				// �ǂɓ��������t���O��|������Ń��[�v���甲����
				if (j == KabeNum)
				{
					HitFlag = 0;
					break;
				}
			}
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�̏���

			// �ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < KabeNum; i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Kabe[i];

				// �|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					HitFlag = 1;
					break;
				}
			}
		}

		// �ǂɓ������Ă�����ǂ��牟���o���������s��
		if (HitFlag == 1)
		{
			// �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for (int k = 0; k < Hit_TryNum; k++)
			{
				int i = 0;
				// �ǃ|���S���̐������J��Ԃ�
				for (i = 0; i < KabeNum; i++)
				{
					// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Kabe[i];

					// �v���C���[�Ɠ������Ă��邩�𔻒�
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

					// �������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					NowPos = VAdd(NowPos, VScale(Poly->Normal, 5.0f));

					int j = 0;
					// �ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					for (j = 0; j < KabeNum; j++)
					{
						// �������Ă����烋�[�v�𔲂���
						Poly = Kabe[j];
						if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
					}

					// �S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
					if (j == KabeNum) break;
				}

				// i �� KabeNum �ł͂Ȃ��ꍇ�͑S���̃|���S���ŉ����o�������݂�O�ɑS�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂Ń��[�v���甲����
				if (i != KabeNum) break;
			}
		}
	}

	// ���|���S���Ƃ̓����蔻��
	if (YukaNum != 0)
	{
		// �W�����v�����㏸���̏ꍇ�͏����𕪊�
		if (velo.y > 0)
		{
			float MinY;

			// �V��ɓ����Ԃ��鏈�����s��

			// ��ԒႢ�V��ɂԂ���ׂ̔���p�ϐ���������
			MinY = 0.0f;

			// �����������ǂ����̃t���O�𓖂����Ă��Ȃ����Ӗ�����O�ɂ��Ă���
			HitFlag = 0;

			// ���|���S���̐������J��Ԃ�
			for (int i = 0; i < YukaNum; i++)
			{
				// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
				Poly = Yuka[i];

				// ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
				LineRes = HitCheck_Line_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

				// �ڐG���Ă��Ȃ������牽�����Ȃ�
				if (LineRes.HitFlag == FALSE) continue;

				// ���Ƀ|���S���ɓ������Ă��āA�����܂Ō��o�����V��|���S����荂���ꍇ�͉������Ȃ�
				if (HitFlag == 1 && MinY < LineRes.Position.y) continue;

				// �|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1;

				// �ڐG�����x���W��ۑ�����
				MinY = LineRes.Position.y;
			}

			// �ڐG�����|���S�������������ǂ����ŏ����𕪊�
			if (HitFlag == 1)
			{
				// �ڐG�����ꍇ�̓v���C���[�̂x���W��ڐG���W�����ɍX�V
				NowPos.y = MinY - height;

				// �x�������̑��x�͔��]
				obj->minus_gravity_velo();
			}
		}
		else
		{
			float MaxY;

			// ���~�����W�����v���ł͂Ȃ��ꍇ�̏���

			// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
			HitFlag = 0;

			// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
			MaxY = 0.0f;

			// ���|���S���̐������J��Ԃ�
			for (int i = 0; i < YukaNum; i++)
			{
				// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
				Poly = Yuka[i];

				// �W�����v�����ǂ����ŏ����𕪊�
				if (isAir)
				{
					// �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, height, 0.0f)), VAdd(NowPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}
				else
				{
					//�����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, height, 0.0f)), VAdd(NowPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}

				// �������Ă��Ȃ������牽�����Ȃ�
				if (LineRes.HitFlag == FALSE) continue;

				// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
				if (HitFlag == 1 && MaxY > LineRes.Position.y) continue;

				// �|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1;

				// �ڐG�����x���W��ۑ�����
				MaxY = LineRes.Position.y;
			}

			// ���|���S���ɓ����������ǂ����ŏ����𕪊�
			if (HitFlag == 1)
			{
				// ���������ꍇ

				// �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
				NowPos.y = MaxY;
				obj->grounded();
				// �x�������̈ړ����x�͂O��
				//pl.JumpPower = 0.0f;

			//	// �����W�����v���������ꍇ�͒��n��Ԃɂ���
			//	if (pl.State == 2)
			//	{
			//		// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
			//		if (MoveFlag)
			//		{
			//			// �ړ����Ă���ꍇ�͑����Ԃ�
			//			Player_PlayAnim(1);
			//			pl.State = 1;
			//		}
			//		else
			//		{
			//			// �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
			//			Player_PlayAnim(4);
			//			pl.State = 0;
			//		}

			//		// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
			//		pl.AnimBlendRate = 1.0f;
			//	}
			//}
			//else
			//{
			//	// ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ��
			//	if (pl.State != 2)
			//	{
			//		// �W�����v���ɂ���
			//		pl.State = 2;

			//		// ������Ƃ����W�����v����
			//		pl.JumpPower = PLAYER_FALL_UP_POWER;

			//		// �A�j���[�V�����͗������̂��̂ɂ���
			//		Player_PlayAnim(3);
			//	}
			//}
			}
		}
	}

	MV1CollResultPolyDimTerminate(HitDim);
	return NowPos;
}

void Stage::draw() const
{
	MyDraw::Draw3DModel(model_, transform_);

	//Vec3 objPos;


















}
