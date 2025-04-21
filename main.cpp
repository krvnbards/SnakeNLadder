#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <thread>
#include <limits>
#include <vector>
#include <climits>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_W 87
#define KEY_S 83

// Regular Colors
#define BLACK       "\033[30m" 
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Bright Colors
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

// Background Colors
#define BG_BLACK       "\033[40m"
#define BG_RED         "\033[41m"
#define BG_GREEN       "\033[42m"
#define BG_YELLOW      "\033[43m"
#define BG_BLUE        "\033[44m"
#define BG_MAGENTA     "\033[45m"
#define BG_CYAN        "\033[46m"
#define BG_WHITE       "\033[47m"

// Bright Background Colors
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"

// Text Styles
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"  // Swap foreground and background
#define HIDDEN      "\033[8m"
#define STRIKETHROUGH "\033[9m"

// Reset Styles
#define RESET_BOLD        "\033[21m"
#define RESET_DIM         "\033[22m"
#define RESET_ITALIC      "\033[23m"
#define RESET_UNDERLINE   "\033[24m"
#define RESET_BLINK       "\033[25m"
#define RESET_REVERSE     "\033[27m"
#define RESET_HIDDEN      "\033[28m"
#define RESET_STRIKETHROUGH "\033[29m"


using namespace std;

#define SPACE "                                                         "
#define SPACE2 "                                              "
#define SPACE1 "  "
#define CENTER "                                                                             "

string OPTION_COLOR = "";
string HIGHLIGHTED_OPTION_COLOR = "";
string LOGO_COLOR = "";

string FOREGROUND = "";
string BACKGROUND = "";
string RESET = FOREGROUND+BACKGROUND;
string BORDER_COLOR = "";
			// WHITE BG BLACK TEXT         // BRIGHT RED BG BLACK TEXT
	
// SA BOARD SETTINGS NI
string BOARD_BACKGROUND[] = {"", ""}; // 106 103 = YELLOW CYAN      101 107 = RED WHITE
string BOARD_TEXT[] = {"", ""};
string alt_color[] = {BOARD_TEXT[0]+BOARD_BACKGROUND[0], BOARD_TEXT[1]+BOARD_BACKGROUND[1]};
string SYMBOL_COLORS[] = {"", "", "", ""}; // Snake Tail Ladder Special(POWERUP)
string PLAYER_SYMBOL = "●";

string TEXT_COLOR = "97";

int boardHeight = (3 * 10) + 2; // Example: 10 rows of numbers, each 3 lines + 2 border lines
int logStartY = boardHeight + 2 + 19;

// MENU HIGHLIGHT
string HIGHLIGHT_BG = "97";
string HIGHLIGHT_FG = "104";
string HIGHLIGHT = "\033[" + HIGHLIGHT_BG + ";" + HIGHLIGHT_FG + "m";

string POWER_UPS[] = {"Extra Roll", "Boost", "Slow Down", "Teleport", "Snake Repellent", "Shield"};

//[-------------------------------VARIABLES-------------------------------]
const int MAX_PLAYERS = 6;
int numOfPlayers = 0;
int turnToPlay = -1;

int START_NUMBER = 0;

struct playa {
	string name = "";
	int position = -1;
	string color;
	bool completed;
	bool snakeShield;
	bool Shield;
	bool isAI;
};

struct Theme {
    string name;
    string foreground;
    string background;
    string checker1;
    string checker2;
    string optionColor;
    string highlightedOptionColor;
};

string boardColor = "0";
string backgroundColor = "0"; 
string displayBoardColor;
string colo = "color ";
string finalCombined = colo + backgroundColor + boardColor;
const char *charColor = finalCombined.c_str();

int enableLoading = 1;
int enableSFX = 1;
int autoPause = 0;
int enableAnimations = 1;
int bgmEnabled = 1;

int name_position = 1;
int color_position = 1;
int selectingPlayer = -1;

bool extraRoll = false;

unordered_map<int, int> snakes = {
    {99, 21},  {56, 15}, {47, 20}, {88, 24}, {94, 45}, 
    {78, 37}, {82, 59}, {67, 29}, {35, 5},  {14, 4},  
    {19, 8},  {23, 2},  {31, 9}
};

unordered_map<int, int> ladders = {
    {3, 22},  {6, 25},  {11, 40}, {60, 85}, {18, 33}, 
    {27, 50}, {44, 66}, {53, 74}, {63, 81}, {72, 91}
};

unordered_set<int> powerups = {
    5, 12, 19, 26, 39, 48, 58, 69, 72, 89
};

vector<string> availableColors = {
    "\033[38;2;200;0;0m",   // Red
    "\033[38;2;0;150;0m",   // Green
    "\033[38;2;200;200;0m", // Yellow
    "\033[38;2;0;0;200m",   // Blue
    "\033[38;2;200;0;200m", // Magenta
    "\033[38;2;0;200;200m", // Cyan
    "\033[38;2;200;200;200m", // White
    "\033[38;2;255;0;0m",   // Bright Red
    "\033[38;2;0;255;0m",   // Bright Green
};

//------------------------------------------------------------------------

enum stat_list {
	MAINMENU = 1,
	HOW_TO_PLAY,
	SELECT_PLAYERS,
	SELECT_COLORS,
	ABOUT_PAGE,
	GAME_ENTERNAME,
	GAME_STARTED,
	SETTINGS_PAGE,
	SELECT_PLAYER_COLOR,
	EXIT_GAME,
	SELECT_THEMES,
	VOLUME_PAGE,
};

enum stat_list STATUS = MAINMENU;

vector<playa> Player;


//[--------------------------FUNCTION PROTOTYPES--------------------------]
void displayBoard();
void LogoArt();
void setConsoleSize(int width, int height);
void ShowMainMenu();
int getConsoleWidth();
int getConsoleHeight();
void SelectPlayers();
void HowToPlay();
void Pause(int ms);
void AboutPage();
void showProgressBar(int total, int consoleWidth);
void EnterName();
void StartGame();
void SelectColors();
void SelectPlayerColor();
void ClearGame();
void displaySettingsPage(int cursor);
void showCursor();
void hideCursor();
void SettingsPage();
void displayMenu(int cursor);
void displayPlayerOptions(int cursor, int page);
void displayLegend();
void playHopSound();
void PlayBackgroundMusic();
void movePlayerAnimation(int playerIndex, int targetPosition, bool forward, bool isTeleport);
void handleLadderOrSnake(int playerIndex);
void slowDownOpponent(int player);
void applyPowerUp(int player);
void movePlayer(int player, int roll);
void ThemesPage();
void VolumePage();
void announceWinner(int player);
bool checkGameOver();
void clearScreen();
void giveShield(int player, int type);
int getNextPlayer(int currentPlayer);
void ForPlayingArt();
void SimulateF11();
void SimulateEnter();
void ThankyouArt();
void addComputer(int count);
void ExitGame();
void moveToPosition(int x, int y);
void PrintCharDelay(string text, int delay);
void PrintCharDelay2(string text, int delay);
void PrintAnimation(const string lines[], int size, int delay);
void DevelopersArt();
void changeTheme(int theme);
void ApplyTheme(const Theme& theme);
//------------------------------------------------------------------------

int main()
{

	HWND hwnd = GetConsoleWindow();
	if (hwnd) {
        
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~(WS_SIZEBOX);  
        SetWindowLong(hwnd, GWL_STYLE, style);
    }
    
	
	SetConsoleOutputCP(CP_UTF8);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    if (GetConsoleMode(hOut, &dwMode)) {
        // Enable VT Processing
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }

    ShowWindow(hwnd, SW_MAXIMIZE);
    
	//setlocale(LC_ALL, "");
	//setConsoleSize(1200, 1200);
	
	int height = getConsoleHeight();
	cout << height;
	
    cout << "\n\n" << RESET;
    
    system(charColor);
    hideCursor();
    system("mode 650");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0);
	
	changeTheme(1);
	clearScreen();
	srand(time(0));
    
    if(enableLoading == 1) {
   		Sleep(2000); // Wait for 2 seconds

   	 	// Simulate pressing F11 twice
    	SimulateF11();
    	Sleep(500); // Small delay between key presses
    	SimulateF11();

    	// Simulate pressing Enter twice
    	Sleep(500); // Small delay between key presses
   		SimulateEnter();
    	Sleep(500); // Small delay between key presses
    	SimulateEnter();
    
    	cout << "\n\n\n\n\n";
    	LogoArt();
		
		int consoleWidth = getConsoleWidth(); // Get the console width
		string space="";
		for(int i = 1; i <= (consoleWidth-15) / 2; i++)
			space += " ";
			
			
	    cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << space << "LOADING GAME...\n"; 
	    showProgressBar(50, consoleWidth);
	}
	changeTheme(1);
	clearScreen();
	PlayBackgroundMusic();
	bgmEnabled = 1;
	while(1) { // GAME IS RUNNING
		switch(STATUS) {
			case MAINMENU: {
				ShowMainMenu();
				break;
			}
			case GAME_ENTERNAME: {
				EnterName();
				break;
			}
			case SELECT_PLAYERS: {
				SelectPlayers();
				break;
			}
			case ABOUT_PAGE: {
				AboutPage();
				break;
			}
			case SELECT_THEMES: {
				ThemesPage();
				break;
			}
			case VOLUME_PAGE: {
				VolumePage();
				break;
			}
			case SETTINGS_PAGE: {
				SettingsPage();
				break;
			}
			case SELECT_COLORS: {
				SelectColors();
				break;
			}
			case HOW_TO_PLAY: {
				HowToPlay();
				break;
			}
			case SELECT_PLAYER_COLOR: {
				SelectPlayerColor();
				break;
			}
			case GAME_STARTED: {
				StartGame();
				break;
			}
			case EXIT_GAME: {
				ExitGame();
				return 0;
			}
		}
	}
    return 0;
}

//----------------------------FUNCTION DEFINITIONS-----------------------]

void moveToPosition(int x, int y) {
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Create a COORD structure with the given x and y values, cast to SHORT
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    
    // Set the console cursor position to the specified coordinates
    SetConsoleCursorPosition(hConsole, coord);
}

