//
//  Geometry.h
//
//  (c) CJG 2016, cjgribel@gmail.com
//

#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "stdafx.h"
#include <vector>
#include "vec\vec.h"
#include "vec\mat.h"
#include "ShaderBuffers.h"
#include "drawcall.h"
#include "mesh.h"

using namespace linalg;

class Geometry_t
{
protected:

	// pointers to device vertex & index arrays
	ID3D11Buffer* vertex_buffer = nullptr;
	ID3D11Buffer* index_buffer = nullptr;
	//pointers to material buffer and texture sampler
	ID3D11Buffer* MaterialBuffer = nullptr;
	ID3D11SamplerState* SamplerState = nullptr;

public:

	Geometry_t(ID3D11Device* device);

	//
	// Map and update the matrix buffer
	//
	void CreateSampler(ID3D11Device* device);

	virtual void MapMatrixBuffers(
		ID3D11DeviceContext* device_context,
		ID3D11Buffer* matrix_buffer,
		mat4f ModelToWorldMatrix,
		mat4f WorldToViewMatrix,
		mat4f ProjectionMatrix);

	virtual void MapMaterialBuffers(
		ID3D11DeviceContext* device_context,
		ID3D11Buffer* material_buffer,
		vec4f Ka, vec4f Kd, vec4f Ks);

	virtual void render(ID3D11DeviceContext* device_context) const = 0;


	void compute_tangentspace(vertex_t& v0, vertex_t& v1, vertex_t& v2);

	virtual ~Geometry_t()
	{ 
		// release the Krak-..device buffers
		SAFE_RELEASE(vertex_buffer);
		SAFE_RELEASE(index_buffer);
	}
};


class Quad_t : public Geometry_t
{
	// our local vertex and index arrays
	std::vector<vertex_t> vertices;
	std::vector<unsigned> indices;
	unsigned nbr_indices = 0;

public:

	Quad_t(ID3D11Device* device);

	void render(ID3D11DeviceContext* device_context) const;

	~Quad_t() { }
};


class Cube_t : public Geometry_t
{
	// our local vertex and index arrays
	std::vector<vertex_t> vertices;
	std::vector<unsigned> indices;
	unsigned nbr_indices = 0;


public:

	Cube_t(ID3D11Device* device);

	void render(ID3D11DeviceContext* device_context) const;

	~Cube_t() { }
};

class OBJModel_t : public Geometry_t
{
	// index ranges, representing drawcalls, within an index array
	struct index_range_t
	{
		size_t start;
		size_t size;
		unsigned ofs;
		int mtl_index;
	};

	std::vector<index_range_t> index_ranges;
	std::vector<material_t> materials;

	void append_materials(const std::vector<material_t>& mtl_vec)
	{
		materials.insert(materials.end(), mtl_vec.begin(), mtl_vec.end());
	}

public:

	OBJModel_t(
		const std::string& objfile,
		ID3D11Device* device);

	void render(ID3D11DeviceContext* device_context) const;

	~OBJModel_t() { }
};

#endif