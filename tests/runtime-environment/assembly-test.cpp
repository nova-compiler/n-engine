//
// assembly-test.cpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#include "runtime-environment\assembly.hpp"

#include <n-test\test-unit.hpp>

using namespace Nova;
using namespace std;

TEST_UNIT("runtime-environment\\assembly")

	static bool CompareBuffer(
		const DynamicBuffer & buffer, void * ptr, size_t size
		) {
			if (buffer.GetSize() != size) return false;
			return memcmp(buffer.GetPointer(), ptr, size) == 0; 
		}

	TEST_METHOD("basic", testContext) {
		DynamicBuffer buffer;

		AssemblyWriter writer;
		writer.AddI4(buffer);

		Internal::InstructionMemoryStructure::AddI4 stub;
		stub.Instruction = Instruction::add_i4;

		testContext.Accept(CompareBuffer(buffer, &stub, sizeof stub));
	}

END_TEST_UNIT
