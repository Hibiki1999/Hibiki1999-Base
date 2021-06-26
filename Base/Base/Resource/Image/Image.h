#ifndef IMAGE_H_
#define IMAGE_H_

#include <assert.h>
#include <array>
#include <vector>
#include <DxLib.h>

class DivImage
{
public:
	int XNum = 0;
	int YNum = 0;
	int XSize = 0;
	int YSize = 0;
	int* HandleArray = NULL;
	int AllNum = 0;
	DivImage(int XNum, int YNum, int XSize, int YSize)
	{
		this->XNum = XNum;
		this->YNum = YNum;
		this->XSize = XSize;
		this->YSize = YSize;
		AllNum = XNum * YNum;

		this->HandleArray = new int[AllNum];
		for (int i = 0; i < AllNum; i++) HandleArray[i] = -1;

		int* ary = HandleArray;
#ifdef _DEBUG 
		//ImagePowCheck((*this));
#endif
	};
	~DivImage()
	{
		if (this->HandleArray != NULL)
			delete[] this->HandleArray;
	};
#ifdef _DEBUG 
	//bool is_pow2(unsigned int x) // 2�ׂ̂��悩�v�Z
	//{
	//	return (x != 0) && (x & (x - 1)) == 0;
	//}
	//void ImagePowCheck(DivImage& divImage)
	//{
	//	if (divImage.XSize > 0 && divImage.YSize > 0
	//		&& is_pow2(divImage.XSize) && is_pow2(divImage.YSize)) return;
	//	else assert("3D�Ɏg���Ȃ�2�ׂ̂���̉摜�T�C�Y�ɂ��Ȃ���" == "");
	//}
#endif
private:
	DivImage(const DivImage& divImage) {};

	//������Z�q�̃I�[�o�[���[�h
	DivImage& operator=(const DivImage& divImage) {};
};

class Image
{
public:
	Image() {};
	~Image() {};
	static int LoadDivGraphs(const TCHAR* FileName, DivImage& divImage);
	static void Init();
	//�����Œ�`
	//static int test;
	
	static DivImage mapChip;
	static DivImage Explo;
	
	static int ModelHandle;
	static int sphere;

	static int Boss;
private:

};

#endif // !IMAGE_H_

