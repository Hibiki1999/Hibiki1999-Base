#ifndef MYMATH_H_
#define MYMATH_H_

// ���w�֘A�N���X
class MyMath
{
public:
	// C ++�W���ł́A�ÓIstatic�萔�́y�����^�z�܂��́y�񋓌^�z�݂̂��N���X���ŏ������ł��܂��B
	// ���ꂪ�A�ꕔ�̏�������������Ă���̂ɑ���static float�Ȃǂ��������ł��Ȃ����R�ł��B

	// �yOH,�m�[�z float�������`���邽�߂�����cpp�t�@�C�����쐬���Ȃ���
	//static const float Sqrt2 =�y���̃C�R�[���ŃG���[�z 1.41421356237f; 
	// ���[�g2
	static const float Sqrt2; // = 1.41421356237f;

	static const float PI;// = 3.14159265359f;

	static const float Deg2Rad;//=PI/2;

			/// <summary>
		/// �~�Ɖ~���d�Ȃ��Ă��邩�𒲂ׂ�
		/// </summary>
		/// <param name="x1">�~1�̒��Sx</param>
		/// <param name="y1">�~1�̒��Sy</param>
		/// <param name="radius1">�~1�̔��a</param>
		/// <param name="x2">�~2�̒��Sx</param>
		/// <param name="y2">�~2�̒��Sy</param>
		/// <param name="radius2">�~2�̔��a</param>
		/// <returns>�d�Ȃ��Ă����true�A�d�Ȃ��Ă��Ȃ����false��ԋp����</returns>
	static bool CircleCircleIntersection(
		float x1, float y1, float radius1,
		float x2, float y2, float radius2)
	{
		return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
			< ((radius1 + radius2) * (radius1 + radius2));
	}

}; // �y���Ӂz�Z�~�R���������Ły�錾���K�v�ł��G���[�z

#endif // �y�錾���K�v�ł��G���[�͏�̃Z�~�R���������z