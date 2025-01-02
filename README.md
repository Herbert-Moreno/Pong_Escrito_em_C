# Pong - Escrito em C
Este é um projeto simples de um **Jogo Pong** desenvolvido em **C** utilizando a Lib Raylib. O Pong é um dos primeiros jogos eletrônicos criados, e neste projeto, recriei a versão básica do jogo para testar conhecimentos em C.


## Funcionalidades

- **Singleplayer**: O jogo é jogado contra um adversário controlado por IA.
- **Controle da paleta**: O jogador controla uma paleta para rebater a bola usando as teclas: **W A S D**.
- **Pontuação**: Cada vez que a bola ultrapassa a paleta, o adversário ganha um ponto.
- **Aumento de dificuldade**: A velocidade da bola aumenta conforme o tempo de jogo, tornando o desafio mais interessante.

## Requisitos

- Saber o basico de C (se quiser modificar)
- Saber como linkar as lib no vscode
- Sistema operacional com suporte a C (Windows, Linux, macOS).
- Compilador C ("nesse projeto foi utilizado o compilador gcc").

## Como rodar

1. Clone este repositório:

> ```git clone https://github.com/seu-usuario/pong.git```

2. Abra o projeto no Visual Studio Code

> link: https://code.visualstudio.com/

3. instale a lib do Raylib usando o UCRT64(compilador C windows)

> link tutorial como instalar C pelo Vscode: https://code.visualstudio.com/docs/cpp/config-mingw

> link do msys(compilador): https://www.msys2.org/wiki/MSYS2-installation/

> codigo para baixar raylib pelo UCRT64: ```pacman -S mingw-w64-ucrt-x86_64-raylib```