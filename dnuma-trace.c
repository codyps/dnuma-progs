#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_PATH 4096
#define _STR(x) #x
#define STR(x) _STR(x)
static const char *find_debugfs(void)
{
	static char debugfs[MAX_PATH+1];
	static int debugfs_found;
	char type[100];
	FILE *fp;

	if (debugfs_found)
		return debugfs;

	if ((fp = fopen("/proc/mounts","r")) == NULL)
		return NULL;

	while (fscanf(fp, "%*s %"STR(MAX_PATH)"s %99s %*s %*d %*d\n", debugfs, type) == 2)
		if (strcmp(type, "debugfs") == 0)
			break;
	fclose(fp);

	if (strcmp(type, "debugfs") != 0)
		return NULL;

	debugfs_found = 1;

	return debugfs;
}

static const char *find_trace(void)
{
	static char t[MAX_PATH + 1];
	if (t[0] != '\0')
		return t;

	const char *mt = getenv("T");
	if (mt)
		strcpy(t, mt);
	if (t[0] != '\0')
		return t;

	const char *d = find_debugfs();
	if (!d)
		return NULL;

	strcpy(t, d);
	strcat(t, "/trace/trace");
	return t;
}

static void die(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);

	putc('\n', stderr);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	const char *dfs = find_debugfs();
	if (!dfs)
		die("could not find debugfs");

	return 0;
}
