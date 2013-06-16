//
// type-traits.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_COMMON_TYPE_TRAITS_HEADER_
#define _NOVA_COMMON_TYPE_TRAITS_HEADER_

#include <cstdint>

namespace Nova {

	typedef void * staddr_t;
	typedef void * refaddr_t;

	template <typename _Ty>
	struct EngineTypeTraits {
		static const bool Supported = false;
	};

	template <>
	struct EngineTypeTraits<std::int32_t> {
		static const bool Supported = true;
		static const size_t Size = 4;
	};

} // namespace Nova

#endif // !_NOVA_COMMON_TYPE_TRAITS_HEADER_