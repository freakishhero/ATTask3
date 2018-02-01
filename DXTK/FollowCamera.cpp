#include "FollowCamera.h"
//#include "GameObject2D.h"
#include "GameData.h"

FollowCamera::FollowCamera(float _fov, float _aspect, float _near, float _far, GameObject2D* _target, Vector3 _dpos, Vector3 _up)
	: Camera(_fov, _aspect, _near, _far)
	, target(_target)
	, dpos(_dpos)
	, y_offset(50)
{
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

	//Vector2 target_pos = target->getPos();
	//SetPos(Vector3(target_pos.x, target_pos.y + y_offset, 0) + dpos);
}
