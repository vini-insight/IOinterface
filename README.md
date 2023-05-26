<!-- # IOinterface
IOinterface
 -->

# Interface de E/S - Problema #2 – 2023.1

# Diagrama de Comunicação

<p>Este diagrama visa mostrar como se dá o protocolo de comunicação entre o SBC (Orange Pi PC Plus) e a nodeMCU (ESP8266) que estão acoplados em nosso protótipo. </p>

<div>
	<img src="/images/diagramaComunicação.jpg" alt="img" >
</div>

# Fluxogramas

<!-- ![Screenshot]() -->

<p>Abaixo seguem alguns fluxogramas que detalham o funcionamento do protótipo. O primeiro sobre ligar e desligar. O segundo sobre os controles. O terceiro sobre a leitura de sensores. O quarto a respeito do monitoramento de unidades de sensoriamento. https://app.diagrams.net/ (software utilizado para criar o fluxograma)</p>

## Chave liga e desliga (DIP switch)

<p>Os dois cliclos abaixo podem acontecer em qualquer moment durante a execução. Isso quer dizer que o protótipo pode ser desligado e ligado em qualquer momento. Temos um DIP switch de quatro chaves. Usamos a quarta para ligar e desligar o protótipo</p>

<div>
	<img src="/images/Flowchart-chave-DIP-ligaEdesliga.jpg" alt="img" >
</div>

<p></p>
<p></p>
<p></p>

## Botões de Controle (push buttons)

<p>Para utilizar o protótipo, o usuário precisa apertar os botões disponíveis de acordo com a função desejada que é exibida no display de LCD. </p>

<div>
	<img src="/images/Flowchart-funcionamento-botões.jpg" alt="img" >
</div>

<p></p>
<p></p>
<p></p>

## Ler Sensores (analógico ou digital)

<p>Abaixo os detalhes de como são feitas as leituras dos sensores. Temos um Potênciômetro que fazer o papel do sensor analógico e dois push buttons que faz o papel dos sensores digitais.</p>

<div>
	<img src="/images/Flowchart-ler-sensores.jpg" alt="img" >
</div>

<p></p>
<p></p>
<p></p>

## Monitoramento

<p>O Monitoramento é feito da mesa forma que a leitura de qualquer sensor. A diferença é que na leitura o valor só é lido e exibido apenas uma vez. Para monitorar, a leitura é feita várias vezes e a exibição também. Podemos monitorar apenas um sensor ou todos os sensores. No caso de um único sensor os valores são exibidos na tela até que o usuárie pressine o botão ok. No caso de todos os sensores os valores são exibidos um de cada vez até que se pressione ok.</p>

<div>
	<img src="/images/Flowchart-monitorar-sensores.jpg" alt="img" >
</div>

# Sensor

<p>Um Sensor é um dispositivo que tem a função de detectar e responder com eficiência algum estímulo. Existem vários tipos de sensores que respondem à estímulos diferentes como por exemplo: luz, som, eletricidade, magnétismo, temperatura, pressão, movimento, entre outros. Depois que o sensor recebe o estímulo, a sua função é emitir um sinal que seja capaz de ser convertido e interpretado pelos outros dispositivos.</p>

<p>Os sensores são usados em vários tipos de aplicações nas indústrias, comércios e residenciais. Por exemplo, um sensor Mecâncico pode fornecer informações a respeito de posição (linear / angular), aceleração, força, massa, densidade, momento, torque e aceleração. Um sensor Óptico, por sua vez, fornece informações a respieto de onda (amplitude, fase, polarização), velocidade da onda, índice de refração, emissividade, absorsão e refletividade.</p>

<p>A escolha do sensor depende exclusivamente do objetivo da sua instalação. Portanto, é preciso avaliar as condições do ambiente e optar pelo sensor mais adequado para aquela atividade. Existem sensores Analógicos e Digitais.</p>

## Sensor Analógico

<p>
	<img src="/images/instrumentacao_e_sensores_a01_f04_a.jpg" alt="img" align="right">
	São os sensores que respondem através de sinais analógicos. Devido à sua natureza analógica, a saída desses sensores podem assumir infinitos valores ao longo do tempo, dentro de sua faixa de operação. Ou seja, considerando os seus limites inferior e superior de saída, para qualquer variação sentida pelo sensor existirá um sinal de saída equivalente. Portanto, os sinais de saída podem variar entre inúmeros valores dentro desses limites. ariáveis como temperatura, pressão, vazão, umidade, força, velocidade, distância etc., são exemplos de variáveis que podem assumir qualquer valor ao longo do tempo. A direita temos um gráfico do sinal da saída de um sensor analógico.
</p>

<p></p>

<!-- <div>
	<img src="" alt="img" style="height: 20%; width: 20%;" align="left">
</div> -->

## Sensor Digital

<p>
	<img src="/images/" alt="img" align="right">
	
</p>

# Visão Geral do Protótipo

<div>
	<img src="/images/visãoGeralTimer.jpg" alt="img" >
</div>

# Descrição do Projeto e Requisitos

<p> O objetivo é desenvolver um software capaz de ler de sensores analógicos e digitais em um microcontrolador utilizando comunicação serial.</p>

<p> O protótipo de sistema de sensoriamento genérico utiliza uma plataforma baseada em uma <a href="https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf">NodeMCU</a> para a confecção das unidades de sensoriamento.</p>

<p> O gerenciamento do sistema será comandado por um <a href="https://dl.linux-sunxi.org/H3/Allwinner_H3_Datasheet_V1.0.pdf">Single Board Computer SPB</a> e os valores das leituras serão mostrados no  <a href="https://www.sparkfun.com/datasheets/LCD/HD44780.pdf">display LCD 16x2</a></p>

