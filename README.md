# Interface de E/S - Problema #2 – 2023.1

# Demonstração

# Fluxograma

![Screenshot]()

https://app.diagrams.net/ (software utilizado para criar o fluxograma)

# Visão Geral do Protótipo

<div>
	<img src="" alt="img" >
</div>

# Descrição do Projeto e Requisitos

<p> O objetivo é desenvolver um software capaz de ler de sensores analógicos e digitais em um microcontrolador utilizando comunicação serial.</p>

<p> O protótipo de sistema de sensoriamento genérico utiliza uma plataforma baseada em uma <li><a href="https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf">NodeMCU</a></li> para a confecção das unidades de sensoriamento.</p>

<p> O gerenciamento do sistema será comandado por um <li><a href="https://dl.linux-sunxi.org/H3/Allwinner_H3_Datasheet_V1.0.pdf">Single Board Computer SPB</a></li> e os valores das leituras serão mostrados no  <li><a href="https://www.sparkfun.com/datasheets/LCD/HD44780.pdf">display LCD 16x2</a></li></p>

## Requisitos Atendidos

- Solução desenvolvida em linguagem C
- Script de compilação do tipo Makefile para criação do executavel
- Para o SBC
  - Apenas o SBC é capaz de iniciar a comunicação
  - Interligação com até 32 unidades de sensoriamento
- Para a NodeMCU
  - A leitura dos sensores deve ter a maior precisão possível
  - Os comandos serão compostos por palavras de 1 byte (8 bits)
  - As requisições podem ser direcionadas para uma unidade ou todas
  - Comandos e respostas devem ser exibidas no display LCD 16x2

# Makefile

<p>Um makefile é um arquivo que por padrão é chamado de "Makefile". Nele contém um conjunto de diretivas usadas pela ferramenta de automação de compilação make para gerar um alvo/meta(instalar, desinstalar, remover alguns arquivos e outros). Um makefile contém essencialmente atribuições de variáveis, comentários e regras (“targets”). Comentários são iniciados com o carácter "#".</p>

<p>O texto contido em um Makefile é usado para a compilação, ligação(linking), montagem de arquivos de projeto entre outras tarefas como limpeza de arquivos temporários, execução de comandos, etc. Vantagens do uso do Makefile:</p>

- Evita a compilação de arquivos desnecessários. Por exemplo, se seu programa utiliza 120 bibliotecas e você altera apenas uma, o make descobre (comparando as datas de alteração dos arquivos fontes com as dos arquivos anteriormente compilados) qual arquivo foi alterado e compila apenas a biblioteca necessária.
- Automatiza tarefas rotineiras como limpeza de vários arquivos criados temporariamente na compilação.
- Pode ser usado como linguagem geral de script embora seja mais usado para compilação.

<p>O objetivo de Makefile é definir regras de compilação para projetos de software. O programa make interpreta o conteúdo do Makefile e executa as regras lá definidas.</p>

# Ambiente de Desenvolvimento e Testes

# Arquitetura ARM

ARM significa Advanced RISC Machines, ou Máquinas RISC Avançadas. RISC é acrônimo de Reduced Instruction Set Computer, ou Computador com um conjunto reduzido de instruções. O que mostra que a arquitetura ARM foi inspirado no RISC, onde o objetivo era desenvolver um hardware simples e também um conjunto pequeno de instruções que garanta tamanho reduzido, velocidade e eficiência no consumo de potência.

# Orange Pi PC Plus

