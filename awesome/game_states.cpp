#include "game_states.h"

void menu()
{
	int mode = INITIAL_MODE;
	int level = 0;

	while (mode != EXIT)
	{
		switch (mode)
		{
		case INITIAL_MODE:
			mode = select_mode();
			break;
		case SINGLE_MODE:
			mode = select_level();
			break;
		case MULTI_MODE:
			mode = socketing();
			break;
		default:
			break;
		}
	}
}

int select_mode()
{
	bool quit = false;
	int mode = 0;
	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{
			message = TTF_RenderText_Solid(font, "Press space to start, esc key to quit", textColor);
			apply_surface(0, 0, background, screen);
			title_message = TTF_RenderText_Solid(font2, "Awesome Dodge", textColor);
			apply_surface((640 - title_message->w) / 2, 80, title_message, screen);
			apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
			message = TTF_RenderText_Solid(font, "Single         Multi", textColor);
			apply_surface((640 - message->w) / 2, 480 / 2 + message->h, message, screen);
			message2 = TTF_RenderText_Solid(font, "Single         ", textColor);
			int tmp = message2->w;
			message2 = TTF_RenderText_Solid(font, ">", textColor);
			apply_surface((640 - message->w) / 2 - 8 + mode * tmp, 480 / 2 + message->h, message2, screen);
			SDL_Flip(screen);
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
				{
					if (mode >= 1) break;
					mode++;
					break;
				}
				case SDLK_LEFT:
				{
					if (mode <= 0) break;
					mode--;
					break;
				}
				case SDLK_SPACE:
				{
					message = NULL;
					if (mode == 1) return MULTI_MODE;
					else if (mode == 0) return SINGLE_MODE;
					break;
				}
				case SDLK_ESCAPE://esc 키가 눌리면 종료
					return EXIT;
					break;
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				return EXIT;
				quit = true;
			}
		}
	}
}

int select_level()
{
	bool quit = false;
	int selector = 0;
	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{
			message = TTF_RenderText_Solid(font, "Press space to start, esc key to quit", textColor);
			apply_surface(0, 0, background, screen);
			title_message = TTF_RenderText_Solid(font2, "Awesome Dodge", textColor);
			apply_surface((640 - title_message->w) / 2, 100, title_message, screen);
			apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
			message = TTF_RenderText_Solid(font, "level 1         level 2        level 3", textColor);
			apply_surface((640 - message->w) / 2, 480 / 2 + message->h, message, screen);
			message2 = TTF_RenderText_Solid(font, "level 1         ", textColor);
			int tmp = message2->w;
			message2 = TTF_RenderText_Solid(font, ">", textColor);
			apply_surface((640 - message->w) / 2 - 8 + selector * tmp, 480 / 2 + message->h, message2, screen);
			SDL_Flip(screen);
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
				{
					if (selector >= 2) break;
					selector++;
					break;
				}
				case SDLK_LEFT:
				{
					if (selector <= 0) break;
					selector--;
					break;
				}
				case SDLK_SPACE:
				{
					message = NULL;
					init();
					main_game(selector, SINGLE_MODE);
					return INITIAL_MODE;
					break;
				}
				case SDLK_ESCAPE://esc 키가 눌리면 종료
					return INITIAL_MODE;
					break;
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				return EXIT;
				quit = true;
			}
		}
	}
}

