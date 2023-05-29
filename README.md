<!-- # IOinterface
IOinterface
 -->
 # Interface de E/S - Problema #2 – 2023.1

# Vídeo Demonstrativo

<p>inserir viídeo aqui.</p>

# Visão Geral do Protótipo

<div>
	<img src="/images/visãoGeralTimer.jpg" alt="img" >
</div>

# Descrição do Projeto e Requisitos

<p> O objetivo é desenvolver um software capaz de ler de sensores analógicos e digitais em um microcontrolador utilizando comunicação serial.</p>

<p> O protótipo de sistema de sensoriamento genérico utiliza uma plataforma baseada em uma <a href="https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf">NodeMCU</a> para a confecção das unidades de sensoriamento.</p>

<p> O gerenciamento do sistema será comandado por um <a href="https://dl.linux-sunxi.org/H3/Allwinner_H3_Datasheet_V1.0.pdf">Single Board Computer SBC</a> e os valores das leituras serão mostrados no  <a href="https://www.sparkfun.com/datasheets/LCD/HD44780.pdf">display LCD 16x2</a></p>

## Requisitos

<ul> 
<li> Solução deve ser desenvolvida em linguagem C </li>
<li> Deve conter o Script de compilação do tipo Makefile para criação do executavel </li>
<li>Para o SBC
<ul> 
  <li>Apenas o SBC deve ser capaz de iniciar a comunicação </li>
  <li>Deve ser possível a interligação com até 32 unidades de sensoriamento </li>
</ul>
<li>Para a NodeMCU
<ul> 
  <li>A leitura dos sensores deve ter a maior precisão possível </li>
  <li>Os comandos serão compostos por palavras de 1 byte (8 bits) </li>
  <li>As requisições podem ser direcionadas para uma unidade ou todas </li>
  <li>Comandos e respostas devem ser exibidas no display LCD 16x2 </li>
</ul>
</ul>

<!-- # Makefile -->

# Ambiente de Desenvolvimento

Neste projeto existem vários ambientes de desenvolvimento e execução. Parte na Orange Pi e parte no módulo nodeMCU. Do lado da Orange Pi foi necessário fazer acesso remoto via protoclo SSH, e, do lado da nodeMCU os códigos eram carregados por Wi-Fi usando o módulo ESP8266 integrado a nodeMCU. A edição dos códigos foi feita usando editores de texto nativos nos computadores do laboratório, ou IDEs que foram instaladas, ou cujo acesso está disponível online (via navegador de intenet).

## Computadores do Laboratório

