//
// runtime-context-test.cpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#include "runtime-environment\runtime-context.hpp"

#include <n-test\test-unit.hpp>

#include <cstdint>
#include <iostream>

using namespace Nova;
using namespace std;

TEST_UNIT("runtime-environment\\runtime-context")
	TEST_METHOD("basic", testContext) {
		DynamicBuffer codeBuffer;

		vector<int> values;

		RuntimeScopeManager * runtimeScopeManager = new RuntimeScopeManager();
		RuntimeScope & scope = runtimeScopeManager->CreateNewScope();
		ExternalScope & printScope = runtimeScopeManager->CreateExternalScope();
		printScope.SetCallbackFunction(
			[&values] (RuntimeFixedStack & stack) {
				values.push_back(stack.Pop<std::int32_t>());
			});

		AssemblyWriter()
			.PushI4C(codeBuffer, int32_t(4))
			.PushI4C(codeBuffer, int32_t(2))
			.AddI4(codeBuffer)
			.XCall(codeBuffer, printScope.GetId());
		scope.SetCodeBuffer(move(codeBuffer));

		RuntimeContext * runtimeContext = RuntimeContextBuilder()
			.SetRegisterSet(new RegisterSet())
			.SetRuntimeStack(new RuntimeFixedStack(40))
			.SetRuntimeScopeManager(runtimeScopeManager)
			.SetStartScope(scope.GetId())
			.Build();

		runtimeContext->Run();

		testContext.Accept(values.size() == 1 && values[0] == 6);

		delete runtimeContext;
	}
END_TEST_UNIT
