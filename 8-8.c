
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main()
{
    int sock;
    struct sockaddr_in server;
    int n;
    char buf[65536];

    /* ソケットの作成 */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);

    /*"127.0.0.1"の部分は必要に応じて変更*/
    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr.s_addr);

    /*サーバに接続*/
    n = connect(sock,(struct sockaddr *)&server,sizeof(server));

    if(n != 0){
        perror("connect");
        return 1;
    }
    /*無限に送信を続けている*/
    /*
    最初はwrite()を行うことを伝えるprintf()が連続的に表示されるが、そのうち新しくprintf()が行われない状態になる
    そのあと、受信側で２秒間のsleep()が終了してread()されるたびに、少しだけwrite()が行われるという状態になる
    */
    while (1){
        printf("write %ld bytes\n",sizeof(buf));
        n = write(sock,buf,sizeof(buf));
        if(n <= 0){
            printf("write error: %d\n",n);
            break;
        }
        
    }
    
    /* sockの終了 */
    close(sock);

    return 0;
}