# Piranômetro de Baixo Custo

Projeto de piranômetro (sensor de radiação solar) de baixo custo utilizando fotodiodo BPV10NF e amplificador HX711.

## 📋 Descrição

Este projeto implementa um piranômetro utilizando um fotodiodo BPV10NF acoplado a um HX711 (amplificador de célula de carga com conversor ADC de 24 bits). O sistema faz leituras contínuas da radiação solar e envia os dados brutos pela porta serial.

## 🔧 Hardware

### Componentes
- **Microcontrolador**: Heltec WiFi LoRa 32 V3 (ESP32)
- **Sensor**: Fotodiodo BPV10NF
- **Amplificador**: HX711 (ADC 24 bits)

### Conexões
| HX711 | ESP32 |
|-------|-------|
| SCK   | GPIO 48 |
| DOUT  | GPIO 47 |
| VCC   | 3.3V |
| GND   | GND |

## 💻 Software

### Requisitos
- [PlatformIO](https://platformio.org/)
- Plataforma: Espressif32
- Framework: Arduino

### Dependências
- `bogde/HX711@^0.7.5`

### Configuração Serial
- Porta: `/dev/tty.usbserial-0001` (macOS/Linux)
- Velocidade: 115200 baud

## 🚀 Como Usar

### Instalação
1. Clone o repositório
2. Abra o projeto no PlatformIO (VS Code)
3. Conecte a placa Heltec WiFi LoRa 32 V3

### Build e Upload
```bash
# Compilar o projeto
pio run

# Compilar e fazer upload
pio run --target upload

# Abrir monitor serial
pio device monitor
```

### Leitura dos Dados
O sistema envia dados no formato CSV pela porta serial:
```
timestamp_ms,raw
1234,567890
2345,568123
...
```

- **timestamp_ms**: Tempo em milissegundos desde o início
- **raw**: Valor bruto da leitura (sem offset ou calibração)

## 📊 Funcionamento

1. **Inicialização**: O HX711 é inicializado com ganho 128
2. **Amostragem**: Cada leitura é uma média de 20 amostras
3. **Frequência**: Leituras a cada 500ms
4. **Saída**: Dados brutos enviados via serial em formato CSV

## ⚙️ Parâmetros Ajustáveis

No código `src/main.cpp`:
- `AVG_SAMPLES`: Número de amostras para média (padrão: 20)
- `delay(500)`: Intervalo entre leituras em ms
- `hx.set_gain(128)`: Ganho do amplificador (128, 64 ou 32)

## 📝 Notas

- Os dados são brutos (sem offset ou calibração)
- Para calibração, será necessário processar os dados posteriormente
- O HX711 possui timeout de 5 segundos na inicialização

## 🔗 Recursos

- [Datasheet BPV10NF](https://www.vishay.com/docs/81521/bpv10nf.pdf)
- [Biblioteca HX711](https://github.com/bogde/HX711)
- [Heltec WiFi LoRa 32 V3](https://heltec.org/project/wifi-lora-32-v3/)

