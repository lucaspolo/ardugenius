
#define DO 33
#define RE 73
#define MI 165
#define FA 349

int numeros[100];
int posicao;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  randomSeed(analogRead(0));
  configuraPinos();
}

void inicializaNumeros() {
  Serial.println("inicializaNumeros()");
  for(int i = 0; i < 100; i++) numeros[i] = 0;
  posicao = 0;
}

void configuraPinos() {
  Serial.println("configuraPinos()");
  for(int i = 2; i <= 5; i++) pinMode(i, INPUT);
  for(int i = 9; i <= 12; i++) pinMode(i, OUTPUT);
}

void loop() {
  principal(); 
}

void principal() {
  Serial.println("principal()");
  inicializaNumeros();
  
  while(true) {
    insereNovoNumero();
    exibirSequencia();
    if(!validaSequencia()) {
       perdeu();
       return;
    }
  }
  
}

void insereNovoNumero() {
  Serial.println("insereNovoNumero()");
  int pinoNovo = numeroRandomico();
  numeros[posicao] = pinoNovo;
  posicao++;
  numeros[posicao] = 0; 
}

boolean validaSequencia() {
  Serial.println("validaSequencia()");

  for(int i = 0; numeros[i] != 0; i++) {
    int botaoLido = lerBotao();
    if(botaoLido == numeros[i]) {
      piscaLed(numeros[i]);
    } else {
        return false;
    }
  }
  return true;
}

void perdeu() {
  Serial.println("perdeu()");
  buzz(3);
}

void buzz(int repeticoes) {
  Serial.println("buzz()");
  for(int i = 0; i < repeticoes; i++) {
    tone(8, 262, 8/1000);
    delay(100);
    noTone(8);
    delay(100);
  }
}

int numeroRandomico() {
  Serial.println("numeroRandomico()");
  return random(9, 13); 
}

void exibirSequencia() {
  Serial.println("exibirSequencia()");
  for(int i = 0; numeros[i] != 0; i++) {
    if(numeros[i] == 0) return;
    piscaLed(numeros[i]);
  }
}

void piscaLed(int pino) {
  Serial.println("piscaLed()");
  digitalWrite(pino, HIGH);
  tom(pino);
  delay(250);
  digitalWrite(pino, LOW);
  delay(250);
}

void tom(int pino) {
  Serial.println("tom()");
  switch(pino) {
    case 9:
      tone(8, DO, 8/1000);
      break;
    case 10:
      tone(8, RE, 8/1000);
      break;
    case 11:
      tone(8, MI, 8/1000);
      break;
    case 12:
      tone(8, FA, 8/1000);
      break;
    default:
      break;
  }
  delay(250);
  noTone(8);
}

int lerBotao() {
  Serial.println("lerBotao()");
  Serial.println("Iniciando ler botao");
  while(true) {                                        
    for(int i = 2; i < 6; i++) {
      if(digitalRead(i) == HIGH) {
        return i + 7;
      }
    }  
  } 
}
