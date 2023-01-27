//Incluir bibliotecas
#include <LiquidCrystal.h>

//Notas para o Arduino tocar
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//Definir constantes
#define pier 6
#define pControlador 4
#define pContraste 5
#define tamanhoTela 80
#define x 6
#define qntdFrames 3
#define tCaminho 12
#define intervaloClick 300
#define intervaloTick 500
#define notasIntervalo 150
#define moverTempo 200

//Declarar variaveis globais
LiquidCrystal lcd(2, 3, A0, A1, A2, A3);
unsigned int pos = 0, ajuste = 0, pontuacao = 0, recorde = 0, intervaloMover = moverTempo;
unsigned int posM[2] = {29, 1};
int matrizPos[2][12] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
bool adicionar = 0;
unsigned long tClick = intervaloClick, tempo = 0, tMover = intervaloMover, tTick = intervaloTick, tempoNota = notasIntervalo;

//Melodia da música
word melodia[] = {NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_B4,
NOTE_A4, NOTE_CS5, 0, NOTE_A4, NOTE_B4, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_DS5, NOTE_B4, NOTE_FS5, NOTE_B4,
NOTE_FS5, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_FS5, NOTE_AS4, NOTE_FS5, NOTE_AS4, NOTE_G5, 0, NOTE_FS5, NOTE_D5, NOTE_FS5,
NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_E5, 0, NOTE_D5, 0, NOTE_CS5, 0, NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5,
NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_CS5, 0, NOTE_A4,
NOTE_B4, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_DS5, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_FS5, NOTE_B4,
NOTE_FS5, NOTE_AS4, NOTE_FS5, NOTE_AS4, NOTE_G5, 0, NOTE_FS5, NOTE_D5, NOTE_FS5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_CS5,
0, NOTE_FS5, 0, NOTE_CS5, 0, NOTE_D5, 0, 0, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_D5, 0,
NOTE_CS5, 0, NOTE_D5, 0, NOTE_A4, 0, 0, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, 0, NOTE_FS5,
0, NOTE_E5, 0, NOTE_D5, 0, 0, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_D5, 0, NOTE_CS5, 0,
NOTE_D5, 0, NOTE_FS5, 0, 0, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_D5, 0, NOTE_E5, 0, NOTE_CS5,
0, NOTE_D5, 0, 0, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_D5, 0, NOTE_CS5, 0, NOTE_D5, 0,
NOTE_A4, 0, 0, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, 0, NOTE_FS5, 0, NOTE_E5, 0, NOTE_D5,
0, 0, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_D5, 0, NOTE_CS5, 0, NOTE_D5, 0, NOTE_FS5, NOTE_D5,
NOTE_FS5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_E5, 0, NOTE_D5, 0, NOTE_CS5, 0, NOTE_A4, 0, 0,
NOTE_A5, 0, 0, NOTE_E5, 0, 0, 0, 0, 0, NOTE_D5, 0, 0, NOTE_A5,
0, 0, NOTE_A4, 0, 0, 0, 0, 0, NOTE_A4, 0, 0, NOTE_D5, 0,
0, NOTE_A5, 0, 0, 0, 0, NOTE_B5, NOTE_A5, 0, 0, NOTE_E5, 0, 0,
NOTE_D5, 0, 0, 0, 0, 0, NOTE_A4, 0, 0, NOTE_A5, 0, 0, NOTE_E5,
0, 0, 0, 0, 0, NOTE_D5, 0, 0, NOTE_A5, 0, 0, NOTE_A4, 0,
0, 0, 0, 0, NOTE_A4, 0, 0, NOTE_D5, 0, 0, NOTE_A5, 0, 0,
0, 0, NOTE_B5, NOTE_A5, 0, 0, NOTE_E5, 0, 0, NOTE_D5, 0, 0, 0,
0, 0, NOTE_A4, 0, 0, NOTE_A5, 0, NOTE_FS5, NOTE_E5, 0, NOTE_D5, NOTE_CS5, 0,
NOTE_D5, NOTE_E5, 0, 0, NOTE_CS6, NOTE_C6, NOTE_B5, NOTE_A5, 0, 0, 0, 0, 0,
NOTE_B4, 0, 0, NOTE_A5, 0, NOTE_FS5, NOTE_E5, 0, NOTE_D5, NOTE_E5, 0, NOTE_FS5, NOTE_CS5,
0, 0, NOTE_E5, 0, 0, NOTE_E5, 0, NOTE_D5, NOTE_CS5, 0, NOTE_D5, NOTE_A4, 0,
0, NOTE_A5, 0, NOTE_FS5, NOTE_E5, 0, NOTE_D5, NOTE_CS5, 0, NOTE_D5, NOTE_E5, 0, 0,
NOTE_CS6, NOTE_C6, NOTE_B5, NOTE_A5, 0, 0, 0, 0, 0, NOTE_B4, 0, 0, NOTE_A5,
0, NOTE_FS5, NOTE_E5, 0, NOTE_D5, NOTE_E5, 0, NOTE_FS5, NOTE_CS5, 0, 0, NOTE_E5, 0,
0, NOTE_E5, 0, NOTE_D5, NOTE_CS5, 0, NOTE_D5, NOTE_A4, 0, NOTE_D4, NOTE_E4, 0, NOTE_D4,
NOTE_GS3, 0, NOTE_D4, NOTE_E4, 0, NOTE_D4, NOTE_G3, 0, NOTE_D4, NOTE_E4, 0, NOTE_G4, NOTE_FS4,
0, NOTE_E4, NOTE_D4, 0, NOTE_A3, NOTE_A4, 0, NOTE_D4, NOTE_E4, 0, NOTE_D4, NOTE_GS3, 0,
NOTE_D4, NOTE_E4, 0, NOTE_D4, NOTE_G3, 0, NOTE_D4, NOTE_E4, 0, NOTE_G4, NOTE_FS4, 0, NOTE_E4,
NOTE_D4, 0, NOTE_A3, NOTE_A4, 0, NOTE_D4, NOTE_E4, 0, NOTE_D4, NOTE_A3, 0, NOTE_D4, NOTE_E4,
0, NOTE_FS4, NOTE_D4};

