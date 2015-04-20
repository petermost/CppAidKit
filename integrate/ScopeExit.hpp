#pragma once

#include <functional>

namespace RohdeSchwarz 
{
	class ScopeExit
	{
		public:
			ScopeExit( const std::function< void() > &code )
				: code_( code )
			{
			}

			~ScopeExit()
			{
				code_();
			}

		private:
			std::function< void() > code_;
	};
}