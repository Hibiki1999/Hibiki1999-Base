#include "MyMath.h"

const float MyMath::Sqrt2 = 1.41421356237f;//(float�͗L�����͎���7���܂Ő��m��������ȍ~�͊��ɂ���Č덷�o���)

const float MyMath::PI = 3.14159265359f;

const float MyMath::Deg2Rad = PI / 180;

// �y���[���Ƃ���.h��float�Ȃ�static�����Ȃǂ̏����������Ȃ��������R�z
// �ꌾ
// �ȉ����ꌾ�ł܂Ƃ߂�Ɓu.h�w�b�_�̓}�V�����ɂ���ĕς��悤�Ȃ��Ƃ͋L�q�ł��Ȃ��v
// PC��}�V����|��R���p�C���ɂ���ď����̐��x�Ȃǂ␔�l�Ɍ덷���o�邩��
// ���ɂ���ĕϓ�����\���̂���float�Ȃ�(int�����͌덷���Ȃ�)
// ��static const�ÓI�萔�Ƃ���.h�w�b�_�ŏ��������邱�Ƃ������Ȃ�����(�萔�Ƃ����Ȃ�) �u�}�V���ˑ��v
// cpp�ő��v�Ȃ̂�cpp�͎��ۂ̏����x�[�X�œ����̂Ły���I�ȓ����Ă��悢�����ƂȂ邩��z(�ǂ̊��ł������Ƃ͌���Ȃ�)
// �y�׋��z�ȉ��T�C�g��C++��Bjarne����̐�����|�󂵂����̂�����
// https://qastack.jp/programming/9656941/why-cant-i-initialize-non-const-static-member-or-static-array-in-class