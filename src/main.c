#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
void tree(const char *path, int);

int main(int argc, const char *argv[])
{
  for (int i = 0; i < argc; i++)
    tree(argv[i], 0);
  return 0;
}

int isFile(const char *name)
{
  DIR *directory = opendir(name);

  if (directory != NULL)
  {
    closedir(directory);
    return 0;
  }

  if (errno == ENOTDIR)
  {
    return 1;
  }

  return -1;
}

void tree(const char *path, int indentLength)
{
  struct dirent *entry;
  DIR *dir = opendir(path);
  if (dir == NULL)
    return;

  readdir(dir);
  readdir(dir);

  while ((entry = readdir(dir)) != NULL)
  {
    // if (!isFile(entry->d_name))
    //   tree(entry->d_name, indentLength + 4);
    char name[3000] = "";
    strcat(name, path);
    strcat(name, entry->d_name);

    for (int i = 0; i < indentLength; i++)
      printf(" ");

    if (!isFile(name))
    {
      printf("- %s\n", entry->d_name);
      tree(name, indentLength + 4);
    }
    else
    {
      printf("| %s\n", entry->d_name);
    }
  }

  closedir(dir);
}
