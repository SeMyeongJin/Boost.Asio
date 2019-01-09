// boostAsio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

int main()
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER);
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
	boost::asio::ip::tcp::socket socket(io_service);
	acceptor.accept(socket);
	cout << "Ŭ���̾�Ʈ ����" << endl;

	for (;;)
	{
		array<char, 128> buf;
		buf.assign(0);
		boost::system::error_code error;
		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if (error)
		{
			if (error == boost::asio::error::eof)
			{
				cout << "Ŭ���̾�Ʈ���� ������ ���������ϴ�." << endl;
			}
			else
			{
				cout << "error No: " << error.value() << ", message : " << error.message() << endl;
			}
			break;
		}
		cout << "���� �޼���: " << &buf[0] << endl;
		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128 - 1, "Re:%s", &buf[0]);
		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		boost::system::error_code ignored_error;
		socket.write_some(boost::asio::buffer(szMessage, nMsgLen), ignored_error);
		cout << "Ŭ���̾�Ʈ�� ���� �޽���: " << szMessage << endl;
	}
	
	getchar();

    return 0;
}

