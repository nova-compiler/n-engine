//
// sample-main.cpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#include <n-test\test-manager.hpp>

int main() {
	Nova::Test::GetTestManagerInstance().RunAll();
	return 0;
}