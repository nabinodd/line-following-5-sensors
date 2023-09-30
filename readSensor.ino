
void getSensor()
{
  senD[0] = digitalRead(7);
  senD[1] = digitalRead(8);
  senD[2] = digitalRead(10);
  senD[3] = digitalRead(11);
  senD[4] = digitalRead(12);

#ifdef BW
  for (int i = 0; i < 5; i++) senD[i] = !senD[i];
#endif

#ifdef WB
#endif
}

void stp()
{
  for (int i = 0; i <= 6; i++) digitalWrite(i, LOW);
  digitalWrite(9, LOW);
  //Serial.println("STOP");

}
