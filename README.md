🌱 Painel de Irrigação Inteligente
Um controlador de irrigação local-first desenvolvido com ESP8266, pensado para continuar funcionando mesmo sem internet ou servidor MQTT.

📸 Hardware
ESP8266

Módulo relé de 2 canais (protocolo serial 0xA0)

Fonte de 5V

Válvulas solenóides 127V/220V

🎯 Motivação
A maioria dos sistemas de irrigação depende de serviços externos e para de funcionar se a conexão cai.
Este projeto foi criado para rodar 100% localmente, com integração opcional via MQTT e Home Assistant.

🔧 Funcionalidades
Controle de 2 válvulas independentes

Até 3 ciclos de irrigação por dia

Funciona totalmente offline

Interface web responsiva (tema escuro)

Integração opcional com MQTT/Home Assistant

Configurações persistentes via LittleFS

Provisionamento de Wi-Fi com WiFiManager

🧠 Arquitetura
Modo Local  
Usuário → Interface Web (ESP8266) → Servidor HTTP interno → Lógica de controle → Relés → Válvulas

Com Home Assistant  
Home Assistant → Broker MQTT → ESP8266 → Módulo Relé → Válvulas

🌐 Interface Web
Botões de controle

Configuração de horários

Controle de ciclos

Atualização automática (5s)

Configurações avançadas

Reset de fábrica

Tecnologias: HTML5, CSS, JavaScript (Fetch API), JSON, PROGMEM

📡 Integração com Home Assistant
Descoberta automática via MQTT

Criação de entidades para cada válvula

Tópicos:

irrigacao_esp/v1/state

irrigacao_esp/v1/set

irrigacao_esp/v2/state

irrigacao_esp/v2/set

⚙️ Instalação
Clone este repositório:

bash
git clone https://github.com/seuusuario/smart-irrigation-panel.git
Abra no Arduino IDE ou PlatformIO

Configure suas credenciais de Wi-Fi (ou use o AP gerado automaticamente)

Faça o upload para o ESP8266

🚀 Uso
Acesse a interface web pelo IP do ESP8266

Configure os ciclos de irrigação

Controle manual das válvulas

Integração opcional com Home Assistant via MQTT

⚠️ Limitações
Sem sensores de umidade (irrigação baseada apenas em tempo)

Requer Wi-Fi para recursos MQTT

Sem acesso remoto sem configuração externa

📈 Melhorias Futuras
Sensores de umidade do solo

Agendamento individual por válvula

Controle remoto via LoRa

Automação baseada em clima

Dashboard avançado

👨‍💻 Autor
Marcos Gabriel Ferreira Miranda  
Desenvolvedor IoT | Automação Residencial e Agrícola
Belo Horizonte - MG
