#include "classes.h"
using namespace std;
void Expert::set(string str)
{
	id = str;
}
void Expert::FillProfile(void* client_socket)
{
	char buf[100];
	recv((SOCKET)client_socket, buf, SIZE, 0);
	surname = buf;
	recv((SOCKET)client_socket, buf, SIZE, 0);
	name = buf;
	recv((SOCKET)client_socket, buf, SIZE, 0);
	patronymic = buf;
	expertise.post = recvInt(client_socket);
	expertise.grade = recvInt(client_socket);
	expertise.rank = recvInt(client_socket);
	expertise.treatise = recvInt(client_socket);
	expertiseK = expertise.post + expertise.grade + expertise.rank + expertise.treatise;
}
void Expert::SendProfile(void* client_socket)
{
	sendString(client_socket, id);
	sendString(client_socket, surname);
	sendString(client_socket, name);
	sendString(client_socket, patronymic);
	sendInt(client_socket, expertise.post);
	sendInt(client_socket, expertise.grade);
	sendInt(client_socket, expertise.rank);
	sendInt(client_socket, expertise.treatise);
	sendInt(client_socket, expertiseK);

}
void Expert::fscan(fstream& exp)
{
	exp >> surname;
	exp >> name;
	exp >> patronymic;
	exp >> expertise.post;
	exp >> expertise.grade;
	exp >> expertise.rank;
	exp >> expertise.treatise;
	exp >> expertiseK;
}
void Expert::fprint(fstream& exp)
{
	exp << surname << endl;
	exp << name << endl;
	exp << patronymic << endl;
	exp << expertise.post << endl;
	exp << expertise.grade << endl;
	exp << expertise.rank << endl;
	exp << expertise.treatise << endl;
	exp << expertiseK;
}