#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{

	int source,count=0;
	char line[100], buffer;
	char *pattern;

	if (argc == 3)
	{
		pattern = argv[1];

		source = open(argv[2], O_RDONLY);

		if (source == -1)
		{
			fprintf(stderr, "Unable to open file");
			return 1;
		}

		while (read(source, &buffer, 1))
		{

			if (buffer == '\n')
			{
				line[count] = '\0';

				if (strstr(line, pattern))
					printf("%s\n", line);

				count = 0;

				for (int i = 0; i < 100; i++)
					line[i] = 0;
			}

			else
				line[count++] = buffer;
		}
		return 0;
	}

	if (argc == 4)
	{
		pattern = argv[2];

		source  = open(argv[3], O_RDONLY);

		if (source == -1)
		{
			fprintf(stderr, "Unable to open file");
			return 1;
		}

		if (strcmp(argv[1], "-c") == 0)
		{
			int match = 0;
			while (read(source, &buffer, 1))
			{
				if (buffer == '\n')
				{
					line[count] = '\0';
					if (strstr(line, pattern))
						match++;
					count = 0;
					for (int i = 0; i < 100; i++)
						line[i] = 0;
				}
				else
					line[count++] = buffer;
			}
			printf("No of matches: %d\n", match);
		}

		else if (strcmp(argv[1], "-n") == 0)
		{
			int c=1;
			while (read(source, &buffer, 1))
			{
				if (buffer == '\n')
				{
					line[count] = '\0';
					if (strstr(line, pattern))
						printf("%d:%s\n", c, line);
					count = 0;
					for (int i = 0; i < 100; i++)
						line[i] = 0;
					c++;
				}
				else
					line[count++] = buffer;
			}
		}
		else if (strcmp(argv[1],"-v") == 0)
		{

			while (read(source, &buffer, 1))
			{
				if (buffer == '\n')
				{
					line[count] = '\0';
					if (!strstr(line, pattern))
						printf("%s\n",line);
					count = 0;
					for (int i = 0; i < 100; i++)
						line[i] = 0;
				}
				else
					line[count++] = buffer;
			}
		}
		else
		{
			fprintf(stderr, "Invalid argument\n");
			return 1;
		}
	}

	else
		printf("Invalid no. of arguments\n");
	close(source);
}