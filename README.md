#Problema dos Fumantes - Grupo 06

Este projeto consiste na implementação do problema clássico de sincronização de processos conhecido como "Problema dos Fumantes", desenvolvido para a disciplina de Sistemas Operacionais do curso de Análise e Desenvolvimento de Sistemas (ADS) no IFPI Campus Parnaíba.

#Descrição do Problema
O problema envolve um agente e três fumantes. O agente possui suprimentos infinitos de tabaco, papel e fósforos. Ele coloca dois ingredientes na mesa e o fumante que possui o terceiro ingrediente deve pegá-los, montar o cigarro e fumar. O agente só coloca novos ingredientes após o fumante terminar.

#Tecnologias e Recursos
- Linguagem: C 
- Sincronização: Semáforos e/ou Mutexes.

#Como Executar
Para compilar e rodar o programa, utilize o GCC no terminal:

```bash
gcc main.c -o fumantes -lpthread
./fumantes