word contadorNotas = 0;
void setup()
{
  pinMode(pContraste, OUTPUT);
  pinMode(pier, OUTPUT);
  analogWrite(pContraste, 30);
  Serial.begin(9600);
  lcd.begin(16, 2);

  
  carregarSprites();
  carregarLayout();
  ajustarTabela(1, pontuacao);
  lcd.setCursor(x+4, pos);
  lcd.write(byte(0));
}
void musica()
{
  if(tempo >= tempoNota)
  {
    noTone(pier);
    tone(pier, melodia[contadorNotas], notasIntervalo);
    tempoNota = tempo+notasIntervalo*2;
    contadorNotas++;
    if(contadorNotas >= sizeof(melodia)/sizeof(melodia[0]))
    {
      contadorNotas = 0;
    }
  }
}
void carregarLayout()
{
  /*
   *Carregar o layout onde fica a pontuação, recorde e a divisão.
   */
  for(int i = 0; i < 2; i++)
  {
    lcd.setCursor(0, i);
    if(i == 0)
    {
      lcd.print("Scr:");
    }
    else
    {
      lcd.print("Bst:");
    }
    for(int j = 0; j <= x-4; j++)
    {
      lcd.write("0");
    }
    lcd.write("|");
  }
  
}

void carregarSprites()
{
  /*
   * Carregar os sprites na memoria do Arduino.
   */
  static byte nave[8] = {
    B11000,
    B01100,
    B01110,
    B10001,
    B10001,
    B01110,
    B01100,
    B11000
  };
  lcd.createChar(0, nave);
  static byte asteroides[] = {
    //+1 para a esquerda
    B00000,
    B00000,
    B00000,
    B00001,
    B00001,
    B00001,
    B00000,
    B00000,

    //+3 para a esquerda
    B00000,
    B00000,
    B00011,
    B00111,
    B00110,
    B00111,
    B00011,
    B00000,

    //Cheio
    B00000,
    B00000,
    B01110,
    B11101,
    B11011,
    B11111,
    B01110,
    B00000,

    //+7 para a esquerda
    B00000,
    B00000,
    B11000,
    B10100,
    B01100,
    B11100,
    B11000,
    B00000,

    //+9 para a esquerda
    B00000,
    B00000,
    B00000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,

    //Vazio
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
  };

  for(int i = 0; i < 6; i++)
  {
    lcd.createChar(i+1, &asteroides[i*8]);
  }
}

