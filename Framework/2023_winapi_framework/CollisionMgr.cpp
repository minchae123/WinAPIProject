#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Scene.h"
#include "Collider.h"
void CollisionManager::Update()
{
	for (UINT Row = 0; Row < (UINT)OBJECT_GROUP::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)OBJECT_GROUP::END; ++Col)
		{
			if (_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((OBJECT_GROUP)Row, (OBJECT_GROUP)Col);
			}
		}
	}
}
void CollisionManager::CollisionGroupUpdate(OBJECT_GROUP eLeft, OBJECT_GROUP eRight)
{
	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInstance()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(eRight);
	// �浹 �˻縦 �غ���.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� ���� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr ||
				vecLeft[i] == vecRight[j])
				continue;
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();
			COLLIDER_ID colID;
			colID.left_ID = pLeftCol->GetID();
			colID.right_ID = pRightCol->GetID();

			// ã�ƶ�.
			auto iter = _mapColInfo.find(colID.ID);
			// �����
			if (iter == _mapColInfo.end())
			{
				// �־��
				_mapColInfo.insert({ colID.ID, false });
				// ������ ��ƶ�.
				iter = _mapColInfo.find(colID.ID);
			}
			// �浹�ϳ�?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// �������� �浹 ��
				if (iter->second)
				{
					// ���� �ϳ� ���� �����̶��
					if(vecLeft[i]->GetIsDead() || vecRight[j]->GetIsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->StayCollision(pRightCol);
						pRightCol->StayCollision(pLeftCol);
					}
				}
				// ������ �浹x
				else
				{
					//if()
					pLeftCol->EnterCollision(pRightCol);
					pRightCol->EnterCollision(pLeftCol);
					iter->second = true;
				}
			}
			// ���ϳ�?
			else
			{
				if (iter->second)
				{
					pLeftCol->ExitCollision(pRightCol);
					pRightCol->ExitCollision(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* pLeft, Collider* pRight)
{
	// �浹�˻� �˰���
	// AABB 
	Vector2 vLeftPos = pLeft->GetFinalPos();
	Vector2 vRightPos = pRight->GetFinalPos();
	Vector2 vLeftScale = pLeft->GetScale();
	Vector2 vRightScale = pRight->GetScale();
	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CollisionManager::CheckGroup(OBJECT_GROUP eLeft, OBJECT_GROUP eRight)
{
	// �������� ������ ���ô�.
	UINT Row = (UINT)eLeft;
	UINT Col = (UINT)eRight;
	Row = min(Row, Col);

	//// ��Ʈ ����
	// üũ�� �Ǿ��ִٸ�
	if (_arrCheck[Row] & (1 << Col))
	{
		_arrCheck[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�r
	else
	{
		_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionManager::CheckReset()
{
	memset(_arrCheck, 0, sizeof(UINT) * (UINT)(OBJECT_GROUP::END));
}

