#include "SoundEffectManager.h"


void SoundEffectManager::add(std::string name, int volume)
{
	sound_effects_.push_back(std::make_shared<SoundEffectObject>(name, volume));
}

bool SoundEffectManager::check_end(std::string name)
{
	for (const auto& se : sound_effects_) {
		if (se->tag == name) {
			return se->isDead;
		}
	}
	return false;
}

void SoundEffectManager::update()
{
	for (const auto& se : sound_effects_) {
		se->Update();
	}
}

void SoundEffectManager::remove()
{
	for (auto se = sound_effects_.begin(); se != sound_effects_.end();) {
		if ((*se)->isDead) {
			se = sound_effects_.erase(se);
		}
		else {
			se++;
		}
	}
}
