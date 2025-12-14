# 🎯 Jogo de Reflexo: Acertar o Alvo (PIC18F4550)

> Projeto desenvolvido para a disciplina de Microcontroladores utilizando o kit didático XM118.

![MCU](https://img.shields.io/badge/Microcontrolador-PIC18F4550-blue)
![Language](https://img.shields.io/badge/Linguagem-C-orange)
![IDE](https://img.shields.io/badge/IDE-MPLAB__X-green)
![Status do Projeto](https://img.shields.io/badge/Status-Concluído-green)

## 📄 Descrição

Este projeto consiste em um jogo eletrônico de reflexo e precisão. O objetivo do jogador é pressionar o botão no momento exato em que o "alvo" (representado visualmente no kit) atinge a posição correta.

O diferencial do sistema é sua **lógica progressiva**: o jogo se torna mais rápido e desafiador a cada rodada, exigindo maior concentração do usuário.

## 🕹️ Funcionalidades do Sistema

### ⚙️ Menu de Configurações
Antes de iniciar, o usuário pode personalizar a partida através de uma interface interativa (LCD/Display):
* **Controle de Volume:** Ajuste da intensidade da música/efeitos sonoros de fundo (PWM/Buzzer).
* **Seleção de Dificuldade:** Define a velocidade inicial do alvo. Níveis mais altos resultam em movimentos mais rápidos desde o início.
* **Número de Rodadas:** Define a duração da partida.

### 🎮 Dinâmica de Jogo (Gameplay)
* **Aceleração Progressiva:** A velocidade de deslocamento do alvo não é fixa. Ela é calculada dinamicamente baseada em dois fatores:
    1.  A dificuldade escolhida inicialmente.
    2.  O número da rodada atual.
* **Feedback:** O sistema indica visualmente ou sonoramente se o usuário acertou ou errou o alvo.

## 🛠️ Hardware e Ferramentas

### Kit de Desenvolvimento: **XM118**
O projeto foi estruturado para utilizar os recursos da placa XM118.

**Periféricos Utilizados:**
* **Microcontrolador:** PIC18F4550
* **Entradas:** Botões (Push Buttons) para interação e configurações.
* **Saídas Visuais:** [LEDs / Display LCD 16x2 / Display 7 Segmentos] *(Escolha o que você usou)*.
* **Saída Sonora:** Buzzer (para a música de fundo e efeitos).

### Software
* **Linguagem:** C (Padrão ANSI/Embedded)
* **Compilador:** XC8 Compiler
* **IDE:** MPLAB X IDE

## 🧠 Conceitos Técnicos Aplicados

Neste projeto, foram exercitados conceitos fundamentais de sistemas embarcados:
* **Timers:** Para controle preciso da velocidade do alvo e varredura de tempo.
* **Interrupções:** Para leitura responsiva dos botões (evitando *polling* excessivo).
* **Máquina de Estados:** Controle do fluxo do jogo (Menu -> Jogo -> Resultado -> Fim).
* **PWM (Opcional):** Controle da frequência sonora para o volume e notas musicais.

## 🚀 Como Executar

1.  Abra o projeto no **MPLAB X IDE**.
2.  Certifique-se de que o compilador **XC8** está instalado e configurado.
3.  Conecte o gravador (ex: PICkit 3) ao kit XM118.
4.  Compile e grave o firmware no PIC18F4550.
5.  Ao iniciar, utilize os botões indicados para navegar no menu de configurações.

---

## ✒️ Autor

* **Vinicius Souza Dias** - *Desenvolvimento*

---
