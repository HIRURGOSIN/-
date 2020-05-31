#include "Worker.h"
#include "classes.h"
using namespace std;
void Worker::send(void* client_socket)
{
	sendString(client_socket, surname);
	sendString(client_socket, name);
	sendString(client_socket, patronymic);
	sendInt(client_socket, commends);
	sendInt(client_socket, reports);
	sendInt(client_socket, hours);
	sendInt(client_socket, details);
	sendFloat(client_socket, mark);
}
void Worker::set(void* client_socket)
{
	surname = recvString(client_socket);
	name = recvString(client_socket);
	patronymic = recvString(client_socket);
	commends = recvInt(client_socket);
	reports = recvInt(client_socket);
	hours = recvInt(client_socket);
	details = recvInt(client_socket);
	mark = 0.00;
}
void Worker::fscan(fstream& workers)
{
	workers >> surname;
	workers >> name;
	workers >> patronymic;
	workers >> commends;
	workers >> reports;
	workers >> hours;
	workers >> details;
	workers >> mark;
}
void Worker::fprint(fstream& workers)
{
	workers << surname << endl;
	workers << name << endl;
	workers << patronymic << endl;
	workers << commends << endl;
	workers << reports << endl;
	workers << hours << endl;
	workers << details << endl;
	workers << mark;
}
