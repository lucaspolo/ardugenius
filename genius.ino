
#define DO 33
#define RE 37
#define MI 41
#define FA 44

int numeros[100];
int posicao = 0;

void setup() {
  Serial.begin(9600);
  numeros[0] = 0;
  configuraPinos();
  
}

void configuraPinos() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  while(true) {
    buzz();
    principal(); 
  }  
}

void principal() {
  int pinoNovo = numeroRandomico();
  numeros[posicao] = pinoNovo;
  posicao++;
  numeros[posicao] = 0;
  validaSequencia();
}

void validaSequencia() {
  exibirSequencia();
  for(int i = 0; numeros[i] != 0; i++) {
    int botaoLido = lerBotao();
    Serial.println(botaoLido);
    if(botaoLido == numeros[i]) {
      piscaLed(numeros[i]);
    } else {
        perdeu();
        break;
    }
  }
}

void perdeu() {
  buzz();
  buzz();
  buzz();
  numeros[0] = 0;
  posicao = 0;
}

void buzz() {
  tone(8, 262, 8/1000);
  delay(100);
  noTone(8);
  delay(100);
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
      tone(8, 262, 8/1000);
      break;
    case 10:
      tone(8, 262, 8/1000);
      break;
    case 11:
      tone(8, 262, 8/1000);
      break;
    case 12:
      tone(8, 262, 8/1000);
      break;
    default:
      //tone(8, 262, 8/1000);
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

void teste() {
  Serial.println("Iniciando funcao de teste");
  numeros[0] = 9;
  numeros[1] = 10;
  numeros[2] = 11;
  numeros[3] = 12;
  numeros[4] = 0;
  exibirSequencia();
  lerBotao();
  Serial.println("Finalizando funcao de teste");
}
