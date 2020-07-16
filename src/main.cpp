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

// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3); 
// Botão definido na entrada digital 15 (GPIO15)
#define pinbotao 15 
#define led_botao 2

// Definido estado da variavel estadodobotao tipo verdadeiro ou falsa
boolean estadobotao = false; 
// Definido estado da variavel estantbotão na variavel tipo verdadeiro ou falsa
boolean estantbotao = false; 
//Definido estado da variavel troca tipo verdadeiro ou falsa
boolean troca = false;

void tela_inicial () // Função que mostra mensagem ao ligar o dispositivo
{
  //Posiciona o cursor, primeiro a coluna depois a linha
lcd.setCursor(3,0);
lcd.print("APM TERMINAL");
lcd.setCursor(4,1);
lcd.print("SISTEMA VAN");
delay(3000);
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(150);
  }
  for (int posicao = 0; posicao < 10; posicao++)
  {
    lcd.scrollDisplayRight(); //Rolagem para a direita
    delay(150);
  }
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft(); // Rolagem para a esquerda
    delay(150);
  }
delay(3000);
lcd.clear();
}

void tela_espera ()
{
 lcd.setCursor(2,0);
 lcd.print("APM TERMINAL");
 }
//Função que mostra mensagem quado a van é solicitada
void chama_van ()
{
 lcd.setCursor(2,0);
 lcd.print("VAN A CAMINHO !");
 lcd.setCursor(4,1);
 lcd.print("AGUARDE...");
}

void setup()
{ // Inicializa o LCD
  lcd.begin(16,2);
  //Liga o blacklight
  lcd.backlight();
  // Variavel pinbotao definida como entrada(INPUT)
  pinMode(pinbotao, INPUT);
  // Variavel led_botão definida como saída.(OUTPUT) 
  pinMode(led_botao,OUTPUT);
  // Inicia o serial de leitura do xbee no BAUD RATE 9600
  XBee.begin(9600);
  // Inicia o serial monitor no BAUD RATE 9600 
  //Serial.begin(9600);
  //Chama a função tela_inicial()
  tela_inicial(); 
}

void loop()
{ // Será repetido infinitamente pelo arduino
 
}