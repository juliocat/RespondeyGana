//----------------------
// an array of strings
char *preguntas[31]={"^Sinonimo: Querer@Amar Odiar Beber*", 
"^La suma 2+4=?@4 5 24 2 6*", 
"^No pertenece:@Rueda Timon Pez*", 
"^Agua = H2O@1)V 2)F*",
"^Sinonimo: sumiso@a)docil b)osado*",
"^Division 9/3@1)4 2)3 3)2 4)9*",
"^5 x 6=?@1)11 2)25 3)30*",
"^Sinonimo fiel@a)leal b)traidor*",
"^Antonimo fregor@silencio ruido*",
"^Suma 7+(-2)=?@1)9 2)7 3)6 4)5*",
"^elemento AU?@1)oro 2)plata*",
"^elemento zn?@1)cobre 2)cinc*",
"^elemento pb?@1)plomo 2)plata*",
"^elemento rn?@1)radon 2)radio*",
"^elemento ti?@1)talio 2)tulio*",
"^elemento li?@1)lirio 2)litio*",
"^(20x3)/2?@1)10 2)20 3)30*",
"^4 x 8 =?@1)20 2)24 3)32*",
"^9 / 1 =?@1)3 2)9 3)6*",
"^(((7x3)/1)+3)=?@1)24 2)21 3)19*",
"^sinonimo mar?@1)playa 2)lago*",
"^sinonimo pincho?@1)usb 2)cactus*",
"^sinonimo ropa?@1)media 2)liga*",
"^sinonimo sol?@1)luz 2)moneda*",
"^sinonimo balon?@1)globo 2)cuota*",
"^antonimo luz?@1)oscuro 2)negro*",
"^antonimo hueco?@1)lleno 2)tapon*",
"^antonimo aire?@1)vacio 2)carbono*",
"^antonimo fragor?@1)silencio 2)pausa*",
"^antonimo ileso?@1)herido 2)violado*",
"^Su puntaje es:@"};

int respuestas[30]={1, 
5, 
3, 
1,
1,
2,
3,
1,
2,
4,
1,
2,
1,
1,
1,
2,
3,
3,
2,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1};

int nrorptas[30]={3, 
5,
3,
2,
2,
4,
3,
2,
2,
4,
2,
2,
2,
2,
2,
2,
3,
3,
3,
3,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2};

int usados[10];

int puntaje,f=1;
//Generar orden aleatorio de preguntas
void aleatorios(){
  int num,i,j;
  bool repetido;
  for (j=0;j<10;j++){
    repetido=false;
    delay(3);
    randomSeed(millis());// genera una semilla para aleatorio a partir de la función millis()
    num=random(30);//genera numeros entre 0 y 9
    Serial.println(num);
    for (i=0; i <=j;i++){
      if (num == usados[i]){
        repetido = true; 
      }
    }//fin for i
    if (repetido==true){
      j=j-1;
    }
    else{
      usados[j]=num;      
    }
    //delay(500);
  }//fin for j
}

void setup() {
  Serial.begin(9600);
}
int rp=0,pr=-1,er=0;
void loop() {
  delay(1000);
  if(f==1){//Iniciar juego
    f=0;
    aleatorios();//generar preguntas aleatorias
    Serial.write('*');//Limpiar pantalla
    Serial.write("^Presione@una tecla*");
  }
  
  //-------------------------------
  if (Serial.available() > 0){
   rp=Serial.read();
   if(pr>-1 && pr<10){
      if(rp>nrorptas[usados[pr]]){
         Serial.write('#');//Envía error
      }
      else
         {
           //if(pr>=0 && pr<=9){//Dentro del rango de preguntas
             if(respuestas[usados[pr]]==rp) {puntaje++;}
             pr++;
           //}
         }
     }
     else if(pr==-1){
       pr++;
     }//Fin pr>-1
     //--------------
     if(pr==10){
       Serial.write(preguntas[30]);
       Serial.print(puntaje);
       Serial.write('*');//Limpiar pantalla
       delay(5000);
       puntaje=0;
       Serial.write("^Desea jugar@de nuevo s/n?*");
       pr++;
     }
     else{
       if(pr==11){
         if(rp==1){//continuar jugando
           pr=-1;
           rp=0;
           f=1;
           Serial.write('$');//Reiniciar
         }
         else
           Serial.write("^Gracias!@por haber jugado*");
       }
       else{
         Serial.write(preguntas[usados[pr]]);
       }//fin pr==11
     }
  }  
}
