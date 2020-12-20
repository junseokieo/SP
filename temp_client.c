#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXBUF 255

int main(){

  int ssock;
  int clen;
  struct sockaddr_in client_addr, server_addr;
  char buf[MAXBUF];

  // 소켓을 생성한다. 인터넷 도메인에서 사용, Datagram 형태로 연결
  if ((ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
    perror("socket error"); // socket 생성에 오류가 발생할 경우
    exit(1);
  }

  // 소켓에 연결하기 위한 서버 옵션 설정
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(4100);

  while(1)
  {
        fgets(buf,MAXBUF, stdin);
        //UDP 데이터를 송신한다.
        // 변환을 희망하는 온도를 단위와 함께 입력한다
        sendto(ssock, (void *)buf, MAXBUF, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

        // udp 데이터를 수신한다.
        recvfrom(ssock, (void *)buf, MAXBUF, 0, (struct sockaddr *)&client_addr, (socklen_t*)&clen);
        //server로 부터 받은 변환된 온도를 출력한다.
        printf("converted temp is : %s\n\n", buf);
  }
  return 0;
}
