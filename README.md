# Clang Socket Programming

C言語でTCPソケットを実装

## フロー
![](https://www.ibm.com/support/knowledgecenter/ja/ssw_ibm_i_71/rzab6/rxab6502.gif)

## Memo
listenするためのsocket(fd)と データ読み書き用のsocket(fd)は別, accpetする度にデータ読み書き用のfdが生成される

## 参考
- http://www.geekpage.jp/programming/linux-network/
- https://www.ibm.com/support/knowledgecenter/ja/ssw_ibm_i_71/rzab6/rzab6soxoverview.htm
- https://www.ibm.com/support/knowledgecenter/ja/ssw_ibm_i_71/rzab6/connectionor.htm
