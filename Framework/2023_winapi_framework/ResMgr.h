#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL
{
	BGM, EFFECT, END
};
struct SoundInfo
{
	FMOD::Sound* pSound; // 실제 사운드 메모리
	bool IsLoop;
};
class Texture;

class ResourceManager
{
	SINGLE(ResourceManager);
public:
	Texture* TexLoad(const wstring& strKey,
		const wstring& strRelativePath);
	Texture* TexFind(const wstring& strKey);
	void Release();
private:
	map<wstring, Texture*> _mapTex;
	FMOD::System* _pSystem; // 사운드 시스템
	map<wstring, SoundInfo*> _mapSound;
	FMOD::Channel* _pChannel[(UINT)SOUND_CHANNEL::END]; // 오디오 채널
public:
	void Init();
	void LoadSound(const wstring& strKey, const wstring& strReleativePath, bool IsLoop);
	void Play(const wstring& strKey);
	void Stop(SOUND_CHANNEL eChannel);
	void Volume(SOUND_CHANNEL eChannel, float fVol);
	void Pause(SOUND_CHANNEL eChannel, bool Ispause);
private:
	SoundInfo* FindSound(const wstring& strKey);
};

