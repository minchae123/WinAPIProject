#pragma once
class Scene;
class SceneManager
{
	SINGLE(SceneManager);
public:
	void Init();
	void Update();
	void Render(HDC dc);
public:
	void LoadScene(const wstring& scenename);
	void RegisterScene(const wstring& scenename, std::shared_ptr<Scene> scene);
public:
	const std::shared_ptr<Scene>& GetCurScene() const
	{
		return _pCurScene;
	}
private:
	// ����Ʈ ������
	std::shared_ptr<Scene> _pCurScene; // ���� ��
	// ������ �����ϴ� ��.
	map<wstring, std::shared_ptr<Scene>> _mapScene;
};