void EnterName() {
	int colorIndex = 0;
	bool proceed=true;
	string center="";
	string center2="";
	int width = getConsoleWidth();
	for(int i = 1; i <= (width - 74) / 2; i++)
		center += " ";
		
	for(int i = name_position; i <= numOfPlayers; i++) {
		clearScreen();
		cout << "\n\n\n\n\n\n";
		LogoArt();
		center2="";
		
		string SPACES = "                                 ";
		
		string NORMAL_COLOR = OPTION_COLOR;
		cout << endl << endl;
	 	cout << center << NORMAL_COLOR << "██████████████████████████████████████████████████████████████████████████" << RESET << endl;
	 	cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                   Please enter name for Player " << name_position << "             [0] Back  █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "██████████████████████████████████████████████████████████████████████████" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "█                                                                        █" << RESET << endl;
	    cout << center << NORMAL_COLOR << "██████████████████████████████████████████████████████████████████████████" << RESET << endl;
	    cout << endl;
	    
	    for(int h = 1; h <= (width -12) / 2; h++)
	    	center2 += " ";
	    
	    int count = 1;
	    if(Player.size() > 0) {
	    	cout << center << "Player list:" << endl;
    		for(const playa& p : Player) {
    			cout << center2 << count << ". " << p.name << endl;
    			count++;
			}
		}
	    
	    if(count == 1)
	    	cout << "\033[5A"; 
	    else
	    	cout << "\033[" + to_string(5+count) + "A";  
	    
	    showCursor();
		cout << "\033[" << to_string(width / 2) << "C" << NORMAL_COLOR; 
			    	
		string names;
	    getline(cin >> ws, names);
	    cout << RESET;
	    if(names[0] == '0') {
	    	if(name_position == 1) {
	    		proceed=false;
	    		break;
			}
	    	i--;
	    	Player.pop_back();
	    	name_position--;
	    	Pause(500);
	    	continue;
		}
	    bool error = false;
	    for(const playa& p : Player) {
	    	if(p.name.compare(names) == 0) {
	    		cout << endl<<endl<< center << "The name is already taken! Please enter a different name.\n";
	    		error = true;
	    		break;
			}
		}
		
		if(error) {
			Pause(1000);
			i--;
			continue;
		}
		string assignedColor;
		for (const string& color : availableColors) {
	        bool isUsed = false;
	        for (const playa& p : Player) {
	            if (p.color.compare(color) == 0) {
	                isUsed = true;
	                break;
	            }
	        }
	        
	        if (!isUsed) {
	            assignedColor = color;
	            break;
	        }
	    }
	
		// 										completed snakeShield Shield isAI
		Player.push_back({names, START_NUMBER, assignedColor, false, false, false, false});
		name_position++;
	}
	
	if(!proceed) {
		Player.clear();
		STATUS=SELECT_PLAYERS;
		name_position = -1;
		return;
	}
	
	if(numOfPlayers == 1)
	{
		addComputer(1);
		addComputer(2);
		addComputer(3);
		addComputer(4);
		addComputer(5);
	}
	
	clearScreen();
	LogoArt();
	name_position = 1;
	color_position = 1;
	STATUS = SELECT_COLORS;
}

void announceWinner(int player) {
    cout << SPACE SPACE2 << "\033[" << Player[player].color
         << Player[player].name << RESET << " has reached 100 and WON the game!" << endl;
    _getch();
    Player[player].completed = true;
}

void changeTheme(int theme) {
	if(theme == 1) { // Classic
		
		LOGO_COLOR = "\033[38;2;0;0;0m\033[48;2;255;127;39m";
		
		FOREGROUND = "\033[38;2;255;255;255m";
		BACKGROUND = "\033[48;2;0;45;45m";
		RESET = FOREGROUND+BACKGROUND;
		BORDER_COLOR = "\033[38;2;255;255;255m";
					// WHITE BG BLACK TEXT         // BRIGHT RED BG BLACK TEXT
					
		OPTION_COLOR = "";
		HIGHLIGHTED_OPTION_COLOR = "\033[48;2;0;0;0m\033[38;2;255;102;204m";
			
		// SA BOARD SETTINGS NI
		BOARD_BACKGROUND[0] = "\033[48;2;246;129;50m"; 
		BOARD_BACKGROUND[1] = "\033[48;2;255;229;148m"; 
		BOARD_TEXT[0] = "\033[38;2;0;0;0m";
		BOARD_TEXT[1] = "\033[38;2;0;0;0m";
		
		alt_color[0] = BOARD_TEXT[0]+BOARD_BACKGROUND[0];
		alt_color[1] = BOARD_TEXT[1]+BOARD_BACKGROUND[1];
		SYMBOL_COLORS[0] = "\033[38;2;139;0;0m"; // Snake Tail Ladder Special(POWERUP)
		SYMBOL_COLORS[1] = "\033[38;2;139;0;0m"; // Snake Tail Ladder Special(POWERUP)
		SYMBOL_COLORS[2] = "\033[38;2;0;100;200m"; // Snake Tail Ladder Special(POWERUP)
		SYMBOL_COLORS[3] = "\033[38;2;0;200;0m"; 
	}
}

bool checkGameOver() {
    int remainingPlayers = 0;
    for (int i = 0; i < numOfPlayers; i++) {
        if (!Player[i].completed) remainingPlayers++;
    }
    if (remainingPlayers <= 1) {
        cout << SPACE SPACE2 << "\033[1;31mGame Over! Returning to main menu...\n" << RESET;
        _getch();
        ClearGame();
        STATUS = MAINMENU;
        return true;
    }
    return false;
}

void SimulateF11() {
    // Simulate pressing the "F11" key down
    keybd_event(VK_F11, 0, 0, 0);

    // Simulate releasing the "F11" key
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
}

