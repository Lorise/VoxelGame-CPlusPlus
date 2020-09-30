#pragma once

namespace lib
{
	class GameObject
	{
	public:
		virtual ~GameObject()
		{
		}

		virtual void Init() = 0;

		virtual void Event() = 0;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;

		virtual void PreRender() = 0;
		virtual void Render() = 0;

		virtual void Cleanup() = 0;
	};
}
