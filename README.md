# 🌱 Smart Irrigation Panel
ESP8266 + MQTT + Home Assistant + Web Interface
Painel inteligente para controle de 2 válvulas solenóide com automação por horário e integração nativa com Home Assistant.



## 📌 Overview
Este projeto consiste em um painel de irrigação inteligente baseado em ESP8266, capaz de:
Controlar 2 válvulas solenóide independentes


Executar automação por horário embarcada


Integrar automaticamente com Home Assistant via MQTT Discovery


Oferecer interface web responsiva


Armazenar configurações localmente


Sincronizar horário via NTP


Operar de forma autônoma ou integrada ao HA


O sistema pode funcionar:
100% local (apenas interface web)


Integrado ao Home Assistant


Em modo híbrido (manual + automático + HA)



## 🎯 Objetivo do Projeto
Desenvolver um controlador de irrigação:
Independente de nuvem


Configurável via navegador


Persistente após reinicialização


Integrável a sistemas de automação


Seguro contra perda de energia


Modular e escalável



## 🧠 Arquitetura do Sistema
Usuário
  ↓
Interface Web (ESP8266)
  ↓
Servidor HTTP interno
  ↓
Lógica embarcada
  ↓
Relés (Válvula 1 e 2)
Modo com Home Assistant:
Home Assistant
      ↓
    MQTT Broker
      ↓
    ESP8266
      ↓
  Relé Board Serial
      ↓
 Válvulas Solenóide



## 🔌 Hardware Utilizado
ESP8266


Módulo Relé 2 canais (com protocolo serial 0xA0)


Fonte 5V estabilizada


Válvulas solenóide 127V/220V


Painel físico para instalação



## ⚙️ Principais Funcionalidades
🔹 1. Controle Manual
Acionamento individual de cada válvula


Atualização em tempo real


Sincronização MQTT



🔹 2. Automação por Horário
Até 3 ciclos diários


Horário configurável via interface


Comparação por minuto atual


Ativação simultânea das duas válvulas


Delay de 1 segundo entre acionamentos (proteção elétrica)


Lógica:
int cur = timeClient.getHours() * 60 + timeClient.getMinutes();
Evita dependência externa para temporização.

🔹 3. NTP Time Sync
Sincronização com pool.ntp.org


Atualização a cada 60 segundos


Fuso configurado (-10800 para Brasil)



🔹 4. Persistência com LittleFS
Armazena:
Horários


Ciclos ativos


Estado de automação


Configuração MQTT


Arquivo salvo em:
/config.txt
Isso garante que o sistema reinicie com a última configuração válida.

🔹 5. WiFiManager
Provisionamento automático


Cria rede "ESP_Irrigacao" se não houver Wi-Fi salvo


Portal de configuração intuitivo


Elimina necessidade de hardcoding de rede.


🔹 6. Integração com Home Assistant (MQTT Discovery)
O sistema cria automaticamente 2 entidades:
Válvula 1
Válvula 2
Tópicos:
irrigacao_esp/v1/state
irrigacao_esp/v1/set
irrigacao_esp/v2/state
irrigacao_esp/v2/set
Auto Discovery:
homeassistant/switch/irrigacao_esp_v1/config
homeassistant/switch/irrigacao_esp_v2/config
Isso permite:
Reconhecimento automático


Sincronização de estado


Controle bidirecional



## 🌐 Interface Web
Interface moderna estilo dark theme com:
Switch animado


Controle de ciclos


Seleção de horários


Auto refresh a cada 5 segundos


Página de configurações avançadas


Factory reset


Tecnologias usadas:
HTML5


CSS customizado


Fetch API


JSON


JavaScript dinâmico


PROGMEM para economia de RAM



## 🔄 Protocolo de Comunicação com Relé
Formato enviado via Serial:
[A0][Relay][State][Checksum]
Exemplo:
byte cmd[4] = {0xA0, relay, state, checksum};
Garante integridade simples da mensagem.



## 🛡️ Mecanismos de Segurança e Estabilidade
Delay entre acionamento das válvulas


Controle por estado interno (isIrrigating)


Reconexão automática MQTT


Persistência em caso de queda de energia


Factory Reset via web


Watchdog natural do loop



## 📡 mDNS
Permite acesso via:
http://esp_irrigacao.local
Sem necessidade de IP fixo.



## 📈 Escalabilidade
O sistema foi desenvolvido para permitir expansão futura:
Controle individual por ciclo


Sensores de umidade do solo


Controle remoto via LoRa


Dashboard avançado


Integração com clima


Controle por estação do ano



## 📊 Diferenciais Técnicos
✔ Integração MQTT automática
 ✔ Arquitetura híbrida (local + HA)
 ✔ Interface responsiva embarcada
 ✔ Sistema autônomo
 ✔ Persistência embarcada
 ✔ Provisionamento inteligente
 ✔ Código modular



## 👨‍💻 Autor
Marcos Gabriel Ferreira Miranda

IoT Developer | Automação Residencial e Agrícola

Belo Horizonte - MG

