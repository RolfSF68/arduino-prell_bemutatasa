#define gomb 3
bool allapot;          //digitális bemenet aktuális állapota
bool elozoallapot;     //minden loop ciklus végén elmentem ide a beolvasott állapotot
long ciklus_szamlalo;      
int szamlalo;
long ido;              //ebben tároljuk az utolsó időszámláló kiírás időpontját, hogy 1000msec (1 sec) múlva újra kiírhassuk annak értékét

void setup() 
{
  pinMode(gomb,INPUT);      //nyomógomb bemenet
  digitalWrite(gomb,INPUT_PULLUP);  //felhúzó ellenállás bekapcsolva
  Serial.begin(9600);    //elindítjuk a soros portot
}

void loop() 
{
  ciklus_szamlalo=ciklus_szamlalo+1;    
  allapot=digitalRead(gomb);               //beolvassuk az allapot változóba a bemenet pillanatnyi állapotát 
                                         //(0, ha lenyomtuk a nyomógombot, 1, ha nyomógomb nincs lenyomva)
  if (allapot==0 and elozoallapot==1)   //Azaz, most le van nyomva a gomb és az előző ciklkusban nem volt lenyomva. 
                                        //Ez a bemeneten egy "lefutó él" érzékelést jelent
  {
    szamlalo=szamlalo+1;                //növeljük a számláló értékét, mert a nyomógomb le lett nyomva
    Serial.println(szamlalo);           //kiírjuk a soros portra a számláló állapotát
  }
  elozoallapot=allapot;                 //a jelenlegi állapot lesz az új állapot

  if (ido+1000<millis())                //ha 1 sec telt el az előző 
  {
    //Serial.println(ciklus_szamlalo);    //kiírjuk ciklus_szamlalo értékét a soros portra
    ciklus_szamlalo=0;                  //töröljük ciklus_szamlalo értékét, újra kezdjük a számlálást
    ido=millis();                       //tároljuk a millis() értékét, így az if-ben vizsgálhatjuk, hogy eltelt-e 1 másodperc
  }
}
