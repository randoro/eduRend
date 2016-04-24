
#include "Geometry.h"


void Geometry_t::MapMatrixBuffers(
	ID3D11DeviceContext* device_context,
	ID3D11Buffer* matrix_buffer,
	mat4f ModelToWorldMatrix,
	mat4f WorldToViewMatrix,
	mat4f ProjectionMatrix)
{
	// map the resource buffer, obtain a pointer to it and then write our matrices to it
	D3D11_MAPPED_SUBRESOURCE resource;
	device_context->Map(matrix_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	MatrixBuffer_t* matrix_buffer_ = (MatrixBuffer_t*)resource.pData;
	matrix_buffer_->ModelToWorldMatrix = linalg::transpose(ModelToWorldMatrix);
	matrix_buffer_->WorldToViewMatrix = linalg::transpose(WorldToViewMatrix);
	matrix_buffer_->ProjectionMatrix = linalg::transpose(ProjectionMatrix);
	device_context->Unmap(matrix_buffer, 0);
}


Quad_t::Quad_t(ID3D11Device* device)
{
	// populate the vertex array with 4 vertices
	vertex_t v0, v1, v2, v3;
	v0.Pos = { -0.5, -0.5f, 0.0f };
	v0.Normal = { 0, 0, 1 };
	v0.TexCoord = { 0, 0 };
	v1.Pos = { 0.5, -0.5f, 0.0f };
	v1.Normal = { 0, 0, 1 };
	v1.TexCoord = { 0, 1 };
	v2.Pos = { 0.5, 0.5f, 0.0f };
	v2.Normal = { 0, 0, 1 };
	v2.TexCoord = { 1, 1 };
	v3.Pos = { -0.5, 0.5f, 0.0f };
	v3.Normal = { 0, 0, 1 };
	v3.TexCoord = { 1, 0 };
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	// populate the index array
	// triangle #1
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	// triangle #2
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	// vertex array descriptor
	D3D11_BUFFER_DESC vbufferDesc = { 0.0f };
	vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbufferDesc.CPUAccessFlags = 0;
	vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vbufferDesc.MiscFlags = 0;
	vbufferDesc.ByteWidth = vertices.size()*sizeof(vertex_t);
	// data resource
	D3D11_SUBRESOURCE_DATA vdata;
	vdata.pSysMem = &vertices[0];
	// create vertex buffer on device using descriptor & data
	HRESULT vhr = device->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);

	//  index array descriptor
	D3D11_BUFFER_DESC ibufferDesc = { 0.0f };
	ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibufferDesc.CPUAccessFlags = 0;
	ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
	ibufferDesc.MiscFlags = 0;
	ibufferDesc.ByteWidth = indices.size()*sizeof(unsigned);
	// data resource
	D3D11_SUBRESOURCE_DATA idata;
	idata.pSysMem = &indices[0];
	// create index buffer on device using descriptor & data
	HRESULT ihr = device->CreateBuffer(&ibufferDesc, &idata, &index_buffer);

	// local data is now loaded to device so it can be released
	vertices.clear();
	nbr_indices = indices.size();
	indices.clear();
}

void Quad_t::render(ID3D11DeviceContext* device_context) const
{
	//set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// bind our vertex buffer
	UINT32 stride = sizeof(vertex_t); //  sizeof(float) * 8;
	UINT32 offset = 0;
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	// bind our index buffer
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// make the drawcall
	device_context->DrawIndexed(nbr_indices, 0, 0);
}


