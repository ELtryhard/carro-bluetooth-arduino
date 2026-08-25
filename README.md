# Carro Controlado por Bluetooth com Arduino (PAP)

Projeto desenvolvido como Prova de Aptidão Profissional (PAP) do Curso Profissional de Técnico de Gestão e Programação de Sistemas Informáticos (TGPSI), na Escola Secundária do Castelo da Maia.

## Descrição

Carro robótico com dois modos de funcionamento, controlado por um Arduino:

- **Modo Manual**: controlado remotamente via Bluetooth, através de uma aplicação móvel desenvolvida em MIT App Inventor, que envia os comandos de movimento (frente, trás, esquerda, direita).
- **Modo Autónomo**: o carro anda sozinho, utilizando um sensor ultrassónico (HC-SR04) para detetar obstáculos e desviar-se automaticamente.

Um botão físico permite alternar entre os dois modos, ligando e desligando os motores consoante o modo selecionado.

## Componentes utilizados

- Arduino (Uno/Nano)
- Módulo Bluetooth HC-05
- Sensor ultrassónico HC-SR04
- Motores DC + ponte H (driver de motores)
- Botão físico para alternância de modo
- Chassis do carro

## Aplicação Móvel

A aplicação de controlo remoto foi desenvolvida em **MIT App Inventor**, comunicando com o Arduino via Bluetooth para envio dos comandos de movimento.

## Autor

André Patrício
