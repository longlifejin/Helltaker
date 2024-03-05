#include "pch.h"

int main()
{
    FRAMEWORK.Init(1920, 1080, "Helltaker");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}