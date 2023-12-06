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
	std::shared_ptr<Scene> pCurScene = SceneManager::GetInstance()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(eRight);
	// 충돌 검사를 해보자.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없는 경우
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

			// 찾아라.
			auto iter = _mapColInfo.find(colID.ID);
			// 없어용
			if (iter == _mapColInfo.end())
			{
				// 넣어라
				_mapColInfo.insert({ colID.ID, false });
				// 넣은거 잡아라.
				iter = _mapColInfo.find(colID.ID);
			}
			// 충돌하네?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 이전에도 충돌 중
				if (iter->second)
				{
					// 둘중 하나 삭제 예정이라면
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
				// 이전에 충돌x
				else
				{
					//if()
					pLeftCol->EnterCollision(pRightCol);
					pRightCol->EnterCollision(pLeftCol);
					iter->second = true;
				}
			}
			// 안하네?
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

bool CollisionManager::IsCollision(Collider* left, Collider* right)
{
	// 충돌검사 알고리즘
	// AABB 
	Vector2 vLeftPos = left->GetFinalPos();
	Vector2 vRightPos = right->GetFinalPos();
	Vector2 vLeftScale = left->GetScale();
	Vector2 vRightScale = right->GetScale();
	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;

	//OBB
	//OBB 충돌
	/*Vector2 leftPos = left->GetFinalPos();
	Vector2 rightPos = right->GetFinalPos();
	// 1. distance를 구한다.
	Vector2 distance = rightPos - leftPos;
	// 2. Ah와 Aw, Bh와 Bw를 구한다.
	Vector2 aHeight = left->GetHeightVector();
	Vector2 aWidth = left->GetWidthVector();
	Vector2 bHeight = right->GetHeightVector();
	Vector2 bWidth = right->GetWidthVector();
	// 3. 투영을 해서 d에 대한 값과 w(너비) 및 h(높이)를 이용하여 충돌이 났는지 확인한다.

	// 4개의 충돌이 모두 발생햇는지 안했는지 따라서 모두 발생했으면 true 아니면 false
	Vector2 vectors[4] = { aWidth, aHeight, bHeight, bWidth };
	for (int i = 0; i < 4; ++i)
	{
		double sum = 0;
		Vector2 normal = vectors[i].Normal(); // 정규화된 벡터를 구한다.
		// 한 축을 중심으로 나머지 내적한 값(투명)한 것들을 다 더 한다.
		for (int j = 0; j < 4; ++j)
		{
			sum += abs(vectors[j].Dot(normal));
		}
		// 두 점 사이의 거리를
		float distanceVector = distance.Dot(normal);

		if (abs(distanceVector) > sum)
		{
			return false;
		}
	}
	return true;*/
}

void CollisionManager::CheckGroup(OBJECT_GROUP eLeft, OBJECT_GROUP eRight)
{
	// 작은쪽을 행으로 씁시다.
	UINT Row = (UINT)eLeft;
	UINT Col = (UINT)eRight;
	Row = min(Row, Col);

	//// 비트 연산
	// 체크가 되어있다면
	if (_arrCheck[Row] & (1 << Col))
	{
		_arrCheck[Row] &= ~(1 << Col);
	}
	// 체크가 안되어있다면r
	else
	{
		_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionManager::CheckReset()
{
	memset(_arrCheck, 0, sizeof(UINT) * (UINT)(OBJECT_GROUP::END));
}

