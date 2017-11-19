/* Códigos das instruções */
typedef enum {
  PUSH,
  POP,
  DUP,
  ADD,
  SUB,
  MUL,
  DIV,
  JMP,
  JIT,
  JIF,
  CALL,
  RET,
  STS,
  RCS,
  EQ,
  GT,
  GE,
  LT,
  LE,
  NE,
  STO,
  RCL,
  END,
  PRN,
  STL,
  RCE,
  ALC,
  FRE,
  ATR,
<<<<<<< HEAD
  SIS
=======
  MOV,
  ATQ,
  COL
>>>>>>> origin/otavio
} OpCode;

/* Tipos dos operandos */
/* no momento, são todos inteiros */
typedef enum {
  NUM,
  ACAO,
  VAR,
  CELULA
} Tipo;

/* Operando */
 typedef struct { 
   Tipo t; 
   union {
 	int n; 
 	int ac;
 	int v; 
<<<<<<< HEAD
   };
=======
   } val;
>>>>>>> origin/otavio
} OPERANDO;

/*terreno*/
typedef enum {
  ESTRADA,
  MONTANHA,
  RIO,
  BASE
} Terreno;

<<<<<<< HEAD
/*Celula*/
typedef struct {
  Terreno terreno,
  short int cristais,
  short int ocupado
} Celula;
=======
/*Celula
typedef struct {
  Terreno terreno;
  short int cristais;
  short int ocupado;
} Celula;*/
>>>>>>> origin/otavio

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;

/*Acao*/
typedef enum {
  MOVER,
  COLETAR,
  ATACAR
<<<<<<< HEAD
} ACAO
=======
} AC;
>>>>>>> origin/otavio
