/************* cd_ls_pwd.c file **************/
int cd()
{
  // printf("cd: under construction READ textbook!!!!\n");
  int ino = getino(pathname); //return error if ino == 0
  MINODE* mip = iget(dev, ino); 
  if (S_ISDIR(mip->INODE.i_mode)) {
    iput(running->cwd); //release old cwd
    running->cwd = mip; //change cwd to mip
  } else {
    printf("ERROR: not a directory\n");
    return -1;
  }


  // READ Chapter 11.7.3 HOW TO chdir
}

int ls_file(MINODE *mip, char *name)
{
  // printf("ls_file: to be done: READ textbook!!!!\n");
  printf("%s  ", name);
  // READ Chapter 11.7.3 HOW TO ls
}

int ls_dir(MINODE *mip)
{
  printf("ls_dir\n");

  char buf[BLKSIZE], temp[256];
  DIR *dp;
  char *cp;

  get_block(dev, mip->INODE.i_block[0], buf);
  dp = (DIR *)buf;
  cp = buf;
  
  while (cp < buf + BLKSIZE){
     //gets the name of each file
     strncpy(temp, dp->name, dp->name_len);
     temp[dp->name_len] = 0;
	
     ls_file(mip, temp);

     cp += dp->rec_len;
     dp = (DIR *)cp;
  }
  printf("\n");
}

int ls()
{
  if (!strcmp(pathname, "")) { //if no path is specified, use cwd by default
    printf("No path specified, using cwd\n");
    ls_dir(running->cwd);
  } else {
    int pathname_ino = getino(pathname);
    MINODE* mip = iget(dev, pathname_ino); //opening iget
    if (!S_ISDIR(mip->INODE.i_mode)) { //checks to make sure the path is a directory, not a file
      printf("Error, pathname: %s is not a directory\n", pathname);
      return -1;
    }
    ls_dir(mip);
    iput(mip); //closing iput
  }
  return 0;
}

char *pwd(MINODE *wd)
{
  printf("pwd: READ HOW TO pwd in textbook!!!!\n");
  if (wd == root){
    printf("/\n");
    return;
  }
}



