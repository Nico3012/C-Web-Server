#include <stdint.h>
#include <stdio.h>

uint16_t my_htons(uint16_t hostshort) {
    // Check the endianness of the system
    uint16_t test = 1;
    uint8_t *test_ptr = (uint8_t *)&test;
    
    // If the system is little-endian
    if (test_ptr[0] == 1) {
        return (hostshort << 8) | (hostshort >> 8);
    } else {
        // If the system is big-endian, no need to swap bytes
        return hostshort;
    }
}

int main() {
    uint16_t hostshort = 8080;
    uint16_t networkshort = my_htons(hostshort);

    printf("Network short: 0x%x\n", networkshort);

    return 0;
}
