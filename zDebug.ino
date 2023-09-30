void debugPID()
{
  if (millis() > currenthw[0] + PRINT_TIME_HW)
  {
    Serial.print("Error = ");
    Serial.print(Input);
    Serial.print("  PID = ");
    Serial.print(Output);
    currenthw[0] = millis();
    Serial.print("\t");
  }
}
void debugSensor()
{
  if (millis() > currenthw[1] + PRINT_TIME_HW)
  {
    getSensor();

    for (int i = 0; i < 5; i++)
    {
      Serial.print("D");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(senD[i]);
      Serial.print("\t");
    }
    Serial.println();
    currenthw[1] = millis();
  }
}

void debugSensorAlong()
{
  if (millis() > currenthw[3] + PRINT_TIME_HW)
  {
    getSensor();
    for (int i = 0; i < 5; i++)
    {
      Serial.print(senD[i]);
      Serial.print(" ");
    }
    Serial.print("");
    currenthw[3] = millis();
    Serial.print("\t");
  }
}

void debugMotor()
{
  if (millis() > currenthw[2] + PRINT_TIME_HW)
  {
    Serial.print("L_PWR = ");
    Serial.print(ml);
    Serial.print("  ");
    Serial.print("R_PWR= ");
    Serial.println(mr);
    currenthw[2] = millis();
  }
}