void SimulateEnter() {
    // Simulate pressing the "Enter" key down
    keybd_event(VK_RETURN, 0, 0, 0);

    // Simulate releasing the "Enter" key
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

int getNextPlayer(int currentPlayer) {
    int nextPlayer = currentPlayer;
    int attempts = numOfPlayers;
    do {
        nextPlayer = (nextPlayer + 1) % numOfPlayers;
        attempts--;
    } while (Player[nextPlayer].completed && attempts > 0);
    return nextPlayer;
}

void diceArt(int number) {
    const string diceFaces[6][7] = {
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█             █",
            "█             █",
            "█      ●      █",
            "█             █",
            "█             █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ●           █",
            "█             █",
            "█             █",
            "█             █",
            "█           ● █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ●           █",
            "█             █",
            "█      ●      █",
            "█             █",
            "█           ● █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ●         ● █",
            "█             █",
            "█             █",
            "█             █",
            "█ ●         ● █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ●         ● █",
            "█             █",
            "█      ●      █",
            "█             █",
            "█ ●         ● █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        },
        {
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀█",
            "█ ●    ●    ● █",
            "█             █",
            "█             █",
            "█             █",
            "█ ●    ●    ● █",
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄█"
        }
    };
    
    int width=getConsoleWidth();
    string center="";
    for(int i = 1; i < (width - 15) / 2; i++)
    	center += " ";
    	
    	int player = turnToPlay;

    for (int i = 0; i < 7; ++i) {

        cout << RESET << center << Player[player].color << "\033[48;2;255;255;255m" << diceFaces[number - 1][i] << RESET << endl;
    }
}

void PlayBackgroundMusic() {
    mciSendString("open \"resources/background-music.mp3\" type mpegvideo alias bgm", NULL, 0, NULL);
    mciSendString("setaudio bgm volume to 150", NULL, 0, NULL); // Volume range: 0 (mute) to 1000 (max)
    mciSendString("play bgm repeat", NULL, 0, NULL); // Repeat to loop continuously
}

void StopBGM() {
    mciSendString("stop bgm", NULL, 0, NULL); // Repeat to loop continuously
}

void playSound(int type) {
	if(enableSFX) {
		if(type == 1){ // hop
		
			mciSendString("stop hop", NULL, 0, NULL);
    		mciSendString("close hop", NULL, 0, NULL);
    		
			mciSendString("open resources/hop-sfx.wav alias hop", NULL, 0, NULL);
			mciSendString("setaudio hop volume to 400", NULL, 0, NULL);
    		mciSendString("play hop", NULL, 0, NULL);
		}
		else if(type == 2){ // menu switch
		
			mciSendString("stop menu", NULL, 0, NULL);
    		mciSendString("close menu", NULL, 0, NULL);
    		
			mciSendString("open resources/Retro12.wav alias menu", NULL, 0, NULL);
    		mciSendString("play menu", NULL, 0, NULL);
		}
		else if(type == 3){ // ladder
		
			mciSendString("stop hit", NULL, 0, NULL);
    		mciSendString("close hit", NULL, 0, NULL);
    		
			mciSendString("open resources/orch-hit.wav alias hit", NULL, 0, NULL);
    		mciSendString("play hit", NULL, 0, NULL);
		}
		else if(type == 4){ // ladder
		
			mciSendString("stop trombone", NULL, 0, NULL);
    		mciSendString("close trombone", NULL, 0, NULL);
    		
			mciSendString("open resources/sad-trombone.wav alias trombone", NULL, 0, NULL);
    		mciSendString("play trombone", NULL, 0, NULL);
		}
		else if(type == 6){ // victory
		
			mciSendString("stop victory", NULL, 0, NULL);
    		mciSendString("close victory", NULL, 0, NULL);
    		
			mciSendString("open \"resources/goodresult.mp3\" type mpegvideo alias victory", NULL, 0, NULL);
    		mciSendString("play victory", NULL, 0, NULL);
		}
		else if(type == 7){ // enter
		
			mciSendString("stop menu", NULL, 0, NULL);
    		mciSendString("close menu", NULL, 0, NULL);
    		
			mciSendString("open resources/Retro11.wav alias menu", NULL, 0, NULL);
    		mciSendString("play menu", NULL, 0, NULL);
		}
		else if(type == 8){ // enter
		
			mciSendString("stop dice", NULL, 0, NULL);
    		mciSendString("close dice", NULL, 0, NULL);
    		
			mciSendString("open resources/dice.wav alias dice", NULL, 0, NULL);
    		mciSendString("play dice", NULL, 0, NULL);
		}
		else if(type == 9){ // enter
		
			mciSendString("stop tp", NULL, 0, NULL);
    		mciSendString("close tp", NULL, 0, NULL);
			mciSendString("open resources/teleport.wav alias tp", NULL, 0, NULL);
			mciSendString("setaudio tp volume to 350", NULL, 0, NULL);
    		mciSendString("play tp", NULL, 0, NULL);
		}
		else if (type == 10) {
			
			mciSendString("stop boost", NULL, 0, NULL);
    		mciSendString("close boost", NULL, 0, NULL);
			mciSendString("open resources/boost.mp3 type mpegvideo alias boost", NULL, 0, NULL);
			mciSendString("setaudio boost volume to 400", NULL, 0, NULL);
    		mciSendString("play boost", NULL, 0, NULL);
		}
		else if (type == 11) {
			
			mciSendString("stop shield", NULL, 0, NULL);
    		mciSendString("close shield", NULL, 0, NULL);
			mciSendString("open resources/shield.mp3 type mpegvideo alias shield", NULL, 0, NULL);
			//mciSendString("setaudio shield volume to 400", NULL, 0, NULL);
    		mciSendString("play shield", NULL, 0, NULL);
		}
		else if (type == 12) {
			
			mciSendString("stop slow", NULL, 0, NULL);
    		mciSendString("close slow", NULL, 0, NULL);
			mciSendString("open resources/freeze.mp3 type mpegvideo alias slow", NULL, 0, NULL);
			//mciSendString("setaudio slow volume to 400", NULL, 0, NULL);
    		mciSendString("play slow", NULL, 0, NULL);
		}
	}
}


void ClearGame() {
	turnToPlay = -1;
	numOfPlayers = 0;
	selectingPlayer = -1;
	Player.clear();
}

void rollDiceAnimation() {
    srand(time(0));
    int revealAt = rand() % 3 + 3;

    for (int i = 0; i < revealAt; ++i) {
        int randomFace = rand() % 6 + 1;
        //cout << "\033[H\033[J";
        //cout << SPACE SPACE2 "Rolling the dice...\n";
        if(i > 0)
        	cout << "\033[7A"; // Move the cursor up 7 lines
        
        diceArt(randomFace);
        int delay = rand() % 300 + 500;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void rollPowerUps() {
    srand(time(0));
    //int revealAt = rand() % 3 + 3;

    for (int i = 0; i < 6; ++i) {
        int randomFace = rand() % 7;
        cout << "\r" << "\033[J" << SPACE SPACE2 << SYMBOL_COLORS[3] << POWER_UPS[randomFace] << RESET;
        int delay = rand() % 300 + 500;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

int revealPowerUp() {
	int finalPower = rand() % 6;
	Pause(1000);
	cout << "\r" << SPACE SPACE2 << "\033[J" << "You gained the power up: " << SYMBOL_COLORS[3] << POWER_UPS[finalPower] << RESET << endl;
	return finalPower;
}

int revealFinalDice() {
    int finalNumber = rand() % 6 + 1;
    //cout << "\033[H\033[J";
    
    int width = getConsoleWidth();
    string center = "";
    for(int i = 1; i <= (width - 18) / 2; i++)
    	center += " ";
    
    cout << center << "The dice rolled...\n";
    Pause(1000);
    diceArt(finalNumber);
    center = "";
    for(int i = 1; i <= (width - 14) / 2; i++)
    	center += " ";
    cout << center << "You rolled a " << finalNumber << "!" << endl;
    return finalNumber;
}

void movePlayer(int player, int roll) {
    int finalPos = Player[player].position + roll;

    // Handle board boundaries
    if (finalPos > 100) {
        int excess = finalPos - 100;
        finalPos = 100 - excess;
    }

	cout << "\033[10A\033[J";
	
	int width = getConsoleWidth();
	string center = "";
	for(int i = 1; i <= (width - 38) / 2; i++)
		center += " ";
    // Animate movement
    cout << endl << center << "\033[" << Player[player].color << Player[player].name
         << RESET << " moves " << roll << " spaces forward!" << endl;

	hideCursor();
    Pause(1500);
    movePlayerAnimation(player, finalPos, true, false);
	
    // Check if landed on a snake, ladder, or power-up
    handleLadderOrSnake(player);
    

    if (powerups.find(Player[player].position) != powerups.end()) {
        // Player landed on a power-up
        applyPowerUp(player);
    }
}

void teleportPlayer(int playerIndex) {
    int minMove = 5; // Minimum forward move
    int maxMove = 20; // Maximum forward move
    int newPos = Player[playerIndex].position + (rand() % (maxMove - minMove + 1) + minMove);

    if (newPos > 100) newPos = 100; // Ensure it doesn't exceed the last tile

    // Avoid teleporting to a snake's head
    while (snakes.find(newPos) != snakes.end()) {
        newPos--;
    }
  
    cout << SPACE SPACE2 << SYMBOL_COLORS[3] << "TELEPORT! "<< RESET << Player[playerIndex].name << " activated a teleport power-up! --> " << newPos << endl;
	Pause(1500);
     
    movePlayerAnimation(playerIndex, newPos, true, true);
    handleLadderOrSnake(playerIndex); // Check for further movement from ladder/snake
}

void applyPowerUp(int player) {
    cout << SPACE SPACE2 << "\033[" << Player[player].color << Player[player].name 
         << RESET << ", has stepped on a " << SYMBOL_COLORS[3] << "POWERUP!" << RESET << "." << endl;

    cout << SPACE SPACE2 << "\033[JRolling power-ups..." << endl;
    rollPowerUps();
    int power = revealPowerUp();
    //power = 4;

    if (power == 0) { // Extra Roll
        cout << SPACE SPACE2 << SYMBOL_COLORS[3] 
             << "You will be able to roll the dice again!" << RESET << endl;
        turnToPlay--;
        Pause(1000);
    } 
    else if (power == 1) { // Boost (+5 Spaces)
        int boostAmount = 2;
        int finalPos = Player[player].position + boostAmount;
        if (finalPos > 100) finalPos = 100 - (finalPos - 100);

        cout << SPACE SPACE2 << SYMBOL_COLORS[3] 
             << "You will move +" << boostAmount << " extra spaces forward!" << RESET << endl;
        if(enableSFX) playSound(10);
        Pause(1500);

        movePlayerAnimation(player, finalPos, true, false);
        handleLadderOrSnake(player);
    } 
    else if (power == 2) { // Slow Down (Opponent moves -3)
    	playSound(12);
        slowDownOpponent(player);
    }
    else if(power == 3) { // Teleport
    	teleportPlayer(player);
	}
	else if(power == 4) { // Snake Repellent
		playSound(11);
		giveShield(player, 1);
	}
	else if(power == 5) {
		playSound(11);
		giveShield(player, 2);
	}
}

void giveShield(int player, int type) {
	if(type == 1) {
		cout << SPACE SPACE2 << "\033[" << Player[player].color << Player[player].name << " will repel the effect of Snakes for once!" << RESET << endl;
		Player[player].snakeShield = true;
		_getch();
	}
	else if(type == 2) {
		cout << SPACE SPACE2 << "\033[" << Player[player].color  << Player[player].name << " will repel negative effects targeted by players!" << RESET << endl;
		Player[player].Shield = true;
		_getch();
	}
}

void slowDownOpponent(int player) {
	
	if(Player[player].isAI) {
		cout << SPACE SPACE2 << Player[player].color << Player[player].name << " will choose the first player available to move -3 spaces backward." << RESET << endl;
	}
	else {
		cout << SPACE SPACE2 << SYMBOL_COLORS[3] << "Choose an opponent to move -3 spaces backward." << RESET << endl;	
		cout << SPACE SPACE2 << "Player list:" << endl;
	}

    
    int cursor = 0, movesBackward = 3;
    vector<int> validPlayerIndices;

    // Get valid players
    for (int i = 0; i < numOfPlayers; i++) {
        if (!Player[i].completed && Player[i].name != Player[player].name) {
            validPlayerIndices.push_back(i);
        }
    }

    int count = validPlayerIndices.size();
    
    
    if(Player[player].isAI) {
    	playSound(7);
        hideCursor();
        int selectedIndex = validPlayerIndices[0];

        // **Move back step by step (without clearing screen)**
        int finalPos = max(1, Player[selectedIndex].position - movesBackward);
        
        hideCursor();
        while (Player[selectedIndex].position > finalPos) {
            Player[selectedIndex].position--;  // Move one step at a time
            moveToPosition(0, 19);
            displayBoard();  // Redraw board without clearing screen
            if (enableSFX) playSound(1);
            fflush(stdout);
            Pause(200);
        }

        // Handle ladder or snake after moving back
        handleLadderOrSnake(selectedIndex);
        return;
	}
	
    int times=0;
    while (true) {
    	if(times > 0) {
    		cout << "\033[" << to_string(count+1) << "A";
			cout << "\n\033[J";  // Move cursor up and clear only necessary lines
		}
        
        times++;
        for (int i = 0; i < count; i++) {
            if (i == cursor)
                cout << HIGHLIGHT << SPACE SPACE2 << " > \033[" << Player[validPlayerIndices[i]].color 
                     << "m" << Player[validPlayerIndices[i]].name << HIGHLIGHT << "\033[K" << RESET << endl;
            else
                cout << SPACE SPACE2 << RESET << "\033[" << Player[validPlayerIndices[i]].color 
                      << Player[validPlayerIndices[i]].name << RESET << endl;
        }

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        char input = _getch();
        switch (input) {
            case KEY_ENTER: {
            	playSound(7);
                hideCursor();
                int selectedIndex = validPlayerIndices[cursor];

                // **Move back step by step (without clearing screen)**
                int finalPos = max(1, Player[selectedIndex].position - movesBackward);
                
                hideCursor();
                while (Player[selectedIndex].position > finalPos) {
                    Player[selectedIndex].position--;  // Move one step at a time
                    moveToPosition(0, 19);
                    displayBoard();  // Redraw board without clearing screen
                    if (enableSFX) playSound(1);
                    fflush(stdout);
                    Pause(200);
                }

                // Handle ladder or snake after moving back
                handleLadderOrSnake(selectedIndex);
                return;
            }
            case KEY_UP: case KEY_W: case 'w': cursor = (cursor == 0) ? count - 1 : cursor - 1; break;
            case KEY_DOWN: case KEY_S: case 's': cursor = (cursor == count - 1) ? 0 : cursor + 1; break;
        }
        if (enableSFX) playSound(2);
    }
}

void movePlayerAnimation(int playerIndex, int finalPos, bool forward, bool isTeleport = false) {
	
	if (isTeleport) {
        Player[playerIndex].position = finalPos;
        playSound(9); 
        moveToPosition(0, 19);
        displayBoard();
        return;
    }
    
    hideCursor();
    int currentPosition = Player[playerIndex].position;
    int distance = abs(finalPos - currentPosition);

    // Dynamically adjust step size based on distance
    int stepSize = (distance > 15) ? 5 : (distance > 8) ? 3 : 1;

    while (currentPosition != finalPos) {
        if (forward) {
            currentPosition += stepSize;
            if (currentPosition > finalPos) currentPosition = finalPos;
        } else {
            currentPosition -= stepSize;
            if (currentPosition < finalPos) currentPosition = finalPos;
        }

        Player[playerIndex].position = currentPosition;

		hideCursor();
        moveToPosition(0, 19);
        displayBoard();
        if (enableSFX) playSound(1); // Step sound

        fflush(stdout);
        Pause(200); // Delay for animation
    }
}

void handleLadderOrSnake(int playerIndex) {
    int pos = Player[playerIndex].position;
	string center = "";
	int width = getConsoleWidth();
    if (ladders.find(pos) != ladders.end()) {
        int ladderEnd = ladders[pos];
        playSound(3);
        for(int i = 1; i <= (width-42) / 2; i++)
        	center += " ";
        cout << SPACE SPACE2 << "\033[" << Player[playerIndex].color << Player[playerIndex].name
             << RESET << ", has stepped on a " << SYMBOL_COLORS[2] << "LADDER! -->" 
             << ladderEnd << RESET << "." << endl;
        Pause(1500);
        movePlayerAnimation(playerIndex, ladderEnd, true, false);
    } 
    else if (snakes.find(pos) != snakes.end()) {
    	
    	for(int i = 1; i <= (width-42) / 2; i++)
        	center += " ";
        	
    	if(Player[playerIndex].snakeShield) {
    		cout << center << "\033[" << Player[playerIndex].color << Player[playerIndex].name
             << RESET << ", has repelled the effects of " << SYMBOL_COLORS[0] << "SNAKE!" << RESET << endl;
             Player[playerIndex].snakeShield = false;
             return;
		}
        int snakeTail = snakes[pos];
        playSound(4);
        cout << center << "\033[" << Player[playerIndex].color << Player[playerIndex].name
             << RESET << ", has stepped on a " << SYMBOL_COLORS[0] << "SNAKE! -->" 
             << snakeTail << RESET << "." << endl;
        Pause(1500);
        movePlayerAnimation(playerIndex, snakeTail, false, false);
    }
}

void clearScreen() {
	//system("cls");
	moveToPosition(0, 0);
	cout << RESET;
	cout << "\033[J";
	cout << RESET;
}

bool promptRoll(int player) {
	int width = getConsoleWidth();
	string center = "";
	for(int i = 1; i <= (width - 42) / 2; i++)
		center += " ";
	
	cout << "\033[" << logStartY << ";0H";
    cout << center << Player[player].color 
         << Player[player].name << RESET << ", press Enter to roll the dice!" << endl << SPACE SPACE2;
    
    while (true) {
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        char input = _getch();
        input = tolower(input);

        if (input == KEY_ESC) {
            cout << "Do you want to return to the main menu? (y/n): ";
            while (true) {
                char input2 = _getch();
                input2 = tolower(input2);
                if (input2 == 'y') return false;
                if (input2 == 'n') break;  
            }
            cout << endl << SPACE SPACE2 << "\033[" << Player[player].color 
                 << Player[player].name << RESET << ", press Enter to roll the dice!" << endl << SPACE SPACE2;
        }
        
        if(input == 'm') {
        	if(bgmEnabled) {
        		StopBGM();
        		bgmEnabled = 0;
        		cout  << "Background music has been disabled.";
        		Pause(950);
        		cout << "\r\033[J";
			}
			else {
				PlayBackgroundMusic();
				cout << "Background music has been enabled.";
				Pause(950);
				cout << "\r\033[J";
			    bgmEnabled = 1;		
			}
		}

        if (input == KEY_ENTER) return true; 
    }
}

void StartGame() {
    turnToPlay = 0; // First player
    int width = getConsoleWidth();
	string center = "";
	for(int i = 1; i <= (width - 42) / 2; i++)
		center += " ";
    while (true) {
        // Clear screen and display game state
        clearScreen();
        //system("cls");
        
        if(getConsoleHeight() >= 35)
        	LogoArt();
        	
        displayLegend();
        
        displayBoard();
        int player = turnToPlay;
        bool extraRoll = false;

        // Prompt player to roll the dice
        if(Player[player].isAI) {
        	cout << "\033[" << logStartY << ";0H";
		    cout << center << Player[player].color 
		         << Player[player].name << RESET << " will now roll his dice!" << endl << SPACE SPACE2;
         
        	Pause(1000);
        	playSound(8);
	        cout << "\033[1A\r\033[J\033[" << Player[player].color;
	        cout << endl;
	        rollDiceAnimation();
	        cout << "\033[7A\033[J";
	        int roll = revealFinalDice();
	        //roll=5;
			Pause(1000);
	        movePlayer(player, roll);
	
	        if (Player[player].position == 100) {
	            announceWinner(player);
	            if (checkGameOver()) return;
	        }

	        turnToPlay = extraRoll ? player : getNextPlayer(turnToPlay);
		}
        else
        {
        	if (!promptRoll(player)) {
	            STATUS = MAINMENU;
	            ClearGame();
	            return;
	        }
	
			playSound(8);
			
			
	        // Roll and reveal dice
	        cout << "\033[1A\r\033[J\033[" << Player[player].color;
	        cout << endl;
	        rollDiceAnimation();
	        cout << "\033[7A\033[J";
	        int roll = revealFinalDice();
			roll=5;
			Pause(1000);
	        movePlayer(player, roll);
			//roll=6;
	        if (Player[player].position == 100) {
	            announceWinner(player);
	            if (checkGameOver()) return;
	        }
	
	        // Switch turn unless player gets an extra roll
	        turnToPlay = extraRoll ? player : getNextPlayer(turnToPlay);	
		}
    }
}

void SelectPlayerColor() {
	clearScreen();
	LogoArt();

	int sizedt = 0;
	
	int player = selectingPlayer;
	vector<string> storedColors; 
	storedColors.push_back("Back"); 

	for (size_t i = 0; i < availableColors.size(); i++) {
		bool available = true;
		for(const playa& p : Player) {
			if(p.color.compare(availableColors[i]) == 0) {
				available = false;
				break;
			}	
		}
		
		if(available) {
			storedColors.push_back(availableColors[i]);
			sizedt++;		
		}
    }
		
	string options[sizedt+1];    
    options[0] = "Back";
    
    for (size_t i = 1; i <= sizedt; i++) {
	    options[i] = storedColors[i] + PLAYER_SYMBOL + RESET; 
	}
		
    int cursor = 0;
	while(1) {
		clearScreen();
		LogoArt();

		cout << CENTER "Choose available colors for " << Player[player].name << ":\n";
		for(int i = 0; i < sizedt+1; i++) {
			if(i == cursor)
				cout << HIGHLIGHT << CENTER << " > " << options[i]  << HIGHLIGHT << "\033[K" << RESET << endl;
			else
				cout << CENTER << RESET << options[i] << RESET << endl;
		}	
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char input = _getch();
		switch(input) {
			case KEY_ENTER: 
			{
				playSound(7);
				if(cursor == 0) {
					selectingPlayer = -1;
					STATUS=SELECT_COLORS;
					return;
				}
				else if(cursor >= 1 && cursor <= sizedt)
				{
					cout << CENTER << Player[player].name << ", Successfully changed color to: \033[" << storedColors[cursor] << PLAYER_SYMBOL << RESET << "!\n";

	                Player[player].color = storedColors[cursor]; // Assign selected color
	                Pause(800);
	
	                selectingPlayer = -1;
	                STATUS = SELECT_COLORS;
	                return;
				}
				break;
					
			}
			
			case KEY_UP: case KEY_W: case 'w': {
				if(cursor == 0) {
					cursor = sizedt;
				}
				else cursor--;
				
				if(enableSFX)
					playSound(2);
				break;
			}
			case KEY_DOWN: case 'S': case 's': 
			{
				if(cursor == sizedt) {
					cursor = 0;
				}
				else cursor++;
				
				if(enableSFX)
						playSound(2);
				break;
			}
		}
	}
    
}

void SelectColors() {
	clearScreen();
	LogoArt();
	int width = getConsoleWidth();
	int size = Player.size();
	string options[size+2];
	options[0] = "Back";
	options[1] = "Start Game";
	int count = 2;
	for(const playa& p : Player) {
		options[count] = p.name + " : " + p.color + PLAYER_SYMBOL + RESET;
		count++;
	}
	
	
	int cursor = 0;
	while(true) {
		clearScreen();
		cout << "\n\n\n\n\n";
		LogoArt();
		string center="";
			for(int h = 1; h <= (width - 49) / 2; h++) 
				center += " ";
		cout << center << "Choose a color for each player or Start the game:\n";
		for(int i = 0; i < size+2; i++) {
			center="";
			int len = options[i].length();
			if(i > 1)
				len -= 13;
			for(int h = 1; h <= (width - len) / 2; h++) center += " ";
			if(i == cursor)
				cout << HIGHLIGHT << center << " > " << options[i] << HIGHLIGHT << "\033[K" << RESET << endl;
			else
				cout << center << RESET << options[i] << RESET << endl;
		}
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char input = _getch();
		switch(input) {
			case KEY_ENTER: 
			{
				playSound(7);
				switch(cursor) 
				{
					case 0: {
						name_position = Player.size();
						Player.pop_back();
						STATUS=GAME_ENTERNAME;
						return;
					}
					case 1: {
						STATUS=GAME_STARTED;
						return;
					}
					case 2 ... 8: {
						selectingPlayer = cursor-2;
						STATUS=SELECT_PLAYER_COLOR;	
						return;
					}
				}
				break;
			}
			
			case KEY_UP: case KEY_W: case 'w': {
				if(cursor == 0) {
					cursor = size+1;
				}
				else cursor--;
				
				if(enableSFX)
					playSound(2);
				break;
			}
			case KEY_DOWN: case KEY_S: case 's': {
				if(cursor == size+1) {
					cursor = 0;
				}
				else cursor++;
				
				if(enableSFX)
					playSound(2);
				break;
			}
		}
	}
}

void DevelopersArt() {

	string DevelopersText = R"(
██████╗ ███████╗██╗   ██╗███████╗██╗      ██████╗ ██████╗ ███████╗██████╗ ███████╗
██╔══██╗██╔════╝██║   ██║██╔════╝██║     ██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝
██║  ██║█████╗  ██║   ██║█████╗  ██║     ██║   ██║██████╔╝█████╗  ██████╔╝███████╗
██║  ██║██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║     ██║   ██║██╔═══╝ ██╔══╝  ██╔══██╗╚════██║
██████╔╝███████╗ ╚████╔╝ ███████╗███████╗╚██████╔╝██║     ███████╗██║  ██║███████║
╚═════╝ ╚══════╝  ╚═══╝  ╚══════╝╚══════╝ ╚═════╝ ╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝
                                                                                  
)";

	istringstream stream(DevelopersText);
	string line;

	while(getline(stream, line)) {
		std::cout << SPACE1 SPACE SPACE1 SPACE2 << line << std::endl;
	}
}

void AboutPage() {
	system("cls");
	clearScreen();
	LogoArt();
	string choice;
	int width = getConsoleWidth();
	string center = "";
	for(int i = 1; i <= (width - 52) / 2; i++)
		center += " ";
	const string devNames[] = {{(CENTER "                                                    ")},
							   {(CENTER"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄")},
							   {(CENTER"█                                                  █")},
							   {(CENTER"█                 Kervin Bardilas                  █")},
							   {(CENTER"█                  Jules Omambac                   █")},
							   {(CENTER"█                 Kendrick Lanuza                  █")},
							   {(CENTER"█                                                  █")},
							   {(CENTER"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█")}};

	int nameSize = sizeof(devNames)/sizeof(devNames[0]);
	PrintAnimation(devNames, nameSize, 100);

	while(1) {

		cout << endl;
		center="";
		for(int i = 1; i<=(width - 24)/2; i++)
			center+=" ";
			
		PrintCharDelay2(CENTER"See developers description(y/n): ", 10);
		cin >> choice;
		cout << endl;

		if (choice == "y" || choice == "Y") {
			const string devDescription1[] = {{(CENTER"Age:    20")},
											 {(CENTER"Status: Student")},
											 {(CENTER"Gender: Male")},
											 {(CENTER"Motto: Do it scared, do it tired, do it broke, do it alone, do it unsure, but do it\n "
											    CENTER"		anyways. Because we think we have forever to chase our dreams\n"
											    CENTER"		but today is all we really have and you'll never get it back.\n"
											    CENTER"		and you'll never get it back. No regrets!\n")}};

			const string devDescription2[] = {{(CENTER "Age:	18")},
											 {( CENTER"Status: Student")},
											 {( CENTER"Gender: Male")},
											 {( CENTER"Motto: Live intentionally!\n")}};

			const string devDescription3[] = {{(CENTER "Age:	19")},
											 {( CENTER"Status: Student")},
											 {(CENTER "Gender: Male")},
											 {(CENTER "Motto: Just do it!")}};

			const string* devDESCRIPTIONS[] = {devDescription1, devDescription2, devDescription3};								 
			int descriptionSize[] = {
										sizeof(devDescription1)/ sizeof(devDescription1)[0],
										sizeof(devDescription2)/ sizeof(devDescription2)[0],
										sizeof(devDescription3)/ sizeof(devDescription3)[0]
										};

			const string devNames[] = {{( "Name: Kervin Bardilas")},
									   {( "Name: Jules Omambac")},
									   {( "Name: Kendrick Lanuza")}};

			int numDetails = sizeof(devDESCRIPTIONS)/sizeof(devDESCRIPTIONS[0]);

			for(int i = 0; i < numDetails; i++) {
				PrintCharDelay(CENTER + devNames[i], 15);
				PrintAnimation(devDESCRIPTIONS[i], descriptionSize[i],200);
			}
			_getch();
			break;
		} 
		else if(choice == "N" || choice == "n") {
			cout << CENTER << "Returning to main menu!" << endl;
			STATUS = MAINMENU;
			break;
		} 
		else {
			system("cls");
			cout <<  "Invalid choice!" << endl;

		}

	}

	cout << endl;	
	cout << "Return to main menu. Press any key to continue...";
	_getch();
	STATUS = MAINMENU;
}

void PrintCharDelay(string text, int delay = 10) {

	for (char ch : text) {
		cout << ch; 
		Sleep(delay);
	}
	cout << endl;
}

void PrintCharDelay2(string text, int delay = 15) {

	for (char ch : text) {
		cout << ch;
		Sleep(delay);
	}
}
void PrintAnimation(const string lines[], int size, int delay = 100 ) {

	for (int i = 0; i < size; i++) {
		cout << lines[i] << endl;
		this_thread::sleep_for(chrono::milliseconds(delay)); 
	}
}

void SelectPlayers() {
	
	system("cls");
	int width = getConsoleWidth();
	string center="";
	for(int i = 1; i <= (width - 30) / 2; i++)
		center += " ";
	
	cout << "\n\n\n\n";
	LogoArt();
	cout << center <<  "Select the number of players: \n\n";
	
	int cursor = 0;
	int page = 1;
	moveToPosition(0, 16); cout << "\033[J";
	displayPlayerOptions(cursor, page);
	
	while(true) {
		hideCursor();
        moveToPosition(0, 16); cout << "\033[J";
		displayPlayerOptions(cursor, page);
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char input = _getch();
		switch(input) {
			case KEY_ENTER: {
				playSound(7);
				switch(cursor) {
					case 0: {
						STATUS=MAINMENU;
			
						if(enableSFX)
							playSound(2);
						return;
					}
					case 1 ... 6: {
						if(enableSFX)
							playSound(2);
						
						name_position = 1;
						numOfPlayers = cursor;
						STATUS=GAME_ENTERNAME;
						return;
					}
				}
				break;
			}
			
			case KEY_ESC: {
				STATUS=MAINMENU;
	
				if(enableSFX)
					playSound(2);
				return;
			}
			
			case KEY_UP: case KEY_W: case 'w': {
				if(page == 1) {
					if(cursor == 0) {
						cursor = 3;
					}
					else cursor--;
				}
				else if(page == 2) {
					if(cursor == 4) {
						cursor = 6;
					}
					else cursor--;
				}
				
				if(enableSFX)
					playSound(2);
				break;
			}
			case KEY_LEFT: case 'A': case 'a': {
				if(page == 1) {
					page = 2;
					cursor = 3;
				}
				else {
					page = 1;
					cursor = 0;
				}
				break;
			}
			case KEY_RIGHT: case 'D': case 'd': {
				if(page == 2) {
					page = 1;
					cursor = 0;
				}
				else {
					page = 2;
					cursor = 4;
				}
				break;
			}
			case KEY_DOWN: case KEY_S: case 's': {
				if(page == 1) {
					if(cursor == 3) {
						cursor = 0;
					}
					else cursor++;	
				}
				else {
					if(cursor == 6) {
						cursor = 4;
					}
					else cursor++;
				}
				
				if(enableSFX)
					playSound(2);
				break;
			}
		}
	}	
}

void ThankyouArt() {

	string ThankYouText = R"(
 
████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗    ██╗   ██╗ ██████╗ ██╗   ██╗
╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝    ╚██╗ ██╔╝██╔═══██╗██║   ██║
   ██║   ███████║███████║██╔██╗ ██║█████╔╝      ╚████╔╝ ██║   ██║██║   ██║
   ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗       ╚██╔╝  ██║   ██║██║   ██║
   ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗       ██║   ╚██████╔╝╚██████╔╝
   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝       ╚═╝    ╚═════╝  ╚═════╝ 
                                                                                                                                                                     
   )";
  		istringstream stream(ThankYouText);
   		string line;
  		while(getline(stream, line)) {
   		std::cout << setw(34) << SPACE SPACE1 SPACE1 SPACE1 SPACE1 SPACE1  << line << std::endl; 
   }

}

void ForPlayingArt() {

	string forPlayingText = R"(
███████╗ ██████╗ ██████╗     ██████╗ ██╗      █████╗ ██╗   ██╗██╗███╗   ██╗ ██████╗ ██╗
██╔════╝██╔═══██╗██╔══██╗    ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██║████╗  ██║██╔════╝ ██║
█████╗  ██║   ██║██████╔╝    ██████╔╝██║     ███████║ ╚████╔╝ ██║██╔██╗ ██║██║  ███╗██║
██╔══╝  ██║   ██║██╔══██╗    ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██║██║╚██╗██║██║   ██║╚═╝
██║     ╚██████╔╝██║  ██║    ██║     ███████╗██║  ██║   ██║   ██║██║ ╚████║╚██████╔╝██╗
╚═╝      ╚═════╝ ╚═╝  ╚═╝    ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝
                                                                                       
)";

	istringstream stream(forPlayingText);
	string line;
	while(getline(stream, line)) {
		std::cout << SPACE SPACE1 SPACE1 << line << std:: endl;
	}
}

void ExitGame() {
	system("cls");
	LogoArt();
	ThankyouArt(); 
	ForPlayingArt();
	system("pause");
	exit(0);	
}

void ApplyTheme(const Theme& theme) {
    FOREGROUND = theme.foreground;
    BACKGROUND = theme.background;
    RESET = FOREGROUND + BACKGROUND;
    OPTION_COLOR = theme.optionColor;
    HIGHLIGHTED_OPTION_COLOR = theme.highlightedOptionColor;
    BOARD_BACKGROUND[0] = theme.checker1;
    BOARD_BACKGROUND[1] = theme.checker2;
    BOARD_TEXT[0] = "\033[38;2;0;0;0m";
    BOARD_TEXT[1] = "\033[38;2;0;0;0m";
    alt_color[0] = BOARD_TEXT[0] + BOARD_BACKGROUND[0];
    alt_color[1] = BOARD_TEXT[1] + BOARD_BACKGROUND[1];
    SYMBOL_COLORS[0] = "\033[38;2;139;0;0m";
    SYMBOL_COLORS[1] = "\033[38;2;139;0;0m";
    SYMBOL_COLORS[2] = "\033[38;2;0;100;200m";
    SYMBOL_COLORS[3] = "\033[38;2;0;200;0m";
    
    cout << CENTER "Applying theme: " << theme.name << "\n";
}
    
void ThemesPage() {
	system("cls");
	cout << "\n\n\n";
	LogoArt();
	
	Theme themes[] = {
        {"Classic & Elegant", "\033[38;2;0;0;0m", "\033[48;2;255;255;240m", "\033[48;2;128;0;32m", "\033[48;2;255;215;0m", "\033[38;2;180;180;180m\033[48;2;40;40;40m", "\033[38;2;255;255;255m\033[48;2;180;0;0m"},
        {"Modern & Sleek", "\033[38;2;255;255;255m", "\033[48;2;46;46;46m", "\033[48;2;0;128;128m", "\033[48;2;192;192;192m", "\033[38;2;200;200;200m\033[48;2;20;20;20m", "\033[38;2;255;255;255m\033[48;2;80;0;0m"},
        {"Vibrant & Playful", "\033[38;2;0;0;128m", "\033[48;2;211;211;211m", "\033[48;2;255;102;0m", "\033[48;2;135;206;235m", "\033[38;2;255;255;0m\033[48;2;0;0;180m", "\033[38;2;0;255;0m\033[48;2;180;0;0m"},
        {"Earthy & Natural", "\033[38;2;1;50;32m", "\033[48;2;245;222;179m", "\033[48;2;226;114;91m", "\033[48;2;128;128;0m", "\033[38;2;180;150;100m\033[48;2;30;120;30m", "\033[38;2;255;255;255m\033[48;2;80;40;0m"}
    };
    
    int choice;
    cout << CENTER "Select a theme:\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << themes[i].name << "\n";
    }
    cout << CENTER "Enter your choice (1-4): ";
    cin >> choice;
    
    if (choice >= 1 && choice <= 4) {
        changeTheme(choice);
        ApplyTheme(themes[choice - 1]);   
    } else if (choice == 0) {
    	cout << CENTER "Going back to main menu\n";
    	_getch();
    	STATUS = MAINMENU;
	} else  {
        cout << CENTER "Invalid choice. Try again.\n";
    }
    system("pause");
    STATUS = MAINMENU;
}    
    
void SettingsPage() {
	system("cls");
	cout << "\n\n\n";
	LogoArt();
    moveToPosition(0, 13);
    displaySettingsPage(0);
    int cursor = 0;
    while (true) {
        hideCursor();
        cout << "\n\n";
        moveToPosition(0, 13);
        displaySettingsPage(cursor);

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        char input = _getch();

        switch (input) {
            case KEY_ENTER:
                playSound(7);
                if (enableSFX) playSound(2);
                STATUS = (cursor == 0) ? MAINMENU : 
                         (cursor == 1) ? SELECT_THEMES : VOLUME_PAGE;
                return;
            case KEY_UP: case KEY_W: case 'w':
                cursor = (cursor == 0) ? 2 : cursor - 1;
                if (enableSFX) playSound(2);
                break;
            case KEY_DOWN: case KEY_S: case 's':
                cursor = (cursor == 2) ? 0 : cursor + 1;
                if (enableSFX) playSound(2);
                break;
        }
    }
}

void VolumePage() {
	system("cls");
	cout << "\n\n\n";
	
	LogoArt();
	cout << endl << SPACE << RESET << "Sorry, this page is unavailable at the moment. :(";
	Pause(3000);
	STATUS=SETTINGS_PAGE;
}
	

void displayMenu(int cursor) {
	string NORMAL_COLOR = OPTION_COLOR;       // Green (Default)
    string HIGHLIGHTED_COLOR = HIGHLIGHTED_OPTION_COLOR;  // Yellow (Highlighted)
    
    int center = getConsoleWidth();    
    //string RESET = "\033[0m";
    
    string centerspace = "";
    for(int i= 1; i <= (center - 55) / 2; i++) {
    	centerspace += " ";
	}
	string menuOptions[] = {
	"███████████████████████████████████████████████████████\n"
	"█                                                     █\n"
	"█   █▀▀ ▀▀█▀▀ █▀▀█ █▀▀█ ▀▀█▀▀   █▀▀▀ █▀▀█ █▀▄▀█ █▀▀   █\n"
	"█   ▀▀█   █   █▄▄█ █▄▄▀   █     █ ▀█ █▄▄█ █ ▀ █ █▀▀   █\n"
	"█   ▀▀▀   ▀   ▀  ▀ ▀ ▀▀   ▀     ▀▀▀▀ ▀  ▀ ▀   ▀ ▀▀▀   █\n"
	"███████████████████████████████████████████████████████\n",
	
	"███████████████████████████████████████████████████████\n"
	"█                                                     █\n"
	"█              █▀▀█ █▀▀▄ █▀▀█ █  █ ▀▀█▀▀              █\n"
	"█              █▄▄█ █▀▀▄ █  █ █  █   █                █\n"
	"█              ▀  ▀ ▀▀▀  ▀▀▀▀  ▀▀▀   ▀                █\n"
	"███████████████████████████████████████████████████████\n",
	
	"███████████████████████████████████████████████████████\n"
	"█                                                     █\n"
	"█  █  █ █▀▀█ █   █   ▀▀█▀▀ █▀▀█   █▀▀█ █   █▀▀█ █  █  █\n"
	"█  █▀▀█ █  █ █▄█▄█     █   █  █   █  █ █   █▄▄█ █▄▄█  █\n"
	"█  ▀  ▀ ▀▀▀▀  ▀ ▀      ▀   ▀▀▀▀   █▀▀▀ ▀▀▀ ▀  ▀ ▄▄▄█  █\n"
	"█                                                     █\n"
	"███████████████████████████████████████████████████████\n",
	
	"███████████████████████████████████████████████████████\n"
	"█                                                     █\n"
	"█       █▀▀ █▀▀ ▀▀█▀▀ ▀▀█▀▀  ▀  █▀▀▄ █▀▀▀ █▀▀         █\n"
	"█       ▀▀█ █▀▀   █     █   ▀█▀ █  █ █ ▀█ ▀▀█         █\n"
	"█       ▀▀▀ ▀▀▀   ▀     ▀   ▀▀▀ ▀  ▀ ▀▀▀▀ ▀▀▀         █\n"
	"███████████████████████████████████████████████████████\n",
	
	"███████████████████████████████████████████████████████\n"
	"█                                                     █\n" 
	"█           █▀▀ █ █ ▀█▀ ▀█▀   █▀▀ █▀█ █▄█ █▀▀         █\n" 
	"█           █▀▀ ▄▀▄  █   █    █ █ █▀█ █ █ █▀▀         █\n" 
	"█           ▀▀▀ ▀ ▀ ▀▀▀  ▀    ▀▀▀ ▀ ▀ ▀ ▀ ▀▀▀         █\n" 
    "█                                                     █\n" 
	"███████████████████████████████████████████████████████\n",
	};
	for(int i = 0; i < 5; i++) {
		std::string COLOR = (i == cursor) ? HIGHLIGHTED_COLOR : NORMAL_COLOR;

        std::istringstream stream(menuOptions[i]);
        std::string line;
        while (getline(stream, line)) {
            std::cout << RESET << centerspace << COLOR << line << RESET << std::endl;
        }
        cout << endl;
	}
}

void displayPlayerOptions(int cursor, int page) {
	string NORMAL_COLOR = OPTION_COLOR;       // Green (Default)
    string HIGHLIGHTED_COLOR = HIGHLIGHTED_OPTION_COLOR;  // Yellow (Highlighted)
    //string RESETCOL = "\033[0m";
    
    int center = getConsoleWidth();
    
    string centerspace = "";
    for(int i= 1; i <= (center - 44) / 2; i++) {
    	centerspace += " ";
	}
	string centerspace2 = "";
    for(int i= 1; i <= (center - 11) / 2; i++) {
    	centerspace2 += " ";
	}

	string playerOptions[] = {
	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█         █▀▀█  █▀▀█  █▀▀█  █ ▄▀           █\n"
	"█         █▀▀▄  █▄▄█  █     █▀▄            █\n"
	"█         █▄▄█  █  █  █▄▄█  █  █           █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",	
		
	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█    ▄█     █▀▀█ █   █▀▀█ █  █ █▀▀ █▀▀█    █\n"
	"█     █     █▄▄█ █   █▄▄█ █▄▄█ █▀▀ █▄▄▀    █\n"
	"█    ▄█▄    █    ▀▀▀ ▀  ▀ ▄▄▄█ ▀▀▀ ▀ ▀▀    █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",

	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█  █▀█    █▀▀█ █   █▀▀█ █  █ █▀▀ █▀▀█ █▀▀  █\n"
	"█   ▄▀    █▄▄█ █   █▄▄█ █▄▄█ █▀▀ █▄▄▀ ▀▀█  █\n"
	"█  █▄▄    █    ▀▀▀ ▀  ▀ ▄▄▄█ ▀▀▀ ▀ ▀▀ ▀▀▀  █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",  

	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█  █▀▀█   █▀▀█ █   █▀▀█ █  █ █▀▀ █▀▀█ █▀▀  █\n"
	"█    ▀▄   █▄▄█ █   █▄▄█ █▄▄█ █▀▀ █▄▄▀ ▀▀█  █\n"
	"█  █▄▄█   █    ▀▀▀ ▀  ▀ ▄▄▄█ ▀▀▀ ▀ ▀▀ ▀▀▀  █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",

	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█   █▀█   █▀▀█ █   █▀▀█ █  █ █▀▀ █▀▀█ █▀▀  █\n"
	"█  █▄▄█▄  █▄▄█ █   █▄▄█ █▄▄█ █▀▀ █▄▄▀ ▀▀█  █\n"
	"█     █   █    ▀▀▀ ▀  ▀ ▄▄▄█ ▀▀▀ ▀ ▀▀ ▀▀▀  █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",

	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█  █▀▀   █▀▀█ █   █▀▀█ █  █ █▀▀ █▀▀█ █▀▀   █\n"
	"█  ▀▀▄   █▄▄█ █   █▄▄█ █▄▄█ █▀▀ █▄▄▀ ▀▀█   █\n"
	"█  ▄▄▀   █    ▀▀▀ ▀  ▀ ▄▄▄█ ▀▀▀ ▀ ▀▀ ▀▀▀   █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",

	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█  ▄▀▀▄   █▀▀█ █   █▀▀█ █  █ █▀▀ █▀▀█ █▀▀  █\n"
	"█  █▄▄    █▄▄█ █   █▄▄█ █▄▄█ █▀▀ █▄▄▀ ▀▀█  █\n"
	"█  ▀▄▄▀   █    ▀▀▀ ▀  ▀ ▄▄▄█ ▀▀▀ ▀ ▀▀ ▀▀▀  █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",
	};

	if(page == 1) {
		for(int i = 0; i < 4; i++) {
			std::string COLOR = (i == cursor) ? HIGHLIGHTED_COLOR : NORMAL_COLOR;
	
	        std::istringstream stream(playerOptions[i]);
	        std::string line;
	        while (getline(stream, line)) {
	            std::cout << RESET << centerspace << COLOR << line << RESET << std::endl;
	        }
	        cout << endl;
		}	
		cout << endl;
	    cout << centerspace2 << "Page 1 of 2" << endl;
	}
	else if(page == 2) {
		for(int i = 4; i < 7; i++) {
			std::string COLOR = (i == cursor) ? HIGHLIGHTED_COLOR : NORMAL_COLOR;
	
	        std::istringstream stream(playerOptions[i]);
	        std::string line;
	        while (getline(stream, line)) {
	            std::cout << RESET << centerspace << COLOR << line << RESET << std::endl;
	        }
	        cout << endl;
		}	
		cout << endl;
	    cout << centerspace2 << "Page 2 of 2" << endl;
	}
}

void displaySettingsPage(int cursor) {
	string NORMAL_COLOR = OPTION_COLOR;       // Green (Default)
    string HIGHLIGHTED_COLOR = HIGHLIGHTED_OPTION_COLOR;  // Yellow (Highlighted)
    //string RESETCOL = "\033[0m";
    
    int center = getConsoleWidth();
    
    string centerspace = "";
    for(int i= 1; i <= (center - 44) / 2; i++) {
    	centerspace += " ";
	}

	string playerOptions[] = {
	"████████████████████████████████████████████\n"
	"█                                          █\n"
	"█         █▀▀█  █▀▀█  █▀▀█  █ ▄▀           █\n"
	"█         █▀▀▄  █▄▄█  █     █▀▄            █\n"
	"█         █▄▄█  █  █  █▄▄█  █  █           █\n"
	"█                                          █\n"
	"████████████████████████████████████████████\n",
	 
	"████████████████████████████████████████████\n"
	"█▌                                        ▐█\n"
	"█▌           ▀█▀ █ █ █▀▀ █▄█ █▀▀          ▐█\n"
	"█▌            █  █▀█ █▀▀ █ █ █▀▀          ▐█\n"
	"█▌            ▀  ▀ ▀ ▀▀▀ ▀ ▀ ▀▀▀          ▐█\n"
	"█▌                                        ▐█\n"
	"████████████████████████████████████████████\n",	
		
	"████████████████████████████████████████████\n"
	"█▌                                        ▐█\n"
	"█▌        █ █ █▀█ █   █ █ █▄█ █▀▀         ▐█\n"
	"█▌        ▀▄▀ █ █ █   █ █ █ █ █▀▀         ▐█\n"
	"█▌         ▀  ▀▀▀ ▀▀▀ ▀▀▀ ▀ ▀ ▀▀▀         ▐█\n"
	"█▌                                        ▐█\n"
	"████████████████████████████████████████████\n",
	};

	for(int i = 0; i < 3; i++) {
		std::string COLOR = (i == cursor) ? HIGHLIGHTED_COLOR : NORMAL_COLOR;

        std::istringstream stream(playerOptions[i]);
        std::string line;
        while (getline(stream, line)) {
            std::cout << RESET << centerspace << COLOR << line << RESET << std::endl;
        }
        cout << endl;
	}	
	cout << endl;
}


void HowToPlay() { //THIS IS DONE UNLESS THERE ARE CHANGES IN THE POWERUPS AND HOW THE GAMEPLAY CHANGES, WILL TWEAK IT IF THERE ARE ANY CHANGES
	 clearScreen();
	 LogoArt();
	 string SPACEZ = "                            ";
	 cout << SPACE2 << SPACEZ << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
	 cout << SPACE2 << SPACEZ << "                                  SNAKE AND LADDER                         \n";
	 cout << SPACE2 << SPACEZ << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\n";

	 cout << SPACE << SPACEZ << "Welcome to the exciting game of Snake and Ladder with Power-Ups!\n\n";

	 cout << SPACE2 << SPACEZ << "HOW TO PLAY: \n";
	 cout << SPACE2 << SPACEZ << "1. Each player takes turns rolling the dice by pressing a key.\n";
	 cout << SPACE2 << SPACEZ << "2. The number rolled on the dice determines how many spaces the player moves\n";
	 cout << SPACE2 << SPACEZ << "   forward.\n";
	 cout << SPACE2 << SPACEZ << "3. Landing on the bottom of a ladder (L) will instantly move you up to a higher\n"; 
	 cout << SPACE2 << SPACEZ << "   space. Ladders are your friends!\n";
	 cout << SPACE2 << SPACEZ << "4. Landing on the head of a snake (S) will send you sliding down to a lower space.\n";
	 cout << SPACE2 << SPACEZ << "   Watch out for those sneaky snakes!\n";
	 cout << SPACE2 << SPACEZ << "5. If you land on a Power-Up (?) space, a random effect will trigger, which can\n";
	 cout << SPACE2 << SPACEZ << "   help or hinder your progress.\n";
	 cout << SPACE2 << SPACEZ << "6. The first player to reach exactly square 100 wins the game. If the dice roll\n";
	 cout << SPACE2 << SPACEZ << "   exceeds 100, you bounce back the extra spaces.\n\n";

	 cout << SPACE2 << SPACEZ << "LEGEND: \n";
	 cout << SPACE2 << SPACEZ << "S = Snake (Move Down)\n";
	 cout << SPACE2 << SPACEZ << "L = Ladder (Move Up)\n";
	 cout << SPACE2 << SPACEZ << "? = Power-Up (Random Effect)\n";
	 cout << SPACE2 << SPACEZ << PLAYER_SYMBOL << " = Player (Each dot color represents a different player)\n\n";

	 cout << SPACE2 << SPACEZ << "POWER-UP EFFECTS: \n";
	 cout << SPACE2 << SPACEZ << "- Extra Roll: Roll the dice again and advance further.\n";
	 cout << SPACE2 << SPACEZ << "- Boost: Move forward a few extra spaces.\n";
	 cout << SPACE2 << SPACEZ << "- Slow Down: Force another player to lose their next turn.\n";
	 cout << SPACE2 << SPACEZ << "- Teleport: Instantly move to a random space on the board.\n";
	 cout << SPACE2 << SPACEZ << "- Snake Repellent: Avoid the effect of the next snake you encounter.\n";
	 cout << SPACE2 << SPACEZ << "- Shield: Protect yourself from one negative effect.\n\n";

	 cout << SPACE2 << SPACEZ << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
	 cout << SPACE2 << SPACEZ << "                             Press any key to return...        \n";
	 cout << SPACE2 << SPACEZ << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";

	 _getch();
	 STATUS = MAINMENU;
}

void LogoArt() {
	string text = R"(
████████████████████████████████████████████████████████████████████████████████████████████████████████████
█▌  .▄▄ ·  ▐ ▄  ▄▄▄· ▄ •▄ ▄▄▄ ..▄▄ ·      ▄▄▄·  ▐ ▄ ·▄▄▄▄      ▄▄▌   ▄▄▄· ·▄▄▄▄  ·▄▄▄▄  ▄▄▄ .▄▄▄  .▄▄ ·   ▐█
█▌  ▐█ ▀. •█▌▐█▐█ ▀█ █▌▄▌▪▀▄.▀·▐█ ▀.     ▐█ ▀█ •█▌▐███▪ ██     ██•  ▐█ ▀█ ██▪ ██ ██▪ ██ ▀▄.▀·▀▄ █·▐█ ▀.   ▐█
█▌  ▄▀▀▀█▄▐█▐▐▌▄█▀▀█ ▐▀▀▄·▐▀▀▪▄▄▀▀▀█▄    ▄█▀▀█ ▐█▐▐▌▐█· ▐█▌    ██▪  ▄█▀▀█ ▐█· ▐█▌▐█· ▐█▌▐▀▀▪▄▐▀▀▄ ▄▀▀▀█▄  ▐█
█▌  ▐█▄▪▐███▐█▌▐█ ▪▐▌▐█.█▌▐█▄▄▌▐█▄▪▐█    ▐█ ▪▐▌██▐█▌██. ██     ▐█▌▐▌▐█ ▪▐▌██. ██ ██. ██ ▐█▄▄▌▐█•█▌▐█▄▪▐█  ▐█
█▌   ▀▀▀▀ ▀▀ █▪ ▀  ▀ ·▀  ▀ ▀▀▀  ▀▀▀▀      ▀  ▀ ▀▀ █▪▀▀▀▀▀•     .▀▀▀  ▀  ▀ ▀▀▀▀▀• ▀▀▀▀▀•  ▀▀▀ .▀  ▀ ▀▀▀▀   ▐█
████████████████████████████████████████████████████████████████████████████████████████████████████████████
	)";
	
	int center = getConsoleWidth();    
    //string RESET = "\033[0m";
    
    string centerspace = "";
    for(int i= 1; i <= (center - 108) / 2; i++) {
    	centerspace += " ";
	}
	
	string NORMAL_COLOR = LOGO_COLOR;
	istringstream stream(text);
    string line;
    while (getline(stream, line)) {
        std::cout << centerspace << NORMAL_COLOR << line << endl << RESET ; 
    }

/*
    for(int i = 0; i < 21; i++)
    	cout << "▄▄▄▄▄▄▄▄▄▄▄";
    cout << "▄▄▄▄▄▄" << endl;*/
}

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80; // Default width
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return width;
}

