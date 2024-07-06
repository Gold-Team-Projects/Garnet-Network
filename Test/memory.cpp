#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef unsigned char byte;

#pragma pack(1)
struct test {
    uint8_t a, b, c;
} __attribute__((packed));

template <typename T>
void to_bytes(const T& value, byte* buffer)
{
    memcpy(buffer, &value, sizeof(T));
}
template <typename T>
T from_bytes(byte* buffer)
{
    T output;
    memcpy(&output, buffer, sizeof(T));
    return output;
}
void print_bytes(byte* buffer, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        printf("%02X ", static_cast<byte>(buffer[i]));
    }
    printf("\n");
}

int main()
{
    char a, b, c;

    a = 'a'; // 61
    b = 'b'; // 62
    c = 'c'; // 63

    printf("a, b, and c as hexes: %02x %02x %02x\n", a, b, c);

    char* ptr;
    char ar[3] = { a, b, c };
    ptr = ar;

    printf("pointer/array test: %c %c %c\n", ptr[0], ptr[1], ptr[2]);

    byte buffer1[3];
    uint8_t buffer2[3];
    test t;
    t.a = 61;
    t.b = 62;
    t.c = 63;

    buffer1[0] = (byte)t.a;
    buffer1[1] = (byte)t.b;
    buffer1[2] = (byte)t.c;

    buffer2[0] = (uint8_t)buffer1[0];
    buffer2[1] = (uint8_t)buffer1[1];
    buffer2[2] = (uint8_t)buffer1[2];

    printf("conversion (as bytes): %c %c %c\n", buffer1[0], buffer1[1], buffer1[2]);
    printf("conversion (as numbers): %d %d %d\n", buffer2[0], buffer2[1], buffer2[2]);
    printf("addresses: %hhn %hhn %hhn\n", &t.a, &t.b, &t.c);
    printf("sizeof(t): %li\n", sizeof(t));

    byte* buffer3;
    test t2;
    t2.a = 89;
    t2.b = 87;
    t2.c = 88;
    to_bytes<test>(t2, buffer3);
    print_bytes(buffer3, sizeof(test));

    printf("buffer3: %i %i %i\n", buffer3[0], buffer3[1], buffer3[2]);

    test t3 = from_bytes<test>(buffer3);
    printf("t3: %i %i %i\n", t3.a, t3.b, t3.c);
}