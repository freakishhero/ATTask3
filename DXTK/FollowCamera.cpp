#include "FollowCamera.h"
#include "GameObject2D.h"
#include "GameData.h"

FollowCamera::FollowCamera(float _fov, float _aspect, float _near, float _far, GameObject2D* _target, Vector3 _dpos, Vector3 _up)
	: Camera(_fov, _aspect, _near, _far)
	, dpos(_dpos)
	, y_offset(0)
{
	target = _target;
}


/* Updates the camera's position relative to the target's position.
*/
void FollowCamera::Tick(GameData* _GD)
{
	FollowTarget(_GD);
	Camera::Tick(_GD);
}


void FollowCamera::SetTarget(GameObject2D* _target)
{
	target = _target;
}


/* Matches the camera's position with the target object's position.
*/
void FollowCamera::FollowTarget(GameData* _GD)
{
	if (!target)
		return;
	/*
	if ((int)target->GetPos().x % 64 == 0)
	{
		SetPos(Vector3(target->GetPos().x, pos.y, 0) + dpos);
	}
	if ((int)target->GetPos().y % 64 == 0)
	{
		SetPos(Vector3(target->GetPos().x, pos.y, 0) + dpos);
	}
	*/
	Vector2 target_pos = target->GetPos();
	SetPos(Vector3(target_pos.x, target_pos.y, 0));
}
