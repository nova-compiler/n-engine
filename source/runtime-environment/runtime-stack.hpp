//
// runtime-stack.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_RUNTIME_STACK_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_RUNTIME_STACK_HEADER_

#include <cstdint>

#include "..\common\exception.hpp"
#include "..\common\type-traits.hpp"

namespace Nova {

	INHERIT_EXCEPTION(StackException, RuntimeException)

	/// <summary>
	/// A stack managment class for the virtual execution in the engine. It provides a fixed stack
	/// space for storage.
	/// </summary>
	/// <remarks>
	/// The class doesn't track the type for inserted elements. To get a value with a different type
	/// to the one inserted can give an undefined behavior.
	/// </remarks>
	struct RuntimeFixedStack {
		/// <summary>
		/// Address for the stack buffer.
		/// </summary>
		staddr_t _stack;

		/// <summary>
		/// Current position of the buffer, new elements will be inserted at this position.
		/// </summary>
		staddr_t _stackOffset;

		/// <summary>
		/// Address for the limit of the stack.
		/// </summary>
		staddr_t _stackEnd;

		/// <summary>
		/// Utility function to validate if the type is supported by the engine.
		/// </summary>
		template <typename _Ty>
		inline void _ValidateType(
			) const {
				static_assert(EngineTypeTraits<_Ty>::Supported == true,
					"Type used is not supported by the engine");
			}

		/// <summary>
		/// Utility function to check if the specified address is inside of the buffer.
		/// </summary>
		/// <param name='address'>Address to check.</param>
		template <typename _Ty>
		inline void _ValidateAddress(
			staddr_t address
			) const {
				if (address < _stack || _stackOffset < address + EngineTypeTraits<_Ty>::Size)
					throw InvalidArgumentException("The address is invalid.");
			}

	public:
		/// <summary>
		/// Creates a new stack with the specified buffer size. This size can't be changed.
		/// </summary>
		/// <param name='stackSize'>Size of the stack.</param>
		inline RuntimeFixedStack(
			size_t stackSize
			)
			: _stack(new std::int8_t[stackSize]), _stackOffset(_stack), _stackEnd(_stack + stackSize)
			{
			}

		/// <summary>
		/// Release resources from the instance.
		/// </summary>
		inline ~RuntimeFixedStack(
			) {
				delete[] _stack;
			}

		/// <summary>
		/// Get the value stored at the specified address.
		/// </summary>
		/// <param name='address'>Address of the value.</param>
		template <typename _Ty>
		inline _Ty Get(
			staddr_t address
			) const {
				_ValidateType<_Ty>();
				_ValidateAddress<_Ty>(address);
				return * reinterpret_cast<_Ty *>(address);
			}

		/// <summary>
		/// Store the value at the specified address.
		/// </summary>
		/// <param name='address'>Address of the value.</param>
		/// <param name='value'>Value to be stored.</param>
		template <typename _Ty>
		inline void Set(
			staddr_t address, const _Ty & value
			) {
				_ValidateType<_Ty>();
				_ValidateAddress<_Ty>(address);
				* reinterpret_cast<_Ty *>(address) = value;
			}

		/// <summary>
		/// Returns current offset position of the stack.
		/// </summary>
		inline staddr_t GetCurrentAddress(
			) const {
				return _stackOffset;
			}

		/// <summary>
		/// Removes the top element from the stack and returns it.
		/// </summary>
		template <typename _Ty>
		inline _Ty Pop(
			) {
				_ValidateType<_Ty>();
				_Ty returnValue = Top<_Ty>();
				_stackOffset -= EngineTypeTraits<_Ty>::Size;
				return returnValue;
			}

		/// <summary>
		/// Pushes a new element at the top of the stack.
		/// </summary>
		template <typename _Ty>
		inline void Push(
			const _Ty & value
			) {
				_ValidateType<_Ty>();
				if (_stackEnd - _stackOffset < EngineTypeTraits<_Ty>::Size)
					throw StackException("Value can't pushed to stack. Stack remaining space too small.");
				
				staddr_t currentAddress = _stackOffset;
				_stackOffset += EngineTypeTraits<_Ty>::Size;
				Set<_Ty>(currentAddress, value);
			}

		/// <summary>
		/// Returns the top element of the stack.
		/// </summary>
		template <typename _Ty>
		inline _Ty Top(
			) const {
				_ValidateType<_Ty>();
				if (_stackOffset - _stack < EngineTypeTraits<_Ty>::Size)
					throw StackException("Value can't getted from stack. Stack size too small.");
				return Get<_Ty>(_stackOffset - EngineTypeTraits<_Ty>::Size);
			}
	};

}

#endif // !_NOVA_RUNTIME_ENVIRONMENT_RUNTIME_STACK_HEADER_