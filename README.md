# Projeto Tecnicas de Programação

## Grupo
 - Otavio Ho Aragoni nº usp 9793798
 - Danilo Carlotti nº usp 5442378
 - Gabriel Peng nº usp 9293074

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

### Parte 3

#Partes faltantes
- Visualização: a implementação da visualização foi feita, porém ainda precisamos decidir nas imagens que serão utilizadas para cada terreno, robô, cristal e etc.
- Ataque: ainda estamos trabalhando na questão de sensores e ataques possíveis, por isso não implementamos esta função
- terrenos: estamos trabalhando na questão gráfica dos terrenos, que serão mostrados na arena em python a depender do tipo de terreno possível. Além disso, precisará haver png's específicos para quando o terreno está ocupado com robô e cristais, etc.