int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1; // Error case
}

void ShowMainMenu() {
    clearScreen();
    cout << "\n";
    LogoArt();
    
    int cursor = 0;
    cout << "\n\n";
    
    moveToPosition(0, 13);
    displayMenu(cursor);
    
	
	int times=0;
    while (true) {
    	//clearScreen();
        //LogoArt();
        hideCursor();
        cout << "\n\n";
        moveToPosition(0, 13);
        times++;
        displayMenu(cursor);

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        char input = _getch();

        switch (input) {
            case KEY_ENTER:
                playSound(7);
                if (enableSFX) playSound(2);
                STATUS = (cursor == 0) ? SELECT_PLAYERS : 
                         (cursor == 1) ? ABOUT_PAGE : 
                         (cursor == 2) ? HOW_TO_PLAY : 
                         (cursor == 3) ? SETTINGS_PAGE : 
                         EXIT_GAME;
                return;
            case KEY_UP: case KEY_W: case 'w':
                cursor = (cursor == 0) ? 4 : cursor - 1;
                if (enableSFX) playSound(2);
                break;
            case KEY_DOWN: case KEY_S: case 's':
                cursor = (cursor == 4) ? 0 : cursor + 1;
                if (enableSFX) playSound(2);
                break;
        }
    }
}

void Pause(int ms) {

	if(autoPause == 1) {
		system("pause");
	} else {
		
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	}
}

