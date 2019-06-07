/*
 * filecopy.cpp
 *
 *  Created on: 2019年3月9日
 *      Author: liu
 */
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
using namespace std;

int main()
{
	string filename,outfilename;
	// 输入源文件路径名和文件名 e.g. /home/test.txt
	cout<<"please input the source file path and file name"<<endl;
	cin>>filename;
	//打开源文件，如出现错误则退出
    int filein = open(filename.c_str(), O_RDONLY);
    if(filein==-1)
    {
    	cout<<"failed to open the source file"<<endl;
    	return -1;
    }
    //输入目标文件路径和文件名 e.g. /home/test_copy.txt
    cout<<"please input the target file path and file name"<<endl;
	cin>>outfilename;
	//打开目标文件，如出现错误则退出
    int fileout = open(outfilename.c_str(), O_WRONLY|O_CREAT,S_IRWXU);
    if(filein==-1)
        {
        	cout<<"failed to open the source file"<<endl;
        	return -1;
        }
    //从源文件读取并写入目标文件
    char context[1024] = {'\0'};
    int len = 0;
    //设置flag，当成功读写，置为true
    bool flag=false;
    while((len = read(filein, context, sizeof(context))) > 0)
    {
	if(write(fileout,context, len)>0)
		flag=true;
    }
    //关闭两个文件
    close(filein);
    close(fileout);
    //成功读写，输出操作成功
    if(flag)
    	{
    	cout<<"file copied successfully"<<endl;
    	return 0;
    	}
    //否则输出copy操作失败
    else
    {
    	cout<<"failed to copy this file"<<endl;
    	return -1;
    }
}



