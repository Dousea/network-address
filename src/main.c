#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

struct ipaddr
{
    uint8_t addr[4];
    uint8_t m;
};

void setmaskaddr(uint8_t *buf, uint8_t m)
{
    for (int32_t i = 0; i < m; ++i)
    {
        uint8_t *byte = buf + (uint8_t)floor(i/8);
        *byte |= 128UL >> (i%8);
    }
}

uint32_t getsubnets(uint8_t m)
{
    return (uint32_t)pow(2, m-(uint8_t)(floor(m/8)*8));
}

uint32_t gethosts(uint8_t m)
{
    return (uint32_t)pow(2, 32-m);
}

void setbcaddr(uint8_t *addr, uint8_t *ip, uint8_t *mask)
{
    for (int32_t i = 0; i < 4; ++i)
        addr[i] = ip[i] | (uint8_t)~mask[i];
}

void setsubnetaddr(uint8_t *addr, uint8_t *ip, uint8_t *mask)
{
    for (int32_t i = 0; i < 4; ++i)
        addr[i] = ip[i] & mask[i];
}

int main()
{
    struct ipaddr ip;

    printf("Input: ");
    scanf("%hhu.%hhu.%hhu.%hhu/%hhu", ip.addr, ip.addr+1, ip.addr+2, ip.addr+3, &ip.m);

    uint8_t m[] = {0,0,0,0};
    setmaskaddr(m, ip.m);
    printf("Natural mask: %hhu.%hhu.%hhu.%hhu\n", m[0], m[1], m[2], m[3]);
    uint32_t subnets = getsubnets(ip.m);
    printf("Total subnets: %u (%u w/o zeros & ones)\n", subnets, subnets-2);
    uint32_t hosts = gethosts(ip.m);
    printf("Total hosts each subnet: %u (%u can be assigned)\n", hosts, hosts-2);
    uint8_t bcaddr[] = {0,0,0,0};
    setbcaddr(bcaddr, ip.addr, m);
    printf("Broadcast address: %hhu.%hhu.%hhu.%hhu\n", bcaddr[0], bcaddr[1], bcaddr[2], bcaddr[3]);
    uint8_t subnetaddr[] = {0,0,0,0};
    setsubnetaddr(subnetaddr, ip.addr, m);
    printf("Subnet address: %hhu.%hhu.%hhu.%hhu\n", subnetaddr[0], subnetaddr[1], subnetaddr[2], subnetaddr[3]);

    return EXIT_SUCCESS;
}