void showProgressBar(int total, int consoleWidth) {
    const int barWidth = 50; // Width of the progress bar
    int padding = (consoleWidth - barWidth - 4) / 2; // Centering spaces

    //std::cout << "\033[1;0m"; // Set green color

    for (int i = 0; i <= total; ++i) {
        int pos = (i * barWidth) / total;

        std::cout << "\r" << std::string(padding, ' ') << "[";
        for (int j = 0; j < barWidth; ++j) {
            std::cout << (j < pos ? "█" : "░");
        }
        std::cout << "] " << i << "% " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Hide cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Show cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

string getSlotValue(int position) {
	string output = "";
	
    if (snakes.find(position) != snakes.end()) 
	{
		output = string(" ") + SYMBOL_COLORS[0] + "S" + displayBoardColor;
		return output;
	}
	
	if(powerups.find(position) != powerups.end()) {
		if(position < 10)
			return SYMBOL_COLORS[3] + "?"; 
		else return string(" ") + SYMBOL_COLORS[3] + "?";
	}
	
	for(auto sn : snakes) {
		if(sn.second == position) {
			if(position < 10)
				return SYMBOL_COLORS[1] + "T";
			else
				return string(" ") + SYMBOL_COLORS[0] + "T";
		}
	}
	
    if (ladders.find(position) != ladders.end()) {
    	if(position < 10)
			return SYMBOL_COLORS[2] + "L"; 
		else return string(" ") + SYMBOL_COLORS[2] + "L";
	}
    return to_string(position); 
}

void FillRemainingPlayers() {
	int size = Player.size();
	for(int i = size; i <= MAX_PLAYERS-1; i++) {
		Player.push_back({"", -1, "30", false, false, false, false});
	}
}

void addComputer(int count) {
	string assignedColor;
	for (const string& color : availableColors) {
        bool isUsed = false;
        for (const playa& p : Player) {
            if (p.color.compare(color) == 0) {
                isUsed = true;
                break;
            }
        }
        
        if (!isUsed) {
            assignedColor = color;
            break;
        }
    }
	//									completed snakeShield Shield isAI
	string name = "Computer " + to_string(count);
	numOfPlayers++;
	Player.push_back({name, START_NUMBER, assignedColor, false, false, false, true});	
}

void displayLegend() {
	
	vector<playa> sortedPlayers = Player; 
    sort(sortedPlayers.begin(), sortedPlayers.end(), [](const playa &a, const playa &b) {
        return a.position > b.position; 
    });
    int width = getConsoleWidth();
    string center = "";
    for(int i = 1; i <= (width - 63) / 2; i++)
    	center += " ";
    	
    	
    cout << center << "Legend" << "     " << "Special Tiles   [M] BGM    [ESC] Return to Main Menu" << endl;                                   
    center = "";
    for(int i = 1; i <= (width - 82) / 2; i++)
    	center += " ";
    cout <<  center << BORDER_COLOR << "██████████████████████████████████████████████████████████████████████████████████" << RESET << endl;
    
    string TWELVE = "            ";

    int maxRows = max(6, (int)sortedPlayers.size());

    for (int i = 0; i < maxRows; i++) {
        cout << center << BORDER_COLOR << "█";

        if (i < sortedPlayers.size()) {
            string positionStr = "(" + to_string(sortedPlayers[i].position) + ")";
            int posWidth = positionStr.length();  // Get the width of the position (3 for 100)
            cout << RESET << sortedPlayers[i].color
                 << setw(20) << sortedPlayers[i].name << " : " << PLAYER_SYMBOL << " "	
                 << setw(6 - posWidth) << "" << positionStr << RESET;  // Adjust width dynamically
        } else {
            cout << RESET << setw(31) << " ";
        }

        cout << RESET << "          " << setw(12) << BORDER_COLOR << "█";

        if (i == 0) cout << RESET << SYMBOL_COLORS[0] << setw(18) << " S : Snake                " << RESET;    
		else if (i == 1) cout << RESET << SYMBOL_COLORS[1] << setw(18) << " T : Tail                 " << RESET;
		else if (i == 2) cout << RESET << SYMBOL_COLORS[2] << setw(18) << " L : Ladder               " << RESET;
        else if (i == 3) cout << RESET << SYMBOL_COLORS[3] << setw(18) << " ? : Power-Up             " << RESET;
        else if(i == 4) cout << RESET << setw(14) << "Playing now: " << Player[turnToPlay].color << setw(12) << Player[turnToPlay].name << RESET;
        else if(i == 5) {
        	int nextPlayerIndex = turnToPlay;
            int attempts = numOfPlayers;
            
            do {
                nextPlayerIndex = (nextPlayerIndex + 1) % numOfPlayers;
                attempts--;
            } while (Player[nextPlayerIndex].completed && attempts > 0);
            
			cout << RESET << setw(14) << "Next Turn: ";
            if (!Player[nextPlayerIndex].completed) {
                cout << Player[nextPlayerIndex].color << 
             		setw(12) << Player[nextPlayerIndex].name << RESET;
            } else {
                cout << RESET << setw(12) << "Next Turn: -" << RESET ;
            }
		}
        else cout << setw(17) << "                          ";
		cout << RESET << TWELVE << BORDER_COLOR << "█" << RESET << endl;
    }

    cout << center << BORDER_COLOR << "██████████████████████████████████████████████████████████████████████████████████" << RESET << endl << endl;
}


void displayBoard() {
	
	//displayLegend();
	//START OF BOARD
    int number = 100;
    bool alternate = true;
    bool colorSwap = true;
    
    int width = getConsoleWidth();
    string center = "";
    for(int i = 1; i <= (width - 82) / 2; i++)
    	center += " ";

	hideCursor();
	cout << "\033[s";
	cout << center;
    for(int s = 0; s < 10; s++) 
	{
    	if(s==8)
        	cout << BORDER_COLOR << "██████████";
        else
        	cout << BORDER_COLOR << "████████";
    }
    cout << endl;
    
    for (int i = 0; i < 10; i++) 
	{
		int savedSlotNumbers[10];
    	cout << RESET << center;
        if (alternate) 
		{
            for (int h = 0; h < 10; h++) 
			{
                if(h == 0) 
				{
                	displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
						
					savedSlotNumbers[h] = number;
						
					if(number < 10)
						cout << BORDER_COLOR << "█" << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " <<  RESET;
					else if(number == 100)
						cout << BORDER_COLOR << "█" << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " << RESET;				
					else
						cout << BORDER_COLOR << "█" << displayBoardColor << "   " << getSlotValue(number--) << displayBoardColor << "   " << RESET;				
						
					colorSwap = !colorSwap;
            	}
            	else if(h==9) 
				{
            		displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
						
					savedSlotNumbers[h] = number;
					
					if(number < 10)
						cout << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " << RESET << BORDER_COLOR << "█" << RESET;
					else if(number == 100)
						cout << "█" << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " << RESET << BORDER_COLOR << "█" << RESET;				
					else
						cout << displayBoardColor << "   " << getSlotValue(number--) << displayBoardColor << "   " << RESET << BORDER_COLOR << "█" << RESET;				
						
					colorSwap = !colorSwap;
				}
                else 
				{
                	displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
                	
                	savedSlotNumbers[h] = number;
                	
            		if(number == 100) 
            			cout << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << " " << RESET;
            		else
						cout << displayBoardColor << "   " << getSlotValue(number--) << displayBoardColor << "   " << RESET;
						
					colorSwap = !colorSwap;
            	}
        	}
        	alternate = false;
        }
		else 
		{
			int start = number - 9;
            for (int h = 0; h < 10; h++) 
			{
                if(h == 0) 
				{
                	displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
                	savedSlotNumbers[h] = start + h;
                		
                	if(start+h < 10 && start+h != 10) 
					{
                		cout << BORDER_COLOR << "█" << displayBoardColor << "    " << getSlotValue(start+h) << displayBoardColor << "   " << RESET;
					}
					else 
					{
						cout << BORDER_COLOR << "█" << displayBoardColor << "   " << getSlotValue(start+h) << displayBoardColor << "   " << RESET;
					}
                	colorSwap = !colorSwap;
				}
				else if(h == 9) {
					displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
					savedSlotNumbers[h] = start + h;
                		
                	if(start+h < 10 && start+h != 10) 
					{
                		cout << displayBoardColor << "    " << getSlotValue(start+h) << displayBoardColor << "   " << RESET << BORDER_COLOR << "█" << RESET;
					}
					else 
					{
						cout  << displayBoardColor << "   " << getSlotValue(start+h) << displayBoardColor << "   " << RESET << BORDER_COLOR << "█" << RESET;
					}
                	colorSwap = !colorSwap;
				}
				else {
                	displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
                	savedSlotNumbers[h] = start + h;
                		
                	if(start+h < 10 && start+h != 10)
                		cout << displayBoardColor << "    " << getSlotValue(start+h) << displayBoardColor << "   " << RESET;	
                	else
                		cout << displayBoardColor << "   " << getSlotValue(start+h) << displayBoardColor << "   " << RESET;	
                		
                	colorSwap = !colorSwap;
				}
					
			
            }
            
            number -= 10;
            alternate = true;
	    }
        colorSwap = !colorSwap;
        cout << endl;
        
        
        cout << center;

		bool paddingColorSwap = !colorSwap;
		string BEFORE_NUMBER_TEXT = "";
		string AFTER_NUMBER_TEXT = "";
		string num_text;
		int count = 0;
		
		
		map<int, vector<pair<int, string>>> slotPlayers;
	    for (size_t i = 0; i < Player.size(); i++) {
	        slotPlayers[Player[i].position].push_back({i, Player[i].color});
	    }
		int usingcolor=0;
		for (int h = 0; h < 10; h++) {
		    num_text = "";
		    if (paddingColorSwap)
		    {			
		        displayBoardColor = alt_color[0];
		        usingcolor=0;
			}
		    else{
		    	displayBoardColor = alt_color[1];
				usingcolor=1;	
			}
		
		    int slotNum = savedSlotNumbers[h];
		
		    size_t numPlayers = slotPlayers[slotNum].size();
		    for (size_t i = 0; i < 3; i++) {
		        if (i < numPlayers)
		            num_text += displayBoardColor + slotPlayers[slotNum][i].second + PLAYER_SYMBOL + displayBoardColor + " " + RESET;
		        else
		            num_text += displayBoardColor + "  ";  
		    }
		
		   
		    if (h == 0) {
		        BEFORE_NUMBER_TEXT = RESET + BORDER_COLOR + "█" + displayBoardColor + " ";
		        AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET;
		    } else if (h == 9) {
		        BEFORE_NUMBER_TEXT = displayBoardColor + " ";
		        AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET + BORDER_COLOR + "█" + RESET;
		    } else {
		        BEFORE_NUMBER_TEXT = displayBoardColor + " ";
		        AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET;
		    }
		
		    cout << BEFORE_NUMBER_TEXT << num_text << AFTER_NUMBER_TEXT;
		    paddingColorSwap = !paddingColorSwap;
		}
		cout << endl;
		
		
		bool secondRowNeeded = false;
		for (auto &pair : slotPlayers) {
		    if (pair.second.size() > 3) {
		        secondRowNeeded = true;
		        break;
		    }
		}
		
		
	    cout << center;
	    for (int h = 0; h < 10; h++) {
	        num_text = "";
	        if (paddingColorSwap)
		    {			
		        displayBoardColor = alt_color[0];
		        usingcolor=0;
			}
		    else{
		    	displayBoardColor = alt_color[1];
				usingcolor=1;	
			}
	
	        int slotNum = savedSlotNumbers[h];
	        size_t numPlayers = slotPlayers[slotNum].size();
	
	        for (size_t i = 3; i < 6; i++) {  
	            if (i < numPlayers)
	                num_text += displayBoardColor + slotPlayers[slotNum][i].second + PLAYER_SYMBOL + displayBoardColor + " " + RESET;
	            else
	                num_text += displayBoardColor + "  "; 
	        }
	
	        
	        if (h == 0) {
	            BEFORE_NUMBER_TEXT = BORDER_COLOR + "█" + displayBoardColor + " ";
	            AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET;
	        } else if (h == 9) {
	            BEFORE_NUMBER_TEXT = displayBoardColor + " ";
	            AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET + BORDER_COLOR + "█" + RESET;
	        } else {
	            BEFORE_NUMBER_TEXT = displayBoardColor + " ";
	            AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET;
	        }
	
	        cout << BEFORE_NUMBER_TEXT << num_text << AFTER_NUMBER_TEXT;
	        paddingColorSwap = !paddingColorSwap;
	    }
	    cout << endl;
        
	    if(i == 9) {
	    	cout << center;
	        for(int s = 0; s < 10; s++) {
	        	if(s==8)
	            	cout << BORDER_COLOR << "██████████";
	            else
	            	cout << BORDER_COLOR << "████████";
	        }
		}
    }
    cout << RESET << endl;
}

void setConsoleSize(int width, int height) {
    // Get the console window handle
    HWND console = GetConsoleWindow();

    // Set window position & size
    MoveWindow(console, 100, 100, width, height, TRUE);

    // Set the buffer size to match the window size
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 100, 30 };  // Width x Height (adjust if needed)
    SetConsoleScreenBufferSize(hOut, bufferSize);
}

//------------------------------------------------------------------------
