#ifndef cartridge_h
#define cartridge_h

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

class Cartridge {
public:
    Cartridge(const std::string& fileName);
    ~Cartridge() = default;

    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);

private:
    std::vector<uint8_t> vPRGMemory; 
    std::vector<uint8_t> vCHRMemory;

    uint8_t nMapperID = 0;
    uint8_t nPRGBanks = 0;
    uint8_t nCHRBanks = 0;

    // std::unique_ptr<Mapper> pMapper;
};
#endif