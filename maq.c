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
  "MOV",
  "ATQ",
  "COL"
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

Maquina *cria_maquina(INSTR *p, int exercito, int x, int y) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip = 0;
  m->prog = p;
  m->exercito = exercito;
  m->ocupacao = 0;
  m->v = cria_vizinhanca( x, y);
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
  OPERANDO oip;
  OPERANDO oip2;
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
      if (op1.t == NUM && op2.t == NUM) {
        res.t = NUM;
        res.val.n = op1.val.n + op2.val.n;
        empilha(pil, res);
      }
      break;
    case SUB:
    op1 = desempilha(pil);
    op2 = desempilha(pil);
    if (op1.t == NUM && op2.t == NUM) {
      res.t = NUM;
      res.val.n = op1.val.n - op2.val.n;
      empilha(pil, res);
    }
    break;
    case MUL:
    op1 = desempilha(pil);
    op2 = desempilha(pil);
    if (op1.t == NUM && op2.t == NUM) {
      res.t = NUM;
      res.val.n = op1.val.n * op2.val.n;
      empilha(pil, res);
    }
    case DIV:
    op1 = desempilha(pil);
    op2 = desempilha(pil);
    if (op1.t == NUM && op2.t == NUM) {
      res.t = NUM;
      res.val.n = op1.val.n / op2.val.n;
      empilha(pil, res);
    }
    case JMP:
      ip = arg.val.n;
      continue;
    case JIT:
      tmp = desempilha(pil);
      if (tmp.t == NUM){
        if (desempilha(pil).val.n != 0) {
          ip = arg.val.n;
          continue;
        }
      }
      break;
    case JIF:
      tmp = desempilha(pil);
      if (tmp.t == NUM){
        if (tmp.val.n == 0) {
        ip = arg.val.n;
        continue;
        }
      }
      break;
    case CALL:
      oip.t = NUM;
      oip.val.n = ip;
      oip2.val.n = exec->topo;
      empilha(rbp, oip2); // empilha em rbp a posição que o endereço de retorno esta
      empilha(exec, oip);
      ip = arg.val.n;
      continue;
    case RET:
      ip = desempilha(exec).val.n;
      desempilha(rbp); // ajusta o rbp para a função anterior
      break;
    case EQ:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.t == NUM && op2.t == NUM){
        if (op1.val.n == op2.val.n){
          oip.val.n = 1;
          empilha(pil, oip);
        }
        else{
          oip.val.n = 0;
          empilha(pil, oip);
        }
      }
      break;
    case GT:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.t == NUM && op2.t == NUM){
        if (op1.val.n < op2.val.n){
        oip.val.n = 1;
          empilha(pil, oip);
        }
        else{
          oip.val.n = 0;
          empilha(pil, oip);
        }
      }
      break;
    case GE:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.t == NUM && op2.t == NUM){
        if (op1.val.n <= op2.val.n){
        oip.val.n = 1;
          empilha(pil, oip);
        }
        else{
          oip.val.n = 0;
          empilha(pil, oip);
        }
      }
      break;
    case LT:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.t == NUM && op2.t == NUM){
        if (op1.val.n > op2.val.n){
        oip.val.n = 1;
          empilha(pil, oip);
        }
        else{
          oip.val.n = 0;
          empilha(pil, oip);
        }
      }
      break;
    case LE:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.t == NUM && op2.t == NUM){
        if (op1.val.n >= op2.val.n){
          oip.val.n = 1;
          empilha(pil, oip);
        }
        else{
          oip.val.n = 0;
          empilha(pil, oip);
        }
      }
      break;
    case NE:
      op1 = desempilha(pil);
      op2 = desempilha(pil);
      if (op1.t == NUM && op2.t == NUM){
        if (op1.val.n != op2.val.n){
          oip.val.n = 1;
          empilha(pil, oip);
        }
        else{
          oip.val.n = 0;
          empilha(pil, oip);
        }
      }
      break;
    case STO:
      m->Mem[arg.val.n] = desempilha(pil);
      break;
    case RCL:
      empilha(pil,m->Mem[arg.val.n]);
      break;
    case END:
      return;
    case PRN:
      tmp = desempilha(pil);
      if (tmp.t == CELULA) {
      }
      break;
    case RCE:
      empilha(pil, exec->val[rbp->val[rbp->topo - 1].val.n + arg.val.n]);  // empilha o valor da variavel local
      break;
    case STL:
      exec->val[rbp->val[rbp->topo - 1].val.n + arg.val.n] = desempilha(pil); 
      break;
    case ALC:
      exec->topo = exec->topo + arg.val.n; // movimenta o topo da pilha de exec para aloca memoria
      break;
    case FRE:
      exec->topo = rbp->val[rbp->topo - 1].val.n + 1; // ajusta o topo da pilha de exec para desaloca memoria
      break;
    case ATR:
      tmp = desempilha(pil);
      //empilha(pil, );
      break;
    case MOV:
      Sistema(m, MOVER, arg.val.n);
      break;
    case ATQ:
      Sistema(m, ATACAR, arg.val.n);
      break;
    case COL:
      Sistema(m, COLETAR, arg.val.n);
      break;
    }
    D(imprime(pil,5));
    D(puts("\n"));

    ip++;
  }
}

Vizinhanca cria_vizinhanca(int x, int y)
{
	Vizinhanca *v = (Vizinhanca*)malloc(sizeof(Vizinhanca));
	v->pos1 = {(x-1)%6, y};
	v->pos2 = {(x-1)%6, (y+1)%};
	v->pos3 = {x, (y+1)%6};
	v->pos4 = {(x-1)%6, y};
	v->pos5 = {x, (y-1)%6};
	v->pos6 = {(x-1)%6, (y-1)%6}
	return v;
}
