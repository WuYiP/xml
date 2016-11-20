                      安装libxml2库
Libxml2是个C语言的XML程式库，能简单方便的提供对XML文件的各种操作，
并且支持XPATH查询，及部分的支持XSLT转换等功能。
Libxml2的下载地址是http://xmlsoft.org/，完全版的库是开源的，并且带有例子程式和说明文件。最佳将这个库先下载下来，因为这样能查看其中的文件和例子。
由于我是在linux下用C语言进行研发的，所以我下载的是libxml2-2.6.20.tar.gz版本的源码包。
具体安装步骤：
   解压：$tar zxvf libxml2-2.6.20.tar.gz
   进入解压后的安装目录：$cd libxml2-2.6.20
   安装三部曲：1 ）$./configure 
               2 )  $make
               3 )  $make install
安装完毕。
例：
创建test.c文件
gcc -I /usr/local/include/libxml2  -L /usr/local/lib -lxml2 test.c -o test可以命令编译通过
