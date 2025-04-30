#include <mbedtls/mbedtls_config.h>
#include <ntifs.h>
#include <windef.h>
#include <ntstrsafe.h>
#include <ntimage.h>
#include <intrin.h>

int libmbedtls_printf(const char *format, ...)
{
    return 0;
}

int libmbedtls_snprintf(char *s, size_t n, const char *format, ...)
{
    va_list ArgList;
    int Result;

    va_start(ArgList, format);
    Result = _snprintf(s, n, format, ArgList);
    va_end(ArgList);

    return Result;
}

void* libmbedtls_calloc(size_t num, size_t size)
{
    void* Pointer;
    size_t NumberOfBytes;

    Pointer = NULL;
    NumberOfBytes = num * size;

    if (0 != NumberOfBytes) {
        Pointer = ExAllocatePoolWithTag(NonPagedPool, NumberOfBytes, 'mbed');

        if (NULL != Pointer) {
            memset(Pointer, 0, NumberOfBytes);
        }
    }

    return Pointer;
}

void libmbedtls_free(void *ptr)
{
    if (NULL != ptr) {
        ExFreePoolWithTag(ptr, 'mbed');
    }
}

int64_t mbedtls_ms_time(void)
{
    LARGE_INTEGER SystemTime = { 0 };
    KeQuerySystemTime(&SystemTime);
    return SystemTime.QuadPart / 10000;
}
