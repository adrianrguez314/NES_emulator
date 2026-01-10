#include "cartridge.h"
#include <fstream>
#include <iostream>

Cartridge::Cartridge (const std::string& fileName) {
    struct Header {
            char name[4];
            uint8_t prg_rom_chunks;
            uint8_t chr_rom_chunks;
            uint8_t mapper1;
            uint8_t mapper2;
            uint8_t prg_ram_size;
            uint8_t tv_system1;
            uint8_t tv_system2;
            char unused[5];
    } header;

    std::ifstream ifs(fileName, std::ifstream::binary);
    if (ifs.is_open()) {
        ifs.read((char*)&header, sizeof(Header));

        nPRGBanks = header.prg_rom_chunks;
        PRGMemory.resize(nPRGBanks * 16384);
        
        nCHRBanks = header.chr_rom_chunks;
        CHRMemory.resize(nCHRBanks * 8192);

        mapper = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);

        if (header.mapper1 & 0x04) ifs.seekg(512, std::ios_base::cur); 

        ifs.read((char*)PRGMemory.data(), PRGMemory.size());
        ifs.read((char*)CHRMemory.data(), CHRMemory.size());


        if (mapper == 0) {
            pMapper = std::make_unique<Mapper_000>(nPRGBanks, nCHRBanks);
        }
        bImageValid = true;
        ifs.close();
    }
    else {
        bImageValid = false;
    }
}
bool Cartridge::cpuRead(uint16_t addr, uint8_t &data) {
    uint32_t mapped_addr = 0;

    if (pMapper->cpuMapRead(addr, mapped_addr)) {
        data = PRGMemory[mapped_addr];
        return 1;
    }
    return 0;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data) {
    uint32_t mapped_addr = 0;

    if(pMapper->cpuMapWrite(addr,mapped_addr)) {
        PRGMemory[mapped_addr] = data;
    }
    return 0;
}