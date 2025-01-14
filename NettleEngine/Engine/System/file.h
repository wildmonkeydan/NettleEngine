#pragma once
#include "../types.h"



namespace Nettle {
	namespace System {
		class FileBase
		{
		public:
			enum Err {
				NOT_FOUND,
				EOF_REACHED,
				READ_ERROR,
				WRITE_ERROR
			};

			enum ESeek
			{
				Set,
				Current,
				End
			};

			virtual bool Open(tinystl::string filepath) = 0;
			virtual void Close() = 0;
			virtual size_t Read(void* buffer, size_t size, size_t count) = 0;
			virtual size_t Write(const void* buffer, size_t size, size_t count) = 0;
			virtual char GetChar() = 0;
			virtual char PutChar(char put) = 0;
			virtual size_t Tell() = 0;
			virtual size_t Seek(size_t seekPos, ESeek origin) = 0;
			virtual Err Error() = 0;
		public:
			Err recent;
		};
	}
}