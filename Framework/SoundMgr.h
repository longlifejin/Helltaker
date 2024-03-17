#pragma once
#include "Singleton.h"

class SoundMgr :public Singleton<SoundMgr>
{
    friend Singleton<SoundMgr>;
private:
    SoundMgr();
    ~SoundMgr() override;

    sf::Sound bgm[2];
    int frontBgmIndex = 0;
    float fadespeed = 0.5f;
    float fadeLimit = 1.f;
    bool isFading = false;
    float crossFadeDuration = 1.f;
    float crossFadeTimer = 0.f;

    std::list <sf::Sound*> playing;
    std::list <sf::Sound*> waiting;

    float sfxVolume = 100.f;
    float bgmVolume = 100.f;
public:
    void SetSfxVolume(float v) { sfxVolume = v; }
    void SetBgmVolume(float v) { bgmVolume = v; }

    void Init(int totalChannels = 32);
    void Release();

    void Update(float dt);

    void PlaySfx(std::string id, bool loop = false);
    void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);
    void PlayBgm(std::string id, bool crossFade = true);
    void StopBgm();

    void StopAllSfx();

};
#define SOUND_MGR (Singleton<SoundMgr>::Instance())