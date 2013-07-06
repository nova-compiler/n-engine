//
// runtime-context.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_RUNTIME_CONTEXT_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_RUNTIME_CONTEXT_HEADER_

#include "runtime-stack.hpp"
#include "register-set.hpp"
#include "runtime-scope.hpp"
#include "assembly.hpp"

#include "..\common\exception.hpp"
#include "..\common\type-traits.hpp"

#include <cstdint>

namespace Nova {
	class RuntimeContext {
		RuntimeFixedStack * const _runtimeStack;
		RegisterSet * const _registerSet;
		RuntimeScopeManager * const _scopeManager;
		const scoperef_t _startScope;

		inline bool _ExecuteInstruction(
			Instruction instruction, InstructionAssemblyReader & instructionAssemblyReader
			) {
				switch (instruction) {
				case Instruction::nop:
					{
						instructionAssemblyReader.Nop();
					}
					return true;
				case Instruction::add_i4:
					{
						instructionAssemblyReader.AddI4();
						std::int32_t a = _runtimeStack->Pop<std::int32_t>(), b = _runtimeStack->Pop<std::int32_t>();
						_runtimeStack->Push<std::int32_t>(a + b);
					}
					return true;
				case Instruction::push_i4c:
					{
						std::int32_t value;
						instructionAssemblyReader.PushI4C(value);
						_runtimeStack->Push<std::int32_t>(value);
					}
					return true;
				case Instruction::push_i4r:
					{
					}
					return true;
				case Instruction::call:
					{
						scoperef_t scopeId;
						instructionAssemblyReader.Call(scopeId);
						_ExecuteScope(scopeId);
					}
					return true;
				case Instruction::xcall:
					{
						scoperef_t scopeId;
						instructionAssemblyReader.XCall(scopeId);
						ExternalScope & scope = _scopeManager->GetExternalScope(scopeId);
						scope.GetCallbackFunction()(* _runtimeStack);
					}
					return true;
				case Instruction::ret:
					{
						instructionAssemblyReader.Ret();
					}
					return false;
				default:
					throw RuntimeException("Unsupported instruction.");
				}
			}

		inline void _ExecuteScope(
			scoperef_t scopeId
			) {
				RuntimeScope & scope = _scopeManager->GetScope(scopeId);
				DynamicBuffer::ConstIterator bufferIterator = scope.GetCodeBuffer().GetConstIterator();
					
				AssemblyReader assemblyReader;
				while (bufferIterator.HasData()) {
					Instruction instruction = assemblyReader.GetInstructionId(bufferIterator);
					if (!_ExecuteInstruction(instruction, InstructionAssemblyReader(assemblyReader, bufferIterator)))
						break;
					assemblyReader.GoNextInstruction(bufferIterator);
				}
			}

	public:
		inline RuntimeContext(
			RuntimeFixedStack * runtimeStack,
			RegisterSet * registerSet,
			RuntimeScopeManager * scopeManager,
			scoperef_t startScope
			)
			: _runtimeStack(runtimeStack), _registerSet(registerSet),
			  _scopeManager(scopeManager), _startScope(startScope)
			{
			}

		inline ~RuntimeContext(
			) {
				delete _runtimeStack;
				delete _registerSet;
				delete _scopeManager;
			}

		inline void Run(
			) {
				_ExecuteScope(_startScope);
			}
	};

	class RuntimeContextBuilder {
		RuntimeFixedStack * _runtimeStack;
		RegisterSet * _registerSet;
		RuntimeScopeManager * _scopeManager;
		scoperef_t _startScope;

	public:
		inline RuntimeContextBuilder(
			)
			: _runtimeStack(nullptr), _registerSet(nullptr),
			  _scopeManager(nullptr), _startScope(InvalidScope)
			{
			}

		inline RuntimeContextBuilder & SetRuntimeStack(
			RuntimeFixedStack * runtimeStack
			) {
				_runtimeStack = runtimeStack;
				return * this;
			}
		
		inline RuntimeContextBuilder & SetRegisterSet(
			RegisterSet * registerSet
			) {
				_registerSet = registerSet;
				return * this;
			}
		
		inline RuntimeContextBuilder & SetRuntimeScopeManager(
			RuntimeScopeManager * scopeManager
			) {
				_scopeManager = scopeManager;
				return * this;
			}
		
		inline RuntimeContextBuilder & SetStartScope(
			scoperef_t startScope
			) {
				_startScope = startScope;
				return * this;
			}

		inline RuntimeContext * Build(
			) {
				return new RuntimeContext(
					_runtimeStack, _registerSet, _scopeManager, _startScope);
			}
	};
}

#endif // !_NOVA_RUNTIME_ENVIRONMENT_RUNTIME_CONTEXT_HEADER_