#include "Game.h"
#include "GameObject.h"
#include "state1.h"
#include "state2.h"
#include <thread>
#include "ClientSocket.h"
#include "SDL_net.h"
#include "state0.h"
#include "vector"
#include "fstream"

// Create a pointer to a ServerSocket object
ClientSocket *cs;

//user input string
string userInput = "";

//username of player
string username = "";

//looping through server sends
int counterState2 = 0;

//string array for passed in stuff
 vector<string> serverInfo;

//to login to server (and add username to server list of usernames
bool login = false;

//how signups are left on this computer
int loginsLeft = 0;

//bool for if signup file has been tampered with
bool signupTampered = false;

void updateConnection() {

		// Run the main loop...
		if ((cs->getShutdownStatus() == false))
		{
			string receivedMessage = "";
			// Check if we've received a message
			receivedMessage = cs->checkForIncomingMessages();

			// If so then...
			if (receivedMessage != "")
			{
				userInput = receivedMessage;

			}

			// Get and deal with input from the user in a non-blocking manner
			//cs->getUserInput("hello");

			// ... until we decide to quit or the server is shut down
		}

}

using namespace std;

int main(int argc, char * argv[]) {

	////// getting amout of sign ups left ////////
	std::ifstream signupLeft;

	signupLeft.open("assets/TG17V45.txt", std::ifstream::in);
	string loginLeft;
	string deleteing;

	signupLeft >> deleteing;
	signupLeft >> loginLeft;

	signupLeft.close();

	//if there are 3 login attempts left
	// initial page ( gjfjkl;3211F F31gbh%go9Fj65 FJE#29124jFHHII )

	// finding how many login attempts are left
	if (loginLeft[9] == '9' && deleteing == "gjfjkl;3211F") {

		loginsLeft = 3;

	}
	else if (loginLeft[2] == 'J' && deleteing == "1gG#3l2319F") {

		loginsLeft = 2;

	}
	else if (loginLeft[7] == '4' && deleteing == "1243tgGH$9@823k") {
		loginsLeft = 1;
	}
	else if (loginLeft[10] == 'h' && deleteing == "FGH449611F") {
		loginsLeft = 0;
	}
	else {
		signupTampered = true;
		return 1;
	}

	//game object
	Game *game = new Game();

	//object state1
	state1 *stateone = new state1();
	//object state2
	state2 *statetwo = new state2();
	//object state0
	state0 *statezero = new state0();


	statezero->setSignupLeft(loginsLeft);

	/////////  STUFF FOR TCP  CONNECTION /////////
		// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	if (SDLNet_Init() == -1)
	{
		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}

	try
	{
		string serverIP;
		int remotePort;
		// Now try to instantiate the client socket
		// Parameters: server address, port number, buffer size (i.e. max message size)
		// Note: You can provide the serverURL as a dot-quad ("1.2.3.4") or a hostname ("server.foo.com")

		cout << "Enter Server IP :";
		//std::cin >> serverIP;
		serverIP = "127.0.0.1";
		cout << "Enter remotePort :";
		//std::cin >> remotePort;
		remotePort = 123;
		cs = new ClientSocket(serverIP, remotePort, 512);
	}
	catch (SocketException e)
	{
		std::cerr << "Something went wrong creating a ClientSocket object." << std::endl;
		std::cerr << "Error is: " << e.what() << std::endl;
		std::cerr << "Terminating application." << std::endl;
		exit(-1);
	}

	// Attempt to connect to the server at the provided address and port
	cs->connectToServer();

	string receivedMessage = "";

	cout << "Use /quit to disconnect or /shutdown to shutdown the server." << endl;

	// Display the initial prompt
	cs->displayPrompt();

	//frame rate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game->init("Expedition", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2250, 1500);

	while (game->running()) {

		//checking connection
		thread first(updateConnection);

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		//for FPS
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {

			SDL_Delay(frameDelay - frameTime);
		}


		//SENDING VARIABLES

		//getting sends from game
		string getVariableToSend = game->getsendVariable();

		if (getVariableToSend != "") {

			cs->getUserInput(getVariableToSend);
			game->setSendVariable();

		}

		//sending x and y to server
		if (game->getStateGame() == 2) {
			counterState2++;

			if (counterState2 == 1) {
				string msg = "";
				msg = username + '#';

				msg += "~xcor:" + to_string(game->returnPlayerX());
				msg += "~ycor:" + to_string(game->returnPlayerY());
				msg += "~rotation:" + to_string(game->returnPlayerR());
				msg += "~spx:" + to_string(game->returnSpeedX());
				msg += "~spkp:" + game->returnSpacekey();
				msg += "~spy:" + to_string(game->returnSpeedY()) + '~';

				cs->getUserInput(msg);
				
			}

			if (counterState2 == 3) {
				counterState2 = 0;
			}
		}


		//sending resized x and y value
		if (game->getStateGame() == 1) {
			stateone->stateoneResizeX(game->getxVar());
			stateone->stateoneResizeY(game->getyVar());
		}

		if (game->getStateGame() == 2) {
			statetwo->statetwoResizeX2(game->getxVar());
			statetwo->statetwoResizeY2(game->getyVar());
		}

		if (game->getStateGame() == 0) {
			statezero->statezeroResizeX(game->getxVar());
			statezero->statezeroResizeY(game->getyVar());
		}

		//sending mouse events

		if (game->getStateGame() == 1) {
			stateone->getLeftButton(game->getLeftButtonDown());
			stateone->getMouseX(game->getMouseX());
			stateone->getMouseY(game->getMouseY());
		}

		if (game->getStateGame() == 2) {
			statetwo->getLeftButton2(game->getLeftButtonDown());
			statetwo->getMouseX2(game->getMouseX());
			statetwo->getMouseY2(game->getMouseY());
		}

		if (game->getStateGame() == 0) {
			statezero->getLeftButton0(game->getLeftButtonDown());
			statezero->getMouseX0(game->getMouseX());
			statezero->getMouseY0(game->getMouseY());
		}

		//sending keyboard events
		if (game->getStateGame() == 2) {
			statetwo->getUpKeyPressed2(game->getUpKeyPressed());
			statetwo->getLeftKeyPressed2(game->getLeftKeyPressed());
			statetwo->getRightKeyPressed2(game->getRightKeyPressed());
			statetwo->getDownKeyPressed2(game->getDownKeyPressed());
			statetwo->getSpaceKeyPressed2(game->getSpaceKeyPressed());
			statetwo->getFKeyPressed2(game->getFKeyPressed());
		}

		//sending username
		if (game->getStateGame() == 2) {
			statetwo->getUsername(username);
		}

		//////dealing with input from server////////
		if (userInput != "") {

			//seeing if input contains a username
			string serverUsername = "";
			bool containsUsername = false;
			for (int x = 0; x < userInput.length(); x++) {
				if (userInput[x] == '#') {
					containsUsername = true;
				}
			}

			//variable for finding username of server player
			string tempUsername = userInput;

			//getting username from input and then deleting it
			if (containsUsername) {
				int iHold = 0;
				int i = 0;
				bool foundUsername = false;
				bool foundUserVariable = false;

				//getting out username
				while (foundUsername == false) {

					if (foundUserVariable == false) {
						if (tempUsername[i] == '#') {
							foundUserVariable = true;
							iHold = i;
						}
					}

					if (iHold == tempUsername.length()-1) {
						foundUsername = true;
					}

					if (foundUserVariable) {
						tempUsername.erase(tempUsername.begin() + iHold);
					}
					//increasing i
					i++;
				}

				//deleting username
				bool deleteUsername = false;
				int i2 = 0;

				while (deleteUsername == false) {

					if (userInput[0] != '#') {
						userInput.erase(userInput.begin() + 0);
					}
					else {
						deleteUsername = true;
						userInput.erase(userInput.begin());
					}


				}

			}
			
			serverUsername = tempUsername;

			///// parsing info from server ///////////

			//// string to take place of userInput
			string userInput2 = userInput;
			//variable to count down iteration of string
			int counting = 0;


			//if there is a username with input..
			if (containsUsername) {

				//looping through string inputs.
				while (userInput2.length() > 2) {

					counting = userInput2.length() - 1;
					bool tempBool = true;

					if (userInput2.length() > 2) {

						userInput2.erase(userInput2.begin() + counting);
						counting--;

						while (tempBool) {

							if (userInput2[counting] != '~') {
								counting--;
							}
							else {
								tempBool = false;
							}

						}

						serverInfo.push_back(userInput2.substr(counting+1, ((userInput2.length() - 1) - counting+1)));
						userInput2.erase(counting, ((userInput2.length() - 1) - counting));
					}

				}

				////////////// going through information from server /////////////

				/*msg += "~xcor:" + to_string(game->returnPlayerX());
				msg += "~ycor:" + to_string(game->returnPlayerY());
				msg += "~rotation:" + to_string(game->returnPlayerR());
				msg += "~spx:" + to_string(game->returnSpeedX());
				msg += "~spy:" + to_string(game->returnSpeedY()) + '~';*/

				//if there is a username...

				for (int i = 0; i < serverInfo.size(); i++) {

					//if the state is 2
					if (game->getStateGame() == 2) {

						//x cordinate
						if (serverInfo[i][0] == 'x' && serverInfo[i][1] == 'c' && serverInfo[i][2] == 'o' && serverInfo[i][3] == 'r') {
							bool foundString = false;

							while (foundString == false) {

								if (serverInfo[i][0] != ':') {
									serverInfo[i].erase(serverInfo[i].begin() + 0);
								}
								else {
									foundString = true;
									serverInfo[i].erase(serverInfo[i].begin());
								}


							}

							////sending x cords of other players
							statetwo->getServerPlayersX(stoi(serverInfo[i]), serverUsername);
						}

						//y cordinate
						else if (serverInfo[i][0] == 'y' && serverInfo[i][1] == 'c' && serverInfo[i][2] == 'o' && serverInfo[i][3] == 'r') {
							bool foundString = false;

							while (foundString == false) {

								if (serverInfo[i][0] != ':') {
									serverInfo[i].erase(serverInfo[i].begin() + 0);
								}
								else {
									foundString = true;
									serverInfo[i].erase(serverInfo[i].begin());
								}


							}

							////sending y cords of other players
							statetwo->getServerPlayersY(stoi(serverInfo[i]), serverUsername);
						}

						//sending rotation angle
						else if (serverInfo[i][0] == 'r' && serverInfo[i][1] == 'o' && serverInfo[i][2] == 't' && serverInfo[i][3] == 'a') {
							bool foundString = false;

							while (foundString == false) {

								if (serverInfo[i][0] != ':') {
									serverInfo[i].erase(serverInfo[i].begin() + 0);
								}
								else {
									foundString = true;
									serverInfo[i].erase(serverInfo[i].begin());
								}


							}

							////sending y cords of other players
							statetwo->getServerRotation(stoi(serverInfo[i]), serverUsername);
						}

						//sending x speed
						else if (serverInfo[i][0] == 's' && serverInfo[i][1] == 'p' && serverInfo[i][2] == 'x' && serverInfo[i][3] == ':') {
							bool foundString = false;

							while (foundString == false) {

								if (serverInfo[i][0] != ':') {
									serverInfo[i].erase(serverInfo[i].begin() + 0);
								}
								else {
									foundString = true;
									serverInfo[i].erase(serverInfo[i].begin());
								}


							}

							////sending x speed of other players
							statetwo->getServerSpeedX(stod(serverInfo[i]), serverUsername);
						}

						//sending y speed
						else if (serverInfo[i][0] == 's' && serverInfo[i][1] == 'p' && serverInfo[i][2] == 'y' && serverInfo[i][3] == ':') {
							bool foundString = false;

							while (foundString == false) {

								if (serverInfo[i][0] != ':') {
									serverInfo[i].erase(serverInfo[i].begin() + 0);
								}
								else {
									foundString = true;
									serverInfo[i].erase(serverInfo[i].begin());
								}


							}

							////sending y speed of other players
							statetwo->getServerSpeedY(stod(serverInfo[i]), serverUsername);
						}

						//sending space key
						else if (serverInfo[i][0] == 's' && serverInfo[i][1] == 'p' && serverInfo[i][2] == 'k' && serverInfo[i][3] == 'p') {
						bool foundString = false;

						while (foundString == false) {

							if (serverInfo[i][0] != ':') {
								serverInfo[i].erase(serverInfo[i].begin() + 0);
							}
							else {
								foundString = true;
								serverInfo[i].erase(serverInfo[i].begin());
							}


						}
						
						////sending space bar pressed from other clients
						statetwo->getServerSpacekey(serverInfo[i], serverUsername);
						}

						//sending health of player
						else if (serverInfo[i][0] == 'd' && serverInfo[i][1] == 'm' && serverInfo[i][2] == 'g' && serverInfo[i][3] == 't') {
						bool foundString = false;

						while (foundString == false) {

							if (serverInfo[i][0] != ':') {
								serverInfo[i].erase(serverInfo[i].begin() + 0);
							}
							else {
								foundString = true;
								serverInfo[i].erase(serverInfo[i].begin());
							}


						}

						////sending health of other players
						statetwo->getServerHealth(stoi(serverInfo[i]), serverUsername);
						}

						//sending which player hit another player
						else if (serverInfo[i][0] == 'p' && serverInfo[i][1] == 'l' && serverInfo[i][2] == 'r' && serverInfo[i][3] == 'h' && serverInfo[i][4] == 'i') {
						bool foundString = false;

						while (foundString == false) {

							if (serverInfo[i][0] != ':') {
								serverInfo[i].erase(serverInfo[i].begin() + 0);
							}
							else {
								foundString = true;
								serverInfo[i].erase(serverInfo[i].begin());
							}


						}

						////sending which player hit another ship
						statetwo->getServerHits(serverInfo[i], serverUsername);
						}
					}

				}

				// setting server Info vector to zero
				for (int i = 0; i < serverInfo.size(); i++) {
					serverInfo[i] = "";
				}
			}


			//getting players from server////////////////////
			if (userInput[0] == 'p' && userInput[1] == 'l' && userInput[2] == 'a') {

				//send players to state 1
				bool foundPlayers = false;

				 while(foundPlayers == false) {

						if (userInput[0] != ':') {
							userInput.erase(userInput.begin() + 0);
						}
						else {
							foundPlayers = true;
							userInput.erase(userInput.begin());
						}


				 }

				//send players connected to state1
				 stateone->getplayersConnected(std::stoi(userInput));
			}


			//////////////// getting player leaving from server ////////////////
				if (userInput[0] == 'u' && userInput[1] == 's' && userInput[2] == 'r' && userInput[3] == 'l') {

					//send players to state 1
					bool foundPlayers = false;

					while (foundPlayers == false) {

						if (userInput[0] != ':') {
							userInput.erase(userInput.begin() + 0);
						}
						else {
							foundPlayers = true;
							userInput.erase(userInput.begin());
						}


					}

					//send player left from state 2
					statetwo->playerLeft(userInput);
				}

			///////// getting player username and pass accepted or not from server //////////
				if (userInput[0] == 'u' && userInput[1] == 's' && userInput[2] == 'r' && userInput[3] == 'a' && userInput[4] == 'c') {

					//sending username to server
					if (login == false) {

						username = statezero->getUsername();

						cs->getUserInput("!user:" + username);
						login = true;
					}

					statezero->setStateFromMain(1);

				}


			////////////////// getting chunk data from server //////////////////

				if (userInput[0] == 'r' && userInput[1] == 'e' && userInput[2] == 't' && userInput[3] == 'c' && userInput[4] == 'h' && userInput[5] == 'u' && userInput[6] == 'n' && userInput[7] == 'k') {


					statetwo->getChunkFromServer(userInput);


				}



			////// setting user error for login if found /////////
				if (userInput[0] == 'u' && userInput[1] == 's' && userInput[2] == 'r' && userInput[3] == 'd' && userInput[4] == 'e') {
					statezero->setLoginError(1);
				}

				////// setting user error for signup if found /////////
				if (userInput[0] == 's' && userInput[1] == 'i' && userInput[2] == 'g' && userInput[3] == 'n' && userInput[4] == 't' && userInput[5] == 'a' && userInput[6] == 'k') {
					statezero->setSignupError(4);
				}

				////// setting error for when user is already logged on
				if (userInput[0] == 'u' && userInput[1] == 's' && userInput[2] == 'r' && userInput[3] == 'a' && userInput[4] == 'l' && userInput[5] == 'o' && userInput[6] == 'n') {
					statezero->setLoginError(9);
				}

				////// if signup is successful /////////
				if (userInput[0] == 's' && userInput[1] == 'i' && userInput[2] == 'g' && userInput[3] == 'n' && userInput[4] == 'a' && userInput[5] == 'c' && userInput[6] == 'p') {
					statezero->setSignupError(5);

					// rewriting signup file
					if (loginsLeft == 3) {

						loginsLeft = 2;

						//delete file
						remove("assets/TG17V45.txt");
						//rewrite file
						ofstream outfile("assets/TG17V45.txt");

						outfile << "1gG#3l2319F 13JFbt$912334 FJ3j32jkl;fjkdas GJ3j211993" << endl;

						outfile.close();
						statezero->setSignupLeft(2);
					}
					else if (loginsLeft == 2) {

						loginsLeft = 1;

						//delete file
						remove("assets/TG17V45.txt");
						//rewrite file
						ofstream outfile("assets/TG17V45.txt");

						outfile << "1243tgGH$9@823k !33ggh342911 GH$%*(@#!jgh32q AFH@#!()!@wdaa" << endl;

						outfile.close();
						statezero->setSignupLeft(1);
					}
					else if (loginsLeft == 1) {

						loginsLeft = 0;

						//delete file
						remove("assets/TG17V45.txt");
						//rewrite file
						ofstream outfile("assets/TG17V45.txt");

						outfile << "FGH449611F FH31919385h5AD! FHG%1024jASCVGE JQJ*!(@EHHPUZy" << endl;

						outfile.close();

						statezero->setSignupLeft(0);

					}


				}

				////////////// getting shots from server /////////////

				if (userInput[0] == 's' && userInput[1] == 'h' && userInput[2] == 'o' && userInput[3] == 'o' && userInput[4] == 't') {


					statetwo->dealWithShooting(userInput);

				}


			//resetting userInput to ""
			userInput = "";
		}

		//bringing back thread
		first.join();
	}

	//send left to server
	cs->getUserInput("usrl:" + username);

	SDLNet_Quit();
	game->clean();
	return 0;

}

