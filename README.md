🌱 Painel de Irrigação Inteligente
Um controlador de irrigação local-first desenvolvido com ESP8266, pensado para continuar funcionando mesmo sem internet ou servidor MQTT.

📸 Montagem de Hardware
Painel principal

Módulo relé de 2 canais

Válvulas solenóides 127V/220V

Fonte de 5V

🎯 Motivação
Eu precisava de um sistema de irrigação confiável, que não dependesse da nuvem e não parasse de funcionar caso a conexão caísse.
A maioria das soluções disponíveis depende fortemente de serviços externos, então criei este projeto para rodar 100% localmente, com MQTT e Home Assistant como camadas opcionais.

🔧 O que ele faz
Controla 2 válvulas solenóides independentes

Executa até 3 ciclos de irrigação por dia

Funciona totalmente offline (sem nuvem)

Integração opcional com MQTT/Home Assistant

Interface web para configuração e controle

Armazena todas as configurações localmente (mesmo após reinício ou queda de energia)

🔄 Como funciona
O usuário define os horários pela interface web

Configurações são salvas no LittleFS

O horário é sincronizado via NTP

A cada minuto, o sistema verifica se deve iniciar um ciclo

Os relés são acionados com um pequeno atraso para proteger o hardware

🧠 Arquitetura do Sistema
Modo Local  
Usuário → Interface Web (ESP8266) → Servidor HTTP interno → Lógica de controle → Relés → Válvulas

Com Home Assistant  
Home Assistant → Broker MQTT → ESP8266 → Módulo Relé → Válvulas

⚙️ Principais Recursos
Controle manual e independente das válvulas

Atualizações em tempo real

Sincronização de estado via MQTT

Automação programada (até 3 ciclos diários)

Comparação minuto a minuto (sem agendador externo)

Ambas válvulas podem funcionar juntas

Atraso de 1s entre ativações (proteção do hardware)

Sincronização de horário via pool.ntp.org (atualização a cada 60s, fuso configurado para Brasil)

Persistência local com LittleFS

Provisionamento de Wi-Fi via WiFiManager (sem credenciais fixas)

📡 Integração com Home Assistant
Descoberta automática via MQTT

Criação de entidades para cada válvula

Tópicos:

irrigacao_esp/v1/state

irrigacao_esp/v1/set

irrigacao_esp/v2/state

irrigacao_esp/v2/set

🌐 Interface Web
Interface responsiva com tema escuro, incluindo:

Botões de controle

Configuração de horários

Controle de ciclos

Atualização automática (a cada 5s)

Configurações avançadas

Reset de fábrica

Tecnologias usadas: HTML5, CSS, JavaScript (Fetch API), JSON, PROGMEM

🛡️ Confiabilidade
Atraso entre ativações para evitar sobrecarga

Controle interno de estado (isIrrigating)

Reconexão automática do MQTT

Persistência local segura contra perda de energia

Reset de fábrica via interface web

⚠️ Limitações
Ainda sem sensores de umidade (baseado apenas em tempo)

Recursos MQTT exigem Wi-Fi

Sem acesso remoto sem configuração externa

🌍 Casos de Uso
Jardins residenciais

Pequenas propriedades rurais

Estufas

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
