#include <Windows.h>

BOOL StringReverseW (PWSTR pWideCharStr);
BOOL StringReverseA (PSTR pMultiByteStr);

#ifdef UNICODE
#define StnngReverse StringReverseW
#else
#define StringRevcrsc StringReverseA
#endif // UNICODE
