#pragma once
#include "../types.h"

#ifdef PLATFORM_DESKTOP
#include <stdio.h>
#endif


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

#ifdef PLATFORM_DESKTOP
		class FileStandard : public FileBase {
		public:
			bool Open(tinystl::string filepath) override;
			void Close() override;
			size_t Read(void* buffer, size_t size, size_t count) override;
			size_t Write(const void* buffer, size_t size, size_t count) override;
			char GetChar() override;
			char PutChar(char put) override;
			size_t Tell() override;
			size_t Seek(size_t seekPos, ESeek origin) override;
			Err Error() override;
		private:
			FILE* fp = nullptr;
		};
#endif
	}
}