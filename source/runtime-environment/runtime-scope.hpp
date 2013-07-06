//
// runtime-scope.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_RUNTIME_ENVIRONMENT_RUNTIME_SCOPE_HEADER_
#define _NOVA_RUNTIME_ENVIRONMENT_RUNTIME_SCOPE_HEADER_

#include "common\type-traits.hpp"
#include "common\dynamic-buffer.hpp"

#include <vector>
#include <functional>

namespace Nova {

	class RuntimeScope {
		DynamicBuffer _codeBuffer;
		scoperef_t _id;

	public:
		inline RuntimeScope(
			scoperef_t id
			)
			: _id(id)
			{
			}

		inline scoperef_t GetId(
			) const {
				return _id;
			}

		inline void SetCodeBuffer(
			const DynamicBuffer & buffer
			) {
				_codeBuffer = buffer;
			}
		
		inline void SetCodeBuffer(
			DynamicBuffer && buffer
			) {
				_codeBuffer = buffer;
			}
		
		inline const DynamicBuffer & GetCodeBuffer(
			) const {
				return _codeBuffer;
			}
	};

	class RuntimeFixedStack;

	class ExternalScope {
		std::function<void (RuntimeFixedStack &)> _callbackFunction;
		scoperef_t _id;

	public:
		inline ExternalScope(
			scoperef_t id
			)
			: _id(id)
			{
			}

		inline scoperef_t GetId(
			) const {
				return _id;
			}

		inline void SetCallbackFunction(
			const std::function<void (RuntimeFixedStack &)> & callback
			) {
				_callbackFunction = callback;
			}
		
		inline std::function<void (RuntimeFixedStack &)> GetCallbackFunction(
			) const {
				return _callbackFunction;
			}
	};

	class RuntimeScopeManager {
		std::vector<RuntimeScope *> _scopes;
		std::vector<ExternalScope *> _externalScopes;

	public:
		inline RuntimeScopeManager(
			) {
			}

		inline ~RuntimeScopeManager(
			) {
				for (auto item : _scopes) delete item;
			}

		inline RuntimeScope & CreateNewScope(
			) {
				RuntimeScope * scope = new RuntimeScope(reinterpret_cast<scoperef_t>(_scopes.size()));
				_scopes.push_back(scope);
				return * scope;
			}
		
		inline ExternalScope & CreateExternalScope(
			) {
				ExternalScope * scope = new ExternalScope(reinterpret_cast<scoperef_t>(_externalScopes.size()));
				_externalScopes.push_back(scope);
				return * scope;
			}

		inline RuntimeScope & GetScope(
			scoperef_t scope
			) {
				return * _scopes[reinterpret_cast<size_t>(scope)];
			}
		
		inline const RuntimeScope & GetScope(
			scoperef_t scope
			) const {
				return * _scopes[reinterpret_cast<size_t>(scope)];
			}
		
		inline ExternalScope & GetExternalScope(
			scoperef_t scope
			) {
				return * _externalScopes[reinterpret_cast<size_t>(scope)];
			}
		
		inline const ExternalScope & GetExternalScope(
			scoperef_t scope
			) const {
				return * _externalScopes[reinterpret_cast<size_t>(scope)];
			}
	};

} // namespace Nova

#endif // !_NOVA_RUNTIME_ENVIRONMENT_INSTRUCTION_SET_HEADER_