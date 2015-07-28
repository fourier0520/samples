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

enum ERROR
{
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
  if(Err != NULL)
  {
    *Err = NO_PROBLEM;
  }
  
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
    goto EndFunction;
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
    goto EndFunction;
  }
  
InvalidValueError:
  if(Err != NULL)
  {
    *Err = INVALID_VALUE;
  }
  goto End;
OverflowValueError:
  if(Err != NULL)
  {
    *Err = OVERFLOW_VALUE;
  }
  goto End;
EndFunction:
  return Value;
}

enum ERROR INPUTDATA_SetPCINum(INPUTDATA *Input, const char *StrPCINum)
{
  char Buf[PCI_NUM_BUFSIZ];
  int StrLength;
  int i;
  enum ERROR Err;
  union
  {
    struct
    {
      char bus[PCI_BUS_LENGTH];
      char dev[PCI_DEV_LENGTH];
      char func[PCI_FUNC_LENGTH];
      char reg[PCI_REG_LENGTH];
    }table;
    char block[PCI_ENTIRE_LENGTH];
  }SplitStrPCINum;

  Err = NoProblem;
  StrLength=strlen(StrPCINum);
  
  for(i = 1; i <= PCI_ENTIRE_LENGTH; i++)
  {
    if(i <= StrLength)
    {
      SplitStrPCINum[PCI_ENTIRE_LENGTH - i] = StrPCINum[StrLength - i];
    }else
    {
      SplitStrPCINum[PCI_ENTIRE_LENGTH - i] = '0';
    }
  }
  
  memsef(Buf, '\0', PCI_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCINum.table.bus, PCI_BUS_LENGTH);
  Input->bus = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }

  memsef(Buf, '\0', PCI_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCINum.table.dev, PCI_DEV_LENGTH);
  Input->dev = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }

  memsef(Buf, '\0', PCI_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCINum.table.func, PCI_FUNC_LENGTH);
  Input->func = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }
  
  memsef(Buf, '\0', PCI_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCINum.table.reg, PCI_REG_LENGTH);
  Input->reg = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }
EndFunction:
  return Err;
}

enum ERROR INPUTDATA_SetPCIENum(INPUTDATA *Input, const char *StrPCIENum)
{
  char Buf[PCIE_NUM_BUFSIZ];
  int StrLength;
  int i;
  enum ERROR Err;
  union
  {
    struct
    {
      char bus[PCIE_BUS_LENGTH];
      char dev[PCIE_DEV_LENGTH];
      char func[PCIE_FUNC_LENGTH];
      char reg[PCIE_REG_LENGTH];
    }table;
    char block[PCIE_ENTIRE_LENGTH];
  }SplitStrPCIENum;

  Err = NoProblem;
  StrLength=strlen(StrPCIENum);
  
  for(i = 1; i <= PCIE_ENTIRE_LENGTH; i++)
  {
    if(i <= StrLength)
    {
      SplitStrPCINum[PCIE_ENTIRE_LENGTH - i] = StrPCIENum[StrLength - i];
    }else
    {
      SplitStrPCINum[PCIE_ENTIRE_LENGTH - i] = '0';
    }
  }
  
  memsef(Buf, '\0', PCIE_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCIENum.table.bus, PCIE_BUS_LENGTH);
  Input->bus = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }

  memsef(Buf, '\0', PCIE_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCIENum.table.dev, PCIE_DEV_LENGTH);
  Input->dev = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }

  memsef(Buf, '\0', PCIE_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCIENum.table.func, PCIE_FUNC_LENGTH);
  Input->func = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }
  
  memsef(Buf, '\0', PCIE_NUM_BUFSIZ);
  strncpy(Buf, SplitStrPCIENum.table.reg, PCIE_REG_LENGTH);
  Input->reg = ChangeStrToUlong(Buf, &Err);
  if(Err != NoProblem)
  {
    goto LabelEnd;
  }
EndFunction:
  return Err;
}
