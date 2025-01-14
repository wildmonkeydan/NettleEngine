#pragma once
#include "../file.h"
#include <stdio.h>

namespace Nettle {
	namespace System {
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
	}
}