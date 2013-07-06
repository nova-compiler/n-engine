//
// assembly.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_ASSEMBLY_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_ASSEMBLY_HEADER_

#include "common\dynamic-buffer.hpp"
#include "register-set.hpp"
#include "instruction-set.hpp"

#include <cstdint>

namespace Nova {

	namespace Internal {
		namespace InstructionMemoryStructure {
			struct Base {
				Instruction Instruction;
			};

			struct Nop : Base {
			};

			struct PushI4C : Base {
				std::int32_t Value;
			};

			struct PushI4R : Base {
				Register RId;
			};

			struct SetI4R : Base {
				Register RId;
			};
			
			struct AddI4 : Base {
			};
			
			struct Call : Base {
				scoperef_t Scope;
			};
						
			struct XCall : Base {
				scoperef_t Scope;
			};
			
			struct Ret : Base {
			};
		};
	};

	class AssemblyWriter {
	public:
		inline AssemblyWriter & Nop(
			DynamicBuffer & output
			) {
				Internal::InstructionMemoryStructure::Nop s;
				s.Instruction = Instruction::nop;

				output.Push(&s, sizeof s);
				return * this;
			}

		inline AssemblyWriter & PushI4C(
			DynamicBuffer & output, std::int32_t value
			) {
				Internal::InstructionMemoryStructure::PushI4C s;
				s.Instruction = Instruction::push_i4c;
				s.Value = value;

				output.Push(&s, sizeof s);
				return * this;
			}
		
		inline AssemblyWriter & PushI4R(
			DynamicBuffer & output, Register rId
			) {
				Internal::InstructionMemoryStructure::PushI4R s;
				s.Instruction = Instruction::push_i4r;
				s.RId = rId;

				output.Push(&s, sizeof s);
				return * this;
			}
		
		inline AssemblyWriter & SetI4R(
			DynamicBuffer & output, Register rId
			) {
				Internal::InstructionMemoryStructure::SetI4R s;
				s.Instruction = Instruction::set_i4r;
				s.RId = rId;

				output.Push(&s, sizeof s);
				return * this;
			}

		inline AssemblyWriter & AddI4(
			DynamicBuffer & output
			) {
				Internal::InstructionMemoryStructure::AddI4 s;
				s.Instruction = Instruction::add_i4;

				output.Push(&s, sizeof s);
				return * this;
			}

		inline AssemblyWriter & Call(
			DynamicBuffer & output, const scoperef_t & scope
			) {
				Internal::InstructionMemoryStructure::Call s;
				s.Instruction = Instruction::call;
				s.Scope = scope;

				output.Push(&s, sizeof s);
				return * this;
			}
		
		inline AssemblyWriter & XCall(
			DynamicBuffer & output, const scoperef_t & scope
			) {
				Internal::InstructionMemoryStructure::XCall s;
				s.Instruction = Instruction::xcall;
				s.Scope = scope;

				output.Push(&s, sizeof s);
				return * this;
			}
							
		inline AssemblyWriter & Ret(
			DynamicBuffer & output
			) {
				Internal::InstructionMemoryStructure::Ret s;
				s.Instruction = Instruction::ret;

				output.Push(&s, sizeof s);
				return * this;
			}
	};

	class AssemblyReader {
		inline void _ThrowIfInvalidInstruction(
			const DynamicBuffer::ConstIterator & bufferIterator, Instruction instruction
			) const {
				if (GetInstructionId(bufferIterator) != instruction)
					throw InvalidArgumentException("The instruction is not valid for this method.");
			}

