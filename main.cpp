#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

string get_data(tcp::socket& socket){
    boost::asio::streambuf buf;
    read_until(socket,buf,"\n");
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void send_data(tcp::socket& socket, const string& message){
    write(socket, buffer(message + "\n"));
}

int main() {

    io_service service;
    tcp::socket  client_socket(service);

    client_socket.connect(tcp::endpoint(address::from_string("127.0.0.1"),9999));

    cout << "Enter username: ";
    string u_name, replay, response;
    getline(cin, u_name);

    send_data(client_socket,u_name);

    while (true){

        response = get_data(client_socket);

        response.pop_back();

        if(response == "exit"){
            cout << "Connection terminated \n";
            break;
        }

        cout << "Server: " << response << "\n";

        cout << u_name << ": ";
        getline(cin,replay);
        send_data(client_socket,replay);

        if(replay == "exit"){
            break;
        }
    }

    return 0;
}
