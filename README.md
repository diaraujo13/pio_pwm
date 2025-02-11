
# Controle de Servomotor por PWM

Autor: Izaías Araújo Gomes da Silva

Este documento descreve os passos para utilização do arquivo `pwm.c` que tem como objetivo controlar um servomotor via PWM, utilizando a placa RP2040 no ambiente Wokwi. 

Foi utilizado a biblioteca `pico/stdlib.h` para controle dos pinos GPIO e outras funções auxiliares, `hardware/pwm.h` para configuração do PWM e `<stdio.h>` para mensagens de depuração.

---
## Instruções de Uso

Para executar o projeto, siga os passos abaixo:

1. Faça o clone desse projeto em seu ambiente de desenvolvimento.
2. Verifique se a extensão Wokwi está instalada em seu ambiente do Visual Studio Code, caso contrário, instale-a (https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode)
2. Tenha a extensão do Raspberry Pi Pico (https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)
3. Tenha a extensão C/C++ (https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
3. Acesse a aba lateral do Raspberry Pi Pico Project e clique em `Import Project` e selecione a pasta do projeto no campo `Location`. Clique em `Select Pico SDK version` e selecione a versão `v2.1.0`. Por fim, clique em `Import`.
6. Após a importação, acesse novamente o menu lateral e clique em `Compile Project` para compilar o código, conferindo que os arquivos serão gerados na pasta `build`. Os arquivos de interesse são o `build/pio_pwm.uf2` e o `build/pio_pwm.elf`.
4. Abra o arquivo `diagram.json` e clique em `Start the simulation` para simular o projeto no ambiente Wokwi.

## Funcionamento

O projeto consiste em controlar um servomotor utilizando o PWM da placa RP2040. O código `pwm.c` implementa a lógica de controle do servomotor, que é acionado por um sinal PWM. O sinal PWM é gerado pelo PIO (Programmable Input/Output) da placa RP2040, que é configurado para gerar um sinal PWM com frequência de 50 Hz e ciclo de trabalho variável. O ciclo de trabalho é ajustado para controlar a posição do servomotor, que varia de 0 a 180 graus.

O LED Azul tem sua intensidade controlada pelo PWM do PIO, que é ajustado para variar a intensidade do LED de acordo, incremento/decremento o brilho.

Inicia-se o programa com o servomotor na posição 0 graus e o LED Azul com brilho máximo. Inicia-se uma sequência de movimentação suave do servomotor, primeiramente para a posição 180 graus e, em seguida, para a posição 90 graus, e por fim, para a posição 0 graus. Entre as movimentações, há um tempo de espera de 5 segundos. Por fim, um movimento contínuo entre 0 e 180 graus é realizado, com um tempo de espera de 10ms segundo entre cada incremento/decremento, onde 1 grau é incrementado.

O movimento do servomotor é limitado entre 0 e 180 graus, enquanto o brilho do LED Azul é limitado entre 0 e 100%.


## Vídeo de Demonstração

O vídeo de demonstração do projeto pode ser acessado no link abaixo:

[Link do Vídeo](https://drive.google.com/drive/u/0/folders/1bZOIqWYcuqrScCAlzAkkLm3mHE6zKTyY)
---

## Considerações Finais
- Certifique-se de que todas as configurações de GPIO e PWM estejam de acordo com as especificações da placa RP2040.
- Teste o sistema no simulador Wokwi antes de implementar no hardware real.
- Ajuste os delays e incrementos conforme necessário para obter uma movimentação suave do servomotor.