void ajustarTabela(int pos, int valor)
{
  //Ajustar os valores na tabela do layout, podendo ajustar recorde e pontuação
  long tamanho = String(valor).length();
  lcd.setCursor(x-tamanho+1, pos);
  lcd.print(valor);
}

void resetar()
{
  /*
   * Resetar o jogo, volta para o estado inicial, exceto o recorde.
   */
  //Conferir se bateu o recorde
  if(pontuacao > recorde)
  {
    recorde = pontuacao;
  }
  //resetar valores
  pontuacao = 0;
  posM[0] = qntdFrames*tCaminho;
  posM[1] = random(0, 2);
  pos = 0;
  adicionar = false;
  ajuste = 0;
  intervaloMover = moverTempo;
  
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < tCaminho; j++)
    {
      matrizPos[i][j] = 0;
    }
  }
  
  //Ajustar layout
  carregarLayout();
  ajustarTabela(1, recorde);
  mAsteroide();
  
  //desenhar jogo novamente
  for(int i = 0; i < 2; i++)
  {
    for(int j = x+2; j < 16; j++)
    {
      lcd.setCursor(j, i);
      lcd.write(byte(6));
    }
  }
  
  lcd.setCursor(x+4, 0);
  lcd.write(byte(0));
}


void mNave()
{
  /*
   * Mover a nave de posição.
   */
  lcd.setCursor(x+4, pos);
  lcd.print(" ");
  if(pos == 1)
  {
    pos = 0;
  }
  else
  {
    pos = 1;
  }
  lcd.setCursor(x+4, pos);
  lcd.write(byte(0));
}

void definirPos()
{
  /*
   * Definir a posição do asteroide e seu frame para cada slot que ele ocupa.
   */
  //Pegar as posições que os asteroides ocupam
  int div = int(posM[0]/qntdFrames);
  int dif = posM[0]-div*qntdFrames;
  
  int pos1 = div;
  int pos2 = pos1+1;
  
  //pegar o frame
  int frame1 = qntdFrames-dif;
  int frame2 = dif+ajuste;
    
  //Ajustar a variavel de ajuste para ela se adequar ao frame correto
  
  if(frame2 == qntdFrames*2){
    ajuste = 0;
    adicionar = false;
  }
  if(frame1 == qntdFrames){
    adicionar = true;
  }
  if(adicionar){
    ajuste += 2;
  }
  
  //modificar matriz das posicoes
  if(0 <= pos1 < tCaminho){
    matrizPos[posM[1]][pos1] = frame1;
  }
  if(0 <= pos2 < tCaminho){
    matrizPos[posM[1]][pos2] = frame2;
  }
}

void mAsteroide()
{
  /*
   * Mover o asteroide.
   */
  if(posM[0] > 0)
  {
    //mudar posicoes
    definirPos();
    posM[0]--;
    
    //desenhar
    for(int i = 2; i < tCaminho; i++)
    {
      for(int j = 0; j <= 1; j++)
      {
       	int frame = matrizPos[j][i];
        if(frame > 0 && frame <= qntdFrames*2)
        {
          lcd.setCursor(i+x, j);
          lcd.write(byte(frame));
          if(frame == 6)
          {
            matrizPos[j][i] = 0;
          }
          //Verificar se o asteroide colidiu com a nave
          if(i == 4 && frame != 0 && pos == posM[1])
          {
            resetar();
          }
        }
      }
    }
  }
  else
  {
    //Faz o asteroide voltar para o inicio
    posM[0] = qntdFrames*tCaminho;
    posM[1] = random(0, 2);
    
    //Adicionar pontuação
    if(pontuacao < 999){
    	pontuacao++;
    	ajustarTabela(0, pontuacao);
    }
  }
}
void loop()
{
  tempo = millis();
  //Tocar musica
  musica();
  //Ver se o botão foi clicado
  if(digitalRead(pControlador) == 1 && tempo >= tClick)
  {
    mNave();
    tClick = tempo+intervaloClick;
  }
  
  //mover asteroide
  if(tempo >= tMover)
  {
  	mAsteroide();
    tMover = tempo+intervaloMover;
  }

  //Acelerar
  if(intervaloMover > 30 && tempo >= tTick)
  {
    intervaloMover--;
    tTick = tempo+intervaloTick;
  }
}
