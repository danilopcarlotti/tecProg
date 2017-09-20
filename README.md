# Projeto Tecnicas de Programação

## Grupo
 - Otavio Ho Aragoni
 - Danilo Carlotti
 - Gabriel Peng

## Parte 1

### implementação do registrador de base (rbp)
implementado como uma pilha na struct 'Maquina' que armazena as posições onde são armazenados os endereços de retorno na pilha de execução. 
### implentação das instruções RCE, STL, ALC, FRE
 - RCE: Empilha (na pilha de dados) o valor armazenado na posição dada pelo argumento
 - STL: Desempilha (da pilha de dados) e armazena o valor como variavel local(frame da pilha de exec) na posição especificada pelo argumento.
 - ALC: Aloca espaço na pilha de execução a partir do rbp no valor especificado pelo arg deslocando o topo da pilha de exec para a pos topo + arg.
 - FRE: Reposiciona o topo da pilha de execução para um acima do rbp.
### Modificações no codigo original
 - CALL: Ao executar o call a posição do endereço de retorno é empilhada na pilha rbp
 - RET: desempilha o rbp
