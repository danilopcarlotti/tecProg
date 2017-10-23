#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

/* #define DEBUG */

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
  "PUSH",
  "POP",
  "DUP",
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "JMP",
  "JIT",
  "JIF",
  "CALL",
  "RET",
  "STS",
  "RCS",
  "EQ",
  "GT",
  "GE",
  "LT",
  "LE",
  "NE",
  "STO",
  "RCL",
  "END",
  "PRN",
  "STL",
  "RCE",
  "ALC",
  "FRE",
  "ATR",
  "SIS"
};
#else
#  define D(X)
#endif

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip = 0;
  m->prog = p;
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)
#define rbp (&m->rbp)

void exec_maquina(Maquina *m, int n) {
  int i;

  for (i = 0; i < n; i++) {
    OpCode   opc = prg[ip].instr;
    OPERANDO arg = prg[ip].op;

    D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));

    switch (opc) {
      OPERANDO tmp, op1, op2, res;
    case PUSH:
      empilha(pil, arg);
      break;
    case POP:
      desempilha(pil);
      break;
    case DUP:
      tmp = desempilha(pil);
      empilha(pil, tmp);
      empilha(pil, tmp);
      break;
    case ADD:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.t == NUM && op2 == NUM) {
        res.t = NUM;
        res.val.n = op1.val.n + op2.val.n;
        empilha(pil, res);
      }
      break;
    case SUB:
    op1 = desempilha(pil);
    op2 = desempilha(pil);
    if (op1.t == NUM && op2 == NUM) {
      res.t = NUM;
      res.val.n = op1.val.n - op2.val.n;
      empilha(pil, res);
    }
    break;
    case MUL:
    op1 = desempilha(pil);
    op2 = desempilha(pil);
    if (op1.t == NUM && op2 == NUM) {
      res.t = NUM;
      res.val.n = op1.val.n * op2.val.n;
      empilha(pil, res);
    }
    case DIV:
    op1 = desempilha(pil);
    op2 = desempilha(pil);
    if (op1.t == NUM && op2 == NUM) {
      res.t = NUM;
      res.val.n = op1.val.n / op2.val.n;
      empilha(pil, res);
    }
    case JMP:
      ip = arg;
      continue;
    case JIT:
      tmp = desempilha(pil);
      if (tmp.val.t == NUM){
        if (desempilha(pil).val.n != 0) {
          ip = arg;
          continue;
        }
      }
      break;
    case JIF:
      tmp = desempilha(pil);
      if (tmp.val.t == NUM){
        if (tmp.val.n == 0) {
        ip = arg;
        continue;
        }
      }
      break;
    case CALL:
      empilha(rbp, exec->topo); // empilha em rbp a posição que o endereço de retorno esta
      empilha(exec, ip);
      ip = arg;
      continue;
    case RET:
      ip = desempilha(exec);
      desempilha(rbp); // ajusta o rbp para a função anterior
      break;
    case EQ:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.val.t == NUM && op2.val.t == NUM){
        if (op1.val.n == op2.val.n)
          empilha(pil, 1);
        else
          empilha(pil, 0);
      }
      break;
    case GT:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.val.t == NUM && op2.val.t == NUM){
        if (op1.val.n < op2.val.n)
          empilha(pil, 1);
        else
          empilha(pil, 0);
      }
      break;
    case GE:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.val.t == NUM && op2.val.t == NUM){
        if (op1.val.n <= op2.val.n)
          empilha(pil, 1);
        else
          empilha(pil, 0);
      }
      break;
    case LT:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.val.t == NUM && op2.val.t == NUM){
        if (op1.val.n > op2.val.n)
          empilha(pil, 1);
        else
          empilha(pil, 0);
      }
      break;
    case LE:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.val.t == NUM && op2.val.t == NUM){
        if (op1.val.n >= op2.val.n)
          empilha(pil, 1);
        else
          empilha(pil, 0);
      }
      break;
    case NE:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.val.t == NUM && op2.val.t == NUM){
        if (op1.val.n != op2.val.n)
          empilha(pil, 1);
        else
          empilha(pil, 0);
      }
      break;
    case STO:
      m->Mem[arg] = desempilha(pil);
      break;
    case RCL:
      empilha(pil,m->Mem[arg]);
      break;
    case END:
      return;
    case PRN:
      tmp = desempilha(pil);
      printf("%d\n", tmp.val.t));
      if (tmp.val.t == CELULA) {
        printf("%d\n", ));
      }
      break;
    case RCE:
      empilha(pil, exec->val[rbp->val[rbp->topo - 1] + arg]);  // empilha o valor da variavel local
      break;
    case STL:
      exec->val[rbp->val[rbp->topo - 1] + arg] = desempilha(pil); 
      break;
    case ALC:
      exec->topo = exec->topo + arg; // movimenta o topo da pilha de exec para aloca memoria
      break;
    case FRE:
      exec->topo = rbp->val[rbp->topo - 1] + 1; // ajusta o topo da pilha de exec para desaloca memoria
      break;
    case ATR:
      tmp = desempilha(pil);
      empilha(pil, );
      break;
    case SIS:
      tmp = desempilha(pil);
      if (tmp.val.t == ACAO) {

      }
      break;
    }
    D(imprime(pil,5));
    D(puts("\n"));

    ip++;
  }
}
