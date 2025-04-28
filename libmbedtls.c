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
    Pointer = ExAllocatePoolWithTag(NonPagedPool, num * size, 'mbed');
    return Pointer;
}

void libmbedtls_free(void *ptr)
{
    ExFreePoolWithTag(ptr, 'mbed');
}

int64_t mbedtls_ms_time(void)
{
    LARGE_INTEGER SystemTime = { 0 };
    KeQuerySystemTime(&SystemTime);
    return SystemTime.QuadPart / 10000;
}
