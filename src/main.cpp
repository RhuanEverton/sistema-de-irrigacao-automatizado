#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FirebaseESP32.h>

#define sensor 32 //PINO ONDE ESTA LIGADO A SAIDA ANALOGICA DO SENSOR DE UMIDADE
#define bomba 26 // PINO ONDE ESTA LIGADO O MODULO RELE

const char* ssid = "nome de sua rede Wifi";
const char* password = "sua senha do Wifi";

#define host "Seu Host"
#define chave "Sua chave"

FirebaseData firebaseData;

byte UmidPercent; // RECEBE A CONVERSAO DA LEITURA ANALOGICA EM PORCENTAGEM DA UMIDADE 
int ValorAnalog; //  VALOR ANALOGICO DO SENSOR DE UMIDADE
int umidade;    //   RECEBE A UMIDADE QUE A PESSOA DESEJA MANTER A PLANTA

AsyncWebServer server(80);

String umidadedosolo() {
    return String(UmidPercent);

}
String umidadedesejada() {
    return String(umidade);
}


// ARQUIVO HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
 <style>
    html {
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
      p { font-size: 3.5rem; }
    .units { font-size: 1.2rem; }
    .umi{
      font-size: 3.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
        .umi2{
      font-size: 2.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <p style="text-align: center;"><strong>Projeto Integrador:</strong><span style="color: #008000;"> Irriga&ccedil;&atilde;o automatizada</span></p>
  <p>  
   <i class="fas fa-tint" style="color:#00add6;"></i> 
   
    <span class="umi"> UMIDADE DO SOLO: </span> 
    <span class="umi" id="umidadedosolo">%UMIDADEDOSOLO%</span>
    <span class="umi">&percnt;</span>
   </p>  

    <p>  
     
    <span class="umi"> UMIDADE DESEJADA: </span> 
    <span class="umi" id="umidadedesejada">%UMIDADEDESEJADA%</span>
    <span class="umi">&percnt;</span>
   </p>  
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("umidadedosolo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/umidadedosolo", true);
  xhttp.send();
}, 500 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("umidadedesejada").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/umidadedesejada", true);
  xhttp.send();
}, 500 ) ;
</script>
</html>)rawliteral";

// FAZ O PROCESSAMENTO DAS REQUISICOES DA PAGINA
String processor(const String& var){
 
  if(var == "UMIDADEDOSOLO"){
    return umidadedosolo();
  }
  if(var == "UMIDADEDDESEJADA"){
    return umidadedesejada();
   }
     return String();
}


void setup() {
pinMode(sensor, INPUT);
pinMode(bomba, OUTPUT); 
digitalWrite(bomba, HIGH);
Serial.begin(115200);
 
 
// FAZ CONEXÃO COM A REDE WIFI 
WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/umidadedosolo", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", umidadedosolo().c_str());
  });
  server.on("/umidadedesejada", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", umidadedesejada().c_str());
  });
  
server.begin(); // INICIA O SERVIDOR

Firebase.begin(host,chave);// FAZ CONEXÃO COM O BANCO DE DADOS 

}

void loop(){

  ValorAnalog = analogRead(sensor); //FAZ A LEITURA DO SENSOR
  UmidPercent = map(ValorAnalog, 0, 4095, 100, 0);// CONVERTE A LEITURA EM PORCENTAGEM
 
  
  Firebase.setFloat(firebaseData,"/Umidadeatual", UmidPercent); // ENVIA A VARIAVEL "UmidPercent" PARA A VARIAVEL "umidadeatual" NO BANCO DE DADOS DO FIREBASE
  Firebase.getInt(firebaseData,"/Umidadedesejada", umidade);  // RECEBE A VARIAVEL "Umidadedesejada" DO BANCO DE DADOS DO FIREBASE E AMARZENA NA VARIAVEL "umidade"
    
      if(UmidPercent < umidade){
         digitalWrite(bomba, LOW);
         delay(250);
        digitalWrite(bomba, HIGH);
        delay(5000);
        loop();
    }
      else if(UmidPercent >= umidade){
            digitalWrite(bomba, HIGH);
    }
   
}  
