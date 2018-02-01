#pragma once
#include "Camera.h"

class GameObject2D;

class FollowCamera : public Camera
{
public:
	FollowCamera(float _FOV, float _AR, float _near, float _far, GameObject2D* _target, Vector3 _pos, Vector3 _up = Vector3::Up);
	~FollowCamera() = default;

	void Tick(GameData* _GD) override;
	void SetTarget(GameObject2D* _target);

private:
	void FollowTarget(GameData *_GD);

	GameObject2D* target;
	Vector3 dpos;
	int y_offset;

};