int socketing()
{
	client = socket(AF_INET, SOCK_STREAM, 0);
	int yes = 1;
	if(setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) std::cout << "socket setting error" << std::endl;

	if (client < 0)
	{
		std::cout << "\n소켓 준비 에러..." << std::endl;
	}

	std::cout << "\n=> 소켓 생성 완료..." << std::endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);

	bool isServer = true;
	int count = 0;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);

	bool isConnect = false;
	bool* cntPointer = &isConnect;
	std::thread waitingMassage(waiting, &cntPointer);
	while (true)
	{
		if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) != -1)
		{
			isServer = false;
			isConnect = true;
			waitingMassage.join();
		}
		count++;
		if (count == 3) break;
	}

	if (isServer)
	{
		inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr); // 초기값인 0.0.0.0으로 초기화

		while ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
		{
			//std::cout << "=> Error binding connection, the socket has already been established..." << std::endl;
			//count = (count + 1) % 4;

			//std::string str = "Server is Creating, Esc key to quit";
			//message = TTF_RenderText_Solid(font, str.c_str(), textColor);
			//apply_surface(0, 0, background, screen);
			//apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
			//SDL_Delay(500);
			//std::string str2 = "Waiting";
			//for (int j = 0; j < count; j++) str2 += " .";
			//message2 = TTF_RenderText_Solid(font, str2.c_str(), textColor);
			//apply_surface((640 - message2->w) / 2, 480 / 2 - message2->h + message->h + 10, message2, screen);
			SDL_Flip(screen);
			if (SDL_PollEvent(&event))
			{
				std::string str = "Server is Creating, Esc key to quit";
				message = TTF_RenderText_Solid(font, str.c_str(), textColor);
				apply_surface(0, 0, background, screen);
				apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);

				if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE://esc 키가 눌리면 종료
						return INITIAL_MODE;
						break;
					default:
						break;
					}
				}
				else if (event.type == SDL_QUIT)
				{
					return EXIT;
				}
			}
		}
		server_addr.sin_addr.s_addr = htons(INADDR_ANY);

		size = sizeof(server_addr);
		std::cout << "=> Looking for clients..." << std::endl;
		server = -1;

		listen(client, 1);

		std::thread listenFor(waitClient, &cntPointer);

		while (!isConnect)
		{
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE://esc 키가 눌리면 종료
						isConnect = true;
						int tmp_client;
						tmp_client = socket(AF_INET, SOCK_STREAM, 0);
						inet_pton(AF_INET, ip, &server_addr.sin_addr);
						if (connect(tmp_client, (struct sockaddr*)&server_addr, size) == -1)
						{
							//error message
							std::cout << "Connecting Error!\nServer was not created." << std::endl;
							exit(1);
						}

						//3번 반복
						//int count = 0;
						/*while (true)
						{
						if (connect(tmp_client, (struct sockaddr *)&server_addr, sizeof(server_addr)) != -1)
						std::cout << "success" << std::endl;
						else std::cout << "fail" << std::endl;
						count++;
						if (count == 3) break;
						}*/
						close(tmp_client);
						close(client);
						close(server);
						listenFor.join();
						waitingMassage.join();
						return INITIAL_MODE;
						break;
					default:
						break;
					}
				}
				else if (event.type == SDL_QUIT)
				{
					return EXIT;
				}
			}
		}
		listenFor.join();
		waitingMassage.join();

		/*count = -1;
		while (true)
		{
			server = accept(client, (struct sockaddr *)&server_addr, &size);
			if(server >= 0) break;
			count = (count + 1) % 4;
			if (waiting(count) == INITIAL_MODE) return INITIAL_MODE;
		}*/
		/* ------------- ACCEPTING CLIENTS  ------------- */
		/* ----------------- listen() ------------------- */

		// first check if it is valid or not
		/*
		if (server < 0)
			std::cout << "=> Error on accepting..." << std::endl;
		*/

		buffer_int[0] = (unsigned int)time(NULL);
		send(server, buffer_int, bufsize, 0);
		srand(buffer_int[0]);
		message = NULL;
		init();
		main_game(0, SERVER_MODE);
		listenFor.~thread();
	}
	else
	{
		inet_pton(AF_INET, ip, &server_addr.sin_addr);
		/*
		while (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
		{}
		*/
		std::cout << "연결 완료!" << std::endl;
		std::cout << "=> 연결된 서버 포트 번호: " << portNum << std::endl;
		int iResult;
		struct timeval tv;
		bool timeout = false;
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(client, &rfds);

		tv.tv_sec = 5;
		tv.tv_usec = 0;

		iResult = select(client + 1, &rfds, (fd_set *)0, (fd_set *)0, &tv);
		if (iResult > 0)
		{
			recv(client, buffer_int, bufsize, 0);
			timeout = true;
		}
		if (!timeout) return INITIAL_MODE;

		srand(buffer_int[0]);
		message = NULL;
		init();
		main_game(0, CLIENT_MODE);
	}

	return INITIAL_MODE;
}

void waiting(bool **isConnect)
{
	int count = 0;
	while (!(**isConnect))
	{
		std::string str = "Waiting";
		for (int j = 0; j < count; j++) str += " .";
		message = TTF_RenderText_Solid(font, str.c_str(), textColor);
		apply_surface(0, 0, background, screen);
		apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
		SDL_Flip(screen);
		SDL_Delay(500);
		count = (count + 1) % 4;
	}
}

