#include <Arduino.h>
#include "HX711.h"

// Pinos do HX711
static const int PIN_SCK  = 48;  
static const int PIN_DOUT = 47;  

HX711 hx;

// Número de amostras para média
static const int AVG_SAMPLES = 20;

// Função para ler média de N amostras
long readAvg(int n) {
  long sum = 0;
  for (int i = 0; i < n; i++) {
    sum += hx.read();
    delay(5);
  }
  return sum / n;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("===================================");
  Serial.println("Piranometro de Baixo Custo");
  Serial.println("Fotodiodo BPV10NF + HX711");
  Serial.println("===================================");

  // Inicializa HX711
  hx.begin(PIN_DOUT, PIN_SCK);
  hx.set_gain(128);

  // Aguarda HX711 ficar pronto
  Serial.print("Aguardando HX711... ");
  unsigned long t0 = millis();
  while (!hx.is_ready()) {
    if (millis() - t0 > 5000) {
      Serial.println("FALHOU!");
      Serial.println("Verifique as conexoes!");
      while(1) { delay(1000); }
    }
    delay(50);
  }
  Serial.println("OK!");

  Serial.println("-----------------------------------");
  Serial.println("Coletando dados brutos (sem offset)");
  Serial.println("timestamp_ms,raw");
}

void loop() {
  if (!hx.is_ready()) {
    delay(500);
    return;
  }

  long raw = readAvg(AVG_SAMPLES);

  // Saída simples: tempo e valor bruto
  Serial.print(millis());
  Serial.print(",");
  Serial.println(raw);

  delay(500);
}