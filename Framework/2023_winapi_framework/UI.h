#pragma once
class UI
{
public:
	UI();
	~UI();
public:
	virtual void Update();
	virtual void OnClick();
	virtual void Render(HDC dc);
public: // setter
	void SetPos(Vector2 pos) { _pos = pos; }
	void SetScale(Vector2 scale) { _scale = scale; }
	void SetText(wstring text) { _uiText = text; }
public: // getter
	Vector2 GetPos() const { return _pos; }
	Vector2 GetScale() const { return _scale; }
	wstring GetText() const { return _uiText; }
private:
	Vector2 _pos;
	Vector2 _scale;
	wstring _uiText;
};

