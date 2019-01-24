#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 1024

typedef struct
{
	char ipAddr[BUFFER_LEN];
	char hwAddr[BUFFER_LEN];
	char device[BUFFER_LEN];
} ARPEntry;

enum osEnum {inv, mac, linuxCommand, linuxFile, windows};

int main(int argc, char *argv[])
{
	int display = 0;
	enum osEnum os = inv;

	char *s;
	while (--argc > 0 && (*++argv)[0] == '-')
	{
		for(s = argv[0]+1; *s != '\0'; s++)
		{
			switch(*s)
			{
				case 'h':
					printf("OS selection:\n\t-l*\tLinux systems\n\t\t-lc\tLinux arp command\n\t\t-lf\tLinux ARP cache file\n\t-m\tmacOS systems\n\t-w\tWindows systems\n\nDisplay option:\n\t-d\tDisplay ARP Table\n");
					return 0;
				case 'm':
					os = mac;
					break;
				case 'l':
					if (*(s+1) == 'c')
					{
						os = linuxCommand;
						s++;
					}
					else if (*(s+1) == 'f')
					{
						os = linuxFile;
						s++;
					}
					else
					{
						printf("Illegal option l%c (-h for help)\n", *(s+1));
						return 0;
					}
					break;
				case 'w':
					os = windows;
					break;
				case 'd':
					display = 1;
					break;
				default:
					printf("Illegal option %c (-h for help)\n", *s);
					argc = 0;
					break;
			}
		}
	}
	if( argc != 0)
	{
		printf("Missing arguments! (-h for help)\n");
		return 0;
	}
	else
	{

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
	else if (os == 4)
	{
		arpCache = popen("arp -a", "r");

		if (arpCache == NULL)
		{
			printf("Failed to run command\n" );
			return 1;
		}

		for (i = 0; i < 3; i++)
		{
			if (!fgets(line, sizeof(line), arpCache))
			{
				return 1;
			}
		}

		while (fscanf(arpCache, "%100s %100s %100s", ipAddr, hwAddr, device) == 3)
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
}