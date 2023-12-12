#include "FlashConfig.h"


void FlashConfig::saveData(){
    uint8_t data[FLASH_SECTOR_SIZE];
    
    uint marker = writeData(data, ssid, 0);
    marker = writeData(data, pass, marker);

    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, data, FLASH_PAGE_SIZE);
    restore_interrupts(interrupts);
}

void FlashConfig::loadData(){
    char *data = (char*) (XIP_BASE + FLASH_TARGET_OFFSET);
    
    uint8_t size = data[0];
    uint32_t index = 1;
    ssid.configSize = size;
    ssid.config = &data[index];
    index = index + size;
    pass.configSize = data[index];
    pass.config = &data[++index];

}


//[MEMO] data structure [1byte of data size][data...][1byte of data size][data...]...
uint FlashConfig::writeData(uint8_t* data, Config config, uint startIdx){
    
    data[startIdx] = config.configSize;
    startIdx += 1;
    for(int idx = 0; idx < config.configSize; idx ++)
    {
        data[startIdx + idx] = config.config[idx];
    }
    return startIdx + config.configSize;
}