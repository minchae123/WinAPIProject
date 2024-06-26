#pragma once 
#define SINGLE(type)			\
private:						\
	type() {}					\
	~type(){}					\
public:							\
	static type* GetInstance()	\
	{							\
		static type Instance;	\
		return &Instance;		\
	}
#define WINDOW_CLASS_NAME L"Gamep"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720 
#define RECT_RENDER(posx, posy, scalex, scaley, hdc) Rectangle(hdc, (int)(posx-scalex/2), (int)(posy-scaley/2), (int)(posx+scalex/2), (int)(posy+scaley/2))
#define CIRCLE_RENDER(posx, posy, scalex, scaley, hdc) Ellipse(hdc, (int)(posx-scalex/2), (int)(posy-scaley/2), (int)(posx+scalex/2), (int)(posy+scaley/2))

#define RECT_MAKE(posx, posy, scalex, scaley) {posx-scalex/2, posy-scaley/2, posx+scalex/2, posy+scaley/2}
#define DeltaTime TimeManager::GetInstance()->GetDeltaTime()
#define KEY_CHECK(key, state) KeyManager::GetInstance()->GetKey(key) == state
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define KEY_UP(key) KEY_CHECK(key, KEY_STATE::UP)
#define KEY_DOWN(key) KEY_CHECK(key, KEY_STATE::DOWN)
#define KEY_PRESS(key) KEY_CHECK(key, KEY_STATE::PRESS)
#define Rad2Deg(rad) rad * (180 / M_PI)
#define Deg2Rad(deg) deg * (M_PI / 180)
#define DebugLog(value) DebugManager::GetInstance()->SetLog(value)
#define Text(value) std::to_wstring(value)
#define SceneLoad(scene) SceneManager::GetInstance()->LoadScene(scene)
