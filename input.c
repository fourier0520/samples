#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

unsigned long ChangeStrToUlong(const char *Str, enum ERROR *Err);

int main (int argc, char *argv[]){
  unsigned long Value;
  char *Ptr;
  char *Str;
  enum ERROR Err;
  Value = ChangeStrToUlong(argv[1], &Err);
  if(Err != NO_PROBLEM)
  {
    printf("ERROR : %d : %s\n", Err, argv[1]);
    exit(1);
  }
  printf("%016lX\n", Value);
  
  
}

#define BASE_DEC 10
#define BASE_HEX 16

enum ERROR{
  NO_PROBLEM = 0,
  INVALID_VALUE = 1,
  OVERFLOW_VALUE = 2,
};

unsigned long ChangeStrToUlong(const char *Str, enum ERROR *Err)
{
  unsigned long Value;
  char *PtrEnd;
  const char *PtrTarget;
  int StrLength;
  *Err = NO_PROBLEM;

  StrLength = strlen(Str);
  if(Str[StrLength - 1] == 't')
  {
    PtrTarget = Str + StrLength - 1;
    Value = strtoul(Str, &PtrEnd, BASE_DEC);
    if(PtrEnd != PtrTarget)
    {
      goto InvalidValueError;
    }
    if(errno == ERANGE)
    {
      goto OverflowValueError;
    }
  goto End;
  }else
  {
    PtrTarget = Str + StrLength;
    Value = strtoul(Str, &PtrEnd, BASE_HEX);
    if(PtrEnd != PtrTarget)
    {
      goto InvalidValueError;
    }
    if(errno == ERANGE)
    {
      goto OverflowValueError;
    }
    goto End;
  }

InvalidValueError:
  *Err = INVALID_VALUE;
  goto End;
OverflowValueError:
  *Err = OVERFLOW_VALUE;
  goto End;
End:
  return Value;
}
