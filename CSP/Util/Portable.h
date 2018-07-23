#pragma once

#include <sys/sysctl.h>
#include <unistd.h>

bool IsDebuggerPresent(void);
void OutputDebugString(const char *fmt, ...);
