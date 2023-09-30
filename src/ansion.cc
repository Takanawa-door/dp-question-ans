#include <chatgqt/ansion.hpp>

bool enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE),
        hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE ||
        hIn == INVALID_HANDLE_VALUE) return 0;

    DWORD in, out;
    if (!GetConsoleMode(hOut, &out) || !GetConsoleMode(hIn, &in)) return 0;

    out |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    in  &= ~ENABLE_VIRTUAL_TERMINAL_INPUT;

    if (!SetConsoleMode(hOut, out) || !SetConsoleMode(hIn, in)) return 0;

    return 1;
}
