/*
UNIVERSIDADE FERDERAL DO AMAZONAS 
ENGENHARIA DA COMPUTAÇAO
MARCELO FERREIRA DE AQUINO
marcelofdeaquino@gmail.com

Analog input, analog output, serial output
 
 Manipulaçao de duas enteiras onde na primeira esteira (esteira principal)
 possui objetos a serem despejados em potes localizados na segunda esteira
 (esteira de potes). Neste sketch foi implementado com ideia de sincronizaçao
 das duas esteiras. Os valores sao impressos no monitor serial.
 
 O circuito:
   * Modulo rele para ligar e desligar os motores das esteiras
   * 3 laser de 5v 
       -- 1 para esteira pricipal e 2 para esteira de potes
   * 3 sensores de luz de 5v
       -- 1 para esteira pricipal e 2 para esteira de potes
   * 2 motores DC de 12v
   * Fonte externa de 12v para alimentaçao dos motores
       -- OBS: a passagem de tensao da fonte para o motor deve 
       ser manipulada pelo modulo rele

 */

const int sensorEsteiraPricipal = A0;  // Entrada analogica do sensor de luz da esteira principal
const int sensorEsteiraSecundaria = A2;  // Entrada analogica do sensor 2 de luz da esteira secundaria

const int esteiraPrincipal = 8;
const int esteiraSecundaria = 9;

// Quantidade desejada de objetos por pote
const int totObj=3;
const int totPote=3;

// Variveis para controle de objetos 
int qtdeObj = 0;         // Quantidade de objetos por pote
int qtdePote = 0;         // Quantidade de potes

// Flag para garantir a contagem de um objeto por vez
int flagCont = 0;

//Flags dos sensores de posicao da esteira secundaria
int flagPote = 0;

// valor dos sensores de luz da esteira principal e da esteira secundaria, respectivamente.
int sensorValueObj = 0;        
int sensorValuePote = 0;       


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(esteiraPrincipal,OUTPUT);
  pinMode(esteiraSecundaria,OUTPUT);  
  inicializar();
}

void inicializar(){
  delay(2000);
  digitalWrite(esteiraPrincipal,LOW);
  digitalWrite(esteiraSecundaria,LOW);
  posProxPote();
}
  
void posProxPote(){
  // Desliga a esteira principal
  digitalWrite(esteiraPrincipal,LOW);
  delay(1000);
  // Liga a esteira secundario
  digitalWrite(esteiraSecundaria,HIGH);

  Serial.println("Posicionando proximo pote...");

  while(flagPote == 1){
     sensorValuePote = analogRead(sensorEsteiraSecundaria);
     if(sensorValuePote < 600)
       flagPote=0;
  }

  while(flagPote == 0){
     sensorValuePote = analogRead(sensorEsteiraSecundaria);
     if(sensorValuePote > 600)
       flagPote=1;
  }
  
  // Chegada da objeto na posiçao
  digitalWrite(esteiraSecundaria,LOW);
  delay(1000);
  //Religa a esteira principal
  digitalWrite(esteiraPrincipal,HIGH);
}

void loop() {
  // Leitura do sensor laser da esteira principal
  sensorValueObj = analogRead(sensorEsteiraPricipal);
  sensorValuePote = analogRead(sensorEsteiraSecundaria);
  
  if ((flagCont == 0)&&(sensorValueObj > 600)){
      flagCont=1;
  }
  if ((flagCont == 1)&&(sensorValueObj < 600)){
      qtdeObj++;
      flagCont=0;
  }
  
  if(qtdeObj >= totObj){
    qtdeObj=0;
    posProxPote();
    qtdePote++;
  }
      

  // print the results to the serial monitor:
  Serial.print("Obj = " );                       
  Serial.print(sensorValueObj);         
  Serial.print(" s2 = " );                       
  Serial.print(sensorValuePote);      
  Serial.print("   qtde = ");      
  Serial.println(qtdeObj);   

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