void waitClient(bool **isConnect)
{
	 server = accept(client, (struct sockaddr *)&server_addr, &size);
	 **isConnect = true;
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (screen == NULL)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}
	srand(time(NULL));
	SDL_WM_SetCaption("Awesome", NULL);

	return true;
}

bool load_files()
{

	background = load_image("assets/background.png");
	font = TTF_OpenFont("assets/BMDOHYEON_ttf.ttf", 24);
	font2 = TTF_OpenFont("assets/RaphLanokFuture.otf", 48);

	player = SDL_LoadBMP("assets/player1.bmp");
	player2 = SDL_LoadBMP("assets/player2.bmp");
	ball = load_image("assets/rocket.bmp");
	heart = SDL_LoadBMP("assets/heart.bmp");
	enemy_heart = SDL_LoadBMP("assets/enemy_heart.bmp");

	if (background == NULL)
	{
		return false;
	}

	if (font == NULL)
	{
		return false;
	}

	return true;
}

void clean_up()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(message);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(ball);

	TTF_CloseFont(font);
	TTF_Quit();

	SDL_Quit();
}

void main_game(int selector, int mode)//난이도 선택 변수
{
	using namespace std;
	bool quit = false;
	//client side player
	int player_position = SCREEN_WIDTH / 2;
	int player_position_y = SCREEN_HEIGHT - 3;
	//server side player
	int player2_position = SCREEN_WIDTH / 2;
	int player2_position_y = SCREEN_HEIGHT - 3;
	Uint8 *keystates = NULL;
	int start_time = SDL_GetTicks();
	int level = 1 + selector; // level 정의
	int life = 3; // life 추가
	int enemy_life = 3;
	int current_balls = 0;
	int i = 0;
	int Die_Count = 0;

	int fps_timer = 0;
	int delay = 0;
	int frames = 0;
	int fps_calc_timer = SDL_GetTicks();
	int score = 0;

	int randomball[MAX_BALLS]; // 떨어지는 볼의 속도를 랜덤하게 조정하기 위해 선언한 배열

	if (mode == SINGLE_MODE) srand((unsigned int)time(NULL)); //in Single Mode set random ball

	for (i = 0; i < MAX_BALLS; i++)
		randomball[i] = 0;

	init_ball();

	while (quit == false)
	{
		for (i = 0; i < current_balls; i++)
		{
			randomball[i] = (double)rand() / RAND_MAX * (level - 1) + BALL_VELOCITY; // 초기 속도와 레벨 사이의 난수 생성
		}


		fps_timer = SDL_GetTicks();
		if (SDL_GetTicks() - start_time > 1)
		{
			start_time = SDL_GetTicks();
			for (i = 0; i < current_balls; i++)
			{
				balls[i].y += randomball[i];//level증가를 위해서 기존 값에 level을 곱해줌
			}
		}
		if (current_balls < MAX_BALLS)
		{
			for (i = 0; i < MAX_BALLS; i++)
			{
				if (balls[i].y > SCREEN_HEIGHT || balls[i].y == 0)
				{
					SDL_Rect new_ball;
					new_ball.x = BALL_SIZE / 2 + rand() % (SCREEN_WIDTH - BALL_SIZE / 2);
					new_ball.y = -(5 + rand() % 350);
					new_ball.w = new_ball.h = BALL_SIZE;
					balls[i] = new_ball;

				}
			}
			current_balls = MAX_BALLS;
		}
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				balls[0].x = player_position;
				balls[0].y = player_position_y;
				life = 1;
				Die_Count = 0;
			}
		}

		keystates = SDL_GetKeyState(NULL);

		if (keystates[SDLK_ESCAPE])
		{
			balls[0].x = player_position;
			balls[0].y = player_position_y;
			life = 1;
			Die_Count = 0;
		}

		if (keystates[SDLK_LEFT] && player_position > PLAYER_WIDTH / 2)
		{
			player_position--;
		}

		if (keystates[SDLK_RIGHT] && player_position < SCREEN_WIDTH - PLAYER_WIDTH / 2)
		{
			player_position++;
		}

		if (keystates[SDLK_UP] && player_position_y > PLAYER_HEIGHT / 2)
		{
			player_position_y--;
		}

		if (keystates[SDLK_DOWN] && player_position_y < SCREEN_HEIGHT - PLAYER_HEIGHT / 2)
		{
			player_position_y++;
		}//위 아래 이동 추가

		apply_surface(0, 0, background, screen);
		if (life == 3) {
			apply_surface(500, 20, heart, screen); apply_surface(540, 20, heart, screen); apply_surface(580, 20, heart, screen);
		}
		// heart decrease as life goes down
		else if (life == 2) {
			apply_surface(540, 20, heart, screen); apply_surface(580, 20, heart, screen);
		}
		else if (life == 1) {
			apply_surface(580, 20, heart, screen);
		}

		for (i = 0; i < MAX_BALLS; i++)
		{
			// printf("ball %i: %i %i\n",i , balls[i].x, balls[i].y);
			apply_surface(balls[i].x, balls[i].y, ball, screen);//판정을 위해서 고친 부분
			if (balls[i].y > SCREEN_HEIGHT)
			{
				current_balls--;
				score++;
				if (score > LEVEL_UP_COUNT * (level - selector))
				{
					level++;//score의 상태에 따라 레벨 증가
				}
			}
			SDL_Rect player_rect;
			SDL_Rect player_rect2;
			player_rect.x = player_position - PLAYER_WIDTH / 2;
			player_rect.y = player_position_y - PLAYER_HEIGHT / 2;
			player_rect.w = PLAYER_WIDTH;
			player_rect.h = PLAYER_HEIGHT;
			player_rect2.x = player2_position - PLAYER_WIDTH / 2;
			player_rect2.y = player2_position_y - PLAYER_HEIGHT / 2;
			player_rect2.w = PLAYER_WIDTH;
			player_rect2.h = PLAYER_HEIGHT;
			if (intersects(balls[i], player_rect) && Die_Count == 0)
			{
				life--;
				if (life <= 0) //life소진시 종료
				{
					if (enemy_life != 0)
						switch (mode)
						{
							//server side
						case SERVER_MODE:
							std::cout << "SERVER SIDE :";
							std::cout << "Last Client: ";
							recv(server, buffer_int, bufsize, 0);
							player2_position = buffer_int[0];
							player2_position_y = buffer_int[1];
							enemy_life = buffer_int[2];
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							buffer_int[0] = player_position;
							buffer_int[1] = player_position_y;
							buffer_int[2] = life;
							std::cout << "Last Server: ";
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							send(server, buffer_int, bufsize, 0);
							break;
							//client side
						case CLIENT_MODE:
							std::cout << "CLIENT SIDE :";
							std::cout << "Last Client: ";
							buffer_int[0] = player_position;
							buffer_int[1] = player_position_y;
							buffer_int[2] = life;
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							send(client, buffer_int, bufsize, 0);
							std::cout << "Last Server: ";
							recv(client, buffer_int, bufsize, 0);
							player2_position = buffer_int[0];
							player2_position_y = buffer_int[1];
							enemy_life = buffer_int[2];
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							break;
						default:
							break;
						}
						close(server);
						close(client);

					if(mode == SINGLE_MODE)
					{
						game_over(level, score, SINGLE_MODE);
					}
					else
					{
						game_over(level, score, LOSER);// 2 == LOSE_CASE
					}
					quit = true;
				}
				else //life가 남아있으면 공 초기화후 계속
				{
					Die_Count++;
				}
			}
		}
		if (Die_Count == 0 || Die_Count % 2 == 0)
		{
			if (Die_Count >= 600) Die_Count = 0;
			apply_surface(player_position - PLAYER_WIDTH / 2, player_position_y - PLAYER_HEIGHT / 2/*SCREEN_HEIGHT - PLAYER_HEIGHT*/, player, screen);//player표시를 이동에 따라 표시
			SDL_SetColorKey(player, SDL_SRCCOLORKEY, SDL_MapRGB(player->format, 255, 255, 255));
		}
		if (Die_Count > 0) Die_Count++;

		if ((mode == CLIENT_MODE || mode == SERVER_MODE) && enemy_life > 0)//Socket 일때 만 표시
		{
			apply_surface(player2_position - PLAYER_WIDTH / 2, player2_position_y - PLAYER_HEIGHT / 2/*SCREEN_HEIGHT - PLAYER_HEIGHT*/, player2, screen);//player2표시를 이동에 따라 표시
			SDL_SetColorKey(player2, SDL_SRCCOLORKEY, SDL_MapRGB(player2->format, 255, 255, 255));
			// Present enemy_life on screen
			if (enemy_life == 3) {
			apply_surface(500, 60, enemy_heart, screen); apply_surface(540, 60, enemy_heart, screen); apply_surface(580, 60, enemy_heart, screen);
			}
			else if (enemy_life == 2) {
			apply_surface(540, 60, enemy_heart, screen); apply_surface(580, 60, enemy_heart, screen);
			}
			else if (enemy_life == 1) {
			apply_surface(580, 60, enemy_heart, screen);
			}

		}



		std::stringstream caption, caption2;
		caption << /* "FPS: " << (int)(frames*1000.0/(SDL_GetTicks() - fps_calc_timer+1)) << */"Score: " << score
			<< "       Level: " << level;//level 추가로 표시
		message = TTF_RenderText_Solid(font, caption.str().c_str(), textColor);
		caption2 << "Life: " << life;
		message2 = TTF_RenderText_Solid(font, caption2.str().c_str(), textColor);
		if (SDL_GetTicks() - fps_calc_timer > 5000)
		{
			frames = 1;
			fps_calc_timer = SDL_GetTicks();
		}
		apply_surface(10, 10, message, screen);

		SDL_Flip(screen);
		frames++;

		delay = SDL_GetTicks() - fps_timer;

		/*  Socket 통신을 위한 부분 추가  */
		if (enemy_life != 0 && life != 0)
			switch (mode)
			{
				//server side
			case SERVER_MODE:
				//std::cout << "Client: ";
				recv(server, buffer_int, bufsize, 0);
				player2_position = buffer_int[0];
				player2_position_y = buffer_int[1];
				enemy_life = buffer_int[2];
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				buffer_int[0] = player_position;
				buffer_int[1] = player_position_y;
				buffer_int[2] = life;
				caption2 << "Enemy Life: " << enemy_life;
				apply_surface(SCREEN_WIDTH - 10 - message2->w, 10, message2, screen);
				//std::cout << "Server: ";
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				send(server, buffer_int, bufsize, 0);
				break;

				//client side
			case CLIENT_MODE:
				//std::cout << "Client: ";
				buffer_int[0] = player_position;
				buffer_int[1] = player_position_y;
				buffer_int[2] = life;
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				send(client, buffer_int, bufsize, 0);
				//std::cout << "Server: ";
				recv(client, buffer_int, bufsize, 0);
				player2_position = buffer_int[0];
				player2_position_y = buffer_int[1];
				enemy_life = buffer_int[2];
				caption2 << "Enemy Life: " << enemy_life;
				apply_surface(SCREEN_WIDTH - 10 - message2->w, 10, message2, screen);
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				break;
			case SINGLE_MODE:
				break;
			}

		if(life != 0 && enemy_life == 0 && (mode == SERVER_MODE || mode == CLIENT_MODE))
		{
			shutdown(client, SHUT_RDWR);
			shutdown(server, SHUT_RDWR);
			close(client);
			close(server);
			game_over(level, score, WINNER);//1 == WIN_CASE
			quit = true;
		}

		if (delay < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - delay);
		}
	}
}

