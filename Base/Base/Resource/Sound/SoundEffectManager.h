#ifndef SOUND_H_
#define SOUND_H_

#include <string>
#include <list>
#include <memory>

#include "BGM_Object/BGM_Object.h"
#include "SoundEffect_Object/SoundEffectObject.h"

class SoundEffectManager
{
public:
	SoundEffectManager() {};
	~SoundEffectManager() {};
	//サウンドエフェクト追加
	void add(std::string name, int volume);
	//サウンドエフェクトの再生を終わったか？
	bool check_end(std::string name);
	//サウンドエフェクトの状態検索
	void update();
	//サウンドエフェクトをメモリに残らないように削除
	void remove();

private:
	//サウンドエフェクトリスト
	std::list<std::shared_ptr<SoundEffectObject>> sound_effects_;

};

#endif // !SOUND_H_

