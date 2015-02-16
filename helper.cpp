#include <QDebug>
#include <QByteArray>
#include <bitset>

struct currentInstruction {
  QString label;
  QString name;
  QStringList token;
} currInstruction;

char registerLookup(QString reg){
  if(reg == "$zero" || reg == "$0")
    return (char)0;
  else if(reg == "$at")
    return (char)1;
  else if(reg == "$v0")
    return (char)2;
  else if(reg == "$v1")
    return (char)3;
  else if(reg == "$a0")
    return (char)4;
  else if(reg == "$a1")
    return (char)5;
  else if(reg == "$a2")
    return (char)6;
  else if(reg == "$a3")
    return (char)7;
  else if(reg == "$t0")
    return (char)8;
  else if(reg == "$t1")
    return (char)9;
  else if(reg == "$t2")
    return (char)10;
  else if(reg == "$t3")
    return (char)11;
  else if(reg == "$t4")
    return (char)12;
  else if(reg == "$t5")
    return (char)13;
  else if(reg == "$t6")
    return (char)14;
  else if(reg == "$t7")
    return (char)15;
  else if(reg == "$s0")
    return (char)16;
  else if(reg == "$s1")
    return (char)17;
  else if(reg == "$s2")
    return (char)18;
  else if(reg == "$s3")
    return (char)19;
  else if(reg == "$s4")
    return (char)20;
  else if(reg == "$s5")
    return (char)21;
  else if(reg == "$s6")
    return (char)22;
  else if(reg == "$s7")
    return (char)23;
  else if(reg == "$t8")
    return (char)24;
  else if(reg == "$t9")
    return (char)25;
  else if(reg == "$k0")
    return (char)26;
  else if(reg == "$k1")
    return (char)27;
  else if(reg == "$gp")
    return (char)28;
  else if(reg == "$sp")
    return (char)29;
  else if(reg == "$fp")
    return (char)30;
  else if(reg == "$ra")
    return (char)31;
  return (char)-1;
}

int decodeInstruction(currentInstruction curr){
  char $rd, $rs, $rt,opcode,shamt, funct;
  int assembled = 0x0000;
  char lower5BitMask = 0x1f;
  char lower6BitMask = 0x3f;
  /*QByteArray assembled;
  assembled.resize(4);
  for(int i = 0; i < 4; i++){
    assembled[0] = 0x00;
  }*/
  if(curr.name == "add"){
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x20;

      assembled = assembled | (0x00 << 26);
      assembled = assembled | (($rs & lower5BitMask) << 21);
      assembled = assembled | (($rt & lower5BitMask) << 16);
      assembled = assembled | (($rd & lower5BitMask) << 11);
      assembled = assembled | ((funct & lower6BitMask) << 0);
      return assembled;
      //qDebug() << $rd << " " << $rs << " " << $rt;
  }

  return 0;
}
