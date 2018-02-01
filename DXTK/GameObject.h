#pragma once
#include "CommonStates.h"
#include "SimpleMath.h"

//=================================================================
//Base Game Object Class
//=================================================================

using namespace DirectX;
using namespace SimpleMath;

class Camera;
struct ID3D11DeviceContext;
struct GameData;
struct DrawData;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData* _DD) = 0;

	//getters
	Vector3 GetPos() const;
	Vector3 GetScale() const;
	Matrix GetWorldMat() const;

	float GetPitch() const;
	float GetYaw() const;
	float GetRoll() const;

	bool IsPhysicsOn() const;
	float GetDrag() const;

	//setters
	void SetPos(Vector3 _pos);

	void SetScale(float _scale);
	void SetScale(float _x, float _y, float _z);
	void SetScale(Vector3 _scale);

	void SetYaw(float _yaw);
	void SetPitch(float _pitch);
	void SetRoll(float _roll);
	void SetYawPitchRoll(float _yaw, float _pitch, float _roll);

	void SetPhysicsOn(bool _physics);
	void TogglePhysics();
	void SetDrag(float _drag);

protected:
	//World transform/matrix of this GO and it components
	Matrix world_mat;
	Matrix rot_mat;
	Matrix fudge;
	Vector3 pos;
	Vector3 scale;
	float yaw;
	float pitch;
	float roll;

	//very basic physics
	bool physics_on;
	float drag;
	Vector3 velocity;
	Vector3 acceleration;

};
