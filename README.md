Projeto Integrador: Irrigação Automatizada
Este projeto implementa um sistema de irrigação automatizada utilizando o microcontrolador ESP32. O dispositivo mede a umidade do solo por meio de um sensor analógico e controla uma bomba de água para manter a umidade do solo em um nível desejado. Os dados são armazenados e recuperados de um banco de dados Firebase.

Estrutura do Projeto
1. Código Fonte
O código principal está contido no arquivo main.ino, que é escrito na linguagem Arduino. Este arquivo abrange:

Inicialização: Configuração de pinos, conexão Wi-Fi e inicialização do servidor web.
Loop Principal: Leitura do sensor, atualização do banco de dados Firebase, e controle da bomba com base nas condições de umidade.
2. Interface Web
A interface web é definida no arquivo index_html. Esta página HTML incorpora JavaScript para atualização dinâmica da umidade do solo e da umidade desejada.

3. Configuração
As credenciais da rede Wi-Fi e informações do banco de dados Firebase são configuradas no início do arquivo main.ino. Certifique-se de preencher essas informações antes de carregar o código no ESP32.

Requisitos de Hardware e Software
Hardware
ESP32
Sensor de Umidade do Solo
Módulo Relé
Software
Arduino IDE
Bibliotecas: WiFi, ESPAsyncWebServer, FirebaseESP32
Configuração Inicial
Clone o Repositório:

bash
Copy code
git clone https://github.com/seu-nome-de-usuario/seu-repositorio.git
Abra o Projeto no Arduino IDE:

Abra o arquivo main.ino no Arduino IDE.
Configuração das Credenciais e Firebase:

Substitua os espaços reservados para ssid e password com as credenciais da sua rede Wi-Fi.
Substitua os espaços reservados para host e chave com as informações do seu banco de dados Firebase.
Upload do Código:

Faça o upload do código para o ESP32.
Funcionamento
O ESP32 lê continuamente a umidade do solo por meio do sensor analógico. A leitura é convertida em porcentagem e comparada com a umidade desejada configurada. Se a umidade do solo estiver abaixo do nível desejado, a bomba de água é acionada para irrigação. Os dados de umidade atual e desejada são atualizados no Firebase em tempo real.

Uso
Monitor Serial:

Abra o Monitor Serial no Arduino IDE para monitorar as informações do dispositivo.
Acesso à Interface Web:

Descubra o endereço IP atribuído ao ESP32 (pode ser visualizado no Monitor Serial).
Acesse o endereço IP no navegador para visualizar a interface web.
Controle da Umidade:

Visualize a umidade do solo em tempo real.
Ajuste a umidade desejada na interface web.
Firebase:

Os dados de umidade atual e desejada são atualizados automaticamente no Firebase.
Você pode monitorar esses dados no console do Firebase.
Contribuições
Contribuições são bem-vindas! Se encontrar problemas ou tiver melhorias, abra problemas ou envie solicitações de pull.



Autor
Rhuan Everton - rhuan@rhuaneverton.com
