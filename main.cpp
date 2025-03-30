#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <windows.h>
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


#define SPACE "                      "
#define SPACE2 "       "
#define SPACE1 "  "

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

string FOREGROUND = "37";
string BACKGROUND = "40";
string RESET = "\033[" + FOREGROUND + ";" + BACKGROUND + "m";
string BORDER_COLOR = "37";
			// WHITE BG BLACK TEXT         // BRIGHT RED BG BLACK TEXT
	
// SA BOARD SETTINGS NI		
string BOARD_BACKGROUND[] = {"106", "103"};
string alt_color[] = {"\033[" + string("30") + ";" + BOARD_BACKGROUND[0] + "m", "\033[" + string("30") + ";"+ BOARD_BACKGROUND[1] + "m"};
string SYMBOL_COLORS[] = {"31", "33", "32", "36"}; // Snake Tail Ladder Special(POWERUP)

string TEXT_COLOR = "30";

// MENU HIGHLIGHT
string HIGHLIGHT = "\033[103;30m";

//[-------------------------------VARIABLES-------------------------------]
const int MAX_PLAYERS = 6;
int numOfPlayers = 0;
int turnToPlay = -1;

struct playa {
	string name = "";
	int position = -1;
	string color;
	int completed = 0;
};

string boardColor = "0";
string backgroundColor = "0"; 
string displayBoardColor;
string colo = "color ";
string finalCombined = colo + backgroundColor + boardColor;
const char *charColor = finalCombined.c_str();

int enableLoading = 0;
int enableSFX = 1;
int autoPause = 0;
int enableAnimations = 1;

int name_position = 1;
int color_position = 1;
int selectingPlayer = -1;

unordered_map<int, int> snakes = {
    {99, 7},  {56, 15}, {47, 20}, {88, 24}, {94, 45}, 
    {78, 37}, {82, 59}, {67, 29}, {35, 5},  {14, 4},  
    {19, 8},  {23, 3},  {31, 9}  // 🐍 More early-game snakes!
};

unordered_map<int, int> ladders = {
    {3, 22},  {6, 25},  {11, 40}, {60, 85}, {17, 33}, 
    {27, 50}, {44, 66}, {53, 74}, {63, 81}, {72, 91}
};

unordered_set<int> powerups = {
    5, 12, 19, 26, 39, 48, 58, 69, 72, 89
};

vector<string> availableColors = {
    "31",
    "32", 
    "33", 
    "34", 
    "35", 
    "36", 
    "37", 
    "91",
    "92",
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
	SELECT_PLAYER_COLOR,
};

enum stat_list STATUS = MAINMENU;

vector<playa> Player;


//[--------------------------FUNCTION PROTOTYPES--------------------------]
void displayBoard();
void LogoArt();
void setConsoleSize(int width, int height);
void ShowMainMenu();
int getConsoleWidth();
void SelectPlayers();
void HowToPlay();
void displayMenuArt();
void Pause(int ms);
void AboutPage();
void showProgressBar(int total, int consoleWidth);
void EnterName();
void StartGame();
void SelectColors();
void SelectPlayerColor();
void ClearGame();
void displayLegend();
//------------------------------------------------------------------------

