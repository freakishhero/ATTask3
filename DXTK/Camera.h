#pragma once
#include "GameObject.h"

//=================================================================
//Base Camera Class
//=================================================================

struct GameData;

class Camera : public GameObject
{
public:
	Camera(float _fov, float _aspect, float _near, float _far, Vector3 _up = Vector3::Up, Vector3 _target = Vector3::Zero);
	~Camera() = default;

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;

	//Getters
	Matrix getProj() const { return proj_mat; }
	Matrix getView() const { return view_mat; }

	//Setters

protected:

	//Principle transforms/matrices for this camera
	Matrix proj_mat;
	Matrix view_mat;

	//parameters for setting up a camera
	float field_of_view;
	float aspect_ratio;
	float near_plane_distance;
	float far_plane_distance;

	Vector3 up;
	Vector3 target;

	float zoom;
};
