#include "include.h"
#include "isAppearance.h"
#include "convert.h"
#include "Cursor.h"

using namespace std;

const int limit_table_column = 78;
const int limit_table_row = 500;
const int limit_charaters = 1024;
const int start_sheet_column = 79;
const int limit_sheet_column = 104;
const string MemoryUsage = " PhysicalM usage :";
const string CPUUsage = "    CPU usage :";
const string VirtualMemoryUsage = " VirtualM  usage :";
char s[limit_charaters];

vector <int> column;

CRITICAL_SECTION cs;


void Available_Memory()
{
	
	FILE* file;
	while(true)
	{
		long long Total_Physical_Memory = 0;
		file = _popen("wmic ComputerSystem get TotalPhysicalMemory", "r");
		{
			int line = 0;
			while (fgets(s, limit_charaters, file) != NULL)
			{
				line++;
				if (line == 2)
				{
					Total_Physical_Memory = convert(s);
				}
			}
		}
		_pclose(file);

		long long Free_Physical_Memory = 0;
		file = _popen("wmic OS get FreePhysicalMemory", "r");
		{
			int line = 0;
			while (fgets(s, limit_charaters, file) != NULL)
			{
				line++;
				if (line == 2)
				{
					Free_Physical_Memory = convert(s);
				}
			}
			Free_Physical_Memory *= 1024;
		}
		_pclose(file);

		

		long long CPU_Usage = 0;
		file = _popen("wmic cpu get loadpercentage","r");
		{
			int line = 0;
			while (fgets(s, limit_charaters, file) != NULL)
			{
				line++;
				if (line == 2)
				{
					CPU_Usage = convert(s);
				}
			}
		}
		_pclose(file);

		long long FreeVirtualMemory = 0;
		file = _popen("wmic OS get FreeVirtualMemory", "r"); 
		{
			int line = 0;
			while (fgets(s, limit_charaters, file) != NULL)
			{
				line++;
				if (line == 2)
				{
					FreeVirtualMemory = convert(s);
				}
			}
		}
		_pclose(file);

		long long TotalVirtualMemory = 0;
		file = _popen("wmic OS get TotalVirtualMemorySize", "r");
		{
			int line = 0;
			while (fgets(s, limit_charaters, file) != NULL)
			{
				line++;
				if (line == 2)
				{
					TotalVirtualMemory = convert(s);
				}
			}
		}
		_pclose(file);

		EnterCriticalSection(&cs);
		GoToRowColumn(1, start_sheet_column + 1 + MemoryUsage.length());
		cout << "    ";
		GoToRowColumn(1, start_sheet_column + 1 + MemoryUsage.length());
		cout << 100 - (Free_Physical_Memory * 100 / Total_Physical_Memory) << "%";
		GoToRowColumn(4, start_sheet_column + 1 + CPUUsage.length());
		cout << "    ";
		GoToRowColumn(4, start_sheet_column + 1 + CPUUsage.length());
		cout << CPU_Usage << "%";
		GoToRowColumn(7, start_sheet_column + 1 + VirtualMemoryUsage.length());
		cout << "    ";
		GoToRowColumn(7, start_sheet_column + 1 + VirtualMemoryUsage.length());
		cout << 100 - FreeVirtualMemory*100/TotalVirtualMemory << "%";
		LeaveCriticalSection(&cs);

		//light = greenlight;
		//this_thread::sleep_for(chrono::milliseconds(500));
	}
}

void Tasklist()
{
	FILE* file;
	while (true)
	{
		file = _popen("tasklist", "r");
		int line = -1;
		EnterCriticalSection(&cs);
		while (fgets(s, limit_charaters, file) != NULL)
		{
			line++;
			if (line == 0) continue;
			GoToRowColumn(line, 1);
			int n = strlen(s);
			for (int i = 0; i < n; i++)
			{
				if (isAppearance(i + 1, column) == true)
				{
					GoToRowColumn(line, i + 2);
				}
				else cout << s[i];
			}
		}
		GoToRowColumn(0, 0);
		LeaveCriticalSection(&cs);
		this_thread::sleep_for(chrono::milliseconds(7000));
		_pclose(file);
	}
}
void create_specific_table()
{
	for (int i = 0; i < limit_table_column; i++)
	{
		if (isAppearance(i,column) == true) cout << '+';
		else cout << "-";
	}
	for (int i = 1; i < limit_table_row; i++)
	{
		GoToRowColumn(i, 0);
		for (int j = 0; j < limit_table_column; j++)
		{
			if (isAppearance(j,column)==true) cout << "|";
			else cout << " ";
		}
	}
	GoToRowColumn(limit_table_row, 0);
	for (int i = 0; i < limit_table_column; i++)
	{
		if (isAppearance(i,column)==true) cout << '+';
		else cout << "-";
	}

	for (int i = 0; i < 3; i++)
	{
		GoToRowColumn(i, start_sheet_column);
		for (int j = start_sheet_column; j < limit_sheet_column; j++)
		{
			if (i == 1)
			{
				if (isAppearance(j, column) == true) cout << "|";
				else cout << " ";
				continue;
			}
			if (isAppearance(j, column) == true) cout << '+';
			else cout << "-";
		}
	}
	GoToRowColumn(1, start_sheet_column + 1);
	cout << MemoryUsage;

	for (int i = 3; i < 6; i++)
	{
		GoToRowColumn(i, start_sheet_column);
		for (int j = start_sheet_column; j < limit_sheet_column; j++)
		{
			if (i == 4)
			{
				if (isAppearance(j, column) == true) cout << "|";
				else cout << " ";
				continue;
			}
			if (isAppearance(j, column) == true) cout << '+';
			else cout << "-";
		}
	}
	GoToRowColumn(4, start_sheet_column + 1);
	cout << CPUUsage;

	for (int i = 6; i < 9; i++)
	{
		GoToRowColumn(i, start_sheet_column);
		for (int j = start_sheet_column; j < limit_sheet_column; j++)
		{
			if (i == 7)
			{
				if (isAppearance(j, column) == true) cout << "|";
				else cout << " ";
				continue;
			}
			if (isAppearance(j, column) == true) cout << '+';
			else cout << "-";
		}
	}
	GoToRowColumn(7, start_sheet_column + 1);
	cout << VirtualMemoryUsage;
	GoToRowColumn(0, 0);
}
void init()
{
	InitializeCriticalSection(&cs);

	/// initialize column of table
	column.push_back(0);
	column.push_back(26);
	column.push_back(35);
	column.push_back(52);
	column.push_back(64);
	column.push_back(77);
	column.push_back(79);
	column.push_back(103);


}
int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(0);
	init();
	create_specific_table();

	
	HANDLE h1,h2;
	DWORD Id;
	h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Tasklist, NULL, 0, &Id);
	h2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Available_Memory, NULL, 0, &Id);
	WaitForSingleObject(h1, INFINITE);
	WaitForSingleObject(h2, INFINITE);
	return 0;
}