int main()
{
	HWND hwnd = GetConsoleWindow();
	if (hwnd) {
        
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);  
        SetWindowLong(hwnd, GWL_STYLE, style);
    }
	
	
	SetConsoleOutputCP(CP_UTF8);
	//system("chcp 65001 > nul");
	setConsoleSize(1200, 1200);
    cout << "\n\n" << RESET;
    
    system(charColor);
	
	system("cls");
	srand(time(0));
    
    if(enableLoading == 1) {
    	
    	string text = R"(
		███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗███████╗       ██╗       ██╗      █████╗ ██████╗ ██████╗ ███████╗██████╗ ███████╗
		██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝██╔════╝       ██║       ██║     ██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝
		███████╗██╔██╗ ██║███████║█████╔╝ █████╗  ███████╗    ████████╗    ██║     ███████║██║  ██║██║  ██║█████╗  ██████╔╝███████╗
		╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ╚════██║    ██╔═██╔═╝    ██║     ██╔══██║██║  ██║██║  ██║██╔══╝  ██╔══██╗╚════██║
		███████║██║ ╚████║██║  ██║██║  ██╗███████╗███████║    ██████║      ███████╗██║  ██║██████╔╝██████╔╝███████╗██║  ██║███████║
		╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝    ╚═════╝      ╚══════╝╚═╝  ╚═╝╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝
		)";
		
		istringstream stream(text);
	    string line;
	    while (getline(stream, line)) {
	        std::cout << SPACE2 << line << std::endl; 
	    }
    	
		int consoleWidth = getConsoleWidth(); // Get the console width
	    cout << "\n\n\n\n\n\n\n\n\n\n\n\n" SPACE SPACE "        LOADING GAME...\n"; 
	    showProgressBar(100, consoleWidth);
	}
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
		}
	}
    return 0;
}

//----------------------------FUNCTION DEFINITIONS-----------------------]

