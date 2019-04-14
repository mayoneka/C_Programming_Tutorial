#include <stdio.h> 
#include <sys/socket.h> //socket(), bind(), accept(), listen()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset()
#include <unistd.h> //close()

#define QUEUELIMIT 5 //定数. C言語では定数は大文字でやるのが通例
#define MSGSIZE 1024
#define BUFSIZE (MSGSIZE + 1)

/*
/usr/include/netinet/in.h:
   struct in_addr {
      u_int32_t s_addr;
   };

   struct sockaddr_in {
      u_char  sin_len;    （このメンバは古いOSでは存在しない）
      u_char  sin_family;  アドレスファミリ。代表的なものは AF_INET (IP/TCP,UDP)。他にも例えば、PF_APPLETALK：アップルトーク とかあった。
      u_short sin_port;    （ポート番号）
      struct  in_addr sin_addr;    （IPアドレス）
      char    sin_zero[8];    （無視してもよい．「詰め物」のようなもの）
   };
*/

int main(int argc, char* argv[]) {

    int servSock; //server socket descripter
    int clitSock; //client socket descripter
    struct sockaddr_in servSockAddr; //server internet socket address
    struct sockaddr_in clitSockAddr; //client internet socket address
    unsigned short servPort; //server port number
    unsigned int clitLen; // client internet socket address length
    char recvBuffer[BUFSIZE];//receive temporary buffer
    int recvMsgSize, sendMsgSize; // recieve and send buffer size

    // atoi は文字列を int 型に変換する (引数は文字列型で渡されるため)
    servPort = (unsigned short) atoi(argv[1]);

    // socket 関数は、OS にソケットの作成を依頼するシステムコール。
    // PF_INET は AF_INET と同じ、TCP/IP。
    // 第二引数はコネクション型(TCP : SOCK_STREAM) かコネクションレス型 (UDP : SOCK_DGRAM)を指定する 。
    // 第三引数はプロトコルを指定。0だと他の引数から自動で判別するらしいが、ここでは明示的に指定。
    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&servSockAddr, 0, sizeof(servSockAddr));
    // IP を使うので AF_INET を使用
    servSockAddr.sin_family      = AF_INET;
    // htonl() 関数は、長整数をホスト・バイト・オーダーからネットワーク・バイト・オーダーに変換する。
    // H形式 / N形式 / ビッグエンディアン / リトルエンディアン
    // 大体のCPUはリトルエンディアンらしいが、ネットワーク機器はビッグエンディアンらしい。
    // そのへんを意識せずに使えるよう、こういった関数がある
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0
    servSockAddr.sin_port        = htons(servPort); // 第一コマンドライン引数


    // bind関数で、作成したソケットと IP/Port を紐づけて行く
    // servSockAddrのポインタを渡す。これはsockaddr構造体自体は14バイトの記憶領域を使用するということが
    // 決められているだけで、Address Family の種類によって構造を変えてられるようにこうなっているらしい
    bind(servSock, (struct sockaddr *) &servSockAddr, sizeof(servSockAddr) );
    
    // listen 関数で、ようやくソケットが接続を受け入れるようになる。
    listen(servSock, QUEUELIMIT);

    while(1) {
        clitLen = sizeof(clitSockAddr);
        // 接続が来ると新しくソケットを確立し、ソケットディスクリプタを返す (clitSock)
        clitSock = accept(servSock, (struct sockaddr *) &clitSockAddr, &clitLen);
        printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));

        while(1) {
            // 確立したソケットディスクリプタをもとに、メッセージを受け取って、受けとったメッセージをそのまま返す
            recvMsgSize = recv(clitSock, recvBuffer, BUFSIZE, 0);
            printf("received : %s\n", recvMsgSize);
            sendMsgSize = send(clitSock, recvBuffer, recvMsgSize, 0);
        }

        close(clitSock);
    }

    close(servSock);

    return EXIT_SUCCESS;
}