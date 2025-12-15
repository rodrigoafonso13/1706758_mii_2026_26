1706758\_mii\_2026\_26

===



//narrativa do trabalho



criar jogo do galo



arquitetura trabalho pratico 1


!\[icon1](/imagens/diagrama-trabalho.jpg)



1. Descrição do Trabalho	3
2. Implementação do Trabalho	3
3. Funcionamento do trabalho	3
4. Conclusão	3
Bibliografia

1.Descrição do Trabalho
O trabalho consiste no desenvolvimento de um Jogo do Galo (3x3) utilizando a  linguagem C, executada na consola.
O jogo permite dois modos de funcionamento:
Jogador vs Jogador (PvP)
Jogador vs Computador (CPU)
O objetivo principal é aplicar conceitos fundamentais de programação, nomeadamente:
Estruturas (struct)
Matrizes
Funções
Estruturas de controlo (if,for,while)
Validação de dados
Lógica de decisão básica para a CPU

2.Implementação do Trabalho	 
Foi criada uma estrutura de tabuleiro, que é composta por uma matriz de 3x3, que representa o jogo.
O tabuleiro inicialmente tem os espaços em branco. A função mostrarTabuleiro mostra o estado atual do jogo. A função ao colocarjogada mostra a posição escolhida. 
As posições fora do tabuleiro são impedidas devido à validação das jogadas.
Para fazer a verificação do vencedor, o programa analisa as linhas, colunas e diagonais à procura de vencedor,caso contrário só se verifica o empate quando o tabuleiro está todo preenchido e sem vencedor.
No código do CPU ele tenta vencer e tentar bloquear o jogador, se não for possível, ele escolhe aleatoriamente um espaço em branco. 

3.Funcionamento do trabalho	
Inicialmente o utilizador escolhe o modo que quer jogar,o tabuleiro é mostrado e o jogador introduz a linha e coluna que quer. No modo contra o CPU, o CPU joga automaticamente quando é a vez dele.
No final o programa verifica se há um vencedor ou se há empate.

4.Conclusão
O trabalho desenvolvido permitiu desenvolver um jogo do galo em linguagem C.
A meu ver está bom devido a gestão do tabuleiro, validação de jogadas,detecção de vitória
E o modo de jogador contra o CPU.
O trabalho cumpre com os objetivos definidos, apesar de que podia ter umas melhorias em termos de interface, na validação de jogadas feitas pelo utilizador e ter uma tabela de resultados para verificar o número de vitórias de ambos os jogadores.
Com isto tudo já me posso gabar que criei um jogo, mas acima de tudo aprofundei ainda mais o meu conhecimento em C.

Bibliografia
Rodrigo Afonso -1706758



