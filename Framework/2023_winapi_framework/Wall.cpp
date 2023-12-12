#include "pch.h"
#include "Wall.h"
#include "DebugManager.h"

Wall::Wall()
{
	CreateCollider();
}

Wall::~Wall()
{
}

void Wall::Update()
{

}

void Wall::Render(HDC dc)
{
	Vector2 clampMin = GetClampMin();
	Vector2 clampMax = GetClampMax();

	Rectangle(dc, clampMin.x, clampMin.y, clampMax.x, clampMax.y);
	Component_Render(dc);
}
