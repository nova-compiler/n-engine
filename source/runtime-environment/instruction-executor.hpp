//
// instruction-executor.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_INSTRUCTION_EXECUTOR_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_INSTRUCTION_EXECUTOR_HEADER_

#include "instruction-set.hpp"
#include "register-set.hpp"
#include "runtime-stack.hpp"
#include "assembly.hpp"

#include <cstdint>

namespace Nova {

	typedef void (* InstructionExecutor) (RuntimeFixedStack & stack, RegisterSet & registerSet, InstructionAssemblyReader & assemblyReader);

	class IInstructionExecutorFactory {
	public:
		virtual InstructionExecutor CreateExecutor(Instruction instruction) = 0;
	};

	class InstructionExecutorFactory : public IInstructionExecutorFactory {
		static void _Nop(
			RuntimeFixedStack & stack, RegisterSet & registerSet, InstructionAssemblyReader & instructionAssemblyReader
			) {
				instructionAssemblyReader.Nop();
			}

		static void _AddI4(
			RuntimeFixedStack & stack, RegisterSet & registerSet, InstructionAssemblyReader & instructionAssemblyReader
			) {
				instructionAssemblyReader.AddI4();
				std::int32_t a = stack.Pop<std::int32_t>(), b = stack.Pop<std::int32_t>();
				stack.Push<std::int32_t>(a + b);
			}

		static void _PushI4C(
			RuntimeFixedStack & stack, RegisterSet & registerSet, InstructionAssemblyReader & instructionAssemblyReader
			) {
				std::int32_t value;
				instructionAssemblyReader.PushI4C(value);
				stack.Push<std::int32_t>(value);
			}

		static void _PushI4R(
			RuntimeFixedStack & stack, RegisterSet & registerSet, InstructionAssemblyReader & assemblyReader
			) {
				throw NotImplementedException();
			}

		static void _Call(
			RuntimeFixedStack & stack, RegisterSet & registerSet, InstructionAssemblyReader & assemblyReader
			) {
				throw NotImplementedException();
			}

		static void _Ret(
			RuntimeFixedStack & stack, RegisterSet & registerSet, InstructionAssemblyReader & assemblyReader
			) {
				throw NotImplementedException();
			}

	public:
		InstructionExecutor CreateExecutor(
			Instruction instruction
			) {
				switch (instruction) {
				case Instruction::nop:
					return _Nop;
				case Instruction::add_i4:
					return _AddI4;
				case Instruction::push_i4c:
					return _PushI4C;
				case Instruction::push_i4r:
					return _PushI4R;
				case Instruction::call:
					return _Call;
				case Instruction::ret:
					return _Ret;
				default:
					throw RuntimeException("Unsupported instruction.");
				}
			}
	};

}

#endif // !_NOVA_RUNTIME_ENVIRONMENT_INSTRUCTION_EXECUTOR_HEADER_