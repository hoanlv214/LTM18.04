#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)
int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);
    SOCKET client = accept(listener, NULL, NULL);
    char buf[256];
    int ret = recv(client, buf, sizeof(buf), 0);
    // Xu ly buffer chua ket qua
    // Lay ra ten may tinh
    char computerName[256];
    strcpy(computerName, buf);
    printf("Computer Name: %s\n", computerName);
    int pos = strlen(computerName) + 1;
    // Lay ra danh sach o dia va kich thuoc
    int numDrivers = (ret - strlen(computerName) - 1) / 5;
    for (int i = 0; i < numDrivers; i++)
    {
        char driveLetter = buf[pos];
        pos = pos + 1;
        float driveSize;
        memcpy(&driveSize, &buf[pos], 4);
        pos = pos + 4;
        printf("%c: %.2f GB\n", driveLetter, driveSize);
    }
    system("pause");
    closesocket(client);
    closesocket(listener);
    WSACleanup();
}