void EnterName() {
	int colorIndex = 0;
	for(int i = name_position; i <= numOfPlayers; i++) {
		system("cls");
		LogoArt();
		
		cout << endl << endl;
	 	cout << SPACE "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << endl;
	    cout << SPACE "█                   Please enter name for Player " << name_position << "             [0] Back  █" << endl;
	    cout << SPACE "█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << endl;
	    cout << SPACE "█                                                                        █" << endl;
	    cout << SPACE "█                                                                        █" << endl;
	    cout << SPACE "█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << endl;
	    cout << endl;
	    
	    int count = 1;
	    if(Player.size() > 0) {
	    	cout << SPACE SPACE2 "Player list:" << endl;
    		for(const playa& p : Player) {
    			cout << SPACE SPACE2 << count << ". " << p.name << endl;
    			count++;
			}
		}
	    
	    if(count == 1)
	    	cout << "\033[3A"; 
	    else
	    	cout << "\033[" + to_string(3+count) + "A";  
	    	
	    cout << "\033[46C"; 
		string names;
	    getline(cin >> ws, names);
	    if(names[0] == '0') {
	    	if(name_position == 1) {
	    		Player.pop_back();
	    		name_position = 0;
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
	    		cout << endl<<endl<< SPACE "The name is already taken! Please enter a different name.\n";
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
	
		
		Player.push_back({names, 1, assignedColor, 0});
		name_position++;
	}
	if(name_position == 0) {
		Player.clear();
		STATUS=SELECT_PLAYERS;
		return;
	}
	system("cls");
	LogoArt();
	name_position = 1;
	color_position = 1;
	STATUS = SELECT_COLORS;
}

void diceArt(int number) {
    const char* diceFaces[6][7] = {
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

    for (int i = 0; i < 7; ++i) {

    	//cout << "\033[7A"; // Move the cursor up 7 lines
        cout << SPACE SPACE2 << diceFaces[number - 1][i] << endl;
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

int revealFinalDice() {
    int finalNumber = rand() % 6 + 1;
    //cout << "\033[H\033[J";
    
    cout << SPACE SPACE2 "The dice rolled...\n";
    Pause(1000);
    diceArt(finalNumber);
    cout << SPACE SPACE2 "You rolled a " << finalNumber << "!" << endl;
    return finalNumber;
}

void StartGame() {
	turnToPlay = 1; // first Player
	while(true) {
		system("cls");
		LogoArt();
		displayLegend();
		cout << "\033[1A";
		cout << "\033[s";
		cout << "\n";
		displayBoard();
		
		int player = turnToPlay-1;
		
		cout << endl << SPACE SPACE2 << "\033[" << Player[player].color << "m" << Player[player].name << RESET << ", press Enter to roll the dice!" << endl << SPACE SPACE2;
		char input;
		int confirm=-1;
		while(1) {
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			input = _getch();
			input = tolower(input);
			if(input == KEY_ESC) {
				cout << "Do you want to return to main menu? (y/n)?: " << endl;
				char input2;
				while(1) {
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					input2 = _getch();
					input2 = tolower(input2);
					if(input2 == 'Y' || input2 == 'y') {
						confirm = 1;
						break;
					}
					else if(input2 == 'N' || input2 == 'n') {
						confirm = 0;
						break;	
					}
				
					continue;
				}
				if(confirm == 0) {
					cout << endl << SPACE SPACE2 << "\033[" << Player[player].color << "m" << Player[player].name << RESET << ", press Enter to roll the dice!" << endl << SPACE SPACE2;
					continue;
				}
			}
			
			if(confirm == 1)
				break;
			
			if(input == KEY_ENTER) {
				break;
			}
			
			
			continue;
		}
		
		if(confirm == 1)
		{
			STATUS = MAINMENU;
			cout << SPACE SPACE2 << "Returning to main menu... " << endl;
			ClearGame();
			Pause(800);
			return;
		}
		
		cout << "Rolling the dice...\n" << "\033[" << Player[player].color << "m";
		rollDiceAnimation();
		//Pause(800);
		cout << "\033[8A\033[J";
        int randomNum = revealFinalDice();
		
		cout << RESET;
	
		Pause(800);
		
		int start = 0;
		if(enableAnimations == 1)
		{
			cout << SPACE SPACE2 << "Press any key to start moving!";
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			_getch();
			
			int finalPos = Player[player].position + randomNum;
		
			while (Player[player].position < finalPos) {
		        Player[player].position++;
		        cout << "\033[u";
	            displayBoard();
		        fflush(stdout);
		        Pause(300);
		    }
				
			if (ladders.find(finalPos) != ladders.end()) {
		        int ladderEnd = ladders[finalPos]; 
		
		        cout << SPACE SPACE2 << "\033[" << Player[player].color << "m" << Player[player].name << RESET << ", has stepped on a \033[" << SYMBOL_COLORS[2] << "mLADDER! +" << ladderEnd - finalPos << RESET << ".";
		        _getch();
		        
		        while (Player[player].position < ladderEnd) {
		            Player[player].position += 2;  
		            if (Player[player].position > ladderEnd) {
		                Player[player].position = ladderEnd; 
		            }
		            cout << "\033[u";
		            displayBoard();
		            
		            fflush(stdout);
		            Pause(200); 
		        }
		    }
		    else if (snakes.find(finalPos) != snakes.end()) {
		        int snakeTail = snakes[finalPos]; 
		
		        
		        cout << SPACE SPACE2 << "\033[" << Player[player].color << "m" << Player[player].name << RESET << ", has stepped on a \033[" << SYMBOL_COLORS[0] << "mSNAKE! -" << snakeTail - finalPos << RESET << ".";
		        _getch();
		        
		        while (Player[player].position > snakeTail) {
		            Player[player].position -= 2;  
		            if (Player[player].position < snakeTail) {
		                Player[player].position = snakeTail; 
		            }
		            cout << "\033[u";
		            displayBoard();
		            fflush(stdout);
		            Pause(200);  
		        }
	    	}
	    	else if (powerups.find(Player[player].position) != powerups.end()) {
			    // Player landed on a power-up tile.
			    // Do nothing for now.
			}
		}
		else {
			Player[player].position += randomNum;
		}
		
		if(turnToPlay == numOfPlayers) {
			turnToPlay = 1;
			continue;
		}
		turnToPlay++;
	}
}

void SelectPlayerColor() {
	system("cls");
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
	    options[i] = "\033[" + storedColors[i] + "m●" + RESET; 
	}
		
    int cursor = 0;
	while(1) {
		system("cls");
		LogoArt();

		cout << SPACE SPACE SPACE1 "Choose available colors for " << Player[player].name << ":\n";
		for(int i = 0; i < sizedt+1; i++) {
			if(i == cursor)
				cout << HIGHLIGHT << SPACE SPACE SPACE2 << " > " << options[i]  << HIGHLIGHT << "\033[K" << RESET << endl;
			else
				cout << SPACE SPACE SPACE2 << RESET << options[i] << RESET << endl;
		}	
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char input = _getch();
		switch(input) {
			case KEY_ENTER: 
			{
				if(cursor == 0) {
					selectingPlayer = -1;
					STATUS=SELECT_COLORS;
					return;
				}
				else if(cursor >= 1 && cursor <= sizedt)
				{
					cout << SPACE SPACE SPACE1 << Player[player].name << ", Successfully changed color to: \033[" << storedColors[cursor] << "m●" << RESET << "!\n";

	                Player[player].color = storedColors[cursor]; // Assign selected color
	                Pause(800);
	
	                selectingPlayer = -1;
	                STATUS = SELECT_COLORS;
	                return;
				}
				break;
					
			}
			
			case KEY_UP: case KEY_W: {
				if(cursor == 0) {
					cursor = sizedt;
				}
				else cursor--;
				
				if(enableSFX)
					PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
			case KEY_DOWN: case 'S': 
			{
				if(cursor == sizedt) {
					cursor = 0;
				}
				else cursor++;
				
				if(enableSFX)
						PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
		}
	}
    
}

void SelectColors() {
	system("cls");
	LogoArt();
	
	cout << SPACE SPACE SPACE1 "Choose a color for each player:\n";
	
	int size = Player.size();
	string options[size+2];
	options[0] = "Back";
	options[1] = "Start Game";
	int count = 2;
	for(const playa& p : Player) {
		options[count] = p.name + " : " + "\033[" + p.color + "m●" + RESET;
		count++;
	}
	
	
	int cursor = 0;
	while(true) {
		system("cls");
		LogoArt();
		
		cout << SPACE SPACE SPACE1 "Choose a color for each player or Start the game:\n";
		for(int i = 0; i < size+2; i++) {
			if(i == cursor)
				cout << HIGHLIGHT << SPACE SPACE SPACE2 << " > " << options[i]  << HIGHLIGHT << "\033[K" << RESET << endl;
			else
				cout << SPACE SPACE SPACE2 << RESET << options[i] << RESET << endl;
		}
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char input = _getch();
		switch(input) {
			case KEY_ENTER: 
			{
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
			
			case KEY_UP: case KEY_W: {
				if(cursor == 0) {
					cursor = size+1;
				}
				else cursor--;
				
				if(enableSFX)
					PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
			case KEY_DOWN: case KEY_S: {
				if(cursor == size+1) {
					cursor = 0;
				}
				else cursor++;
				
				if(enableSFX)
						PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
		}
	}
}

void AboutPage() {
	system("cls");
	LogoArt();
	
	displayBoard();
	_getch();
}

void SelectPlayers() {
	system("cls");
	LogoArt();
	
	cout << SPACE SPACE2 "Select the number of players: \n\n";
	std::string options[] = {"Back", "1 Player", "2 Players", "3 Players", "4 Players", "5 Players", "6 Players"};
	int size = sizeof(options) / sizeof(options[0]);
	int cursor = 0;
	
	string SPACES = "                                                                             ";
	
	while(true) {
		system("cls");
		LogoArt();
		cout << SPACE SPACE2 "Select the number of players: \n\n";
		for(int i = 0; i < size; i++) {
			if(i == cursor)
				cout << HIGHLIGHT << SPACE SPACE SPACE2 << " > " << options[i]  << "\033[K" << RESET << endl;
			else
				cout << SPACE SPACE SPACE2 << options[i] << endl;
		}
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char input = _getch();
		switch(input) {
			case KEY_ENTER: {
				switch(cursor) {
					case 0: {
						STATUS=MAINMENU;
			
						if(enableSFX)
							PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
						return;
					}
					case 1 ... 6: {
						if(enableSFX)
							PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
						
						name_position = 1;
						numOfPlayers = cursor;
						STATUS=GAME_ENTERNAME;
						return;
					}
				}
				break;
			}
			
			case KEY_UP: case KEY_W: {
				if(cursor == 0) {
					cursor = size-1;
				}
				else cursor--;
				
				if(enableSFX)
					PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
			case KEY_DOWN: case KEY_S: {
				if(cursor == size-1) {
					cursor = 0;
				}
				else cursor++;
				
				if(enableSFX)
						PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
		}
	}	
}


void HowToPlay();
void displayMenuArt();


void HowToPlay() { //THIS IS DONE UNLESS THERE ARE CHANGES IN THE POWERUPS AND HOW THE GAMEPLAY CHANGES, WILL TWEAK IT IF THERE ARE ANY CHANGES
	system("cls");
	LogoArt();
    cout << SPACE SPACE2 "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << SPACE SPACE2 "                               🎲 SNAKE AND LADDER 🎲                      \n";
    cout << SPACE SPACE2 "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\n";

    cout << SPACE SPACE2 "Welcome to the exciting game of Snake and Ladder with Power-Ups!\n\n";

    cout << SPACE SPACE2 "📜 HOW TO PLAY: \n";
    cout << SPACE SPACE2 "1. Each player takes turns rolling the dice by pressing a key.\n";
    cout << SPACE SPACE2 "2. The number rolled on the dice determines how many spaces the player moves\n";
	cout << SPACE SPACE2 "   forward.\n";
    cout << SPACE SPACE2 "3. Landing on the bottom of a ladder (L) will instantly move you up to a higher\n"; 
	cout << SPACE SPACE2 "   space. Ladders are your friends!\n";
    cout << SPACE SPACE2 "4. Landing on the head of a snake (S) will send you sliding down to a lower space.\n";
	cout << SPACE SPACE2 "   Watch out for those sneaky snakes!\n";
    cout << SPACE SPACE2 "5. If you land on a Power-Up (?) space, a random effect will trigger, which can\n";
	cout << SPACE SPACE2 "   help or hinder your progress.\n";
    cout << SPACE SPACE2 "6. The first player to reach exactly square 100 wins the game. If the dice roll\n";
	cout << SPACE SPACE2 "   exceeds 100, you bounce back the extra spaces.\n\n";

    cout << SPACE SPACE2 "✨ LEGEND: \n";
    cout << SPACE SPACE2 "S = Snake (Move Down)\n";
    cout << SPACE SPACE2 "L = Ladder (Move Up)\n";
    cout << SPACE SPACE2 "? = Power-Up (Random Effect)\n";
    cout << SPACE SPACE2 "● = Player (Each dot color represents a different player)\n\n";

    cout << SPACE SPACE2 "🧿 POWER-UP EFFECTS: \n";
    cout << SPACE SPACE2 "- 🎲 Extra Turn: Roll the dice again and advance further.\n";
    cout << SPACE SPACE2 "- 🔄 Swap: Switch positions with a random player. This could give you a massive\n";
	cout << SPACE SPACE2 "          advantage or set you back!\n";
    cout << SPACE SPACE2 "- 🛡️ Shield: Protect yourself from the next snake you encounter.\n";
    cout << SPACE SPACE2 "- 🚀 Boost: Move forward a few extra spaces.\n";
    cout << SPACE SPACE2 "- ⏪ Reverse: Force another player to move backward.\n\n";

    cout << SPACE SPACE2 "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << SPACE SPACE2 "                             Press any key to return...        \n";
    cout << SPACE SPACE2 "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";

    _getch();
	STATUS = MAINMENU;
}

void displayMenuArt() { // ADDED THIS, ASCII ART ON TOP, THE CODE BREAKS IF I ADD IT IN THE SHOWMAINMENU
    string startGameText = R"(
		███████╗████████╗ █████╗ ██████╗ ████████╗     ██████╗  █████╗ ███╗   ███╗███████╗
		██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝
		███████╗   ██║   ███████║██████╔╝   ██║       ██║  ███╗███████║██╔████╔██║█████╗  
		╚════██║   ██║   ██╔══██║██╔══██╗   ██║       ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  
		███████║   ██║   ██║  ██║██║  ██║   ██║       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
		╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝        ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝
	)";

    string howToPlayText = R"(
		██╗  ██╗ ██████╗ ██╗    ██╗    ████████╗ ██████╗     ██████╗ ██╗      █████╗ ██╗   ██╗
		██║  ██║██╔═══██╗██║    ██║    ╚══██╔══╝██╔═══██╗    ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝
		███████║██║   ██║██║ █╗ ██║       ██║   ██║   ██║    ██████╔╝██║     ███████║ ╚████╔╝ 
		██╔══██║██║   ██║██║███╗██║       ██║   ██║   ██║    ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  
		██║  ██║╚██████╔╝╚███╔███╔╝       ██║   ╚██████╔╝    ██║     ███████╗██║  ██║   ██║   
		╚═╝  ╚═╝ ╚═════╝  ╚══╝╚══╝        ╚═╝    ╚═════╝     ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   
    )";

    string aboutText = R"(
		 █████╗ ██████╗  ██████╗ ██╗   ██╗████████╗
		██╔══██╗██╔══██╗██╔═══██╗██║   ██║╚══██╔══╝
		███████║██████╔╝██║   ██║██║   ██║   ██║   
		██╔══██║██╔══██╗██║   ██║██║   ██║   ██║   
		██║  ██║██████╔╝╚██████╔╝╚██████╔╝   ██║   
		╚═╝  ╚═╝╚═════╝  ╚═════╝  ╚═════╝    ╚═╝   
	)";

    cout << SPACE2 "Choose an Option:";

    istringstream startStream(startGameText);
    string line;
    while (getline(startStream, line)) {
        cout << SPACE2 << line << endl;
    }
    cout << endl;

    istringstream howToPlayStream(howToPlayText);
    while (getline(howToPlayStream, line)) {
        cout << SPACE2 << line << endl;
    }
    cout << endl;

    istringstream aboutStream(aboutText);
    while (getline(aboutStream, line)) {
        cout << SPACE2 << line << endl;
    }
    cout << endl;
}

void LogoArt() {
	string text = R"(
	███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗███████╗       ██╗       ██╗      █████╗ ██████╗ ██████╗ ███████╗██████╗ ███████╗
	██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝██╔════╝       ██║       ██║     ██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝
	███████╗██╔██╗ ██║███████║█████╔╝ █████╗  ███████╗    ████████╗    ██║     ███████║██║  ██║██║  ██║█████╗  ██████╔╝███████╗
	╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ╚════██║    ██╔═██╔═╝    ██║     ██╔══██║██║  ██║██║  ██║██╔══╝  ██╔══██╗╚════██║
	███████║██║ ╚████║██║  ██║██║  ██╗███████╗███████║    ██████║      ███████╗██║  ██║██████╔╝██████╔╝███████╗██║  ██║███████║
	╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝    ╚═════╝      ╚══════╝╚═╝  ╚═╝╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝
	)";
	
	istringstream stream(text);
    string line;
    while (getline(stream, line)) {
        std::cout << SPACE2 << line << std::endl; 
    }
    
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\n";
}

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80; // Default width
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return width;
}

void ShowMainMenu() {
	system("cls");
	LogoArt();
	
	std::string options[] = {"Start Game", "About", "How to Play"};
	int size = sizeof(options) / sizeof(options[0]);
	int cursor = 0;
	
	string SPACES = "                                                                             ";
	
	while(true) {
		system("cls");
		LogoArt();
		for(int i = 0; i < size; i++) {
			if(i == cursor)
				cout << HIGHLIGHT << SPACE SPACE SPACE2 << " > " << options[i]  << "\033[K" << RESET << endl;
			else
				cout << SPACE SPACE SPACE2 << options[i] << endl;
		}
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char input = _getch();
		switch(input) {
			case KEY_ENTER: {
				switch(cursor) {
					case 0: {
						if(enableSFX)
							PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
						STATUS=SELECT_PLAYERS;
						return;
					}
					case 1: {
						if(enableSFX)
							PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
						STATUS=ABOUT_PAGE;
						return;
					}
					case 2: {
						if(enableSFX)
							PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
						STATUS=HOW_TO_PLAY;
						return;
					}
				}
				break;
			}
			
			case KEY_UP: case KEY_W: {
				if(cursor == 0) {
					cursor = size-1;
				}
				else cursor--;
				
				if(enableSFX)
					PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
			case KEY_DOWN: case KEY_S: {
				if(cursor == size-1) {
					cursor = 0;
				}
				else cursor++;
				
				if(enableSFX)
					PlaySound(TEXT("resources/menu-sfx.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
				break;
			}
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

string getSlotValue(int position) {
	string output = "";
	
    if (snakes.find(position) != snakes.end()) 
	{
		output = string(" ") + "\033[" + SYMBOL_COLORS[0] + "m" + "S" + displayBoardColor;
		return output;
	}
	
	for(auto sn : snakes) {
		if(sn.second == position) {
			if(position < 10)
				return "\033[" + SYMBOL_COLORS[1] + "m" + "T";
			else
				return string(" ") + "\033[" + SYMBOL_COLORS[0] + "m" + "T";
		}
	}
	
    if (ladders.find(position) != ladders.end()) {
    	if(position < 10)
			return "\033[" + SYMBOL_COLORS[2] + "m" + "L"; 
		else return string(" ") + "\033[" + SYMBOL_COLORS[2] + "m" + "L";
	}
	
	if(powerups.find(position) != powerups.end()) {
		if(position < 10)
			return "\033[" + SYMBOL_COLORS[3] + "m" + "?"; 
		else return string(" ") + "\033[" + SYMBOL_COLORS[3] + "m" + "?";
	}
    return to_string(position); 
}

void FillRemainingPlayers() {
	int size = Player.size();
	for(int i = size; i <= MAX_PLAYERS-1; i++) {
		Player.push_back({"", -1, "30", 0});
	}
}

void displayLegend() {
	cout << SPACE SPACE2 "Legend" << SPACE << "Special Tiles" << SPACE << "[ESC] Return to Main Menu" << endl;
	cout << SPACE SPACE2 << "\033[" << BORDER_COLOR << "m▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << RESET << endl;
	
	
	int maxRows = max((int)Player.size(), 4); 
	
	
	for (int i = 0; i < maxRows; i++) {
	    cout << SPACE SPACE2 << "\033[" << BORDER_COLOR << "m█";
	    
	    
	    if (i < Player.size()) {
	        cout << "\033[" << Player[i].color << "m" << setw(20) << Player[i].name << " : " << "● (" << Player[i].position << ")" << RESET;
	    } else {
	        cout << setw(28) << "           ";  
	    }
	    
	    cout << setw(15) << "\033[" << BORDER_COLOR << "m█";  
	
	    
	    if (i == 0) cout << "\033[" << SYMBOL_COLORS[0] << "m" << setw(30) << " S : Snake      ";
	    else if (i == 1) cout << "\033[" << SYMBOL_COLORS[1] << "m" << setw(30) << " T : Tail       ";
	    else if (i == 2) cout << "\033[" << SYMBOL_COLORS[2] << "m" << setw(30) << " L : Ladder     ";
	    else if (i == 3) cout << "\033[" << SYMBOL_COLORS[3] << "m" << setw(30) << " ? : Power-Up   ";
	    else cout << setw(30) << "                ";  
	    
	    cout << "\033[" << BORDER_COLOR << "m" << setw(11) << "█" << RESET << endl;  
	}
	
	
	cout << SPACE SPACE2 << "\033[" << BORDER_COLOR << "m█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█" << RESET << endl << endl;
}

void displayBoard() {
	
	//displayLegend();
	
	
	//START OF BOARD
    int number = 100;
    bool alternate = true;
    
    bool colorSwap = true;

	cout << SPACE2 SPACE;
    for(int s = 0; s < 10; s++) 
	{
    	if(s==8)
        	cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "██████████";
        else
        	cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "████████";
    }
    
    //FillRemainingPlayers();
    
    cout << endl;
    for (int i = 0; i < 10; i++) 
	{
		int savedSlotNumbers[10];
    	cout << RESET << SPACE2 SPACE;
        if (alternate) 
		{
            for (int h = 0; h < 10; h++) 
			{
                if(h == 0) 
				{
                	displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
						
					savedSlotNumbers[h] = number;
						
					if(number < 10)
						cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " <<  RESET;
					else if(number == 100)
						cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " << RESET;				
					else
						cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << displayBoardColor << "   " << getSlotValue(number--) << displayBoardColor << "   " << RESET;				
						
					colorSwap = !colorSwap;
            	}
            	else if(h==9) 
				{
            		displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
						
					savedSlotNumbers[h] = number;
					
					if(number < 10)
						cout << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << RESET;
					else if(number == 100)
						cout << "█" << displayBoardColor << "  " << getSlotValue(number--) << displayBoardColor << "   " << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << RESET;				
					else
						cout << displayBoardColor << "   " << getSlotValue(number--) << displayBoardColor << "   " << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << RESET;				
						
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
                		cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << displayBoardColor << "    " << getSlotValue(start+h) << displayBoardColor << "   " << RESET;
					}
					else 
					{
						cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << displayBoardColor << "   " << getSlotValue(start+h) << displayBoardColor << "   " << RESET;
					}
                	colorSwap = !colorSwap;
				}
				else if(h == 9) {
					displayBoardColor = colorSwap ? alt_color[0] : alt_color[1];
					savedSlotNumbers[h] = start + h;
                		
                	if(start+h < 10 && start+h != 10) 
					{
                		cout << displayBoardColor << "    " << getSlotValue(start+h) << displayBoardColor << "   " << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << RESET;
					}
					else 
					{
						cout  << displayBoardColor << "   " << getSlotValue(start+h) << displayBoardColor << "   " << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "█" << RESET;
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
        
        
        cout << SPACE2 SPACE;

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
		            num_text += "\033[" + slotPlayers[slotNum][i].second + ";" + BOARD_BACKGROUND[usingcolor] + "m" + "●" + displayBoardColor + " " + RESET;
		        else
		            num_text += displayBoardColor + "  ";  
		    }
		
		   
		    if (h == 0) {
		        BEFORE_NUMBER_TEXT = "\033[" + BACKGROUND + ";" + BORDER_COLOR + "m" + "█" + displayBoardColor + " ";
		        AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET;
		    } else if (h == 9) {
		        BEFORE_NUMBER_TEXT = displayBoardColor + " ";
		        AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + "\033[" + BACKGROUND + ";" + BORDER_COLOR + "m" + "█" + RESET;
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
		
		
	    cout << SPACE2 SPACE;
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
	                num_text += "\033[" + slotPlayers[slotNum][i].second + ";" + BOARD_BACKGROUND[usingcolor] + "m" + "●" + displayBoardColor + " " + RESET;
	            else
	                num_text += displayBoardColor + "  "; 
	        }
	
	        
	        if (h == 0) {
	            BEFORE_NUMBER_TEXT = "\033[" + BACKGROUND + ";" + BORDER_COLOR + "m█" + displayBoardColor + " ";
	            AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET;
	        } else if (h == 9) {
	            BEFORE_NUMBER_TEXT = displayBoardColor + " ";
	            AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + "\033[" + BACKGROUND + ";" + BORDER_COLOR + "m█" + RESET;
	        } else {
	            BEFORE_NUMBER_TEXT = displayBoardColor + " ";
	            AFTER_NUMBER_TEXT = displayBoardColor + string(" ") + RESET;
	        }
	
	        cout << BEFORE_NUMBER_TEXT << num_text << AFTER_NUMBER_TEXT;
	        paddingColorSwap = !paddingColorSwap;
	    }
	    cout << endl;
        
	    if(i == 9) {
	    	cout << SPACE2 SPACE;
	        for(int s = 0; s < 10; s++) {
	        	if(s==8)
	            	cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "██████████";
	            else
	            	cout << "\033[" << BACKGROUND << ";" << BORDER_COLOR << "m" << "████████";
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
