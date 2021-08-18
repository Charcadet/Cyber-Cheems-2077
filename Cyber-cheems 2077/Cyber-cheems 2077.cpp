// Cyber-cheems 2077
#include <Windows.h>
#include <iostream>
#include <Psapi.h>
#include <stdlib.h>
#include "color.hpp"

DWORD cdPID;
double curDogecoins;

uintptr_t GetBaseAddress( const HANDLE hProcess )
{
	if ( hProcess == NULL )
		return NULL; // No access to the process

	HMODULE lphModule[ 1024 ]; // Array that receives the list of module handles
	DWORD lpcbNeeded( NULL );  // Output of EnumProcessModules, giving the number of bytes requires to store all modules handles in the lphModule array

	if ( !EnumProcessModules( hProcess, lphModule, sizeof( lphModule ), &lpcbNeeded ) )
		return NULL; // Impossible to read modules

	TCHAR szModName[ MAX_PATH ];
	if ( !GetModuleFileNameEx( hProcess, lphModule[ 0 ], szModName, sizeof( szModName ) / sizeof( TCHAR ) ) )
		return NULL; // Impossible to get module info

	return ( uintptr_t )lphModule[ 0 ]; // Module 0 is apparently always the EXE itself, returning its address
}


int main( )
{
	HWND cyberDogeProcess = FindWindow( NULL, L"MemRun" );
	if ( cyberDogeProcess == NULL )
	{
		std::cout << dye::black_on_red( "[ERROR]" ) << dye::light_red( " Cyber-doge 2077 is not running." ) << std::endl;
		Sleep( 5000 );
		exit( -1 );
	}
	else if ( cyberDogeProcess != NULL )
	{
		std::cout << R"(   ______      __                          ________                            
  / ______  __/ /_  ___  _____            / ____/ /_  ___  ___  ____ ___  _____
 / /   / / / / __ \/ _ \/ ___/  ______   / /   / __ \/ _ \/ _ \/ __ `__ \/ ___/
/ /___/ /_/ / /_/ /  __/ /     /_____/  / /___/ / / /  __/  __/ / / / / (__  ) 
\____/\__, /_.___/\___/_/               \____/_/ /_/\___/\___/_/ /_/ /_/____/  
     /____/                                           2077 | Made by Ricozyx          

)" << '\n';
		Sleep( 1000 ); // Waiting a second so all the stuff doesn't explode into the end-users face

		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Found the process." ) << std::endl;
		GetWindowThreadProcessId( cyberDogeProcess, &cdPID );
		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Got the Process ID." ) << std::endl;
		Sleep( 100 );
		HANDLE pHandle = OpenProcess( PROCESS_ALL_ACCESS, false, cdPID );
		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Opened a handle to the process." ) << std::endl;
		Sleep( 100 );
		uintptr_t cd2077BaseAddr = GetBaseAddress( pHandle );

		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " Found base address of CD2077: " ) << dye::light_green( cd2077BaseAddr ) << std::endl; // TODO: Change to hex
		uintptr_t firstAddr;
		ReadProcessMemory( pHandle, LPCVOID( cd2077BaseAddr + 0x01B3ED10 ), &firstAddr, sizeof( firstAddr ), nullptr );
		uintptr_t secondAddr;
		ReadProcessMemory( pHandle, LPCVOID( firstAddr + 0xE8 ), &secondAddr, sizeof( secondAddr ), nullptr );
		uintptr_t thirdAddr;
		ReadProcessMemory( pHandle, LPCVOID( secondAddr + 0x110 ), &thirdAddr, sizeof( thirdAddr ), nullptr );
		uintptr_t fourthAddr;
		ReadProcessMemory( pHandle, LPCVOID( thirdAddr + 0x8 ), &fourthAddr, sizeof( fourthAddr ), nullptr );
		uintptr_t fifthAddr;
		ReadProcessMemory( pHandle, LPCVOID( fourthAddr + 0x50 ), &fifthAddr, sizeof( fifthAddr ), nullptr );
		uintptr_t sixthAddr;
		ReadProcessMemory( pHandle, LPCVOID( fifthAddr + 0x20 ), &sixthAddr, sizeof( sixthAddr ), nullptr );
		ReadProcessMemory( pHandle, LPCVOID( sixthAddr + 0xB0 ), &curDogecoins, sizeof( curDogecoins ), nullptr );
		std::cout << dye::yellow( "You currently have: " ) << dye::yellow( curDogecoins ) << dye::yellow( " Dogecoins." ) << std::endl;
		double newCoins = 0.00;
		std::cout << dye::yellow( "Enter how much Dogecoins you'd like: " ) << std::endl;
		std::cin >> newCoins;
		WriteProcessMemory( pHandle, LPVOID( sixthAddr + 0xB0 ), &newCoins, sizeof( newCoins ), nullptr );
		Sleep( 300 );
		std::cout << dye::white_on_green( "[SUCCESS]" ) << dye::light_green( " You now have: " ) << dye::light_green( newCoins ) << dye::light_green( " Dogecoins." ) << std::endl;
		Sleep( 2000 );
	}
}
