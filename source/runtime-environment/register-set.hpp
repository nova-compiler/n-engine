//
// runtime-stack.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_REGISTER_SET_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_REGISTER_SET_HEADER_

#include "runtime-stack.hpp"

#include <cstdint>

namespace Nova {

	typedef void * ReferenceAddress;

	enum class Register {
		// General-porpouse registers. They are 64 bits words.
		r0 = 0, r1, r2, r3, r4, r5, r6, r7,

		// Stack frame pointers. Used as references to addresses in the stack.
		sp0, sp1, sp2, sp3, sp4, sp5,

		// Memory-address pointers.
		m0, m1, m2, m3,

		// Comparison register.
		cp
	};
	
	class RegisterSet {
		std::int64_t _rRegisters[8];
		ReferenceAddress _mRegisters[4];
		StackAddress _spRegisters[6];
		bool _cpRegister;

	public:
		inline RegisterSet(
			) {
			}

		inline ~RegisterSet(
			) {
			}

		void SetRRegister(
			Register id, std::int64_t value
			) {
				_rRegisters[static_cast<int>(id)] = value;
			}
	};

}

#endif // !_NOVA_RUNTIME_ENVIRONMENT_REGISTER_SET_HEADER_