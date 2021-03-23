#pragma once

#include <Windows.h>

#include <vector>
#include <array>
#include <string>

class CaraCrypt {
private:
    std::array<DWORD, 3> LFSR;
    std::array<DWORD, 3> MASK;
    std::array<DWORD, 3> ROTA;
    std::array<DWORD, 3> ROTB;
    std::array<BYTE, 5> RNDA;

    void InitCara(void);
    void TransformKey(const std::string);
    void TransformChar(BYTE&);

public:
    CaraCrypt()
        : LFSR{ 0, 0, 0 }, MASK{ 0, 0, 0 }, ROTA{ 0, 0, 0 }, ROTB{ 0, 0, 0 }, RNDA{ 0, 0, 0, 0, 0 }
    {
    }
    ~CaraCrypt() { }

    void TransformBytes(std::vector<BYTE>&, const std::string);
};