Cube_t::Cube_t(ID3D11Device* device)
{
	// populate the vertex array with 4 vertices
	vec3f vPos0, vPos1, vPos2, vPos3, vPos4, vPos5, vPos6, vPos7;

	vPos0 = { -0.5, -0.5f, 0.5f };
	vPos1 = { 0.5, -0.5f, 0.5f };
	vPos2 = { 0.5, 0.5f, 0.5f };
	vPos3 = { -0.5, 0.5f, 0.5f };

	vPos4 = { 0.5, -0.5f, -0.5f };
	vPos5 = { -0.5, -0.5f, -0.5f };
	vPos6 = { -0.5, 0.5f, -0.5f };
	vPos7 = { 0.5, 0.5f, -0.5f };


	vertex_t v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23;

	//front
	v0.Pos = vPos0;
	v0.Normal = { 0, 0, 1 };
	v0.TexCoord = { 0, 0 };

	v1.Pos = vPos1;
	v1.Normal = { 0, 0, 1 };
	v1.TexCoord = { 0, 1 };

	v2.Pos = vPos2;
	v2.Normal = { 0, 0, 1 };
	v2.TexCoord = { 1, 1 };

	v3.Pos = vPos3;
	v3.Normal = { 0, 0, 1 };
	v3.TexCoord = { 1, 0 };


	//right side
	v4.Pos = vPos1;
	v4.Normal = { 1, 0, 0 };
	v4.TexCoord = { 0, 0 };

	v5.Pos = vPos4;
	v5.Normal = { 1, 0, 0 };
	v5.TexCoord = { 0, 1 };

	v6.Pos = vPos7;
	v6.Normal = { 1, 0, 0 };
	v6.TexCoord = { 1, 1 };

	v7.Pos = vPos2;
	v7.Normal = { 1, 0, 0 };
	v7.TexCoord = { 1, 0 };

	//back side
	v8.Pos = vPos4;
	v8.Normal = { 0, 0, -1 };
	v8.TexCoord = { 0, 0 };

	v9.Pos = vPos5;
	v9.Normal = { 0, 0, -1 };
	v9.TexCoord = { 0, 1 };

	v10.Pos = vPos6;
	v10.Normal = { 0, 0, -1 };
	v10.TexCoord = { 1, 1 };

	v11.Pos = vPos7;
	v11.Normal = { 0, 0, -1 };
	v11.TexCoord = { 1, 0 };

	//left side
	v12.Pos = vPos5;
	v12.Normal = { -1, 0, 0 };
	v12.TexCoord = { 0, 0 };

	v13.Pos = vPos0;
	v13.Normal = { -1, 0, 0 };
	v13.TexCoord = { 0, 1 };

	v14.Pos = vPos3;
	v14.Normal = { -1, 0, 0 };
	v14.TexCoord = { 1, 1 };

	v15.Pos = vPos6;
	v15.Normal = { -1, 0, 0 };
	v15.TexCoord = { 1, 0 };

	//down side
	v16.Pos = vPos5;
	v16.Normal = { 0, -1, 0 };
	v16.TexCoord = { 0, 0 };

	v17.Pos = vPos4;
	v17.Normal = { 0, -1, 0 };
	v17.TexCoord = { 0, 1 };

	v18.Pos = vPos1;
	v18.Normal = { 0, -1, 0 };
	v18.TexCoord = { 1, 1 };

	v19.Pos = vPos0;
	v19.Normal = { 0, -1, 0 };
	v19.TexCoord = { 1, 0 };

	//up side
	v20.Pos = vPos3;
	v20.Normal = { 0, 1, 0 };
	v20.TexCoord = { 0, 0 };

	v21.Pos = vPos2;
	v21.Normal = { 0, 1, 0 };
	v21.TexCoord = { 0, 1 };

	v22.Pos = vPos7;
	v22.Normal = { 0, 1, 0 };
	v22.TexCoord = { 1, 1 };

	v23.Pos = vPos6;
	v23.Normal = { 0, 1, 0 };
	v23.TexCoord = { 1, 0 };




	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);
	vertices.push_back(v9);
	vertices.push_back(v10);
	vertices.push_back(v11);
	vertices.push_back(v12);
	vertices.push_back(v13);
	vertices.push_back(v14);
	vertices.push_back(v15);
	vertices.push_back(v16);
	vertices.push_back(v17);
	vertices.push_back(v18);
	vertices.push_back(v19);
	vertices.push_back(v20);
	vertices.push_back(v21);
	vertices.push_back(v22);
	vertices.push_back(v23);

	// populate the index array


	int offset = 0;

	//quad1
	// triangle #1
	indices.push_back(0 + offset);
	indices.push_back(1 + offset);
	indices.push_back(3 + offset);
	// triangle #2
	indices.push_back(1 + offset);
	indices.push_back(2 + offset);
	indices.push_back(3 + offset);

	offset += 4;

	//quad2 (right side)
	// triangle #1
	indices.push_back(0 + offset);
	indices.push_back(1 + offset);
	indices.push_back(3 + offset);
	// triangle #2
	indices.push_back(1 + offset);
	indices.push_back(2 + offset);
	indices.push_back(3 + offset);

	offset += 4;

	//quad3 (back side)
	// triangle #1
	indices.push_back(0 + offset);
	indices.push_back(1 + offset);
	indices.push_back(3 + offset);
	// triangle #2
	indices.push_back(1 + offset);
	indices.push_back(2 + offset);
	indices.push_back(3 + offset);

	offset += 4;

	//quad4 (left side)
	// triangle #1
	indices.push_back(0 + offset);
	indices.push_back(1 + offset);
	indices.push_back(3 + offset);
	// triangle #2
	indices.push_back(1 + offset);
	indices.push_back(2 + offset);
	indices.push_back(3 + offset);

	offset += 4;

	//quad5 (down side)
	// triangle #1
	indices.push_back(0 + offset);
	indices.push_back(1 + offset);
	indices.push_back(3 + offset);
	// triangle #2
	indices.push_back(1 + offset);
	indices.push_back(2 + offset);
	indices.push_back(3 + offset);

	offset += 4;

	//quad6 (up side)
	// triangle #1
	indices.push_back(0 + offset);
	indices.push_back(1 + offset);
	indices.push_back(3 + offset);
	// triangle #2
	indices.push_back(1 + offset);
	indices.push_back(2 + offset);
	indices.push_back(3 + offset);

	// vertex array descriptor
	D3D11_BUFFER_DESC vbufferDesc = { 0.0f };
	vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbufferDesc.CPUAccessFlags = 0;
	vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vbufferDesc.MiscFlags = 0;
	vbufferDesc.ByteWidth = vertices.size()*sizeof(vertex_t);
	// data resource
	D3D11_SUBRESOURCE_DATA vdata;
	vdata.pSysMem = &vertices[0];
	// create vertex buffer on device using descriptor & data
	HRESULT vhr = device->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);

	//  index array descriptor
	D3D11_BUFFER_DESC ibufferDesc = { 0.0f };
	ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibufferDesc.CPUAccessFlags = 0;
	ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
	ibufferDesc.MiscFlags = 0;
	ibufferDesc.ByteWidth = indices.size()*sizeof(unsigned);
	// data resource
	D3D11_SUBRESOURCE_DATA idata;
	idata.pSysMem = &indices[0];
	// create index buffer on device using descriptor & data
	HRESULT ihr = device->CreateBuffer(&ibufferDesc, &idata, &index_buffer);

	// local data is now loaded to device so it can be released
	vertices.clear();
	nbr_indices = indices.size();
	indices.clear();
}




