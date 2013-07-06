//
// exception.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_COMMON_EXCEPTION_HEADER_
#define _NOVA_COMMON_EXCEPTION_HEADER_

#include <string>

namespace Nova {

	class Exception {
		std::string _message;

	public:
		inline Exception(
			) {
			}

		inline explicit Exception(
			const std::string & message
			)
			: _message(message)
			{
			}

		inline std::string GetMessage(
			) const {
				return _message;
			}
	};

#define INHERIT_EXCEPTION(className, baseClass) \
	class className : public baseClass { \
	public: \
		inline className() : baseClass() {} \
		inline explicit className(const std::string & message) : baseClass(message) {} \
	};

	INHERIT_EXCEPTION(RuntimeException, Exception);
	INHERIT_EXCEPTION(InvalidArgumentException, RuntimeException);
	INHERIT_EXCEPTION(NotImplementedException, Exception);

} // namespace Nova

#endif // !_NOVA_COMMON_EXCEPTION_HEADER_