void init_ball()
{
	for (int i = 0; i < MAX_BALLS; i++)
	{
		SDL_Rect new_ball;
		new_ball.x = BALL_SIZE / 2 + rand() % (SCREEN_WIDTH - BALL_SIZE / 2);
		new_ball.y = -(5 + rand() % 350);
		new_ball.w = new_ball.h = BALL_SIZE;
		balls[i] = new_ball;
	}
}

void game_over(int level, int score, int state)
{
	std::stringstream caption;
	std::stringstream caption2;
	switch (state)
	{
		//SINGLE_MODE
		case SINGLE_MODE:
		apply_surface(0, 0, background, screen);
		message = TTF_RenderText_Solid(font, "Game over", textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
		caption << "Level : " << level;
		message = TTF_RenderText_Solid(font, caption.str().c_str(), textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h, message, screen);
		caption2 << "Score is : " << score;
		message = TTF_RenderText_Solid(font, caption2.str().c_str(), textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h + 50, message, screen);
		SDL_Flip(screen);
		break;
		// 1 == WIN_CASE
		case WINNER:
		apply_surface(0, 0, background, screen);
		message = TTF_RenderText_Solid(font, "! ! ! YOU WIN ! ! !", textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
		SDL_Flip(screen);
		break;
		// 2 == LOSE_CASE
		case LOSER:
		apply_surface(0, 0, background, screen);
		message = TTF_RenderText_Solid(font, "( T . T ) YOU LOSE ( T . T )", textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
		SDL_Flip(screen);
		break;
	}

	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || 
				(event.type == SDL_KEYDOWN && 
				(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_ESCAPE)))
			{
				break;
			}
		}
	}
}