<div>
	<img src="/images/Orange Pi PC Plus - Copia.png" alt="img" style="height: 50%; width: 50%;" align="right">
	<p>Orange Pi PC Plus é um SBC Single-Board Card computer, ou, Computador de Cartão de Placa Única. Tem código aberto e usa arquitetura ARM. Suporta alguns Sistemas Operacionais como Android, Debian, Lubuntu, Ubuntu. Orange Pi PC Plus usa Allwinner H3 como CPU.</p>
	<p>A Orange Pi PC Plus pode ser usada para construir um servidor de rede sem fio, jogos, Reprodutor de música e video, entre outros fins. Ela foi projetada para quem deseja usar a tecnologia para criar e inovar.</p>
	<p>O sistema operacional da Orange Pi que utilizamos no laboratório é o Ubuntu Armbian 22.08.8 Jammy. Seu Kernel é Linux 5.15.74-sunxi. Acessamos a placa utilizando um terminal de comandos utilizando protocolo SSH. Para mais informações sobre a Orange Pi, consultar site oficial (http://www.orangepi.org/html/hardWare/computerAndMicrocontrollers/details/Orange-Pi-PC-Plus.html) </p>
</div>

# SSH

<img src="/images/SSH.png" alt="img" align="center">

<p>SSH é a sigla para Secure Socket Shell. Em tradução livre, significa “Concha de Segurança”, mas pode ser adaptado para o termo “Bloqueio de Segurança”. Sendo um dos protocolos específicos de segurança de troca de arquivos entre cliente e servidor de internet, usando criptografia. O objetivo do SSH é permitir que desenvolvedores ou outros usuários realizem alterações em sites e servidores utilizando uma conexão simples e segura.</p>
<p>Para para abrir conexões desse tipo utilizado o protocolo SSH, o sistema operacional deve ter um clienteSSH de forma nativa ou pode ser instalado. No Linux bastar abrir o Terminal e digitar comando SSH que consiste em 3 partes distintas:</p>

    ssh {user}@{host}

<p>O comando da tecla SSH instrui o sistema que deseja abrir uma Conexão de Shell segura criptografada. O {User} representa a conta à qual você deseja acessar. Por exemplo, você pode querer acessar o usuário raiz, que é basicamente sinônimo, para o administrador do sistema, com direitos completos para modificar qualquer coisa no sistema. O {host} refere-se ao computador ao qual você deseja acessar. Este pode ser um endereço IP (por exemplo, 244.235.23.19) ou, um nome de domínio (por exemplo, www.xyzdomain.com).</p>
<p>Quando você pressionar enter, você será solicitado a inserir a senha da conta solicitada. Quando você digitou, nada aparecerá na tela, mas sua senha é, de fato, transmitida. Depois de terminar de digitar, pressione enter mais uma vez. Se sua senha estiver correta, você será saudado com uma janela de terminal remota como na imagem abaixo: </p>

<img src="/images/TERMINAL.png" alt="img" align="center">

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

<p>GPIO São usados por circuitos de sistema em chip (SOC), que incluem um processador, memória e interfaces externas em um único chip. Os pinos GPIO permitem que esses chips sejam configurados para diferentes finalidades e funcionem com diversos tipos de componentes.</p>

<p>As interfaces GPIO são geralmente usadas em conjunto com uma placa de prototipação (Protoboard). Protoboards são um tipo de placa de circuito temporária. Você pode prototipar circuitos adicionando, removendo ou movendo componentes eletrônicos. Muitos projetos que envolvem dispositivos como um Orange Pi fazem com que você monte seu dispositivo em uma placa de ensaio e, em seguida, conecte-o aos pinos GPIO usando fios.</p>

<p>Um dispositivo popular que faz uso de pinos GPIO é o Orange Pi. Esses pinos atuam como interruptores que produzem 3,3 volts quando definidos como ALTO e sem tensão quando definidos como BAIXO. Você pode conectar um dispositivo a pinos GPIO específicos e controlá-lo com um programa de software. Por exemplo, você pode conectar um LED a um GPIO e um pino de aterramento em um Orange Pi. Se um programa de software disser ao pino GPIO para ligar, o LED acenderá.</p>
</div>

# Comando "gpio readall"

<div>
	<p>Para visualizar a flexibilidade de configuração dos pinos GPIO, abaixo segue um print da configuração padrão, quando a Orange Pi acabou de se ligada e o seu sistema operacional iniciado. Apenas digitamos o comando 'gpio readall' no terminal e vemos a saída abaixo:</p>
	<br>
	<img src="/images/Comando gpio readall DefaultSetting.png" alt="img">
	<br>
	<br>
	<p>Observe que a maior parte dos pinos está em modo 'OFF'. No entanto, depois que os pinos GPIO são configurados em linguagem Assembly, executamos novamente no terminal o comando 'gpio readall' e os pinos GPIO são configurados como segue o print abaixo:</p>
	<br>
	<img src="/images/Comando gpio readall PersonalSetting.png" alt="img">
	<br>
	<br>
	<p> É necessário destacar que os pinos GPIO que estão conectados a botões são definidos como 'IN' (entrada) e os pinos GPIO que estão conectados aos LEDs e também ao display LCD estão definidos como 'OUT' (saída).</p>
</div>

# Diagrama de Pinagem do Orange Pi PC Plus v1.2

<div>
<!-- 	<img src="/images/orangePI PC PLUS pinout diagram.png" alt="img" style="height: 20%; width: 20%;" align="left"> -->
	<img src="/images/orangePI PC PLUS pinout diagram.png" alt="img" >
</div>

# Corte detalhado da interface GPIO com os demais componentes

<div>
	<img src="/images/placa de extensão GPIO.jpg" alt="img" >
	<p>Utilizamos uma placa de prototipação (protoboard) para reunir todos os componentes eletrônicos do projeto. A Orange PI e sua porta GPIO é conectada usando uma Placa de Extenção que pode ser vista em destaque na imagem acima. Esta placa de Extenção é de uma Raspberry PI, no entanto, sua interface tem a mesma quantidade de pinos da Orange Pi. Por isso, vamos desconsiderar os nomes inscritos originalmente na Placa de Extenção e vamos adotar a nomenclatura oficial do Diagrama de Pinagem da Orange Pi.</p>
</div>

# Mapeamento dos pinos GPIO

<div>
	<img src="/images/mapeamentoGPIO.jpg" alt="img" >
	<p>Esta seção apresenta o mapeamento dos pinos GPIO com as conexões do display (LCD 16x2), botões (push buttons) e LEDs (Vermelho e Azul) utilizados no projeto. O mapeamento é essencial para garantir a correta comunicação entre o Orange PI e os demais componentes, possibilitando funcionamento das interfaces de usuário.</p>
</div>

# Esquemático do protótipo

<img src="/images/esquematico.jpg" alt="img" >

<p>Prototipação feita antes da montagem dos componentes.</p>

# Interface GPIO com o Display LCD 16x2

<div>
	<img src="/images/GPIOtoLCD subtitles.jpg" alt="img" >
	<p>O mapeamento entre a GPIO e o display LCD 16x2 no modo 4 bits é feito por meio da conexão de 7 pinos da porta GPIO da Orange Pi com outros 7 pinos do microcontrolador display (LCD 16x2). Esses 7 pinos são divididos em 4 bits de dados e 3 bits de controle.</p>
	<p>Os 4 bits de dados (DB4 a DB7) são responsáveis por enviar as informações que serão exibidas no display. Já os 3 bits de controle (RS, Enable e RW) são responsáveis por indicar ao display qual informação está sendo enviada (dados ou instruções), quando uma nova informação deve ser lida (sinal de enable) e se a operação será de escrita ou leitura (neste caso, o bit RW é configurado como leitura ou escrita).Neste contexto, o bit referente ao RW é sempre setado como escrita.</p>
	<p>Para o mapeamento, são utilizados os pinos GPIO do microcontrolador, que são configurados como saídas e conectados aos pinos correspondentes no display.</p>
</div>

# Interface GPIO com o Botões e LEDs

<div>
	<img src="/images/GPIOtoLEDSandBUTTONS subtitles.jpg" alt="img" >
	<p>Temos também o mapeamento entre a GPIO e os pinos que se conectam aos LEDs (vermelhor e azul) e botões (push buttons) que pode ser visto em detalhes na imagem acima. Os pinos GPIO conectados aos LEDs são configurados como pinos de Saída e os que estão conectados aos botões são configurados como Entrada. Os botões quando pressionados Iniciam, Pausam, e Reinicial a contagem no Display LCD 16x2. Quando a contagem é iniciada, o LED vermelho está desligado. Permanece desligado até o fim da contagem. Nesse momento é ligado durante apenas um segundo e depois é desligado. O LED azul é ligado quando a contagem começa e desliga quando a contagem termina. </p>	
</div>

# Datasheets

<p> Datasheet significa ficha ou folha de dados. Normalmente são criadas pelo fabricante do produto ou componente eletrônico. Basicamente é um documento que fornece as especificações de desempenho e outras características. O Datasheet forncesse detalhes suficientes que permitem entender o que é o produto ou componente assim como entender a função do componente no sistema geral. Dependendo da finalidade específica, uma folha de dados pode oferecer um valor médio , um valor típico, uma faixa típica, tolerâncias de engenharia ou um valor nominal . O tipo e a fonte dos dados geralmente são declarados na folha de dados. Uma folha de dados é geralmente usada para comunicação comercial, comunicação técnica para descrever as características de um item ou produto, ou para ajudar a usar os produto.</p>

<p>Datasheets podem ser encontrados no site do fabricante ou em qualquer buscador na internet. Para isso basta digitar "datasheet" + "nome do componente" ou "código do componente". Também existem vários sites que reúnem e compartilham milhares de Datasheets funcionando como verdadeiros repositórios para este tipo de informação. Alguns exemplos são: www.alldatasheet.com OU www.datasheetcatalog.com</p>

</p> Neste projeto vamos utilizar dois Datasheets. Um do processador Allwinner H3 (usado pela Orange Pi) e outro que mostra como usar e configurar o Display LCD 16x2. Uma cópia deles pode ser encontrada aqui mesmo neste projeto acessando a pasta "Datasheets" ou clicando direto nesse link: https://github.com/vini-insight/Assembly1/tree/main/Datasheets </p>

## Allwinner H3

<p> O Datasheet do processador forncesse informações do Mapeamento de Memória, do Controle de Portas de Entrada e Saída, além de como se devem configurar os registradores que fazem a gerenciamento do pinos que esta sendo usados na Porta GPIO. Lembrando que a representação é de 32 bits. Lá são detalhados as posições de cada bit e seus respectivos valores para determinadas funções. Basicamente precisamos saber as informações abaixo para cada pino utilizado:<p>

    Identificação do Pino
    Valor do offset do registrador de função do pino;
    Valor do menor bit da sequencia de 3 bits (o que gera 8 possibilidades de configurações do pino);
    Valor do bit correspondente entre a sequencia de bits 21:0 (21 até 0) para os pinos PAs, OU, 13:0 (13 até 0) para os pinos PGs;
    Valor do offset do registrador de dados;

</p>
</p>
</p>
</p>

## Display LCD 16x2

<img src="/images/LCD 16x2 myPinout.jpg" alt="img" >

<!-- <div> -->

<p>O LCD 16 × 2 é chamado assim porque; tem 16 colunas e 2 linhas. Existem muitas combinações disponíveis, como 8×1, 8×2, 10×2, 16×1, etc. Mas a mais usada é a LCD 16x2. Todos os visores LCD mencionados acima terão 16 pinos e a abordagem de programação também é a mesma.</p>
	
<p>O LCD é matricial de 16*2 pontos e assim terá (16*2=32) 32 caracteres no total e cada caractere será feito de 5*8 pontos de pixel. Agora, sabemos que cada caractere tem (5*8=40) 40 pixels e para 32 caracteres teremos (32*40) 1280 pixels. Além disso, o LCD também deve ser instruído sobre a posição dos pixels.</p>
	
<p>IC de interface como o HD44780 , que é montado no próprio módulo LCD. A função deste IC é obter os comandos e dados do MCU e processá-los para exibir informações significativas em nossa tela LCD.</p>
<!-- </div> -->

### Comandos:

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

# Desenvolvedores

| [<img src="https://avatars.githubusercontent.com/u/58979991?v=4" width=115><br><sub>Gabriel Carvalho</sub>](https://github.com/GabCarvaS) | [<img src="https://avatars.githubusercontent.com/u/7541966?v=4" width=115><br><sub>Vinicius Vieira</sub>](https://github.com/vini-insight) |
| :---------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------: |

# Referências

https://embarcados.com.br/introducao-ao-makefile/
http://orion.lcg.ufrj.br/compgraf1/downloads/MakefileTut.pdf
https://terminalroot.com.br/2019/12/como-criar-um-makefile.html#:~:text=Um%20makefile%20%C3%A9%20um%20arquivo,remover%20alguns%20arquivos%20e%20outros).
https://pt.wikibooks.org/wiki/Programar_em_C/Makefiles
https://resultadosdigitais.com.br/marketing/ssh/#:~:text=SSH%20%C3%A9%20a%20sigla%20para,uma%20conex%C3%A3o%20simples%20e%20segura.
