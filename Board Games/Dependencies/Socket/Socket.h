#pragma once

#include <iostream>
#include <WinSock2.h>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

/**
 * \brief Socket抽象基类
 */
class Socket
{
public:
	/**
	 * \brief socket是否已被创建
	 * \return 
	 */
	bool IsValid() const;

	// 纯虚函数
	virtual bool Send(const char* buffer, int len, int flags = 0) = 0;

	virtual int Receive(char* buffer, int len, int flags = 0) = 0;
protected:
	/**
	 * \brief 私有抽象类构造函数，完成WSA的初始化
	 */
	Socket();

	/**
	 * \brief 私有抽象类析构函数，完成WSA与Socket的资源释放
	 */
	virtual ~Socket();

	SOCKET sock_;
	sockaddr_in address_;
	bool is_init_; // WSA是否被成功初始化
};

/**
 * \brief 服务端Socket
 */
class ServerSocket : public Socket
{
public:
	/**
	 * \brief 构造函数，完成了服务端Socket的创建、绑定监听
	 * \param port 绑定端口号
	 */
	ServerSocket(int port = 8888);

	
	/**
	 * \brief Server中额外持有了一个Socket，需要额外进行资源释放
	 */
	~ServerSocket();
	
	/**
	 * \brief 接受客户端的连接，创建与客户端的Socket：client_sock_
	 * \return 创建是否成功
	 */
	bool Accept();

	/**
	 * \brief 获取服务端的IPV4地址
	 * \return 本机IPV4地址
	 */
	std::string GetIpAddress() const;

	/**
	 * \brief 向已连接的客户端发送数据
	 * \return 发送是否成功
	 */
	bool Send(const char* buffer, int len, int flags = 0) override;

	/**
	 * \brief 接收数据
	 * \return 接收字节数
	 */
	int Receive(char* buffer, int len, int flags = 0) override;
private:
	SOCKET client_sock_;
};

/**
 * \brief 客户端Socket
 */
class ClientSocket : public Socket
{
public:
	ClientSocket();

	/**
	 * \brief 创建Socket并尝试连接服务端
	 * \param ip 服务端IP
	 * \param port 端口号
	 * \return 连接是否成功
	 */
	bool Connect(const std::string& ip, int port = 8888);

	/**
	 * \brief 向已连接的服务端发送数据
	 * \return 发送是否成功
	 */
	bool Send(const char* buffer, int len, int flags = 0) override;
	/**
	 * \brief 接收数据
	 * \return 接收字节数
	 */
	int Receive(char* buffer, int len, int flags = 0) override;
};