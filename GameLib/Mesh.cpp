#include "Mesh.h"
#include "../VoxelGame/BaseGenerator.h"

namespace lib
{
	Mesh::Mesh()
	{
		_mesh = nullptr;
	}

	Mesh::~Mesh()
	{
		SafeRelease( _mesh );
	}

	void Mesh::Render( DWORD AtribID )
	{
		_mesh->DrawSubset( AtribID );
	}

	void Mesh::Build()
	{
		SafeRelease( _mesh );

		HRESULT hr;

		hr = D3DXCreateMeshFVF( DWORD( _VB.size() / 2 ), static_cast< DWORD >( _VB.size() ), D3DXMESH_MANAGED | D3DXMESH_32BIT, Vertex3::FVF, g_engine->core->d3dd9, &_mesh );
		if ( FAILED( hr ) )
		{
			MessageBox( nullptr, "D3DXCreateMeshFVF", "D3DXCreateMeshFVF", MB_OK | MB_ICONERROR );
			return;
		}

		Vertex3 *pVB = nullptr;
		hr = _mesh->LockVertexBuffer( D3DLOCK_DISCARD, reinterpret_cast< void** >( &pVB ) );
		if ( FAILED( hr ) )
		{
			lib::SafeRelease( _mesh );
			MessageBox( nullptr, "LockVertexBuffer", "LockVertexBuffer", MB_OK | MB_ICONERROR );
			return;
		}
		copy( _VB.begin(), _VB.end(), pVB );
		hr = _mesh->UnlockVertexBuffer();
		if ( FAILED( hr ) )
		{
			lib::SafeRelease( _mesh );
			MessageBox( nullptr, "UnlockVertexBuffer", "UnlockVertexBuffer", MB_OK | MB_ICONERROR );
			return;
		}

		DWORD *pIB = nullptr;
		hr = _mesh->LockIndexBuffer( D3DLOCK_DISCARD, reinterpret_cast< void** >( &pIB ) );
		if ( FAILED( hr ) )
		{
			lib::SafeRelease( _mesh );
			MessageBox( nullptr, "LockIndexBuffer", "LockIndexBuffer", MB_OK | MB_ICONERROR );
			return;
		}
		copy( _IB.begin(), _IB.end(), pIB );
		hr = _mesh->UnlockIndexBuffer();
		if ( FAILED( hr ) )
		{
			lib::SafeRelease( _mesh );
			MessageBox( nullptr, "UnlockIndexBuffer", "UnlockIndexBuffer", MB_OK | MB_ICONERROR );
			return;
		}

		DWORD *pAB = nullptr;
		hr = _mesh->LockAttributeBuffer( D3DLOCK_DISCARD, &pAB );
		if ( FAILED( hr ) )
		{
			lib::SafeRelease( _mesh );
			MessageBox( nullptr, "LockAttributeBuffer", "LockAttributeBuffer", MB_OK | MB_ICONERROR );
			return;
		}
		copy( _AB.begin(), _AB.end(), pAB );
		hr = _mesh->UnlockAttributeBuffer();
		if ( FAILED( hr ) )
		{
			lib::SafeRelease( _mesh );
			MessageBox( nullptr, "UnlockAttributeBuffer", "UnlockAttributeBuffer", MB_OK | MB_ICONERROR );
			return;
		}

// 		std::vector< DWORD > adjacencyBuffer( _mesh->GetNumFaces() * 3 );
// 		hr = _mesh->GenerateAdjacency( 0.f, &adjacencyBuffer[ 0 ] );
// 		if ( FAILED( hr ) )
// 		{
// 			gl::SafeRelease( _mesh );
// 			MessageBox( nullptr, "GenerateAdjacency", "GenerateAdjacency", MB_OK | MB_ICONERROR );
// 			return;
// 		}
// 		hr = _mesh->OptimizeInplace( D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &adjacencyBuffer[ 0 ], 0, 0, 0 );
// 		if ( FAILED( hr ) )
// 		{
// 			gl::SafeRelease( _mesh );
// 			MessageBox( nullptr, "OptimizeInplace", "OptimizeInplace", MB_OK | MB_ICONERROR );
// 			return;
// 		}
	}

	void Mesh::AddVertex( D3DXVECTOR3 vertex, D3DXVECTOR3 normal, D3DXVECTOR2 texCoord )
	{
		_VB.push_back( Vertex3( vertex.x, vertex.y, vertex.z, normal.x, normal.y, normal.z, texCoord.x, texCoord.y ) );
	}

	void Mesh::AddIndex( DWORD index )
	{
		_IB.push_back( index );
	}

	void Mesh::AddAttribut( DWORD attribut )
	{
		_AB.push_back( attribut );
	}

	void Mesh::AddTriangle( D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 normal, D3DXVECTOR2 texCoord ) const
	{

	}

	void Mesh::AddQuad( D3DXVECTOR3 leftBottomBack, D3DXVECTOR3 rightTopFront ) const
	{

	}

	std::vector< Vertex3 > Mesh::GetVB() const
	{
		return _VB;
	}

	std::vector<DWORD> Mesh::GetIB() const
	{
		return _IB;
	}

	std::vector<DWORD> Mesh::GetAB() const
	{
		return _AB;
	}

	DWORD Mesh::GetNumVertices()
	{
		if ( _mesh != nullptr )
			return _mesh->GetNumVertices();

		return 0;
	}

	void Mesh::SetVB( std::vector<Vertex3> vb )
	{
		_VB = vb;
	}

	void Mesh::SetIB( std::vector<DWORD> ib )
	{
		_IB = ib;
	}

	void Mesh::SetAB( std::vector<DWORD> ab )
	{
		_AB = ab;
	}
}
