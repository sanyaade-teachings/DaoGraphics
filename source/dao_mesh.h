/*
// Dao Graphics Engine
// http://www.daovm.net
//
// Copyright (c) 2013, Limin Fu
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef __DAO_MESH_H__
#define __DAO_MESH_H__

#include "dao_common.h"


typedef struct DaoxMesh     DaoxMesh;



/*
// All coordinates in the mesh vertices and bouding boxes are local.
*/


typedef struct DaoxMeshChunk  DaoxMeshChunk;
typedef struct DaoxMeshUnit   DaoxMeshUnit;

struct DaoxMeshChunk
{
	DaoxOBBox3D      obbox;      /* with local coordinates in the mesh; */
	DaoxPlainArray  *triangles;  /* <int>: with triangle indices in DaoxMesh; */

	DaoxMeshUnit    *unit;
	DaoxMeshChunk   *parent;
	DaoxMeshChunk   *left;
	DaoxMeshChunk   *right;
};
extern DaoType *daox_type_mesh_unit;

DaoxMeshChunk* DaoxMeshChunk_New( DaoxMeshUnit *unit );
void DaoxMeshChunk_Delete( DaoxMeshChunk *self );



struct DaoxMeshUnit
{
	DAO_CSTRUCT_COMMON;

	DaoxMesh        *mesh;
	DaoxMeshChunk   *tree;
	DaoxMaterial    *material;
	DaoxPlainArray  *vertices;  /* local coordinates; */
	DaoxPlainArray  *triangles; /* local coordinates (for face norms); */
	DaoxOBBox3D      obbox;  /* local coordinates; */
	uint_t           index;  /* unit index in the mesh; */
};
DaoxMeshUnit* DaoxMeshUnit_New();
void DaoxMeshUnit_Delete( DaoxMeshUnit *self );

void DaoxMeshUnit_SetMaterial( DaoxMeshUnit *self, DaoxMaterial *material );




struct DaoxMesh
{
	DAO_CSTRUCT_COMMON;

	DArray      *units;
	DaoxOBBox3D  obbox;  /* local coordinates; */
};
extern DaoType *daox_type_mesh;

DaoxMesh* DaoxMesh_New();
void DaoxMesh_Delete( DaoxMesh *self );

DaoxMeshUnit* DaoxMesh_AddUnit( DaoxMesh *self );
void DaoxMesh_ResetBoundingBox( DaoxMesh *self );
void DaoxMesh_UpdateTree( DaoxMesh *self, int maxtriangles );
void DaoxMesh_MakeViewFrustumCorners( DaoxMesh *self, float fov, float ratio, float near );




#endif
