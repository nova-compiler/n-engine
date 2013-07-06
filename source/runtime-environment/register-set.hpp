//
// runtime-stack.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_REGISTER_SET_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_REGISTER_SET_HEADER_

#include "..\common\type-traits.hpp"

#include <cstdint>

namespace Nova {

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
		refaddr_t _mRegisters[4];
		staddr_t _spRegisters[6];
		bool _cpRegister;

		inline std::int64_t & _GetRValueReference(
			Register id
			) {
				return _rRegisters[static_cast<int>(id)];
			}

		inline staddr_t & _GetSPValueReference(
			Register id
			) {
				return _spRegisters[static_cast<int>(id) - static_cast<int>(Register::sp0)];
			}

		inline refaddr_t & _GetMValueReference(
			Register id
			) {
				return _mRegisters[static_cast<int>(id) - static_cast<int>(Register::m0)];
			}

	public:
		inline RegisterSet(
			) {
			}

		inline ~RegisterSet(
			) {
			}

		inline std::int64_t GetRRegister(
			Register id
			) {
				return _GetRValueReference(id);
			}

		inline void SetRRegister(
			Register id, std::int64_t value
			) {
				_GetRValueReference(id) = value;
			}

		inline staddr_t GetSPRegister(
			Register id
			) {
				return _GetSPValueReference(id);
			}

		inline void SetSPRegister(
			Register id, staddr_t value
			) {
				_GetSPValueReference(id) = value;
			}

		inline refaddr_t SetMRegister(
			Register id
			) {
				return _GetMValueReference(id);
			}

		inline void SetMRegister(
			Register id, refaddr_t value
			) {
				_GetMValueReference(id);
			}
	};

}

#endif // !_NOVA_RUNTIME_ENVIRONMENT_REGISTER_SET_HEADER_