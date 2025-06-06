#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char a, b, c, d;
} IPAddress;

int isPrivateIP(const IPAddress *ip) {
    if (ip->a == 10) return 1;
    if (ip->a == 172 && (ip->b >= 16 && ip->b <= 31)) return 1;
    if (ip->a == 192 && ip->b == 168) return 1;
    return 0;
}

int isReservedIP(const IPAddress *ip) {
    if (ip->a == 0) return 1;
    if (ip->a == 169 && ip->b == 254) return 1;
    return 0;
}

int main() {
    char ip_string[20];
    IPAddress ip;
    printf("Enter an IP address (IPv4): ");
    scanf("%19s", ip_string);
    
    // Parse IP address
    if (sscanf(ip_string, "%hhu.%hhu.%hhu.%hhu", &ip.a, &ip.b, &ip.c, &ip.d) != 4) {
        printf("Invalid IP address format.\n");
        return 1;
    }

    // Determine IP class
    char ip_class;
    if (ip.a >= 1 && ip.a <= 126) {
        ip_class = 'A';
    } else if (ip.a >= 128 && ip.a <= 191) {
        ip_class = 'B';
    } else if (ip.a >= 192 && ip.a <= 223) {
        ip_class = 'C';
    } else if (ip.a >= 224 && ip.a <= 239) {
        ip_class = 'D';
    } else if (ip.a >= 240 && ip.a <= 255) {
        ip_class = 'E';
    } else {
        printf("Invalid IP address.\n");
        return 1;
    }

    // Determine the type (Private, Reserved, or Public)
    if (isPrivateIP(&ip)) {
        printf("IP Class: %c\nType: Private\n", ip_class);
    } else if (isReservedIP(&ip)) {
        printf("IP Class: %c\nType: Reserved\n", ip_class);
    } else {
        printf("IP Class: %c\nType: Public\n", ip_class);
    }

    return 0;
}
