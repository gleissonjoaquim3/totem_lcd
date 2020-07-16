/* Copyright (C) 2020  Gleisson J. J. Cardoso <gleissoncg2@gmail.com>
 *               2020  Robson Cordeiro  <robson.cordeiro@apmt.com>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    .
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/* Código para que seja enviado um sinal via placa xbee para outro dispositivo xbee
//que ao receber este sinal envia outro como resposta */

#include <SoftwareSerial.h> // Inclusão de biblioteca
#include <Arduino.h> // Inclusão de biblioteca
#include <LiquidCrystal_I2C.h>

// Seleciona o números de colunas e linhas do LCD.
int lcdColumns = 16;
int lcdRows = 2;

//Neste programa o LCD está ligado ao esp32 na GPIO21 = SDA / GPIO22 = SCL
//Seleciona o endereço do LCD e seleciona coluna e linhas.
//Se voce não sabe qual o endereço do seu LCD terá que rodar um programa para scanear(Por exemplo: I2C scanner sketch).
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

SoftwareSerial XBee(2, 3); // RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
#define pinbotao 15 // Botão definido na entrada digital 12
#define led_botao 2

boolean estadobotao = false; // Definido estado da variavel estadodobotao tipo verdadeiro ou falsa
boolean estantbotao = false; // Definido estado da variavel estantbotão na variavel tipo verdadeiro ou falsa

void setup()
{ // Inicializa o LCD
  lcd.init();
  //Liga o blacklight
  lcd.backlight();
  //Posiciona o cursor, primeiro a coluna depois a linha
  lcd.setCursor(2,0);
  // Manda uma mensagem
  lcd.print("APM TERMINAL");
  lcd.setCursor(3,1);
  lcd.print("VAN OFICINA");
  delay(3000);
  pinMode(pinbotao, INPUT); // Variavel pinbotao definida como entrada(INPUT)
  pinMode(led_botao,OUTPUT);

   XBee.begin(9600); // Inicia o serial de leitura do xbee no BAUD RATE 9600
  //Serial.begin(9600); // Inicia o serial monitor no BAUD RATE 9600
}

void loop()
{ // Será repetido infinitamente pelo arduino
  XBee.available();  // Verifica se há algum xbee disponivel
  char c = XBee.read(); // Armazena na variavel c o sinal recebido
  //Serial.print(c);
  estadobotao = digitalRead(pinbotao); // estadobotao recebe o sinal do botão

  if (estadobotao == HIGH) // se o botão for pressionado
  {
    XBee.write('L');
    delay(500); // Manda um caracter 'L' para outro disposisivo
  }

  if (estadobotao && !estantbotao ) // Condição que compara o estado atual com o estado anterior do botão
  {
  }

  if (c == 'l' ) // Condição caso receba o caracter correto e o pisca for false
  {
    // Acende o led verde por x segundos e apaga o led vermelho
  }
   // Aqui digo que caso o botao seja acionado entrará em modo de pisca
  delay(200);
}