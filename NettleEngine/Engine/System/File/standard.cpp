#include "standard.h"

///
///
/// File Standard - For platforms that use the standard C File I/O
/// 
/// 

namespace Nettle {
    namespace System {

        bool FileStandard::Open(tinystl::string filepath)
        {
            fp = fopen(filepath.c_str(), "rw");
            if (fp == nullptr) { recent = NOT_FOUND; }
            return fp != nullptr;
        }
        void FileStandard::Close()
        {
            fclose(fp);
        }
        size_t FileStandard::Read(void* buffer, size_t size, size_t count)
        {
            size_t bytesRead = fread(buffer, size, count, fp);
            if (bytesRead != size) {
                recent = READ_ERROR;
                if (feof(fp))
                    recent = EOF_REACHED;
            }
            return bytesRead;
        }
        size_t FileStandard::Write(const void* buffer, size_t size, size_t count)
        {
            size_t bytesWritten = fwrite(buffer, size, count, fp);
            if (bytesWritten != size) {
                recent = WRITE_ERROR;
                if (feof(fp))
                    recent = EOF_REACHED;
            }
            return bytesWritten;
        }
        char FileStandard::GetChar()
        {
            return fgetc(fp);
        }
        char FileStandard::PutChar(char put)
        {
            return fputc(put, fp);
        }
        size_t FileStandard::Tell()
        {
            return ftell(fp);
        }
        size_t FileStandard::Seek(size_t seekPos, ESeek origin)
        {
            return fseek(fp, seekPos, origin);
        }
        FileBase::Err FileStandard::Error()
        {
            return recent;
        }
    }
}