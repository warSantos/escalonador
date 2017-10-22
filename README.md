#### ARQUIVOS TESTES E LOG ####
    
      O simulados suporta qualquer tipo de arquivo que esteja dentro as especificações
    deste documento e em seu relatório. Porém adjunto ao código fonte do software es-
    tão presentes testes e logs utilizados para realizar o relatório que o acompanha,
    logo se for de interesse estes podem ser utilizados para execução.
      Para acessar os testes navegue dentro do diretório Testes/ e la encontra-se vários
    diretórios com a sequinte nomeclatura QUANTIDADE_DE_PROCESSOS-QUANTIDADE_DE_INSTURÇÕES.
    Ex.: 5-5, neste diretório contém 5 processos com todos limitados a um número máximo de 
    5 instruções.
      Testes também podem ser gerados, dentro do diretório teste existe duas ferramentas, 
    geraProcesso.c e geraComandos.c.
      geraProcesso: gera processos aleatórios, com a opção de quantos arquivos de processo gerar
    e sua respectiva quantidade de instruções.
      geraComandos: este por vez produz arquivos para o commander conforme a necessidade de 
    instruções do usuário.
     ### COMPILAÇÃO && EXECUÇÃO ###
        
        $ gcc geraProcesso.c -o geraProcesso
        $ ./geraProcesso
        $ gcc geraComandos.c -o geraComandos
        $ ./geraComandos
        
#### COMPILAÇÃO ####

$ make all

$ make clean

#### EXECUÇÃO #####

$ ./cmder ARQUIVO_COMMANDER INIT

$ ./cmder cmds.txt Testes/5-5/init.txt

#### SAÍDA ####

      A saída do programa consiste em um arquivo de log com o seguinte formato: P_I_Q
      P: quantidade de processos.
      I: limite superior de instruções por processo.
      Q: Quantidade de instruções por quantum.
      
