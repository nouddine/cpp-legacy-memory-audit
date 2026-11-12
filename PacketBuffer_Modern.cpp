#ifdef __BORLANDC__
#include <vcl.h>
#pragma hdrstop
#endif

#include <iostream>
#include <string>

// Compatibilité ascendante : permet de compiler aussi bien sur C++98 (C++Builder classique) que sur C++11/17/20
#if __cplusplus < 201103L
#define nullptr 0
#endif

class PacketBuffer {
private:
    std::string data;

public:
    explicit PacketBuffer(const char* input = "")
        : data(input ? input : "") {
    }

    void append(const char* extra) {
        if (extra != nullptr) {
            data += extra;
        }
    }

    const char* getData() const {
        return data.c_str();
    }

    size_t getSize() const {
        return data.size();
    }
};

void processPackets() {
    PacketBuffer p1("Header:");
    PacketBuffer p2 = p1;
    p1.append("Payload_Data_12345");

    PacketBuffer p3(nullptr);
    p3.append(nullptr);
    p3.append("Safe_Packet");

    std::cout << "P1: " << p1.getData() << std::endl;
    std::cout << "P2: " << p2.getData() << std::endl;
    std::cout << "P3: " << p3.getData() << std::endl;
}

int main() {
    processPackets();
    return 0;
}
