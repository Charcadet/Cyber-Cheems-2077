// Cyber-cheems 2077
#include <Windows.h>
#include <iostream>
#include <Psapi.h>
#include <stdlib.h>
#include "color.hpp"


int menuChoice;
DWORD cdPID;
double currCoins;
double newCoins = 0.00;
double writeCoins = currCoins + newCoins;

uintptr_t firstAddr;
uintptr_t secondAddr;
uintptr_t thirdAddr;
uintptr_t fourthAddr;
uintptr_t fifthAddr;
uintptr_t sixthAddr;

uintptr_t GetBaseAddress( const HANDLE hProcess )
{
	if ( hProcess == NULL )
		return NULL;

	HMODULE lphModule[ 1024 ];
	DWORD lpcbNeeded( NULL );

	if ( !EnumProcessModules( hProcess, lphModule, sizeof( lphModule ), &lpcbNeeded ) )
		return NULL;

	TCHAR szModName[ MAX_PATH ];
	if ( !GetModuleFileNameEx( hProcess, lphModule[ 0 ], szModName, sizeof( szModName ) / sizeof( TCHAR ) ) )
		return NULL;

	return ( uintptr_t )lphModule[ 0 ];
}

void MainMenu( HANDLE pHandle )
{
	system( "CLS" );
	std::cout << dye::light_red( R"(
   _______     __                          ________                            
  / ______\ __/ /_  ___  _____            / ____/ /_  ___  ___  ____ ___  _____
 / /   / / / / __ \/ _ \/ ___/  ______   / /   / __ \/ _ \/ _ \/ __ `__ \/ ___/
/ /___/ /_/ / /_/ /  __/ /     /_____/  / /___/ / / /  __/  __/ / / / / (__  ) 
\____/\__, /_.___/\___/_/               \____/_/ /_/\___/\___/_/ /_/ /_/____/  
     /____/                                           2077 | Made by Ricozyx   

)" ) << '\n';
	ReadProcessMemory( pHandle, LPCVOID( sixthAddr + 0xB0 ), &currCoins, sizeof( currCoins ), nullptr );
	std::cout << dye::white_on_blue( "\n[MAIN-MENU]\n" );
	std::cout << dye::light_blue( "Please choose what you'd like to do:\n" );
	std::cout << dye::light_blue( "[1] - Add to your current coin amount.\n" );
	std::cout << dye::light_blue( "[2] - Change total amount of coins.\n" );
	std::cout << dye::light_blue( "Select option: " );
	std::cin >> menuChoice;
}

void CoinAdder( HANDLE pHandle )
{
	std::cout << dye::white_on_yellow( "[INFO]" ) << dye::yellow( " You currently have: " ) << dye::yellow( currCoins ) << dye::yellow( " Dogecoins." ) << std::endl << std::endl;
	std::cout << dye::yellow( "Enter how much Dogecoins you wanna add: " ) << std::endl;
	std::cin >> newCoins;
	writeCoins = newCoins + currCoins;
	WriteProcessMemory( pHandle, LPVOID( sixthAddr + 0xB0 ), &writeCoins, sizeof( writeCoins ), nullptr );
	Sleep( 300 );
	std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " You now have: " ) << dye::light_green( writeCoins ) << dye::light_green( " Dogecoins." ) << std::endl;
	ReadProcessMemory( pHandle, LPCVOID( sixthAddr + 0xB0 ), &currCoins, sizeof( currCoins ), nullptr );
	Sleep( 3500 );
	MainMenu( pHandle );
}

void CoinChanger( HANDLE pHandle )
{
	std::cout << dye::yellow( "Enter how much Dogecoins you'd like: " ) << std::endl;
	std::cin >> newCoins;
	WriteProcessMemory( pHandle, LPVOID( sixthAddr + 0xB0 ), &newCoins, sizeof( newCoins ), nullptr );
	Sleep( 300 );
	std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " You now have: " ) << dye::light_green( newCoins ) << dye::light_green( " Dogecoins." ) << std::endl;
	ReadProcessMemory( pHandle, LPCVOID( sixthAddr + 0xB0 ), &currCoins, sizeof( currCoins ), nullptr );
	Sleep( 3500 );
	MainMenu( pHandle );
}

int main( )
{
	HWND cyberDogeProcess = FindWindow( NULL, L"MemRun" );
	if ( cyberDogeProcess == NULL )
	{
		SetConsoleTitle( L"[ERROR] Cyber-Cheems 2077" );
		std::cout << dye::black_on_red( "[ERROR]" ) << dye::light_red( " Cyber-doge 2077 is not running." ) << std::endl;
		Sleep( 5000 );
		exit( -1 );
	}
	else if ( cyberDogeProcess != NULL )
	{
		SetConsoleTitle( L"Cyber-Cheems 2077 | By Ricozyx" );
		std::cout << dye::light_red( R"(
   _______     __                          ________                            
  / ______\ __/ /_  ___  _____            / ____/ /_  ___  ___  ____ ___  _____
 / /   / / / / __ \/ _ \/ ___/  ______   / /   / __ \/ _ \/ _ \/ __ `__ \/ ___/
/ /___/ /_/ / /_/ /  __/ /     /_____/  / /___/ / / /  __/  __/ / / / / (__  ) 
\____/\__, /_.___/\___/_/               \____/_/ /_/\___/\___/_/ /_/ /_/____/  
     /____/                                           2077 | Made by Ricozyx   

)" ) << '\n';
		Sleep( 1500 ); // Waiting a second so all the stuff doesn't explode into the end-users face

		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Found the process." ) << std::endl;
		GetWindowThreadProcessId( cyberDogeProcess, &cdPID ); // Gets the PID so we can open a handle to it.
		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Got the Process ID." ) << std::endl;
		Sleep( 100 );
		HANDLE pHandle = OpenProcess( PROCESS_ALL_ACCESS, false, cdPID );
		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Opened a handle to the process." ) << std::endl;
		Sleep( 100 );
		uintptr_t cd2077BaseAddr = GetBaseAddress( pHandle );
		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Found base address of CD2077: " ) << dye::light_green( cd2077BaseAddr ) << std::endl; // TODO: Change to hex

		ReadProcessMemory( pHandle, LPCVOID( cd2077BaseAddr + 0x01B3ED10 ), &firstAddr, sizeof( firstAddr ), nullptr );
		ReadProcessMemory( pHandle, LPCVOID( firstAddr + 0xE8 ), &secondAddr, sizeof( secondAddr ), nullptr );
		ReadProcessMemory( pHandle, LPCVOID( secondAddr + 0x110 ), &thirdAddr, sizeof( thirdAddr ), nullptr );
		ReadProcessMemory( pHandle, LPCVOID( thirdAddr + 0x8 ), &fourthAddr, sizeof( fourthAddr ), nullptr );
		ReadProcessMemory( pHandle, LPCVOID( fourthAddr + 0x50 ), &fifthAddr, sizeof( fifthAddr ), nullptr );
		ReadProcessMemory( pHandle, LPCVOID( fifthAddr + 0x20 ), &sixthAddr, sizeof( sixthAddr ), nullptr );
		ReadProcessMemory( pHandle, LPCVOID( sixthAddr + 0xB0 ), &currCoins, sizeof( currCoins ), nullptr ); // Found the address by using ReClass & CE7.2

		std::cout << dye::white_on_yellow( "[INFO]" ) << dye::yellow( " You currently have: " ) << dye::yellow( currCoins ) << dye::yellow( " Dogecoins." ) << std::endl << std::endl;


		std::cout << dye::white_on_blue( "\n[MAIN-MENU]\n" );
		std::cout << dye::light_blue( "Please choose what you'd like to do:\n" );
		std::cout << dye::light_blue( "[1] - Add to your current coin amount.\n" );
		std::cout << dye::light_blue( "[2] - Change total amount of coins.\n" );
		std::cout << dye::light_blue( "Select option: " );
		std::cin >> menuChoice;
	menu:
		switch ( menuChoice )
		{
		case 1:
			CoinAdder( pHandle );
			goto menu;
		case 2:
			CoinChanger( pHandle );
			goto menu;
		default:
			MainMenu( pHandle );
			goto menu;
		}
	}
}
