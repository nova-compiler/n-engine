//
// dynamic-buffer.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_COMMON_DYNAMIC_BUFFER_HEADER_
#define _NOVA_COMMON_DYNAMIC_BUFFER_HEADER_

#include "exception.hpp"

#include <vector>
#include <cstdint>

namespace Nova {

	namespace Internal {
		class DynamicBufferConstIterator;
	}
	
	class DynamicBuffer {
		std::vector<std::int8_t> _data;

	public:
		typedef Internal::DynamicBufferConstIterator ConstIterator;

		inline DynamicBuffer(
			) {
			}

		inline DynamicBuffer(
			const DynamicBuffer & other
			)
			: _data(other._data)
			{
			}

		inline DynamicBuffer(
			DynamicBuffer && other
			)
			: _data(other._data)
			{
			}

		inline DynamicBuffer & operator = (
			const DynamicBuffer & other
			) {
				_data = other._data;
				return * this;
			}

		inline DynamicBuffer & operator = (
			DynamicBuffer && other
			) {
				_data = other._data;
				return * this;
			}

		inline DynamicBuffer & Push(
			const void * ptr, size_t size
			) {
				const std::int8_t * bufferPtr = reinterpret_cast<const std::int8_t *>(ptr);
				_data.insert(_data.end(), bufferPtr, bufferPtr + size);
				return * this;
			}

		inline const void * GetPointer(
			) const {
				return &_data[0];
			}
		
		inline const void * Read(
			void * outputBuffer, size_t offset, size_t size
			) const {
				if (offset + size > GetSize())
					throw RuntimeException("Not enough space to read.");
				return memcpy(outputBuffer, &_data[offset], size);
			}

		inline size_t GetSize(
			) const {
				return _data.size();
			}

		inline ConstIterator GetConstIterator(
			) const;
	};
	
	namespace Internal {
		class DynamicBufferConstIterator {
			const DynamicBuffer & _source;
			size_t _offset;

		public:
			inline explicit DynamicBufferConstIterator(
				const DynamicBuffer & source
				)
				: _source(source), _offset(0)
				{
				}

			inline DynamicBufferConstIterator(
				const DynamicBufferConstIterator & other
				)
				: _source(other._source), _offset(other._offset)
				{
				}

			inline void Read(
				void * outputBuffer, size_t size
				) const {
					_source.Read(outputBuffer, _offset, size);
				}
			
			inline void Skip(
				size_t size
				) {
					_offset += size;
				}

			inline bool HasData(
				) const {
					return _offset < _source.GetSize();
				}
		};
	}

	inline DynamicBuffer::ConstIterator DynamicBuffer::GetConstIterator(
		) const {
			return DynamicBuffer::ConstIterator(* this);
		}

} // namespace Nova

#endif // !_NOVA_COMMON_DYNAMIC_BUFFER_HEADER_