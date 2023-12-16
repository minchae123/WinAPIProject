#pragma
class Object;
class PoolManager
{
	SINGLE(PoolManager);
public:
	// 풀초기화
	void Init(OBJECT_GROUP _eTypem, int _poolSize);
	// 풀릴리즈
	void Release();
	// 오브젝트 가져오기
	Object* GetObj(OBJECT_GROUP _eType);
	void ReturnObj(OBJECT_GROUP _eType, Object* _pObj);
private:
	map < OBJECT_GROUP, list<Object*>> m_mapObjPool;
};