void Cube_t::render(ID3D11DeviceContext* device_context) const
{
	//set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// bind our vertex buffer
	UINT32 stride = sizeof(vertex_t); //  sizeof(float) * 8;
	UINT32 offset = 0;
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	// bind our index buffer
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// make the drawcall
	device_context->DrawIndexed(nbr_indices, 0, 0);
}


OBJModel_t::OBJModel_t(
	const std::string& objfile,
	ID3D11Device* device)
{
	//
	// load the OBJ
	//
	mesh_t* mesh = new mesh_t();
	mesh->load_obj(objfile);

	// load and organize indices in ranges per drawcall (material)
	//
	std::vector<unsigned> indices;
	size_t i_ofs = 0;

	for (auto& dc : mesh->drawcalls)
	{
		// append the drawcall indices
		for (auto& tri : dc.tris)
			indices.insert(indices.end(), tri.vi, tri.vi + 3);

		// create a range
		size_t i_size = dc.tris.size() * 3;
		int mtl_index = dc.mtl_index > -1 ? dc.mtl_index : -1;
		index_ranges.push_back({ i_ofs, i_size, 0, mtl_index });

		i_ofs = indices.size();
	}

	// vertex array descriptor
	D3D11_BUFFER_DESC vbufferDesc = { 0.0f };
	vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbufferDesc.CPUAccessFlags = 0;
	vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vbufferDesc.MiscFlags = 0;
	vbufferDesc.ByteWidth = mesh->vertices.size()*sizeof(vertex_t);
	// data resource
	D3D11_SUBRESOURCE_DATA vdata;
	vdata.pSysMem = &(mesh->vertices)[0];
	// create vertex buffer on device using descriptor & data
	HRESULT vhr = device->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);

	// index array descriptor
	D3D11_BUFFER_DESC ibufferDesc = { 0.0f };
	ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibufferDesc.CPUAccessFlags = 0;
	ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
	ibufferDesc.MiscFlags = 0;
	ibufferDesc.ByteWidth = indices.size()*sizeof(unsigned);
	// data resource
	D3D11_SUBRESOURCE_DATA idata;
	idata.pSysMem = &indices[0];
	// create index buffer on device using descriptor & data
	HRESULT ihr = device->CreateBuffer(&ibufferDesc, &idata, &index_buffer);

	// copy materials from mesh
	append_materials(mesh->materials);

	// load textures associated with materials to device
	for (auto& mtl : materials)
	{
		HRESULT hr;
		std::wstring wstr; // for conversion from string to wstring

		// Kd_map
		if (mtl.map_Kd.size()) {
			wstr = std::wstring(mtl.map_Kd.begin(), mtl.map_Kd.end());
			hr = DirectX::CreateWICTextureFromFile(device, wstr.c_str(), &mtl.map_Kd_Tex, &mtl.map_Kd_TexSRV);
			printf("loading texture %s - %s\n", mtl.map_Kd.c_str(), SUCCEEDED(hr) ? "OK" : "FAILED");
		}

		// other maps here...
	}

	SAFE_DELETE(mesh);
}


void OBJModel_t::render(ID3D11DeviceContext* device_context) const
{
	//set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// bind vertex buffer
	UINT32 stride = sizeof(vertex_t); //  sizeof(float) * 8;
	UINT32 offset = 0;
	//ID3D11Buffer* buffersToSet[] = { vertex_buffer };
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	// bind index buffer
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// iterate drawcalls
	for (auto& irange : index_ranges)
	{
		// fetch material and bind texture
		const material_t& mtl = materials[irange.mtl_index];
		device_context->PSSetShaderResources(0, 1, &mtl.map_Kd_TexSRV);

		// make the drawcall
		device_context->DrawIndexed(irange.size, irange.start, 0);
	}
}