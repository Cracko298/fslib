#include "FsLib.hpp"
#include <array>
#include <cstdarg>
#include <switch.h>
#include <vector>

static constexpr unsigned int VA_BUFFER_SIZE = 0x1000;

// Feels stupid but needed to get actual output in real time
void Print(const char *Format, ...)
{
    std::va_list VaList;
    std::array<char, VA_BUFFER_SIZE> VaBuffer;
    va_start(VaList, Format);
    vsnprintf(VaBuffer.data(), VA_BUFFER_SIZE, Format, VaList);
    va_end(VaList);
    std::printf(VaBuffer.data());
    consoleUpdate(NULL);
}

int main(void)
{
    consoleInit(NULL);

    PadState GamePad;
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    padInitializeDefault(&GamePad);

    FsLib::Initialize();

    // Just testing this to make sure I got it right this time.
    FsLib::OutputFile JKSVLog("sdmc:/switch/JKSV_log.txt", true);
    JKSVLog.Writef("Debug message here to test appending.");

    Print("Press + to exit.");

    while (true)
    {
        padUpdate(&GamePad);
        if (padGetButtonsDown(&GamePad) & HidNpadButton_Plus)
        {
            break;
        }
        consoleUpdate(NULL);
    }
    FsLib::Exit();
    consoleExit(NULL);
    return 0;
}
