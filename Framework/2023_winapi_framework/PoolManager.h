#pragma
class Object;
class PoolManager
{
	SINGLE(PoolManager);
public:
	// Ǯ�ʱ�ȭ
	void Init(OBJECT_GROUP _eTypem, int _poolSize);
	// Ǯ������
	void Release();
	// ������Ʈ ��������
	Object* GetObj(OBJECT_GROUP _eType);
	void ReturnObj(OBJECT_GROUP _eType, Object* _pObj);
private:
	map < OBJECT_GROUP, list<Object*>> m_mapObjPool;
};
