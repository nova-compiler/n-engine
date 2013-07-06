//
// instruction-set.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_INSTRUCTION_SET_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_INSTRUCTION_SET_HEADER_

namespace Nova {
	
	/// <summary>
	/// Lists of instructions supported by the engine.
	/// </summary>
	/// <remarks>
	/// Notation:
	/// <para>Each instruction is formed by the actual operation name, such as push, set, or add, and followed by the
	/// type it handles. First, it has the data type:</para>
	/// <list type="bullet">
	///   <item>
	///     <term>i1</term>
	///     <description>8-bits integer.</description>
	///   </item>
	///   <item>
	///     <term>i2</term>
	///     <description>16-bits integer.</description>
	///   </item>
	///   <item>
	///     <term>i4</term>
	///     <description>32-bits integer.</description>
	///   </item>
	///   <item>
	///     <term>i8</term>
	///     <description>64-bits integer.</description>
	///   </item>
	///   <item>
	///     <term>fs</term>
	///     <description>Single-precision floating point number.</description>
	///   </item>
	///   <item>
	///     <term>fd</term>
	///     <description>Double-precision floating point number.</description>
	///   </item>
	///   <item>
	///     <term>bn</term>
	///     <description>Boolean</description>
	///   </item>
	/// </list>
	/// </remarks>
	enum class Instruction {
		nop = 0,
		push_i4c,
		push_i4r,
		set_i4r,
		add_i4,
		call,
		xcall,
		ret
	};

} // namespace Nova

#endif // !_NOVA_RUNTIME_ENVIRONMENT_INSTRUCTION_SET_HEADER_