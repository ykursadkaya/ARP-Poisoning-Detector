#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 1024

typedef struct
{
	char ipAddr[BUFFER_LEN];
	char hwAddr[BUFFER_LEN];
	char device[BUFFER_LEN];
} ARPEntry;

int main(int argc, char *argv[])
{
	int display = 0, os = 0;

	if (argc == 1)
	{
		printf("Missing arguments! (-h for help)\n");

		return 0;
	}
	else if (argc >= 2)
	{
		if (!strcmp(argv[1], "-h"))
		{
			printf("OS selection:\n\t-l*\tLinux systems\n\t\t-lc\tLinux arp command\n\t\t-lf\tLinux ARP cache file\n\t-m\tmacOS systems\n\n\t-d\tDisplay ARP Table\n");

			return 0;
		}
		else if (!strcmp(argv[1], "-lf"))
		{
			os = 3;
		}
		else if (!strcmp(argv[1], "-lc"))
		{
			os = 2;
		}
		else if (!strcmp(argv[1], "-m"))
		{
			os = 1;
		}
		else
		{
			printf("Wrong OS selection! (-l* for Linux -m for macOS systems)\n");

			return 0;
		}

		if (argc == 3)
		{
			if (!strcmp(argv[2], "-d"))
			{
				display = 1;
			}
			else
			{
				printf("Wrong argument (-h for help)\n");

				return 0;
			}
		}
		else if (argc > 3)
		{
			printf("Too many arguments are given! (-h for help)\n");

			return 0;
		}
	}

	FILE *arpCache;
	char line[BUFFER_LEN];
	ARPEntry arpEntryArray[254];
	int counter = 0, i = 0, j = 0;
	char ipAddr[BUFFER_LEN], hwAddr[BUFFER_LEN], device[BUFFER_LEN];

	if ((os == 1) || (os == 2))
	{
		arpCache = popen("arp -an", "r");

		if (arpCache == NULL)
		{
			printf("Failed to run command\n" );
			return 1;
		}

		while (fgets(line, sizeof(line), arpCache) != NULL)
		{
			if (os == 1)
			{
				sscanf(line, "%*s %100s %*s %100s %*s %100s", ipAddr, hwAddr, device);
			}
			else if (os == 2)
			{
				sscanf(line, "%*s %100s %*s %100s %*s %*s %100s", ipAddr, hwAddr, device);
			}

			strcpy(arpEntryArray[counter].ipAddr, ipAddr);
			strcpy(arpEntryArray[counter].hwAddr, hwAddr);
			strcpy(arpEntryArray[counter].device, device);

			counter++;
		}
	}
	else if (os == 3)
	{
		arpCache = fopen("/proc/net/arp", "r");
		if (!arpCache)
		{
			printf("Failed to open ARP Cache file\n");
		}
		if (!fgets(line, sizeof(line), arpCache))
		{
			return 1;
		}

		while (fscanf(arpCache, "%100s %*s %*s %100s %*s %100s", ipAddr, hwAddr, device) == 3)
		{
			strcpy(arpEntryArray[counter].ipAddr, ipAddr);
			strcpy(arpEntryArray[counter].hwAddr, hwAddr);
			strcpy(arpEntryArray[counter].device, device);

			counter++;
		}
	}

	if (display)
	{
		for (i = 0; i < counter; i++)
		{
			printf("%s at %s on %s\n", arpEntryArray[i].ipAddr, arpEntryArray[i].hwAddr, arpEntryArray[i].device);
		}
	}

	for (i = 0; i < counter-1; i++)
	{
		for (j = i+1; j < counter; j++)
		{
			if (!strcmp(arpEntryArray[i].device, arpEntryArray[j].device) && strcmp(arpEntryArray[i].ipAddr, arpEntryArray[j].ipAddr) && !strcmp(arpEntryArray[i].hwAddr, arpEntryArray[j].hwAddr))
			{
				printf("ARP Poisoning detected!\n");
			}
		}
	}

	fclose(arpCache);
	return 0;
}