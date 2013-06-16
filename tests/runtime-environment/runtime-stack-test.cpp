//
// runtime-stack-test.cpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#include "runtime-environment\runtime-stack.hpp"

#include <n-test\test-unit.hpp>

#include <cstdint>

using namespace Nova;
using namespace std;

TEST_UNIT("runtime-environment\\runtime-stack")
	TEST_METHOD("basic", testContext) {
		RuntimeFixedStack stack(20);
		
		stack.Push(int32_t(42));
		testContext.Accept(stack.Pop<int32_t>() == 42);

		stack.Push(int32_t(10));
		stack.Push(int32_t(60));
		testContext.Accept(stack.Pop<int32_t>() == 60);
		testContext.Accept(stack.Pop<int32_t>() == 10);
	}

	TEST_METHOD("references", testContext) {
		RuntimeFixedStack stack(20);
		
		stack.Push(int32_t(10));
		StackAddress address = stack.GetCurrentAddress();
		stack.Push(int32_t(60));
		stack.Push(int32_t(50));

		testContext.Accept(stack.Get<int32_t>(address) == 60);
		stack.Set<int32_t>(address, 30);

		testContext.Accept(stack.Pop<int32_t>() == 50);
		testContext.Accept(stack.Pop<int32_t>() == 30);
		testContext.Accept(stack.Pop<int32_t>() == 10);
	}

	TEST_METHOD("limits", testContext) {
		RuntimeFixedStack stack(8);
		
		try {
			stack.Pop<int32_t>();
			testContext.Fail();
		} catch (const StackException &) {
			testContext.Accept();
		}

		stack.Push(int32_t(5));

		StackAddress address = stack.GetCurrentAddress();
		try {
			stack.Get<int32_t>(address);
			testContext.Fail();
		} catch (const InvalidArgumentException &) {
			testContext.Accept();
		}

		stack.Push(int32_t(10));

		try {
			stack.Push(int32_t(30));
			testContext.Fail();
		} catch (const StackException &) {
			testContext.Accept();
		}

	}
END_TEST_UNIT
