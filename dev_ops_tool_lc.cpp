#include <iostream>
#include <fstream>       // File operations.
#include <string>          // String manipulation.
#include <vector>         // Dynamic arrays. 
#include <cstdlib>        // System calls.
#include <windows.h> // Windows API for system details. 
#include <sstream>       // String stream for dynamic JSON string creation..  

using namespace std;


static void fetchSystemDetails() {
	// Memory status.
	MEMORYSTATUSEX memoryStatus;
	memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	if (GlobalMemoryStatusEx(&memoryStatus)) {
		std:wcout << "" << endl;
		std::wcout << L"Memory Usage: " << memoryStatus.dwMemoryLoad << L"%" << "\n" << std::endl;

		std::wcout << L"Total Physical Memory: " << memoryStatus.ullTotalPhys / (1024 * 1024) << L" MB" << std::endl;
	}
	else {
		std::wcerr << L"Failed to get memory status." << std::endl;
	}

	// Fetch CPU details.
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	std::cout << "  Number of Processors: " << sysInfo.dwNumberOfProcessors << "\n";

	// Disk space.
	ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
	if (GetDiskFreeSpaceEx(L"C:\\", &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
		std::wcout << L"  Total Disk Space " << totalBytes.QuadPart / (1024 * 1024 * 1024) << " GB\n";
		std::wcout << L"  Free Disk Space: " << totalFreeBytes.QuadPart / (1024 * 1024 * 1024) << " GB\n";
	}
	else {
		std::wcerr << L"Failed to get disk space details." << std::endl;
	}
}



void simulateIaC() {
	std::string resourceName = "web-server";
	int cpuCores = 2;
	// In MB.
	int memorySize = 4096;
	std::string region = "us-east-1";

	// Generate JSON configuration.
	std::stringstream jsonConfig;
	jsonConfig << "{\n";
	jsonConfig << "  \"resource\":  \"" << resourceName << "\",\n";
	jsonConfig << "  \"cpu\": " << cpuCores << ",\n";
	jsonConfig << "  \"memory\": " << memorySize << ",\n";
	jsonConfig << "  \"region\": \"" << region << "\"\n";
	jsonConfig << "}";

	// Output the configuration.
	std::cout << "" << endl;
	std::cout << "Generated IaC Configuration: \n";
	std::cout << jsonConfig.str() << "\n";

	// Simulate "applying" the configuration.
	std::cout << "" << endl;
	std::cout << "Applying configuration...\n";
	// Simulate delay.
	Sleep(2000);
	std::cout << "" << endl;
	std::cout << "Infrastructure deployed successfully.\n";
	std::cout << "" << endl;
}

// Log all actions to a file for review.
void logAction(const std::string& action) {
	std::ofstream logFile("DevOpsTool.log", std::ios::app);
	if (logFile.is_open()) {
		logFile << action << "\n";
		logFile.close();
	}
	else {
		std:cerr << "Error: Unable to open log file.\n";
	}
}

// Combine everything into the main() function to create a cohesive program.
int main() {
	cout << "Welcome to the DevOps Infrastructure Monitoring Tool\n";
	cout << "=====================================================";
	cout << "" << endl;

	// Log start of program.
	logAction("Program started: ");

	// Call the static function and fetch system details.
	fetchSystemDetails();
	logAction("System details fetched.");

	// Simulate IaC.
	simulateIaC();
	logAction("IaC simulation completed.");

	// End of program.
	logAction("Program ended.");
	cout << "----------------------------------------------\n";
	cout << " **  All actions logged to DevOpTool.log\n";

	return 0;
}