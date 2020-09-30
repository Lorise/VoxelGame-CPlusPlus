#pragma once

namespace lib
{
	template< class T >
	void SafeDeletePtr( T* ptr )
	{
		if ( ptr )
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	template< class T >
	void SafeDeleteArray( T* arr )
	{
		if ( arr )
		{
			delete[] arr;
			arr = nullptr;
		}
	}

	template< class T >
	void SafeRelease( T* d3dObject )
	{
		if ( d3dObject )
		{
			d3dObject->Release();
			d3dObject = nullptr;
		}
	}
}