//
//  Camera.h
//
//	Basic camera class
//

#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

class camera_t
{
	float vfov, aspect;	// aperture attributes
	float zNear, zFar;	// clip planes
	vec3f position;
	float angle = 0;			// rad
	float angle_vel = fPI / 4;	// rad/s

public:

	camera_t(
		float vfov,
		float aspect,
		float zNear,
		float zFar):
		vfov(vfov), aspect(aspect), zNear(zNear), zFar(zFar)
	{

	}

	void moveTo(const vec3f& p)
	{
		position = p;
	}

	void move(const vec3f& v)
	{
		position += v;
	}

	void rotate(const float v)
	{
		angle += v;
	}

	mat4f get_WorldToViewMatrix() const
	{
		mat4f T, R, S, M;
		T = mat4f::translation(-position);
		R = mat4f::rotation(angle, 0.0f, 1.0f, 0.0f);
		//R = mat4f::rotation(fPI / 4, fPI / 4, 0.0f);
		S = mat4f::scaling(1, 1, 1);
		M = R * T * S;
		return M;
		/*view.rotation =*/ //mat4f::rotation(0.2f, 0.0f, 1.0f, 0.0f);

		//return view.translation(-position);
		//return mat4f::translation(-position); // *mat4f::rotation(angle, 1.0f, 0.0f, 0.0f);
	}

	mat4f get_ProjectionMatrix() const
	{
		return mat4f::projection(vfov, aspect, zNear, zFar);
	}
};

#endif