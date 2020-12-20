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
  char temp[2] = "C"; // 온도의 단위가 C인지 F인지 구별하기 위한 기준 문자 설정

  struct sockaddr_in client_addr, server_addr;
  char buf[MAXBUF];
  char *buffer[10] = { NULL, }; // buffer 초기화

  // 소켓을 생성한다.
  if ((ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){ //인터넷 도메인에서 사용, Datagram 형태로 연결
    perror("socket error"); // socket 생성에 오류가 발생할 경우
    exit(1);
  }
  // 소켓에 연결하기 위한 서버 옵션 설정
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(4100);

  // ip주소와 port번호를 socket과 묶는다.
  if (bind(ssock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
    perror("bind error: ");
    exit(1);
  }

  while(1){
        // udp 데이터를 수신한다.
        recvfrom(ssock, (void *)buf, MAXBUF, 0, (struct sockaddr *)&client_addr, (socklen_t *)&clen);
        printf("-----client에게 받은 온도는 : %s", buf); // client로 부터 받은 온도를 출력

        /* buf로 받은 문자열을 띄어쓰기로 나눴을 때
        두번째 문자열(섭씨 혹은 화씨를 의미)를 구분해서 buffer에 저장 */
        char *ptr = strtok(buf, " ");
        int count=0;
        while(ptr != NULL){
             buffer[count] = ptr;
             count++;
             ptr = strtok(NULL, " ");
        }
        // 전송받은 내용의 숫자 부분을 int형으로 변환해 저장
        int num1 = atoi(buffer[0]);
        char retemp[10]; // 단위를 변환시킨 온도 내용을 저장할 문자열 배열

        //섭씨일 때 화씨일때 temp와 비교하여 각각 다른 결과를 도출한다.
        // 만약 섭씨로 받은 경우
        if ( strcmp(buffer[1],temp) == 10){
             printf("temp 단위는 C !\n");
             num1 = ((num1*9)/5)+32; //섭씨 값을 화씨 값으로 계산해서 num1에 저장
             printf("converted temp : %d", num1);
             printf(" F\n\n");
             sprintf(retemp, "%d", num1); // 계산한 num1값을 문자로 바꿔서 retemp로 저장
             strcat(retemp," F"); // retemp에 있는 변환된 온도와 단위를 합친다.

        // 만약 화씨로 받은 경우
        }else if (strcmp(buffer[1],temp) == 3){
             printf("temp 단위는 F !\n");
             num1 = ((num1-32)*5)/9; // 화씨 값을 섭씨 값으로 계산해서 num1에 저장
             printf("converted temp : %d", num1);
             printf(" C\n\n");
             sprintf(retemp, "%d", num1); // 계산한 num1값을 문자로 바꿔서 retemp로 저장
             strcat(retemp," C"); // retemp에 있는 변환된 온도와 단위를 합친다.
        }

      //UDP 데이터를 송신한다.
      sendto(ssock, (void *)retemp, MAXBUF, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
}
      return 0;
}
