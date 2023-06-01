# ⚛️ Medidor de Velocidade Média de Movimento

Medidor de velocidade para estudos de cinemática.

[:us: English](./docs/README_EN.md)

---

## Sobre

O MedidorVMM foi desenvolvido como projeto para ser exibido na [Feira de Ciências: Sustentabilidade e Inovação - 2022](https://www.educacao.ma.gov.br/feira-de-ciencias-sustentabilidade-e-inovacao/).
O projeto tem como foco a utilização da robótica e suas tecnologias para auxiliar no estudo da
física, especialmente no campo da cinemática. Neste projeto, abordaremos o uso da plataforma Arduino
e programação para criar ferramentas de estudo sobre o movimento uniforme.

---

## Esquema elétrico

Abaixo está uma imagem ilustrando o esquema elétrico do projeto.
Você pode abrir o diagrama elétrico no [Fritzing](https://fritzing.org/download/) baixando o [projeto aqui](./docs/assets/Fritzing_Diagram.fzz).

<img src="./docs/datasheets/Fritzing_Diagram.jpg" width="800">

---

## Componentes

| Nome | Modelo | Quantidade | Propriedades | Datasheet | Diagramas |
| ---- | ------ | ---------- | ------------ | --------- | --------- |
| Trilho para Movimento Retilíneo | - | 1 | Comprimento: 93cm |
| Arduino UNO | REV3 | 1 | - |
| LED Emissor IR  | TIL32 | 3 | Branco; 5mm; 940nm | [Here](./docs/datasheets/TIL32_Datasheet.pdf) |  |
| LED Receptor IR | TIL78 | 3 | Preto; 5mm; 940nm | [Here](./docs/datasheets/TIL78_Datasheet.pdf) |  |
| 1602 LCD Keypad Shield | DFR0009 | 1 | Versão antiga | [Here](./docs/datasheets/1902_LCD_Keypad_Shield_Datasheet.pdf) | [Here](./docs/datasheets/DFR0009_LCD_KeyPad_Shield_Schematic.pdf) |
| Resistor 330Ω 1/4W | CR25 | 3 | - |
| Resistor 10KΩ 1/4W | CR25 | 3 | - |
| Micro Servo Motor | SG90 9G | 1 | - | [Here](./docs/datasheets/Micro_Servo_9G_SG90_Datasheet.pdf) |  |
| Cabos | Flexível | 1 | 0.5mm; Verde, Amarelo, Preto,<br> Vermelho, Branco, Azul |
| Protoboard 170 | MB-830 | 1 | - |

---

### Direitos autorais, Licença e Créditos

[MIT License](./LICENSE)

```
Copyright (c) 2023 Abiel (Paodelonga) Mendes.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

O projeto foi baseado nos exemplos retirados do livro [_Arduino & Ensino de Física por Oséias Mourão_](https://ifce.edu.br/sobral/campus-sobral/cursos/posgraduacoes/mestrado-1/mnpef/arquivos/5-produto-educacional-arduino-e-o-ensno-de-fisica.pdf).
