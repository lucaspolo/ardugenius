
#define DO 33
#define RE 73
#define MI 165
#define FA 349

int numeros[100];
int posicao;

void setup() {
  Serial.begin(9600);
  configuraPinos();
  inicializaNumeros();
}

void inicializaNumeros() {
  for(int i = 0; i < 100; i++) numeros[i] = 0;
  posicao = 0;
}

void configuraPinos() {
  for(int i = 2; i <= 5; i++) pinMode(i, INPUT);
  for(int i = 9; i <= 12; i++) pinMode(i, OUTPUT);
}

void loop() {
  while(true) {
    principal(); 
  }  
}

void principal() {
  insereNovoNumero();
  validaSequencia();
}

void insereNovoNumero() {
  int pinoNovo = numeroRandomico();
  numeros[posicao] = pinoNovo;
  posicao++;
  numeros[posicao] = 0; 
}

void validaSequencia() {
  exibirSequencia();
  for(int i = 0; numeros[i] != 0; i++) {
    int botaoLido = lerBotao();
    if(botaoLido == numeros[i]) {
      piscaLed(numeros[i]);
    } else {
        perdeu();
        break;
    }
  }
}

void perdeu() {
  buzz(3);
  numeros[0] = 0;
  posicao = 0;
}

void buzz(int repeticoes) {
  for(int i = 0; i < repeticoes; i++) {
    tone(8, 262, 8/1000);
    delay(100);
    noTone(8);
    delay(100);
  }
}

int numeroRandomico() {
  return random(7, 12 ); 
}

void exibirSequencia() {
  for(int i = 0; numeros[i] != 0; i++) {
    if(numeros[i] == 0) return;
    piscaLed(numeros[i]);
  }
}

void piscaLed(int pino) {
  digitalWrite(pino, HIGH);
  tom(pino);
  delay(250);
  digitalWrite(pino, LOW);
  delay(250);
}

void tom(int pino) {
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
  Serial.println("Iniciando ler botao");
  while(true) {                                        
    for(int i = 2; i < 6; i++) {
      if(digitalRead(i) == HIGH) {
        return i + 7;
      }
    }  
  } 
}