	public:
		inline void GoNextInstruction(
			DynamicBuffer::ConstIterator & buffer
			) const {
				switch (GetInstructionId(buffer)) {
				case Instruction::nop:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::Nop);
					break;
				case Instruction::push_i4c:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::PushI4C);
					break;
				case Instruction::push_i4r:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::PushI4R);
					break;
				case Instruction::add_i4:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::AddI4);
					break;
				case Instruction::set_i4r:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::SetI4R);
					break;
				case Instruction::call:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::Call);
					break;
				case Instruction::xcall:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::XCall);
					break;
				case Instruction::ret:
					buffer.Skip(sizeof Internal::InstructionMemoryStructure::Ret);
					break;
				default:
					throw RuntimeException("Unsupported instruction.");
				}
			}

		inline Instruction GetInstructionId(
			const DynamicBuffer::ConstIterator & bufferIterator
			) const {
				Internal::InstructionMemoryStructure::Base baseInstruction;
				bufferIterator.Read(&baseInstruction, sizeof baseInstruction);
				return baseInstruction.Instruction;
			}

		inline AssemblyReader & Nop(
			const DynamicBuffer::ConstIterator & bufferIterator
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::nop);

				Internal::InstructionMemoryStructure::Nop instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);

				return * this;
			}

		inline AssemblyReader & PushI4C(
			const DynamicBuffer::ConstIterator & bufferIterator, std::int32_t & value
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::push_i4c);

				Internal::InstructionMemoryStructure::PushI4C instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);
				value = instructionData.Value;

				return * this;
			}

		inline AssemblyReader & PushI4R(
			const DynamicBuffer::ConstIterator & bufferIterator, Register & rId
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::push_i4r);

				Internal::InstructionMemoryStructure::PushI4R instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);
				rId = instructionData.RId;

				return * this;
			}

		inline AssemblyReader & SetI4R(
			const DynamicBuffer::ConstIterator & bufferIterator, Register & rId
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::set_i4r);

				Internal::InstructionMemoryStructure::PushI4R instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);
				rId = instructionData.RId;

				return * this;
			}
		
		inline AssemblyReader & AddI4(
			const DynamicBuffer::ConstIterator & bufferIterator
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::add_i4);

				Internal::InstructionMemoryStructure::AddI4 instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);

				return * this;
			}
		
		inline AssemblyReader & Call(
			const DynamicBuffer::ConstIterator & bufferIterator, scoperef_t & scope
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::call);

				Internal::InstructionMemoryStructure::Call instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);
				scope = instructionData.Scope;

				return * this;
			}
			
		inline AssemblyReader & XCall(
			const DynamicBuffer::ConstIterator & bufferIterator, scoperef_t & scope
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::xcall);

				Internal::InstructionMemoryStructure::XCall instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);
				scope = instructionData.Scope;

				return * this;
			}

		inline AssemblyReader & Ret(
			const DynamicBuffer::ConstIterator & bufferIterator
			) {
				_ThrowIfInvalidInstruction(bufferIterator, Instruction::ret);

				Internal::InstructionMemoryStructure::Call instructionData;
				bufferIterator.Read(&instructionData, sizeof instructionData);

				return * this;
			}
	};

	class InstructionAssemblyReader {
		AssemblyReader & _assemblyReader;
		DynamicBuffer::ConstIterator _bufferIterator;

	public:
		inline InstructionAssemblyReader(
			AssemblyReader & assemblyReader, DynamicBuffer::ConstIterator bufferIterator
			)
			: _assemblyReader(assemblyReader), _bufferIterator(bufferIterator)
			{
			}

		inline void Nop(
			) {
				_assemblyReader.Nop(_bufferIterator);
			}

		inline void PushI4C(
			std::int32_t & value
			) {
				_assemblyReader.PushI4C(_bufferIterator, value);
			}

		inline void PushI4R(
			Register & rId
			) {
				_assemblyReader.PushI4R(_bufferIterator, rId);
			}

		inline void SetI4R(
			Register & rId
			) {
				_assemblyReader.SetI4R(_bufferIterator, rId);
			}
		
		inline void AddI4(
			) {
				_assemblyReader.AddI4(_bufferIterator);
			}
		
		inline void Call(
			scoperef_t & scope
			) {
				_assemblyReader.Call(_bufferIterator, scope);
			}
			
		inline void XCall(
			scoperef_t & scope
			) {
				_assemblyReader.XCall(_bufferIterator, scope);
			}
			
		inline void Ret(
			) {
				_assemblyReader.Ret(_bufferIterator);
			}
	};

} // namespace Nova

#endif // !_NOVA_RUNTIME_ENVIRONMENT_ASSEMBLY_HEADER_