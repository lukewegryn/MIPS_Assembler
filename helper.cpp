struct currentInstruction {
  QString label;
  QString name;
  QStringList token;
} currInstruction;

int registerLookup(QString reg){
  if(reg == "$zero" || reg == "$0")
    return 0;
  else if(reg == "$at")
    return 1;
  else if(reg == "$v0")
    return 2;
  else if(reg == "$v1")
    return 3;
  else if(reg == "$a0")
    return 4;
  else if(reg == "$a1")
    return 5;
  else if(reg == "$a2")
    return 6;
  else if(reg == "$a3")
    return 7;
  else if(reg == "$t0")
    return 8;
  else if(reg == "$t1")
    return 9;
  else if(reg == "$t2")
    return 10;
  else if(reg == "$t3")
    return 11;
  else if(reg == "$t4")
    return 12;
  else if(reg == "$t5")
    return 13;
  else if(reg == "$t6")
    return 14;
  else if(reg == "$t7")
    return 15;
  else if(reg == "$s0")
    return 16;
  else if(reg == "$s1")
    return 17;
  else if(reg == "$s2")
    return 18;
  else if(reg == "$s3")
    return 19;
  else if(reg == "$s4")
    return 20;
  else if(reg == "$s5")
    return 21;
  else if(reg == "$s6")
    return 22;
  else if(reg == "$s7")
    return 23;
  else if(reg == "$t8")
    return 24;
  else if(reg == "$t9")
    return 25;
  else if(reg == "$k0")
    return 26;
  else if(reg == "$k1")
    return 27;
  else if(reg == "$gp")
    return 28;
  else if(reg == "$sp")
    return 29;
  else if(reg == "$fp")
    return 30;
  else if(reg == "$ra")
    return 31;
}

QString decodeInstruction(currentInstruction curr){
  return "Hello";
}
