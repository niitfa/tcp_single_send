#include <iostream>
#include <thread>
#include <vector>

//#include "stepper_controller_reciever.h"
//#include "stepper_controller_transmitter.h"
#include "message_transmitter_linux.h"

int number_of_args = 4;

void single_send(char* argv[])
{
	//StepperControllerReciever* receiver = new StepperControllerReciever("127.0.0.1", 6101);

	int val1 = atoi(argv[1]);
	int val2 = atoi(argv[2]);
	int val3 = atoi(argv[3]);

	std::string ip = "127.0.0.1";
	int port = 11152;
	MessageTransmitterLinux* transmitter =
		new MessageTransmitterLinux(ip, port);

	std::cout << "Connecting to " << ip << ":" << port << "... ";

	transmitter->Connect();

	std::cout << "Done!\n";

	std::cout << "Sending " << val1 << " " << val2 << " " << val3 << "... ";
	transmitter->Send(val1, val2, val3);
	std::cout << "Done!\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main(int argc, char* argv[])
{
	//std::cout << argc << std::endl;
	if (argc == number_of_args)
	{
		single_send(argv);
	}
	return 0;
	
	/* std::unique_ptr<StepperControllerReciever> receiver =
		std::make_unique<StepperControllerReciever>("169.254.206.240", 11151);
	std::unique_ptr<StepperControllerTransmitter> transmitter =
		std::make_unique<StepperControllerTransmitter>("169.254.206.240", 11152);

	transmitter->Connect();
	receiver->Connect();

	//while (true)
	{
		int id			= receiver->GetMessageID();
		int long_pos	= receiver->GetLongEncoderValue();
		int ang_pos		= receiver->GetAngEncoderValue();

		std::cout
			<< "Msg ID: "		<< id
			<< "\tLong pos: "	<< long_pos
			<< "\tAng pos: "	<< ang_pos
			<< std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	//receiver->Disconnect();



	int val1 = 0, val2 = 0, val3 = 0;
	while (1)
	{
		std::cout << "Enter command code (1 - move, 2 - stop, 3 - reset): \n> ";
		//std::cout << "Enter  values: \n>";
		std::cin >> val1;
		switch (val1)
		{
		case 1:
			std::cout << "Set position (um) and velocity (um/s):\n> ";
			std::cin >> val2;
			std::cin >> val3;
			break;
		case 2:
			val2 = 0;
			val3 = 0;
			break;
		case 3:
			val2 = 0;
			val3 = 0;
			break;
		default:
			val2 = 0;
			val3 = 0;
			break;
		}

		transmitter->Send(val1 + 16, val2, val3);

	std::cout << "Received: " << receiver->GetMessageID() << ", "
		<< receiver->GetLongEncoderValue() << ", "
		<< receiver->GetAngEncoderValue() << std::endl;
	}
	transmitter->Disconnect();

	return 0; */
}