#pragma once
#include "Headers.h"
#include "Vertex3.h"

namespace lib
{
	class Mesh
	{
	public:
		Mesh();

		~Mesh();

		void Render( DWORD atribID );

		void Build();

		void AddVertex( D3DXVECTOR3 vertex, D3DXVECTOR3 normal, D3DXVECTOR2 texCoord );
		void AddIndex( DWORD index );
		void AddAttribut( DWORD attribut );

		void AddTriangle( D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 normal, D3DXVECTOR2 texCoord ) const;
		void AddQuad( D3DXVECTOR3 leftBottomBack, D3DXVECTOR3 rightTopFront ) const;

		std::vector< Vertex3 > GetVB() const;
		std::vector<DWORD> GetIB() const;
		std::vector<DWORD> GetAB() const;

		DWORD GetNumVertices();

		void SetVB( std::vector<Vertex3> vb );
		void SetIB( std::vector<DWORD> ib );
		void SetAB( std::vector<DWORD> ab );

	private:
		LPD3DXMESH _mesh;

		std::vector< Vertex3 > _VB;
		std::vector< DWORD > _IB;
		std::vector< DWORD > _AB;
	};
}
