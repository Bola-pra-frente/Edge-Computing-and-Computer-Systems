# Edge-Computing-and-Computer-Systems

## Integrantes

| Nome               | RM     |
| ------------------ | ------ |
| Mateus Macedo      | 563294 |
| Gustavo Cavalcanti | 565601 |
| Matheus Augusto    | 565931 |
| Tomás Antonio      | 563295 |
| Felipe Riofrio     | 563068 |

## Descrição do Projeto

Este projeto consiste em um sistema de monitoramento de movimento e temperatura utilizando um microcontrolador ESP32 e um sensor MPU6050 (acelerômetro e giroscópio). O dispositivo coleta dados de aceleração (eixos X, Y, Z), rotação (eixos X, Y, Z) e temperatura, e os envia via Wi-Fi para a plataforma de IoT ThingSpeak. Isso permite a visualização e análise dos dados em tempo real através de gráficos na nuvem.

## Arquitetura Proposta

O sistema segue uma arquitetura simples de IoT, onde o sensor coleta os dados, o microcontrolador processa e os envia para a nuvem através da internet.

### Diagrama de Fluxo

```
[Sensor MPU6050] --> [ESP32] --> [Roteador Wi-Fi] --> [Internet] --> [API ThingSpeak]
```

### Explicação

1.  **Sensor MPU6050**: Captura os dados brutos de aceleração, giroscópio e temperatura.
2.  **ESP32**: Lê os dados do sensor via I2C, estabelece uma conexão com a rede Wi-Fi local e formata os dados para serem enviados via requisição HTTP GET.
3.  **Roteador Wi-Fi**: Fornece a conexão do ESP32 com a Internet.
4.  **API ThingSpeak**: É a plataforma em nuvem que recebe a requisição HTTP, armazena os dados nos campos correspondentes do canal e os disponibiliza para visualização.

## Instruções de Uso

### Hardware Necessário

- Placa de desenvolvimento ESP32
- Sensor Acelerômetro e Giroscópio MPU6050
- Jumpers para as conexões

### Software Necessário

- Arduino IDE com o suporte para placas ESP32 instalado.
- Bibliotecas Arduino:
  - `Adafruit MPU6050`
  - `Adafruit Unified Sensor`

### Configuração e Execução

1.  **Montagem do Circuito**: Conecte o sensor MPU6050 ao ESP32.

    - `VCC` do MPU6050 -> `3.3V` do ESP32
    - `GND` do MPU6050 -> `GND` do ESP32
    - `SCL` do MPU6050 -> `GPIO 22` do ESP32
    - `SDA` do MPU6050 -> `GPIO 21` do ESP32

2.  **Configuração do ThingSpeak**:

    - Crie uma conta no [ThingSpeak](https://thingspeak.com/).
    - Crie um novo canal ("New Channel").
    - Habilite 7 campos ("Field 1" a "Field 7") para receber os dados de aceleração (X, Y, Z), rotação (X, Y, Z) e temperatura.
    - Vá para a aba "API Keys" e copie sua "Write API Key".

3.  **Configuração do Código**:

    - Abra o arquivo [`codigo fonte/medidor_acelerometro.cpp`](codigo%20fonte/medidor_acelerometro.cpp) na Arduino IDE.
    - Altere as variáveis `ssid` e `password` com as credenciais da sua rede Wi-Fi.

    ```cpp
    // ...existing code...
    // Defina suas credenciais Wi-Fi
    const char* ssid = "SUA_REDE_WIFI";
    const char* password = "SUA_SENHA_WIFI";
    // ...existing code...
    ```

    - Cole a sua "Write API Key" do ThingSpeak na variável `thingSpeakUrl`.

    ```cpp
    // ...existing code...
    // URL do ThingSpeak API (substitua pelo seu canal e chave de API)
    const String thingSpeakUrl = "https://api.thingspeak.com/update?api_key=SUA_CHAVE_API";
    // ...existing code...
    ```

4.  **Upload e Monitoramento**:
    - Conecte o ESP32 ao seu computador.
    - Na Arduino IDE, selecione a placa "ESP32 Dev Module" (ou similar) e a porta COM correta.
    - Clique em "Upload" para gravar o código no ESP32.
    - Abra o "Serial Monitor" com a velocidade de `115200` para acompanhar o status da conexão e os dados que estão sendo enviados.
    - Acesse seu canal no ThingSpeak para visualizar os dados sendo plotados nos gráficos.
