#include "pch.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"
Texture* ResourceManager::TexLoad(const wstring& strKey, const wstring& strRelativePath)
{
    // �� ã������ �װ� �����ֱ�
    Texture* pTex = TexFind(strKey);
    if (nullptr != pTex)
        return pTex;

    // ó������ �����Ŵϱ�.. ��� ã�Ƽ�
    wstring strFilepath = PathManager::GetInstance()->GetResPath();
    strFilepath += strRelativePath;
    // ������డ����..
    pTex = new Texture;
    pTex->Load(strFilepath); // �ؽ�ó ��ü�� �ε�..
    pTex->SetKey(strKey); // Ű ��� �����صΰ�..
    pTex->SetRelativePath(strRelativePath);
    _mapTex.insert({ strKey,pTex }); // �װŸ� �ʿ��ٰ� ����.
    return pTex;
}

Texture* ResourceManager::TexFind(const wstring& strKey)
{
    // ã�Ƽ� return
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

    // �� ���� �� �� �ý��� �ݰ� ��ȯ
    _pSystem->close();
    _pSystem->release();
}

void ResourceManager::Init()
{
    FMOD::System_Create(&_pSystem); // �ý��� ���� �Լ�
    // ä�μ�, ���� ���
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

    // �������� ���� ����
    FMOD_MODE eMode = FMOD_LOOP_NORMAL; // �ݺ� ���   
    if (!IsLoop)
        eMode = FMOD_DEFAULT; // ���� 1���� ���

    SoundInfo* ptSound = new SoundInfo;
    ptSound->IsLoop = IsLoop;
  
    // ���� ��ü�� ����� ���� system��.
                            //���ϰ��,  FMOD_MODE, NULL, &sound
    _pSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
    _mapSound.insert({ strKey, ptSound });
}

void ResourceManager::Play(const wstring& strKey)
{
    SoundInfo* ptSound = FindSound(strKey);
    if (!ptSound)
        return;
    _pSystem->update(); // play�Ҷ� update�� �ֱ������� ȣ���ؾ� ���尡 �������� ����.
    SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
    if (!ptSound->IsLoop)
        eChannel = SOUND_CHANNEL::EFFECT;
    // ���� ��� �Լ�. &channel�� � ä���� ���� ����Ǵ��� ������ �ѱ�
    Volume(eChannel, 0.2f);
    _pSystem->playSound(ptSound->pSound, nullptr, false, &_pChannel[(UINT)eChannel]);
}

void ResourceManager::Stop(SOUND_CHANNEL eChannel)
{
    _pChannel[(UINT)eChannel]->stop();
}

void ResourceManager::Volume(SOUND_CHANNEL eChannel, float fVol)
{
    // 0.0 ~ 1.0 ���� ����
    _pChannel[(UINT)eChannel]->setVolume(fVol);
}

void ResourceManager::Pause(SOUND_CHANNEL eChannel, bool Ispause)
{
    // bool���� true�� �Ͻ�����. ��, �� �Լ��� ������ Createsound�Ҷ� 
    // FMOD_MODE�� FMOD_LOOP_NORMAL �̾�� ��.
    _pChannel[(UINT)eChannel]->setPaused(Ispause);
}

SoundInfo* ResourceManager::FindSound(const wstring& strKey)
{
    map<wstring, SoundInfo*>::iterator iter = _mapSound.find(strKey);

    if (iter == _mapSound.end())
        return nullptr;
    return iter->second;
}
