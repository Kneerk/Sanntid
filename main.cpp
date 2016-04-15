
#include <stdio.h>
#include <thread>
#include "elev.h"
#include "OrderManager.h"
#include "Elevator.h"
#include "sendrec.h"
#include "Timer.h"
#include <iostream>

OrderManager orderManager(1);
struct code_message packet;
State current_state;
void listenForOrders(){
	while(true){
		switch(current_state){
			case MASTER:
				orderManager.listen();
				orderManager.code();
				break;
			case SLAVE:
				orderManager.decode();
				orderManager.listen();
				break;
			}
	}
}

void drive(){
	while(true){
		orderManager.manage();
	}
}

void Sender(){
	while(true){
		switch(current_state){
			case MASTER:
			udp_Broadcaster(orderManager.msg);
			usleep(500000);
			break;
			case SLAVE:
			udp_Sender("Hallo", 20023, packet.rip);
			sleep(1);
			break;
		}
	}
}

void Reciever(){
	while(true){
		switch(current_state){
			case MASTER:
			packet = udp_Reciever();
			printf("Message: %s", packet.data);
			break;
			case SLAVE:
			packet = udp_recieve_broadcast();
			break;
		}
	}
}

int main() {
	elev_init();
	udp_init(20018);
	printf("PROGRAM STARTED\n");
	/*int nBytes = 0;
	Timer timer;
	timer.start();
	current_state = MASTER;
	while(!timer.is_time_out(3)){
		nBytes = Bytes();
		if(nBytes > 0){
			current_state = SLAVE;
			packet = udp_recieve_broadcast();
		}
	}
	printf("complete");
	*/
	int input;

	printf("I AM\n");

	std::cin >> input;

	switch(input){
	case 1:
	current_state = MASTER;
	break;
	case 2:
	current_state = SLAVE;
	break;
	}


    std::thread t1(listenForOrders);
    std::thread t2(drive);
    std::thread t3(Sender);
    std::thread t4(Reciever);


    t1.join();
    t2.join();
    t3.join();
    t4.join();
}