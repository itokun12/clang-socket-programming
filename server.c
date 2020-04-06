#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  int len;
  int sock;
  /*
    ソケットの作成
    第一引数: domain, プロトコルファミリー指定 (UNIX, IP, IPV6)
    第二引数: type, 通信方式の指定
    第三引数: protocol,
      プロトコルファミリーの種類ごとに1つのプロトコルのみをサポートする場合は0を指定
    返り値: socketfd, ファイルディスクリプタ
  */
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  /* アドレスの設定 */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;

  /*
    ポート番号などをソケットに割り当てる
    第一引数: sockfd, ファイルディスクリプタ
    第二引数: addr, ソケットに割り当てるアドレス
    第三引数: addrlen, addrの指す構造体のサイズ
    返り値: 成功した場合は0, エラー時は-1
  */
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

  /*
    TCPクライアントからの接続要求を待てる状態にする
    sockfdが参照するソケットを接続待ちソケット(passive socket)として印をつける
    第一引数: sockfd, ファイルディスクリプタ
    第二引数: backlog, 保留中のキューのmax,
      maxの状態で接続要求が到着するとクライアントはエラーを受け取る
    返り値: 成功した場合は0, エラー時は-1
  */
  listen(sock0, 5);

  len = sizeof(client);
  /*
    クライアントから通信接続要求が来るまでプログラムを停止し接続後にプログラムを再開する
    第一引数: sockfd, ファイルディスクリプタ
    第二引数: addr, 接続した相手のIPアドレスやポート番号などの情報
    第三引数: addrlen, addrの指す構造体のサイズ
    返り値: 成功した場合は受け付けたソケットのファイルディスクリプタ,
    エラー時は-1
  */
  sock = accept(sock0, (struct sockaddr *)&client, &len);

  /*
    データの送信
    第一引数: fd, ファイルディスクリプタ
    第二引数: addr, 接続した相手のIPアドレスやポート番号などの情報
    第三引数: addrlen, addrの指す構造体のサイズ
    返り値: 成功した場合はsockfd, エラー時は-1
  */
  write(sock, "HELLO", 5);

  /*
    ソケットを閉じて通信接続を終了する
    クローズされたファイルティスクリプタはどのファイルからも参照されていない状態になり再利用できる
    TCPではcloseの代わりにshutdownも使える
    第一引数: fd, ファイルディスクリプタ
    返り値: 成功した場合は0, エラー時は-1
  */
  close(sock);

  /* listen するsocketの終了 */
  close(sock0);
  return 0;
}