Utilizamos o Sublime Text (https://www.sublimetext.com/), e o TextEditor (https://apps.gnome.org/pt-BR/app/org.gnome.TextEditor/) presente nos computadores do laboratório. Mas poderiam ser usados qualquer outro editor de texto ou IDE.

## Orange Pi

A o código foi desenvolvido utilizando de editor de texto GNU Nano (https://www.nano-editor.org/) acessado diretamente via terminal de comando da Orange Pi. Para compilar e executar usamos os comandos abaixo. O arquivo fonte é o 'p.c' e o executável apenas 'p'.

	gcc p.c -o p -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt // COMPILA SE NÃO ENCONTRAR ERROS
	chmod +x p // ALTERA PERMISSÕES DO ARQUIVO
	sudo ./p // EXECUTA COM PERMISSÕES DE ADMINISTRADOR POIS É NECESSÁRIO ACESSAR PINOS GPIO.

## Módulo nodeMCU

Os códigos de programa da nodeMCU eram feitos usando o Arduino IDE (https://docs.arduino.cc/software/ide-v1/tutorials/Environment). Antes de tudo é necessário baixar e instalar os pacotes necessários para que a IDE reconheça o módulo. Existem alguns tutorias disponíveis na internet que ensinam como configurar nodeMCU e ESP8266.

## Outras Ferramentas e Instrumentos

Foi utilizado um Multímetro para verificar a continuidade da alguns contatos e confirmar informações do mapeamento dos pinos da Orange Pi e também do módulo nodeMCU conectados aos demais componentes eletrônicos do protótipo. Também é possível usar um Osciloscópio para capturar algum sinal dentro do protótipo.

## Impedimentos, Dificuldades, Soluções e Testes

Para este projeto nem sempre poderíamos estar presentes no laboratório pra testar nossas ideias. Isso era um grande impedimento. Também tivemos dificuldades técnicas de causa raíz desconhecida, onde, o módulo nodeMCU se descofigurava com frequencia muito alta impedindo seu acesso via Wi-Fi e também não permitia descarregar o código. Tudo isso poderia atrasar o desenvolvimento do projeto.

Para superar estas dificuldades criamos uma pequena biblioteca (.h) encontrada no seguinte arquivo: (https://github.com/vini-insight/IOinterface/blob/main/testeFunctions.h). Ela simula as funções relacionadas a comunicação serial, escrita de caracteres no display LCD, e leitura de valoes lógicos dos pinos, além de simular os botões da protótipo. Ela utiliza os mesmos nomes das funções originais presentes na Wiring Pi e que serão usadas no projeto final. A ideia ea abstrar os componentes físicos e comunicação serial quando eles estavam indisponíveis para focar no desenvolvimento do projeto.

Por exemplo, quando inserimos esta biblioteca no código, em todas as chamadas da função "lcdPrintf", para escrever caracteres no LCD, eles eram escritos no console. Em todas as chamadas de "digitalRead" ao invés de ler os sinais lógicos dos botões do protótipo, eram capturadas teclas do teclado. A comunicação serial com "serialPutchar", "serialDataAvail", "serialGetchar" respondiam com códigos predefinidos. Quando estavamos usando esta biblioteca personalizada, foi utilizado o GDB online (https://www.onlinegdb.com/online_c_compiler) para testar o código.

Quando os testes estavam ok, nós retiramos as chamadas de nossa biblioteca personalizada e testamos direto no protótipo (quando ambas as placas estavam funcionando normalmente). Desse modo as chamadas originais de "lcdPrintf" voltavam a escrever no display LCD, as chamadas de "serialPutchar", "serialDataAvail", "serialGetchar" voltamva a funcionar via interface UART e "digitalRead" captirava de fato o sinal dos botões do protótipo.

Usando essa estratégia da biblioteca personalizada conseguimos superar os imepdimentos e agilizar o desenvolvimento dos códigos. Claro que algumas pequenas adaptações foram feitas tanto do lado do protótipo quanto do lado da biblioteca personalizada, cujos argumentos podem diferir do original.

## SSH

<img src="/images/SSH.png" alt="img" align="center">

<p>SSH é a sigla para Secure Socket Shell. Em tradução livre, significa “Concha de Segurança”, mas pode ser adaptado para o termo “Bloqueio de Segurança”. Sendo um dos protocolos específicos de segurança de troca de arquivos entre cliente e servidor de internet, usando criptografia. O objetivo do SSH é permitir que desenvolvedores ou outros usuários realizem alterações em sites e servidores utilizando uma conexão simples e segura.</p>
<p>Para para abrir conexões desse tipo utilizado o protocolo SSH, o sistema operacional deve ter um clienteSSH de forma nativa ou pode ser instalado. No Linux bastar abrir o Terminal e digitar comando SSH que consiste em 3 partes distintas:</p>

    ssh {user}@{host}

<p>O comando SSH instrui o sistema que deseja abrir uma Conexão de Shell segura criptografada. O {User} representa a conta à qual você deseja acessar. Por exemplo, você pode querer acessar o usuário raiz, que é basicamente sinônimo, para o administrador do sistema, com direitos completos para modificar qualquer coisa no sistema. O {host} refere-se ao computador ao qual você deseja acessar. Este pode ser um endereço IP (por exemplo, 244.235.23.19) ou, um nome de domínio (por exemplo, www.xyzdomain.com).</p>
<p>Quando você pressionar enter, você será solicitado a inserir a senha da conta solicitada. Quando você digitou, nada aparecerá na tela, mas sua senha é, de fato, transmitida. Depois de terminar de digitar, pressione enter mais uma vez. Se sua senha estiver correta, você será saudado com uma janela de terminal remota como na imagem abaixo: </p>

<img src="/images/TERMINAL.png" alt="img" align="center">

## Principais comandos utilizados no terminal

	- ssh {user}@{host}
	- sudo {senha}
	- cd {nome pasta}
	- cd .. (volta para pasta anterior)
	- cat {nomeArquivo}
	- nano {nomeArquivo}
	- mkdir {nome pasta}
	- rm {nomeArquivo}
	- echo > {nomeArquivo}
	- && (para executar dois comandos como por exemplo mkdir novaPasta && cd novaPasta
	- ls
	- cat {nomeArquivo} (apenas ver o conteudo do arquivo)
	- nano {nomeArquivo}
	- nano (atalhos) CTRL + O (salvar) CTRL + X (fechar editor)
	- gpio readall
	- make {senha}
	- gcc
	- gcc t.c && ./t.out
	- gcc c.c -o c && chmod +x c && ./c
	- rm p.c && nano p.c

<p> </p>

# Linguagem C

<p>C é uma linguagem de programação de computador de uso geral. A linguagem C foi criado na década de 1970 por Dennis Ritchie e continua sendo amplamente utilizada em sistemas operacionais, drivers de dispositivo, pilhas de protocolos de comunicação, em arquiteturas de computador que vão desde o maiordesde supercomputadores até os menores microcontroladores e sistemas embarcados. Existem compiladores C disponíveis para praticamente todas as arquiteturas de computadores e sistemas operacionais modernos. C foi padronizado pela ANSI desde 1989 ( ANSI C) e pela Organização Internacional de Normalização (ISO).</p>

<p>C é uma linguagem procedural imperativa, suportando programação estruturada, escopo de variável léxica e recursão, com um sistema de tipo estático. Ele foi projetado para ser compilado para fornecer acesso de baixo nível à memória e construções de linguagem que mapeiam com eficiência as instruções da máquina, tudo com suporte mínimo de tempo de execução.</p>

<p>Apesar de seus recursos de baixo nível, a linguagem foi projetada para incentivar a programação entre plataformas. Um programa C compatível com os padrões escrito com portabilidade em mente pode ser compilado para uma ampla variedade de plataformas de computador e sistemas operacionais com poucas alterações em seu código-fonte.</p>

<p>
	<img src="/images/cHW.jpg" alt="img" align="left" >
	C não deve ser confundida com C++ (Cplusplus), C# (Csharp), ou, Objective-C que são outras liguagens de programação. A diferença mais importante entre elas é a abordagem de programação que cada uma usa, em outras palavras, o seu paradigma de programação. C++, C# e Objective-C são orientadas a Objetos e seu programas são divididos em conjunto de Classes que instanciam os Objetos. C é uma linguagem orientada a procedimentos e sua ênfase está nas funções. Os programas são divididos em um conjunto de funções. Ao lado um exemplo de código em C.</p>


<p></p>
<br></br>

# Esquemático do protótipo

<img src="/images/esquematico.jpg" alt="img" >

<p>Prototipação feita antes da montagem dos componentes.</p>


# Arquitetura ARM

ARM significa Advanced RISC Machines, ou Máquinas RISC Avançadas. RISC é acrônimo de Reduced Instruction Set Computer, ou Computador com um conjunto reduzido de instruções. O que mostra que a arquitetura ARM foi inspirado no RISC, onde o objetivo era desenvolver um hardware simples e também um conjunto pequeno de instruções que garanta tamanho reduzido, velocidade e eficiência no consumo de potência.

# Processador ARM

<div>
	<img src="/images/allwinnerH3.jpg" alt="img" style="height: 20%; width: 20%;" align="left"> 

    Alguns detalhes e características do processador Allwinner H3:
    - Quad-core Cortex-A7
    - 1.6 GHz
    - arquitetura ARM v7
    - Representação em 32 bits
    - 16 registradores:
           - r0 até r12: são de uso geral
           - r13: Stack Pointer (SP)
           - r14: Link Register (LR)
           - r15: Program Counter (PC)

</div>

# Orange Pi PC Plus

<div>
	<img src="/images/Orange Pi PC Plus-cut.png" alt="img" style="height: 50%; width: 50%;" align="right">
	<p>Orange Pi PC Plus é um SBC Single-Board Card Computer, ou, Computador de Cartão de Placa Única. Tem código aberto e usa arquitetura ARM. Suporta alguns Sistemas Operacionais como Android, Debian, Lubuntu, Ubuntu. Orange Pi PC Plus usa Allwinner H3 como CPU.</p>
	<p>A Orange Pi PC Plus pode ser usada para construir um servidor de rede sem fio, jogos, Reprodutor de música e video, entre outros fins. Ela foi projetada para quem deseja usar a tecnologia para criar e inovar.</p>
	<p>O sistema operacional da Orange Pi que utilizamos no laboratório é o Ubuntu Armbian 22.08.8 Jammy. Seu Kernel é Linux 5.15.74-sunxi. Acessamos a placa utilizando um terminal de comandos utilizando protocolo SSH. Para mais informações sobre a Orange Pi, consultar site oficial (http://www.orangepi.org/html/hardWare/computerAndMicrocontrollers/details/Orange-Pi-PC-Plus.html) </p>
</div>

# GPIO

<div>
	<img src="/images/Pinos GPIO da Orange PI PC plus.jpg" alt="img" style="height: 50%; width: 50%;" align="left">
	<p>GPIO significa General-Purpose Input/Output, ou, Entrada e Saída de Uso Geral. Uma interface de E/S em placas de circuito.</p>
	<p>GPIO é diferente dos padrões de porta comuns (como VGA, HDMI, VDI ou USB). Esses cabos, cada pino conectado dentro da conexão tem uma finalidade definida, que é determinada pelo órgão regulador que criou o padrão.</p>
	<p>A interface GPIO refere-se a um conjunto de pinos. Eles não possui uma função específica, por isso que são chamados de uso geral. Os pino GPIO podem enviar ou receber sinais elétricos que são determinados pelo projetista.</p>
	<p>Embora a maioria dos pinos de uma porta ou interface tenha uma finalidade específica, como enviar um sinal para um determinado componente, a função de um pino GPIO é personalizável e pode ser controlada por software. O GPIO coloca você no comando do que cada pino realmente faz. Existam diferentes tipos de pinos na matriz GPIO.</p>

- Pinos de finalidade especial, que variam de acordo com o GPIO específico em questão.
- Pinos GPIO, que podem ser configurados para enviar ou receber sinais elétricos.
- Pinos de aterramento que não fornecem energia, mas são necessários para completar alguns circuitos.
- Pinos que fornecem energia em tensões típicas, como 3,3 V ou 5 V (para alimentar dispositivos conectados que não possuem fonte de alimentação própria, como um simples LED.

<p>GPIO São usados por SoC (System-on-a-Chip), ou, Sistema em um Chip, que incluem um processador, memória e interfaces externas em um único chip. Os pinos GPIO permitem que esses chips sejam configurados para diferentes finalidades e funcionem com diversos tipos de componentes.</p>

<p>As interfaces GPIO são geralmente usadas em conjunto com uma placa de prototipação (Protoboard). Protoboards são um tipo de placa de circuito temporária. Você pode prototipar circuitos adicionando, removendo ou movendo componentes eletrônicos. Muitos projetos que envolvem dispositivos como um Orange Pi fazem com que você monte seu dispositivo em uma placa de ensaio e, em seguida, conecte-o aos pinos GPIO usando fios.</p>

<p>Um dispositivo popular que faz uso de pinos GPIO é o Orange Pi. Esses pinos atuam como interruptores que produzem 3,3 volts quando definidos como ALTO e sem tensão quando definidos como BAIXO. Você pode conectar um dispositivo a pinos GPIO específicos e controlá-lo com um programa de software. Por exemplo, você pode conectar um LED a um GPIO e um pino de aterramento em um Orange Pi. Se um programa de software disser ao pino GPIO para ligar, o LED acenderá.</p>
</div>

# Diagrama de Pinagem do Orange Pi PC Plus v1.2

<div>
	<img src="/images/orangePI PC PLUS pinout diagram-EDIT.jpg" alt="img" >
</div>

# Corte detalhado da interface GPIO com os demais componentes

<div>
	<img src="/images/placa de extensão GPIO.jpg" alt="img" >
	<p>Utilizamos uma placa de prototipação (protoboard) para reunir todos os componentes eletrônicos do projeto. A Orange PI e sua porta GPIO é conectada usando uma Placa de Extenção que pode ser vista em destaque na imagem acima. Esta placa de Extenção é de uma Raspberry PI, no entanto, sua interface tem a mesma quantidade de pinos da Orange Pi. Por isso, vamos desconsiderar os nomes inscritos originalmente na Placa de Extenção e vamos adotar a nomenclatura oficial do Diagrama de Pinagem da Orange Pi.</p>
</div>

# Mapeamento dos pinos GPIO

<div>
	<img src="/images/mapeamentoGPIOpi2.jpg" alt="img" >
	<p>Esta seção apresenta o mapeamento dos pinos GPIO com as conexões do display (LCD 16x2) e botões (push buttons) utilizados no projeto. O mapeamento é essencial para garantir a correta comunicação entre o Orange PI e os demais componentes, possibilitando funcionamento das interfaces de usuário.</p>
</div>

# Comando "gpio readall"

<div>
	<p>Para visualizar a flexibilidade de configuração dos pinos GPIO, abaixo segue um print da configuração padrão, quando a Orange Pi acabou de se ligada e o seu sistema operacional iniciado. Apenas digitamos o comando 'gpio readall' no terminal e vemos a saída abaixo:</p>
	<br>
	<img src="/images/Comando gpio readall DefaultSetting.png" alt="img">
	<br>
	<br>
	<p>Observe que a maior parte dos pinos está em modo 'OFF'. No entanto, depois que os pinos GPIO são configurados no código do projeto (em linguagem C), executamos novamente no terminal o comando 'gpio readall' e os pinos GPIO são configurados como segue o print abaixo:</p>
	<br>
	<img src="/images/Comando gpio readall PersonalSetting.png" alt="img">
	<br>
	<br>
	<p> É necessário destacar que os pinos GPIO que estão conectados a botões são definidos como 'IN' (entrada) e os pinos GPIO que estão conectados aos LEDs e também ao display LCD estão definidos como 'OUT' (saída).</p>
</div>

## Wiring Pi Numeração de Pinos

<p> A Wiring Pi tem seu próprio sistema de numeração de pinos, que é diferente da numeração oficial GPIO e também da ordem dos pinos fisicamente na placa. Isto se deve a evolução das interfaces GPIO e das placas como a Orange Pi. Originalmente, os pinos eram em menor quantidade e com o passasr do tempo eles aumentaram. Também devido a decisões de projeto alguns pinos tiveram sua numeração redefinida. No entanto a Wiring Pi encapsula todas essas informações, e, se você em seus códigos e projetos seguir usando o sistema de nuemração de pinos da Wiring Pi, vai consiguir manter a compatibilidade com versões antigas de placas e se em algum momento elas sofrerem alguma alteração no padrão de numeração, basta você atualizar a biblioteca. Isso evita que você tenha que sair renumerando todos os pinos em sues códigos e projetos. Abaixo segue o print do sistema de numeração de pinos da Wiring Pi.</p>

<img src="/images/Comando gpio readall WiringPi PINs.jpg" alt="img">

# Interface GPIO da Orange Pi com o Botões e DIP Switch

<div>
	<img src="/images/GPIOtoDIP-SWITCHsandBUTTONS subtitles.jpg" alt="img" >
	<p>O mapeamento entre a GPIO e os pinos que se conectam aos botões (push buttons) que pode ser visto em detalhes na imagem acima. Os pinos GPIO conectados aos botões são configurados como Entrada. Os botões quando pressionados indicam Anterior, Confirma e Próximo nas opções do menu que aparecem no Display LCD 16x2. </p>
	
	<p>O mapeamento entre a GPIO e os pinos que se conectam aos botões (push buttons) e aos LEDs (vermelhor e azul) que pode ser visto em detalhes na imagem acima. Os pinos GPIO conectados aos botões estão configurados como Entrada e os que estão conectados aos LEDs podem ser configurados como pinos de Saída. No entanto, para este projeto optamos por não utilizar os LEDs disponívels nesta interface com a Orange Pi. O único LED que utilizamos está embutido no módulo da nodeMCU e será explicado posteriormente neste texto. Os botões quando pressionados servem para movimentar nas opções no menu que aparecem no Display LCD 16x2</p>
	
<!-- 	<p>Quando a contagem é iniciada, o LED vermelho está desligado. Permanece desligado até o fim da contagem. Nesse momento é ligado durante apenas um segundo e depois é desligado. O LED azul é ligado quando a contagem começa e desliga quando a contagem termina.</p> -->
	
</div>

# Interface GPIO da Orange Pi com o Display LCD 16x2

<div>
	<img src="/images/GPIOtoLCD subtitlesRED.jpg" alt="img" >
	<p>O mapeamento entre a GPIO e o display LCD 16x2 no modo 4 bits é feito por meio da conexão de 7 pinos da porta GPIO da Orange Pi com outros 7 pinos do microcontrolador display (LCD 16x2). Esses 7 pinos são divididos em 4 bits de dados e 3 bits de controle.</p>
	<p>Os 4 bits de dados (DB4 a DB7) são responsáveis por enviar as informações que serão exibidas no display. Já os 3 bits de controle (RS, Enable e RW) são responsáveis por indicar ao display qual informação está sendo enviada (dados ou instruções), quando uma nova informação deve ser lida (sinal de enable) e se a operação será de escrita ou leitura (neste caso, o bit RW é configurado como leitura ou escrita).Neste contexto, o bit referente ao RW é sempre setado como escrita.</p>
	<p>Para o mapeamento, são utilizados os pinos GPIO do microcontrolador, que são configurados como saídas e conectados aos pinos correspondentes no display.</p>
	
	<p>ABAIXO COLOCAR NO TOPICO DE DESENVOLVIMENTO ?</p>
	
	<p>Para simplificar a manipulação do display e das informações que serão exibidas, foi utiilizada a biblioteca lcd.h </p>
</div>

## Display LCD 16x2

<img src="/images/LCD 16x2 myPinout.jpg" alt="img" >

<!-- <div> -->

<p>O LCD 16 × 2 é chamado assim porque tem 16 colunas e 2 linhas. Existem muitas combinações disponíveis, como 8×1, 8×2, 10×2, 16×1, etc. Mas a mais usada é a LCD 16x2. Todos os visores LCD mencionados terão 16 pinos e a abordagem de programação também é a mesma.</p>

<p>O LCD é matricial e composto por caracteres * linhas, ou, 16 * 2, e assim terá (16 * 2 = 32), ou seja, 32 caracteres no total. Cada caractere será feito de 5 * 8 pontos de pixel. Agora, sabemos que cada caractere tem (5 * 8 = 40) 40 pixels e para 32 caracteres teremos (32 * 40) 1280 pixels. Além disso, o LCD também deve ser instruído sobre a posição onde cada cada caractere deve ser inserido. O mesmo acontece com os pixils se quisermos desenhar caracteres expeciais ou psersonalizadosdos.</p>
	
<p>IC de interface como o HD44780 , que é montado no próprio módulo LCD. A função deste IC é obter os comandos e dados do MCU e processá-los para exibir informações significativas em nossa tela LCD.</p>
<!-- </div> -->

### Comandos LCD:

<p>Existem algumas instruções de comandos predefinidos no LCD, que precisamos enviar para o LCD através de algum microcontrolador. Algumas instruções de comando importantes são dadas abaixo:</p>

<div>
	<img src="/images/5x8.jpg" alt="img" align="right">
	
	Código hexadecimal | Comando para registro de instrução LCD

	0F | LCD LIGADO, cursor LIGADO
	01 | Limpar tela de exibição
	02 | voltar para casa
	04 | Diminuir o cursor (deslocar o cursor para a esquerda)
	06 | Incrementar o cursor (deslocar o cursor para a direita)
	05 | Deslocar exibição para a direita
	07 | Deslocar exibição para a esquerda
	0E | Visor LIGADO, cursor piscando
	80 | Forçar o cursor para o início da primeira linha
	C0 | Forçar o cursor para o início da segunda linha
	38 | 2 linhas e matriz 5×7
	83 | Cursor linha 1 posição 3
	3C | ativar segunda linha
	08 | Visor DESLIGADO, cursor DESLIGADO
	C1 | Ir para a segunda linha, posição 1
	OC | Visor LIGADO, cursor DESLIGADO
	C1 | Ir para a segunda linha, posição 1
	C2 | Ir para a segunda linha, posição 2

</div>

### Modo de operação do LCD em 4 bits e em 8 bits:

<p>O LCD pode funcionar em dois modos diferentes, nomeadamente o modo de 4 bits e o modo de 8 bits. No modo de 4 bits, enviamos os dados nibble por nibble, primeiro nibble superior e depois nibble inferior. Para aqueles que não sabem o que é um nibble: um nibble é um grupo de quatro bits, então os quatro bits inferiores (D0-D3) de um byte formam o nibble inferior enquanto os quatro bits superiores (D4-D7) de um byte formam o nibble superior. Isso nos permite enviar dados de 8 bits.</p>

<p>Enquanto no modo de 8 bits, podemos enviar os dados de 8 bits diretamente de uma vez, pois usamos todas as 8 linhas de dados.</p>

<p>O modo de 8 bits é mais rápido e sem falhas do que o modo de 4 bits. Mas a principal desvantagem é que ele precisa de 8 linhas de dados conectadas ao microcontrolador. Isso fará com que fiquemos sem pinos de E/S em nosso MCU, então o modo de 4 bits é amplamente usado. Nenhum pino de controle é usado para definir esses modos. É apenas a maneira de programar essa mudança.</p>

<img src="/images/howTOuseLCD16x2.jpg" alt="img" >

<p>Modo de leitura e gravação do LCD:</p>

<p>Como dito, o próprio LCD consiste em um IC de interface. O MCU pode ler ou gravar neste IC de interface. Na maioria das vezes estaremos apenas escrevendo para o IC, pois a leitura o tornará mais complexo e tais cenários são muito raros. Informações como posição do cursor, interrupções de conclusão de status etc.</p>

<p> Mais detalhes de como usar e operar o Display LCD 16x2 podem ser consultados no seu datasheet https://github.com/vini-insight/Assembly1/tree/main/Datasheets</p>

# Microcontrolador

<p>Um microcontrolador é um pequeno computador em um único chip de circuito integrado. Um microcontrolador contém CPUs ( núcleos de processador ) juntamente com memória e periféricos de entrada/saída programáveis. Os microcontroladores são projetados para aplicações embarcadas, em contraste com os microprocessadores usados em computadores pessoais ou outras aplicações de uso geral que consistem em vários chips discretos.</p>

<p>Na terminologia moderna, um microcontrolador é semelhante, mas menos sofisticado do que um sistema em um chip (SoC). Um SoC pode conectar os chips do microcontrolador externo como os componentes da placa-mãe, mas um SoC geralmente integra os periféricos avançados, como a unidade de processamento gráfico (GPU) e o controlador de interface Wi-Fi , como circuitos internos da unidade do microcontrolador.</p>

<p>Os microcontroladores são usados em produtos e dispositivos controlados automaticamente, como sistemas de controle de motores de automóveis, dispositivos médicos implantáveis, controles remotos, máquinas de escritório, eletrodomésticos, ferramentas elétricas, brinquedos e outros sistemas embarcados. No contexto da internet das coisas (IOT), os microcontroladores são um meio econômico e popular de coleta de dados, sentindo e acionando o mundo físico como dispositivos de borda.</p>


# NodeMCU e ESP8266

<p>O Módulo NodeMCU é uma placa de desenvolvimento para IOT – Internet of Thinks (internet das coisas).  O nome "NodeMCU" é a combinação de: node que significa "nó", a sigla MCU significa "MicroController Unit" ou Unidade de Microcontrolador.</p>

<p>O nodeMCU possui o seu próprio microcontrolador de 32bits, dispensando o uso de um microcontrolador externo, como o Arduino Uno R3. Possui entrada USB Micro que serve tanto para a conexão com um computador quanto para a alimentação, além de um regulador de tensão AMS1117 para diminuir a tensão de entrada de 5V para 3.3V, tensão de operação do NodeMCU, entre outras especificações.</p>

<p>O ESP8266 é um SOC (sistema em um chip). É um chip altamente integrado projetado para fornecer conectividade total à Internet via wi-fi em um pacote pequeno. Pode ser usado como um módulo Wifi externo, usando o firmware padrão AT Command set, conectando-o a qualquer microcontrolador usando o UART serial, ou servindo diretamente como um microcontrolador habilitado para Wifi.</p>

<p>Uma das principais características da placa NodeMCU é ter integrado o módulo ESP8266 para realizar a conexão com a rede Wifi, dando a possibilidade de conectar qualquer dispositivo microcontrolado à rede de internet. Além de uma boa capacidade de processamento, e a conexão com uma rede Wifi, possibilitando conectar diversos dispositivos à Internet atendendo assim uma gama enorme de aplicações, tais como automação residencial, monitoramento remoto, rede de sensores, controle industrial sem fio, entre muitas outras.
<br></br>
<img src="/images/nodeMCUesp8266.png" alt="img" align="center" >
</p>

## Diagrama de Pinagem do Módulo

<p>Utilizamos os pinos A0 (ADC) conectado ao potenciômetro, D0, D1 (GPIO) conectados aos botões.
<br></br>
<img src="/images/nodeMCUesp8266pinout.png" alt="img" align="center" >
</p>

# Interfaceamento de Pinos do módulo nodeMCU com Potenciômetro e botões.

<img src="/images/NODEsubtitles.jpg" alt="img" align="center" >

<br></br>

# Sensor

<p>Um Sensor é um dispositivo que tem a função de detectar e responder com eficiência algum estímulo. Existem vários tipos de sensores que respondem à estímulos diferentes como por exemplo: luz, som, eletricidade, magnétismo, temperatura, pressão, movimento, entre outros. Depois que o sensor recebe o estímulo, a sua função é emitir um sinal que seja capaz de ser convertido e interpretado pelos outros dispositivos.</p>

<p>Os sensores são usados em vários tipos de aplicações nas indústrias, comércios e residenciais. Por exemplo, um sensor Mecâncico pode fornecer informações a respeito de posição (linear / angular), aceleração, força, massa, densidade, momento, torque e aceleração. Um sensor Óptico, por sua vez, fornece informações a respieto de onda (amplitude, fase, polarização), velocidade da onda, índice de refração, emissividade, absorsão e refletividade. A escolha do sensor depende exclusivamente do objetivo da sua instalação. Portanto, é preciso avaliar as condições do ambiente e optar pelo sensor mais adequado para aquela atividade.</p>

<p>Em relação à natureza da saída, existem basicamente dois tipos de sensores: os analógicos, que produzem uma saída contínua proporcional à variação de algum parâmetro da entrada; e os digitais, que geram uma saída do tipo liga/desliga (on / off). Os sensores que produzem saídas digitais do tipo trem de pulsos, por exemplo, são considerados sensores digitais.</p>

## Sensor Analógico

<p>
	<img src="/images/instrumentacao_e_sensores_a01_f04_a.jpg" alt="img" align="right">
	São os sensores que respondem através de sinais analógicos. Devido à sua natureza analógica, a saída desses sensores podem assumir infinitos valores ao longo do tempo, dentro de sua faixa de operação. Ou seja, considerando os seus limites inferior e superior de saída, para qualquer variação sentida pelo sensor existirá um sinal de saída equivalente. Portanto, os sinais de saída podem variar entre inúmeros valores dentro desses limites. ariáveis como temperatura, pressão, vazão, umidade, força, velocidade, distância etc., são exemplos de variáveis que podem assumir qualquer valor ao longo do tempo. Ao lado temos um gráfico do sinal da saída de um sensor analógico.</p>

<p></p>


### Potenciômetro


<p>
	<img src="/images/potenciometro_5.jpg" alt="img" align="right" style="height: 25%; width: 25%;" >
	Um potenciômetro é um tipo especial de resistor de três terminais cuja resistência pode ser ajustada por meio mecânico, girando ou deslizando um eixo móvel, formando assim um divisor de tensão ajustável. Os potenciômetros encontram inúmeras aplicações em vários campos da tecnologia, como por exemplo em amplificadores de áudio, instrumentos musicais eletrônicos, mixers de áudio, eletrodomésticos, televisores, equipamentos industriais, joysticks, osciloscópios analógicos, e muitos outros. Basicamente, os potenciômetros são usados de duas formas em circuitos eletrônicos: como divisores de tensão ajustáveis (aplicação mais comum) ou ainda como limitadores ajustáveis de corrente.</p>
</div>


### ADC - Analog to Digital Converter (Conversor Analógico Digital)

<p>Um Conversor Analógico Digital transforma um sinal analógico, contínuo no tempo, num sinal amostrado, discreto no tempo, quantizado dentro de um número finito de valores inteiros, determinado pela resolução característica do conversor em bits (8, 10, 12, 16, entre outros). Por exemplo, num conversor de 8 bits, o sinal de entrada é transformado em amostras com os valores entre 0 e 255. Na figura abaixo temos um sinal analógico (onda senoide) se transformando em um sinal digital (onda quadrada).</p>

<img src="/images/ADCgraph.jpg" alt="img" align="center">

<p>O módulo ESP8266 NodeMCU possui um ADC e também um pino (A0 porta de entrada analógica) destinado a lidar com a leitura de um sinal Analógico, ou seja, um pino cuja função é receber níveis de tensão e em seguida traduzir os mesmos em uma linguagem adequada para que possamos manipulá-los. Este processo ocorre da seguinte maneira: o NodeMCU que estamos utilizando suporta sinais de tensão entre 0 e 3,3V em suas entradas, portanto, caso nós coloquemos um sinal de tensão de 0 volts na porta de entrada analógica A0, o nosso módulo irá associar esta informação ao número 0 (zero). Em contrapartida, caso o sinal em questão tenha magnitude de 3,3V, o NodeMCU irá referenciar este valor ao número 1023. Se a tensão estiver em qualquer valor intermediário, tera um valor proporcional dentro das 1014 divisões que é a pricisão máxima de leitura com 10 bits.</p>


<!-- <div>	
	<img src="" alt="img" style="height: 20%; width: 20%;" align="left">
</div> -->
<p></p>

## Sensor Digital

<p>
	<img src="/images/instrumentacao_e_sensores_a01_f05_a.jpg" alt="img" align="right">
	São sensores cujas amplitudes da saída são representadas por números binários. Isso significa que os níveis de tensão de saída podem ser interpretados como "0" ou "1", não havendo possibilidade de existir qualquer outro valor entre eles. No entanto, as variáveis físicas "lidas" pelos sensores digitais se apresentam na natureza de forma analógica. Então, para que esses tipos de sensores apresentem na sua saída um formato digital, faz-se necessária a utilização de um circuito eletrônico que possa fazer essa conversão. Na maioria dos casos é utilizado um conversor analógico digital. Ao lado temos um gráfico do sinal da saída de um conversor analógico digital.</p>
	
	
### Push Button

<p>
	<img src="/images/chave-tactil-push-button-BCE04-foto-prod.png" alt="img" align="right" style="height: 15%; width: 15%;" >
	O Push button (botão de pressão) é uma chave que, quando pressionado o botão, ela abre ou fecha o circuito, convertendo assim, um comando mecânico em elétrico. Geralmente eles tem um contato de ação momentânea, abrindo ou fechando o circuito apenas de modo momentâneo. As chaves podem ser do tipo NA (Normalmente aberta) Com o intuito de que, quando pressionado fecha o circuito permitindo assim a passagem de corrente, e mandando um sinal HIGH (1) para o circuito. Ou uma chave NF (normalmente fechada) a fim de que quando pressionada, abra o circuito impedindo a passagem de corrente, mandando assim um sinal LOW (0) para o circuito. Existem dois modos de usar o Push Button:</p>

<p>
	<li>Funcionamento com resistor Pull-down: Funciona como NA, ou seja, só ira mandar um sinal lógico HIGH (1) para o circuito enquanto estiver pressionado, permitindo assim passagem de corrente. Geralmente utiliza-se um resistor de 10KΩ para esta finalidade. </li>
	<li>Funcionamento com resistor Pull-up: Funciona como NF, ou seja, o circuito esta normalmente fechado, mandando um sinal HIGH (1) para o Arduino, enquanto pressionado, a porta digital irá receber um sinal LOW (0) , funciona de modo invertido ao NA.</li>
</p>

<p>O módulo ESP8266 NodeMCU possui alguns pinos GPIO (D0 e D1) em que nossos push buttons estão conectados. Eles farão o papel de Sensores Digitais.</p>

# bit, Byte e caracter

<p>O nome bit é a combinação e abreviação de "binary digit" ou dígito binário. O bit é a unidade de informação mais básica em computação e comunicação digital. O bit representa um estado lógico que pode conter dois valores possíveis como verdadeiro / falso, sim / não , ativado / desativado ou alto / baixo. No entanto esses valores geralmente são representados como "1" ou "0".</p>

<p>Um grupo de dígitos binários é comumente chamado de cadeia de bits (string), vetor de bits (array). Um grupo de oito bits é chamado de um Byte. Caracter é representação binária com 8 bits (1 byte) para codificar letras, números, acentuação, espaçamento e símbolos diversos. O símbolo internacional para o bit" de acordo com o padrão internacioal é a letra minúscula "b". Não devemos confundir com "B" maiúsculo que é o símbolo padrão internacional para o Byte.</p>

# Comunicação Serial e Paralela.

<img src="/images/Serial_vs._parallel_transmission.jpg" alt="img" align="right" style="height: 50%; width: 50%;" >

<p>Nas comunicações a transmissão de dados pode acontecer de duas formas: Paralela e Serial.</p>

<p>Na transmissão Paralela existem vários canais no barramento, um para cada bit do dado a ser transmitido e todos são enviados ao mesmo tempo. Isso garante maior velocidade e desempenho, no entanto eleva os custos pois necessita de maio quantidade de material para funcionar. Por isso não é usada em comunicação de longo alcance.</p>

Na transmissão Serial existe apenas um único canal de comunicação no barramento. O processo de envio de dados acontece Byte a Byte, com um bit sendo enviado de cada vez, sequencialmente. A comunicação serial é usada para todas as comunicações de longa distância e para a maioria das redes de computadores, onde o custo do cabo e as dificuldades de sincronização tornam a comunicação paralela impraticável.</p>

<p>Para se comunicar é necessário enivar alguma informação. Ela pode ser pequana ou grande. Quando esse tamanho é maior do que 1 Byte, ela é separada em grupos de 1 Byte cada e enviada um bit por vez. Quando um caracter é enviado, ele é representado por uma sequência de 8 bits (1 Byte). Para o computador identificar qual o caractere que está chegando é necessário determinar quando termina o envio de um caracter e inicia o seguinte. Essa separação é feita incluindo um bit adicional avisando o computador que um novo dado serial esta disponível (start bit), seguido dos bits de dados, um bit opcional de paridade (checagem de erros) e um ou mais bits de parada (stop bits). Esse é conhecido como Comunicação Assíncrona na qual os dados podem ser enviados e recebidos a qualquer momento.</p>

<table>
	<tr>
		<th>envio de 3 caracteres de forma Serial:</th>
		<th>envio de 3 caracteres de forma Paralela:</th>
  	</tr>
	<tr>
		<td><img src="/images/anim_com_serial.gif" alt="img"></td>
		<td><img src="/images/parallel.gif" alt="img"></td>
	</tr>
</table>
 
<!-- <br> </br>
<p> testando sapoha</p>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br> -->

## Métodos de Transmisão

<p>Síncrono é o método de comunicação que depende de um sinal de "clock", ou seja, cada bit ou conjunto de bits enviado depende de um pulso do clock, tendo como principal vantagem sua velocidade de transmissão de dados, em contrapartida é necessario um fio extra para o clock.</p>

<p>Assíncrono é um método de comunicação que não precisa de um sinal de clock, portanto o número de fios necessários é menor. Contudo, o envio dos dados é mais complicado e susceptível a erros, por isso alguns parâmetros são necessários para garantir o envio sem erros. Um parâmetro muito evidente em comunicações assíncrona é o Baud Rate que especifica a velocidade de recepção e envio, por isso é muito importante que os dois dispositivos utilizem a mesma taxa.</p>

## Sentido de Transmissão

<li>Simplex: os dados são enviados apenas em uma direção. Se trata de dispositivos que sua comunicação é Unidirecional. Efetua apenas o envio ou recebimento.</li>
<li>Half-duplex: os dois lados transmitem, mas somente um de cada vez. O dispositivo que comunica dessa forma pode enviar ou receber mas não executa essas funções simultaneamente.</li>
<li>Full-duplex: ambos os lados podem transmitir simultaneamente. Indica que o dispositivo pode transmitir e receber dados ao mesmo tempo.</li>

# UART

<p>
	<img src="/images/05_Understanding-UART_01_w640_hX.png" alt="img" align="right" style="height: 50%; width: 50%;">
	UART significa "Universal Asynchronous Receiver/Transmitter", ou, Transmissor/Receptor Assíncrono Universal. UART define um protocolo, ou seja, um conjunto de regras para a troca de dados seriais entre dois dispositivos. O UART é muito simples e utiliza somente dois fios entre o transmissor (Tx) e o receptor (Rx) para transmitir e receber em ambas as direções. Ambas as extremidades também têm um aterramento. A comunicação em UART pode ser simplex, half-duplex, ou full-duplex. Dados em UART são transmitidos na forma de frames. O formato e o conteúdo desses frames serão brevemente descritos e explicados. </p>

## Formato de frame (pacote) UART

<p>
	<img src="/images/05_Understanding-UART_02_w640_hX-JPG.jpg" alt="img" align="left">
	UART contém bits inciais, finais, de dados e um bit opcional de paridade para checagem de erros. Como na maioria dos Sistemas Digitais, um "alto" nível de tensão é utilizado para indicar um "1" lógico e um "baixo" nível de tensão é utilizado para indicar um "0" lógico. Uma vez que o protocolo UART não define tensões ou faixas de tensão específicas para esses níveis, algumas vezes o nível alto é chamado "marca", enquanto o nível baixo é chamado "espaço". Observe que, no estado inativo (em que nenhum dado está sendo transmitido) a linha é mantida alta. Isso permite detectar facilmente danos em uma linha ou em um transmissor.</p>

<p>Devido ao UART ser Assíncrono, o transmissor precisa sinalizar que os bits de dados estão chegando. Isso é possível ao utilizar o bit inicial. O bit inicial é uma transição do estado inativo para um estado baixo, imediatamente seguido pelos bits de dados do usuário. Depois que os bits de dados tiverem terminado, o bit final indica o fim dos dados do usuário. O bit de parada é uma transição de volta para o estado alto ou inativo, ou a permanência no estado alto for um tempo de bit adicional. Um segundo bit final (opcional) pode ser configurado, geralmente para dar ao receptor tempo para se preparar para o próximo frame, mas essa é uma prática relativamente incomum.</p>

<p>Os bits de dados são dados de usuário ou bits "úteis" e vêm imediatamente depois do bit inicial. Pode haver de 5 a 9 bits de dados de usuários, apesar de ser mais comum haver 7 ou 8 bits. Esses bits de dados geralmente são transmitidos com o bit menos significativo primeiro (LSB first).</p>

<p>Um frame UART também pode conter um bit opcional de paridade que pode ser utilizado para detecção de erros. Esse bit é inserido entre o fim dos bits de dados e o bit final. O valor do bit de paridade depende do tipo de paridade sendo utilizado (par ou ímpar):</p>

<li>Na paridade par, esse bit é definido de modo que o número total de 1s no frame seja par.</li>
<li>Na paridade ímpar, esse bit é definido de modo que o número total de 1s no frame seja ímpar.</li>

# Comunicação Serial entre Orange Pi e nodeMCU via interface UART

<div>
	<img src="/images/serialUART.jpg" alt="img" >
</div>

<p>Existe um fio conectando o pino PA13 da Orange Pi com o pino GPIO3 da nodeMCU, e, outro fio conectando o pino PA14 da Orange Pi com o pino GPIO1 da nodeMCU. Este esquema faz a comunicação serial via inteface UART onde todos as requisições e comandos são enviados pela Orange Pi. A nodeMCU recebe os comandos e responde as requisições.</p>

<br> </br>

# Protocolo:

## Códigos de para identificar módulos nodeMCU

| **nodeMCUs 1 até 8**  | **nodeMCUs 9 até 16** | **nodeMCUs 17 até 24** | **nodeMCUs 25 até 32** |
|:---------------------:|:---------------------:|:----------------------:|:----------------------:|
| 0b00000001 (node-01)  | 0b00001001 (node-09)  | 0b00010001 (node-17)   | 0b00011001 (node-25)   |
| 0b00000010 (node-02)  | 0b00001010 (node-10)  | 0b00010010 (node-18)   | 0b00011010 (node-26)   |
| 0b00000011 (node-03)  | 0b00001011 (node-11)  | 0b00010011 (node-19)   | 0b00011011 (node-27)   |
| 0b00000100 (node-04)  | 0b00001100 (node-12)  | 0b00010100 (node-20)   | 0b00011100 (node-28)   |
| 0b00000101 (node-05)  | 0b00001101 (node-13)  | 0b00010101 (node-21)   | 0b00011101 (node-29)   |
| 0b00000110 (node-06)  | 0b00001110 (node-14)  | 0b00010110 (node-22)   | 0b00011110 (node-30)   |
| 0b00000111 (node-07)  | 0b00001111 (node-15)  | 0b00010111 (node-23)   | 0b00011111 (node-31)   |
| 0b00001000 (node-08)  | 0b00010000 (node-16)  | 0b00011000 (node-24)   | 0b00100000 (node-32)   |


## Códigos de para escolher Sensores e outras funções

<!-- 
| **codigo** | **descrição**                |
|:----------:|:----------------------------:|
| 0b00100001 | nodeMCU ok                   |
| 0b00100010 | Analog Sensor                |
| 0b00100011 | Digital sensor 1             |
| 0b00100100 | Digital sensor 2             |
| 0b00100101 | LED on                       |
| 0b00100110 | LED off                      |
| 0b00100111 | Analog Sensor Monitoring     |
| 0b00101000 | Digital Sensor 1 Monitoring  |
| 0b00101001 | Digital Sensor 2 Monitoring  |
| 0b00101010 | ALL sensors Monitoring       |
| 0b00111111 | BROADCAST                    |
| 0b00000000 | sensor ERRO                  |
 -->


<!-- style="text-align: center;" -->

<table>
<thead>
  <tr>
    <th>Código</th>
    <th>Descrição</th>
    <th>Código</th>
    <th>Descrição</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>0b00100001</td>
    <td>nodeMCU ok  </td>
    <td>0b00100111</td>
    <td>Analog Sensor Monitoring</td>
  </tr>
  <tr>
    <td>0b00100010</td>
    <td>Analog Sensor</td>
    <td>0b00101000</td>
    <td>Digital Sensor 1 Monitoring</td>
  </tr>
  <tr>
    <td>0b00100011</td>
    <td>Digital sensor 1</td>
    <td>0b00101001</td>
    <td>Digital Sensor 2 Monitoring</td>
  </tr>
  <tr>
    <td>0b00100100</td>
    <td>Digital sensor 2</td>
    <td>0b00101010</td>
    <td>ALL sensors Monitoring</td>
  </tr>
  <tr>
    <td>0b00100101</td>
    <td align="center">LED on</td>
    <td>0b00111111</td>
    <td align="center">BROADCAST</td>
  </tr>
  <tr>
    <td>0b00100110</td>
    <td align="center">LED off</td>
    <td>0b00000000</td>
    <td align="center">sensor ERRO</td>
  </tr>
</tbody>
</table>

<p>O protocolo de comunicação controla e possibilita que a conexão para comunicação ou transferencia de dados entre o SBC e a NodeMCU seja realizada de forma eficiente.</p>

<p>Utilizamos o protocolo Universal Asynchronous Receiver/Transmitter (UART) para realizar essa comunicação. Seu funcionamento se dá de forma serial, ou seja, utiliza fios para conectar o transmissor e o receptor. </p>

<p>Tanto os comandos quanto as respostas são compostos por palavras de 8 bits.</p>

INSERIR CÓDIGOS DE COMANDOS AQUI

# Diagrama de Comunicação

<p>Este diagrama visa mostrar como se dá o protocolo de comunicação entre o SBC (Orange Pi PC Plus) e a nodeMCU (ESP8266) que estão acoplados em nosso protótipo. </p>

<div>
	<img src="/images/diagramaComunicação.jpg" alt="img" >
</div>


# Funcionamento do Sistema de Sensoriamento

# Fluxogramas

<!-- ![Screenshot]() -->

<p>Abaixo seguem alguns fluxogramas que detalham o funcionamento do protótipo. O primeiro sobre ligar e desligar. O segundo sobre os controles. O terceiro sobre a leitura de sensores. O quarto a respeito do monitoramento de unidades de sensoriamento. https://app.diagrams.net/ (software utilizado para criar o fluxograma)</p>

## Chave liga e desliga (DIP switch)

<p>Os dois cliclos abaixo podem acontecer em qualquer moment durante a execução. Isso quer dizer que o protótipo pode ser desligado e ligado em qualquer momento. Temos um DIP switch de quatro chaves. Usamos a quarta para ligar e desligar o protótipo</p>

<div>
	<img src="/images/Flowchart-chave-DIP-ligaEdesliga.jpg" alt="img" >
</div>

## Botões de Controle (push buttons)

<p>Para utilizar o protótipo, o usuário precisa apertar os botões disponíveis de acordo com a função desejada que é exibida no display de LCD. </p>

<div>
	<img src="/images/Flowchart-funcionamento-botões.jpg" alt="img" >
</div>

## Ler Sensores (analógico ou digital)

<p>Abaixo os detalhes de como são feitas as leituras dos sensores. Temos um Potênciômetro que fazer o papel do sensor analógico e dois push buttons que faz o papel dos sensores digitais.</p>


<div>
	<img src="/images/Flowchart-ler-sensores.jpg" alt="img" >
</div>

## Monitoramento

<p>O Monitoramento é feito da mesa forma que a leitura de qualquer sensor. A diferença é que na leitura o valor só é lido e exibido apenas uma vez. Para monitorar, a leitura é feita várias vezes e a exibição também. Podemos monitorar apenas um sensor ou todos os sensores. No caso de um único sensor os valores são exibidos na tela até que o usuárie pressine o botão ok. No caso de todos os sensores os valores são exibidos um de cada vez até que se pressione ok.</p>

<div>
	<img src="/images/Flowchart-monitorar-sensores.jpg" alt="img" >
</div>



<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>
<p></p>


## Protocolo:

<p>O protocolo de comunicação controla e possibilita que a conexão para comunicação ou transferencia de dados entre o SBC e a NodeMCU seja realizada de forma eficiente.</p>

<p>Utilizamos o protocolo Universal Asynchronous Receiver/Transmitter (UART) para realizar essa comunicação. Seu funcionamento se dá de forma serial, ou seja, utiliza fios para conectar o transmissor e o receptor. </p>

<p>Tanto os comandos quanto as respostas são compostos por palavras de 8 bits.</p>

# Resultados e Conclusões

## Requisitos Atendidos

<ul> 
<li> Solução foi desenvolvida em linguagem C </li>
<li> Contém o Script de compilação do tipo Makefile para criação do executavel </li>
<li>Para o SBC
<ul> 
  <li>Apenas o SBC é capaz de iniciar a comunicação </li>
</ul>
<li>Para a NodeMCU
<ul> 
  <li>A leitura dos sensores tem a maior precisão possível </li>
  <li>Os comandos são compostos por palavras de 1 byte (8 bits) </li>
  <li>As requisições podem ser direcionadas para uma unidade ou todas </li>
  <li>Comandos e respostas são exibidas no display LCD 16x2 </li>
</ul>
</ul>

## Conclusão

<p> Desse modo, dos requisitos descritos pelo problemas, conseguimos implementar quase todos. Cumprindo uma boa porcentagem do do que foi solicitado.</p>

<p> O protótipo não realiza a comunicação completa com as 32 NodeMCU (função de Broadcast), apesar de existir a opção no menu.</p>

<p> Em suma, é uma melhoria possível de ser implementada em versões futuras.</p>



# Desenvolvedores

| [<img src="https://avatars.githubusercontent.com/u/58979991?v=4" width=115><br><sub>Gabriel Carvalho</sub>](https://github.com/GabCarvaS) | [<img src="https://avatars.githubusercontent.com/u/7541966?v=4" width=115><br><sub>Vinicius Vieira</sub>](https://github.com/vini-insight) |
| :---------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------: |

# Referências

http://wiringpi.com/

http://wiringpi.com/pins/

https://projects.drogon.net/wiringpi-pin-numbering/

http://wiringpi.com/dev-lib/lcd-library/

http://wiringpi.com/reference/serial-library/

https://www.rohde-schwarz.com/br/produtos/teste-e-medicao/essentials-test-equipment/digital-oscilloscopes/compreender-uart_254524.html#:~:text=O%20que%20%C3%A9%20o%20UART,dados%20seriais%20entre%20dois%20dispositivos.

https://docs.freebsd.org/pt-br/articles/serial-uart/

https://newtoncbraga.com.br/index.php/telecom-artigos/1709-

https://victorvision.com.br/blog/interface-uart/

https://paginas.fe.up.pt/~hsm/misc/old/comp/uart/

https://materialpublic.imd.ufrn.br/curso/disciplina/2/61/4/7

https://www.cnblogs.com/answer/archive/2007/07/12/815282.html

https://www.robocore.net/tutoriais/comparacao-entre-protocolos-de-comunicacao-serial.html

http://www.c2o.pro.br/automacao/ar01s11.html

https://en.wikipedia.org/wiki/Serial_communication

https://edu.ieee.org/br-ufcgras/o-que-e-um-microcontrolador/

https://victorvision.com.br/blog/o-que-e-um-microcontolador/#:~:text=Para%20te%20introduzir%20no%20assunto,o%20poder%20de%20serem%20programados

https://en.wikipedia.org/wiki/Microcontroller

https://www.freecodecamp.org/news/c-vs-cpp-whats-the-difference/

https://fabacademy.org/archives/2015/doc/networking-esp8266.html

https://blogmasterwalkershop.com.br/embarcados/nodemcu/nodemcu-uma-plataforma-com-caracteristicas-singulares-para-o-seu-projeto-iot

https://embarcados.com.br/conversor-a-d/

https://www.electronics-tutorials.ws/combination/analogue-to-digital-converter.html

https://guiarobotica.com/push-button-arduino/#:~:text=O%20Push%20button%20(bot%C3%A3o%20de,circuito%20apenas%20de%20modo%20moment%C3%A2neo.

https://portal.vidadesilicio.com.br/lendo-um-potenciometro-com-o-esp8266-nodemcu/

http://www.comofazerascoisas.com.br/potenciometro-o-que-e-para-que-serve-e-como-funciona.html

https://materialpublic.imd.ufrn.br/curso/disciplina/1/52/1/8

https://materialpublic.imd.ufrn.br/curso/disciplina/1/52/1/7

https://www.mundodaeletrica.com.br/o-que-sao-sensores-e-quais-as-suas-aplicacoes/


