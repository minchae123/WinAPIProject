#include "pch.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"
Texture* ResourceManager::TexLoad(const wstring& strKey, const wstring& strRelativePath)
{
    // 잘 찾았으면 그거 던져주기
    Texture* pTex = TexFind(strKey);
    if (nullptr != pTex)
        return pTex;

    // 처음에는 없을거니까.. 경로 찾아서
    wstring strFilepath = PathManager::GetInstance()->GetResPath();
    strFilepath += strRelativePath;
    // 만들어줘가지고..
    pTex = new Texture;
    pTex->Load(strFilepath); // 텍스처 자체를 로드..
    pTex->SetKey(strKey); // 키 경로 세팅해두고..
    pTex->SetRelativePath(strRelativePath);
    _mapTex.insert({ strKey,pTex }); // 그거를 맵에다가 저장.
    return pTex;
}

Texture* ResourceManager::TexFind(const wstring& strKey)
{
    // 찾아서 return
    auto iter = _mapTex.find(strKey);
    if (iter != _mapTex.end())
    {
        return iter->second;
    }
    return nullptr;
}

void ResourceManager::Release()
{
    // Texture
    map<wstring, Texture*>::iterator iter;
    for (iter = _mapTex.begin(); iter != _mapTex.end(); ++iter)
    {
        if (nullptr != iter->second)
            delete iter->second;
    }
    _mapTex.clear();

    // SOUND
    map<wstring, SoundInfo*>::iterator itersod;
    for (itersod = _mapSound.begin(); itersod != _mapSound.end(); ++itersod)
    {
        if (nullptr != itersod->second)
            delete itersod->second;
    }
    _mapSound.clear();

    // 다 쓰고 난 후 시스템 닫고 반환
    _pSystem->close();
    _pSystem->release();
}

void ResourceManager::Init()
{
    FMOD::System_Create(&_pSystem); // 시스템 생성 함수
    // 채널수, 사운드 모드
    if (_pSystem != nullptr)
        _pSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);
}

void ResourceManager::LoadSound(const wstring& strKey, const wstring& strReleativePath, bool IsLoop)
{
    if (FindSound(strKey))
        return;
    wstring strFilePath = PathManager::GetInstance()->GetResPath();
    strFilePath += strReleativePath;

    // wstring to string
    std::string str;
    str.assign(strFilePath.begin(), strFilePath.end());

    // 루프할지 말지 결정
    FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력   
    if (!IsLoop)
        eMode = FMOD_DEFAULT; // 사운드 1번만 출력

    SoundInfo* ptSound = new SoundInfo;
    ptSound->IsLoop = IsLoop;
  
    // 사운드 객체를 만드는 것은 system임.
                            //파일경로,  FMOD_MODE, NULL, &sound
    _pSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
    _mapSound.insert({ strKey, ptSound });
}

void ResourceManager::Play(const wstring& strKey)
{
    SoundInfo* ptSound = FindSound(strKey);
    if (!ptSound)
        return;
    _pSystem->update(); // play할때 update를 주기적으로 호출해야 사운드가 정지되지 않음.
    SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
    if (!ptSound->IsLoop)
        eChannel = SOUND_CHANNEL::EFFECT;
    // 사운드 재생 함수. &channel로 어떤 채널을 통해 재생되는지 포인터 넘김
    Volume(eChannel, 0.2f);
    _pSystem->playSound(ptSound->pSound, nullptr, false, &_pChannel[(UINT)eChannel]);
}

void ResourceManager::Stop(SOUND_CHANNEL eChannel)
{
    _pChannel[(UINT)eChannel]->stop();
}

void ResourceManager::Volume(SOUND_CHANNEL eChannel, float fVol)
{
    // 0.0 ~ 1.0 볼륨 조절
    _pChannel[(UINT)eChannel]->setVolume(fVol);
}

void ResourceManager::Pause(SOUND_CHANNEL eChannel, bool Ispause)
{
    // bool값이 true면 일시정지. 단, 이 함수를 쓰려면 Createsound할때 
    // FMOD_MODE가 FMOD_LOOP_NORMAL 이어야 함.
    _pChannel[(UINT)eChannel]->setPaused(Ispause);
}

SoundInfo* ResourceManager::FindSound(const wstring& strKey)
{
    map<wstring, SoundInfo*>::iterator iter = _mapSound.find(strKey);

    if (iter == _mapSound.end())
        return nullptr;
    return iter->second;
}
