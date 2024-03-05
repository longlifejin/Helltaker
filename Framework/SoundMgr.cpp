#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{

}

SoundMgr::~SoundMgr()
{
    Release();
}

void SoundMgr::Init(int totalChannels)
{
    Release();

    for (int i = 0; i < totalChannels; ++i)
    {
        waiting.push_back(new sf::Sound());
    }
}

void SoundMgr::Release()
{
    StopAllSfx();
    StopBgm();
    for (auto sound : waiting)
    {
        delete sound;
    }
    waiting.clear();
    for (auto sound : playing)
    {
        delete sound;
    }

    playing.clear();
}



void SoundMgr::Update(float dt)
{

    if (!playing.empty())
    {
        for (auto it = playing.begin(); it != playing.end();)
        {
            if ((*it)->getStatus() == sf::Sound::Stopped)
            {
                waiting.push_back(*it);
                it = playing.erase(it);
            }
            else
            {
                ++it;
            }

        }
        //ũ�ν����̵� ���̶�� ������ ����
        if (isFading)
        {
            bool isEndBack = false;
            bool isEndFront = false;

            int backBgmIndex = (frontBgmIndex == 1) ? 0 : 1;

            float backVolume = bgm[backBgmIndex].getVolume();
            backVolume = Utils::Lerp(backVolume, 0.f, dt * 0.25f);
            bgm[backBgmIndex].setVolume(backVolume);
            if (std::abs(backVolume) < fadeLimit)
            {
                bgm[backBgmIndex].stop();
                bgm[backBgmIndex].setVolume(0.f);
                isEndBack = true;
            }

            float frontVolume = bgm[frontBgmIndex].getVolume();
            frontVolume = Utils::Lerp(frontVolume, bgmVolume, dt * 0.25f);
            bgm[frontBgmIndex].setVolume(frontVolume);
            if (std::abs(bgmVolume - frontVolume) < fadeLimit)
            {
                bgm[frontBgmIndex].setVolume(bgmVolume);
                isEndFront = true;
            }
            if (isEndBack && isEndFront)
            {

                isFading = false;
            }

            // if(crossFadeTimer>=crossFadeDuration)
            // {
            //     crossFadeTimer=0.f;
            //     isFading=false;
            // }
        }
    }
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
    PlaySfx(RES_MGR_SOUND_BUFFER.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
    sf::Sound* sound = nullptr;
    if (waiting.empty())
    {
        sound = playing.front();
        playing.pop_front();
        sound->stop();

    }
    else
    {
        sound = waiting.front();
        waiting.pop_front();
    }

    sound->setBuffer(buffer);
    sound->setLoop(loop);
    sound->setVolume(sfxVolume);
    sound->play();

    playing.push_back(sound);
}

void SoundMgr::PlayBgm(std::string id, bool crossFade)
{
    //fadeDuration, fadeTimer�� ����ؼ� bgm�� ��ü�ϰ� �ʹٸ� crossFade�� ���
    //crossFade�� ����ϸ� ���� ������� bgm�� ������ ���̰� ���ο� bgm�� ������ Ű���.
    //crossFade�� ������� ������ ���� ������� bgm�� �ٷ� ���߰� ���ο� bgm�� �ٷ� Ű���.

    frontBgmIndex = (frontBgmIndex + 1) % 2;
    int backBgmIndex = (frontBgmIndex == 1) ? 0 : 1;

    bgm[frontBgmIndex].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));

    if (crossFade)
    {
        isFading = true;
        bgm[frontBgmIndex].setVolume(0.f);
    }
    else
    {
        StopBgm();
        bgm[frontBgmIndex].setVolume(bgmVolume);
    }

    bgm[frontBgmIndex].setLoop(true);
    bgm[frontBgmIndex].play();
}

void SoundMgr::StopBgm()
{

    bgm[frontBgmIndex].stop();
    bgm[(frontBgmIndex + 1) % 2].stop();
    isFading = false;
    crossFadeTimer = 0.f;
}

void SoundMgr::StopAllSfx()
{
    for (auto sound : playing)
    {
        sound->stop();
        waiting.push_back(sound);
    }
    playing.clear();
}