## Requisitos Atendidos

<ul> 
<li> Solução desenvolvida em linguagem C </li>
<li>Script de compilação do tipo Makefile para criação do executavel </li>
<li>Para o SBC
<ul> 
  <li>Apenas o SBC é capaz de iniciar a comunicação </li>
  <li>Interligação com até 32 unidades de sensoriamento </li>
</ul>
<li>Para a NodeMCU
<ul> 
  <li>A leitura dos sensores deve ter a maior precisão possível </li>
  <li>Os comandos serão compostos por palavras de 1 byte (8 bits) </li>
  <li>As requisições podem ser direcionadas para uma unidade ou todas </li>
  <li>Comandos e respostas devem ser exibidas no display LCD 16x2 </li>
</ul>
</ul>

# Makefile

<p>Um makefile é um arquivo que por padrão é chamado de "Makefile". Nele contém um conjunto de diretivas usadas pela ferramenta de automação de compilação make para gerar um alvo/meta(instalar, desinstalar, remover alguns arquivos e outros). Um makefile contém essencialmente atribuições de variáveis, comentários e regras (“targets”). Comentários são iniciados com o carácter "#".</p>

<p>O texto contido em um Makefile é usado para a compilação, ligação(linking), montagem de arquivos de projeto entre outras tarefas como limpeza de arquivos temporários, execução de comandos, etc. Vantagens do uso do Makefile:</p>

<li>Evita a compilação de arquivos desnecessários. Por exemplo, se seu programa utiliza 120 bibliotecas e você altera apenas uma, o make descobre (comparando as datas de alteração dos arquivos fontes com as dos arquivos anteriormente compilados) qual arquivo foi alterado e compila apenas a biblioteca necessária.</li>
<li>Automatiza tarefas rotineiras como limpeza de vários arquivos criados temporariamente na compilação.</li>
<li>Pode ser usado como linguagem geral de script embora seja mais usado para compilação.</li>

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
	<img src="" alt="img" style="height: 20%; width: 20%;" align="left">

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

# Diagrama de Pinagem do Orange Pi PC Plus v1.2

<div>
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
	<p>Esta seção apresenta o mapeamento dos pinos GPIO com as conexões do display (LCD 16x2) e botões (push buttons) utilizados no projeto. O mapeamento é essencial para garantir a correta comunicação entre o Orange PI e os demais componentes, possibilitando funcionamento das interfaces de usuário.</p>
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
    <p>Para simplificar a manipulação do display e das informações que serão exibidas, foi utiilizada a biblioteca lcd.h </p>
</div>

# Interface GPIO com o Botões e LEDs

<div>
	<img src="/images/GPIOtoLEDSandBUTTONS subtitles.jpg" alt="img" >
	<p>Temos também o mapeamento entre a GPIO e os pinos que se conectam aos botões (push buttons) que pode ser visto em detalhes na imagem acima. Os pinos GPIO conectados aos botões são configurados como Entrada. Os botões quando pressionados indicam Anterior, Confirma e Próximo nas opções do menu que aparecem no Display LCD 16x2. </p>	
</div>

## Display LCD 16x2

<img src="/images/LCD 16x2 myPinout.jpg" alt="img" >

<!-- <div> -->

<p>O LCD 16 × 2 é chamado assim porque tem 16 colunas e 2 linhas. Existem muitas combinações disponíveis, como 8×1, 8×2, 10×2, 16×1, etc. Mas a mais usada é a LCD 16x2.</p>
	
<p>IC de interface como o HD44780 , que é montado no próprio módulo LCD. A função deste IC é obter os comandos e dados do MCU e processá-los para exibir informações significativas em nossa tela LCD.</p>
<!-- </div> -->

## Seleção da NodeMCU

<img src="/images/selecaoNode.png" alt="img" >

<p>Exemplo de funcionamento: Seleção da NodeMCU.</p>

## Seleção do sensor

<img src="/images/escolhaSensor.png" alt="img" >

<p>Exemplo de funcionamento: Seleção do Tipo de Sensor.</p>

### Leitura do Sensor Digital

<img src="/images/leituraSensor.png" alt="img" >

<p>Exemplo de funcionamento: Seleção do Sensor Digital.</p>

### Leitura do Sensor Analógico

<img src="/images/leituraSensorAnalogico.png" alt="img" >

<p>Exemplo de funcionamento: Seleção do Sensor Analógico.</p>

## Protocolo:

<p>O protocolo de comunicação controla e possibilita que a conexão para comunicação ou transferencia de dados entre o SBC e a NodeMCU seja realizada de forma eficiente.</p>

<p>Utilizamos o protocolo Universal Asynchronous Receiver/Transmitter (UART) para realizar essa comunicação. Seu funcionamento se dá de forma serial, ou seja, utiliza fios para conectar o transmissor e o receptor. </p>

<p>Tanto os comandos quanto as respostas são compostos por palavras de 8 bits.</p>

# Referências

https://materialpublic.imd.ufrn.br/curso/disciplina/1/52/1/7

https://www.mundodaeletrica.com.br/o-que-sao-sensores-e-quais-as-suas-aplicacoes/

# Desenvolvedores

| [<img src="https://avatars.githubusercontent.com/u/58979991?v=4" width=115><br><sub>Gabriel Carvalho</sub>](https://github.com/GabCarvaS) | [<img src="https://avatars.githubusercontent.com/u/7541966?v=4" width=115><br><sub>Vinicius Vieira</sub>](https://github.com/vini-insight) |
| :---------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------: |
