
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

// cr�e aREST instance
aREST_UI rest = aREST_UI();

// WiFi parameters
const char* ssid = ""; //-----------------------------------------------------> AQUI COLOQUE O NOME DE SUA REDE LOCAL
const char* password = ""; //-------------------------------------------------> AQUI COOQUE A SENHA DE SUA REDE LOCAL

// port conncetions TCP 
#define LISTEN_PORT           80 //-------------------------------------------> VOCE PODE ALTERAR ESTA PORTA DE ACORDO A SUA NECESSIDADE

// cr�e un instance du server
WiFiServer server(LISTEN_PORT);
void setup(void)
{  
  Serial.begin(115200);
  
  // UI criada
  rest.title("Relay ");
  rest.button(6);
  rest.button(7);
    
 // dê nome e identificação ao módulo
  rest.set_id("1");
  rest.set_name("esp8266");
  
  // Conectando-se ao wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // inicializando o servidos
  server.begin();
  Serial.println("Server started");
  
  // imprimindo o IP
  Serial.println(WiFi.localIP());
  
}

void loop() {
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}
 
