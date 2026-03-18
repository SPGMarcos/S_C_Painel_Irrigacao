#  Painel de Irrigação Inteligente 🌱

ESP8266 + MQTT + Home Assistant + Interface Web
Painel compacto para controle de 2 válvulas solenóide, com automação por horário, operação 100% local e integração nativa com Home Assistant via MQTT Discovery.

![Dashboard](https://github.com/user-attachments/assets/link-gerado)



## 📌 Visão Geral
Projeto de controlador de irrigação embarcado que oferece:

- Controle de 2 válvulas de forma independente.

- Automação por horário com até 3 ciclos diários.

- Integração automática com Home Assistant via MQTT Discovery.

- Interface web responsiva hospedada no próprio ESP8266.

- Persistência local das configurações com LittleFS.

- Sincronização de horário via NTP para execução precisa.

O sistema opera localmente, integrado ao Home Assistant ou em modo híbrido (manual + automático + HA).



## 🎯 Objetivos do Projeto

- Independência de nuvem: operação sem dependência externa.

- Configuração via navegador simples e rápida.

- Persistência após reinicialização e proteção contra perda de energia.

- Integração com sistemas de automação (MQTT / Home Assistant).

- Design modular para facilitar expansão futura.



## 🧠 Arquitetura do Sistema

### Fluxo principal:

- Usuário → Interface Web (ESP8266) → Servidor HTTP interno → Lógica embarcada → Relés → Válvulas

### Modo com Home Assistant:

- Home Assistant → MQTT Broker → ESP8266 → Placa de Relés (serial) → Válvulas



## 🔌 Hardware Utilizado

- ESP8266 (NodeMCU / Wemos)

- Módulo Relé 2 canais (protocolo serial 0xA0)

- Fonte 5V estabilizada

- Válvulas solenóide 127V/220V conforme instalação

- Painel físico para montagem e proteção elétrica



## ⚙️ Principais Funcionalidades

- Controle Manual
Acionamento individual das válvulas via web ou MQTT.

- Atualização de estado em tempo real e sincronização bidirecional com Home Assistant.

- Automação por Horário
Até 3 ciclos diários por válvula.

- Horários configuráveis pela interface; comparação por minuto para precisão.

- Ativação simultânea possível; delay de 1 segundo entre acionamentos para proteção elétrica.

- Lógica de cálculo do minuto do dia usada na rotina:

- cpp
int cur = timeClient.getHours() * 60 + timeClient.getMinutes();
Sincronização de Horário NTP
pool.ntp.org como servidor padrão.

- Atualização periódica; fuso configurável (ex.: -10800 para Brasil).

- Persistência com LittleFS
Armazena horários, ciclos ativos, estado de automação e configuração MQTT em /config.txt.

- Garante restauração automática após reboot.

- Provisionamento Wi‑Fi
WiFiManager: cria rede ESP_Irrigacao se não houver credenciais salvas.

- Portal de configuração intuitivo, sem necessidade de hardcode.

- Integração com Home Assistant via MQTT Discovery
Cria automaticamente duas entidades: Válvula 1 e Válvula 2.

- Tópicos padrão: irrigacao_esp/v1/state; irrigacao_esp/v1/set; irrigacao_esp/v2/state; irrigacao_esp/v2/set

- Mensagens de auto discovery em: homeassistant/switch/irrigacao_esp_v1/config; homeassistant/switch/irrigacao_esp_v2/config

- Permite reconhecimento automático, sincronização de estado e controle bidirecional.



## 🌐 Interface Web

- Dark theme moderno e leve (PROGMEM para economia de RAM).

- Componentes: switch animado, seleção de horários, controle de ciclos, página de configurações avançadas e factory reset.

- Auto refresh a cada 5 segundos; comunicação via Fetch API e JSON.

- Design responsivo para celular e desktop.



## 🔄 Protocolo de Comunicação com Placa de Relés

Formato simples de 4 bytes: [0xA0][Relay][State][Checksum]

Exemplo de envio:

cpp
byte cmd[4] = {0xA0, relay, state, checksum};

Checksum básico para integridade e reenvio em caso de falha.



## 🛡️ Mecanismos de Segurança e Estabilidade

- Delay entre acionamentos para reduzir picos de corrente.

- Controle por estado interno (ex.: isIrrigating) para evitar comandos conflitantes.

- Reconexão automática MQTT e watchdog implícito pelo loop principal.

- Persistência para recuperação após queda de energia.

- Factory reset via interface para recuperação rápida.



## 📡 mDNS

- Acesso por nome local: http://esp_irrigacao.local sem necessidade de IP fixo.

- Logs básicos e indicadores de conectividade disponíveis na interface.



## 📈 Escalabilidade

Planejado para expansão sem grandes mudanças de arquitetura:

- Mais canais de válvula e controle por ciclo individual.

- Sensores de umidade do solo para irrigação por demanda.

- Comunicação LoRa para instalações remotas.

- Dashboard avançado e integração com previsões climáticas.

- Perfis sazonais e regras por estação do ano.



## 📊 Diferenciais Técnicos

- Auto discovery MQTT para integração imediata com Home Assistant.

- Arquitetura híbrida (local + HA) que prioriza operação offline.

- Interface responsiva embarcada; persistência local com LittleFS.

- Provisionamento automático via WiFiManager.

- Código modular e fácil de manter.



## 👨‍💻 Autor
Marcos Gabriel Ferreira Miranda  

IoT Developer | Automação Residencial e Agrícola

Belo Horizonte - MG
