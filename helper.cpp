#include <QDebug>
#include <QByteArray>
#include <bitset>
#include <QStringList>
#include <QList>
#include <iostream>
#include <QPair>

QPair<QString, int> currLabel;
QList<QPair<QString, int> > symbolList;

struct currentInstruction {
  QString label;
  QString name;
  QStringList token;
  int position;
} currInstruction;

QString rmParen(QString arg){
  QString temp;
  temp = arg.remove("(");
  return temp.remove(")");
}

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

int rTypeAssemble(unsigned char opcode, unsigned char $rs, unsigned char $rt, unsigned char $rd, unsigned char shamt, unsigned char funct){
    uint assembled = 0x00000000;
    unsigned char lower5BitMask = 0x1f;
    unsigned char lower6BitMask = 0x3f;

    assembled = assembled | (opcode << 26);
    assembled = assembled | (($rs & lower5BitMask) << 21);
    assembled = assembled | (($rt & lower5BitMask) << 16);
    assembled = assembled | (($rd & lower5BitMask) << 11);
    assembled = assembled | ((shamt & lower5BitMask) << 6);
    assembled = assembled | ((funct & lower6BitMask) << 0);

    return assembled;
}

int iTypeAssemble(unsigned char opcode, unsigned char $rt, unsigned char $rs, unsigned int im){
    uint assembled = 0x00000000;
    unsigned char lower5BitMask = 0x1f;
    //char lower6BitMask = 0x3f;
    uint lower16BitMask = 0x0000ffff;

    //std::cout << sizeof opcode << " bytes";
    assembled = assembled | ((opcode) << 26);
    assembled = assembled | (($rs & lower5BitMask) << 21);
    assembled = assembled | (($rt & lower5BitMask) << 16);
    assembled = assembled | ((im & lower16BitMask) << 0);


    return assembled;
}

int decodeInstruction(currentInstruction curr){
  unsigned char $rd, $rs, $rt, opcode, shamt, funct;
  int immediate;

//r-type instructions
  if(curr.name == "add"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x20;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "addu"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x21;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "and"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x24;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "jr"){
      opcode = 0x00;
      $rs = registerLookup(curr.token.at(0));
      funct = 0x08;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "nor"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x27;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "or"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x25;
      shamt = 0x00;

    return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "slt"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x2a;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "sltu"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x2b;
      shamt = 0x00;

  return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "sll"){
      bool ok = false;
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rt = registerLookup(curr.token.at(1));
      shamt = (char)curr.token.at(2).toInt(&ok, 10);
      funct = 0x00;
      $rs = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "srl"){
      bool ok = false;
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rt = registerLookup(curr.token.at(1));
      shamt = (char)curr.token.at(2).toInt(&ok, 10);
      funct = 0x02;
      $rs = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "sub"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x22;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "subu"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x23;
      shamt = 0x00;

    return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "addi"){
    bool ok = false;
    opcode = 0x08;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);

    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "addiu"){
    bool ok = false;
    opcode = 0x09;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);

    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "andi"){
    bool ok = false;
    opcode = 0x0c;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);

    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "beq"){
    bool ok = false;
    opcode = 0x04;
    $rs = registerLookup(curr.token.at(0));
    $rt = registerLookup(curr.token.at(1));
    QString label = curr.token.at(2);
    for(int i = 0; i < symbolList.size(); i++){
      if(label == symbolList.at(i).first){
            qDebug() << "Found label beq";
            immediate = (symbolList.at(i).second - curr.position - 1);
            return iTypeAssemble(opcode, $rt, $rs, immediate);
          }

    }
      immediate = curr.token.at(2).toInt(&ok, 10);
      return iTypeAssemble(opcode, $rt, $rs, immediate);

  }

  else if(curr.name == "bne"){
    bool ok = false;
    opcode = 0x05;
    $rs = registerLookup(curr.token.at(0));
    $rt = registerLookup(curr.token.at(1));
    QString label = curr.token.at(2);
    for(int i = 0; i < symbolList.size(); i++){
      if(label == symbolList.at(i).first){
            immediate = (symbolList.at(i).second - curr.position - 1);
            qDebug() << "Found label bne";
            return iTypeAssemble(opcode, $rt, $rs, immediate);
          }

    }
      immediate = curr.token.at(2).toInt(&ok, 10);
      return iTypeAssemble(opcode, $rt, $rs, immediate);

  }

  else if(curr.name == "lbu"){
    bool ok = false;
    opcode = 0x24;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "lhu"){
    bool ok = false;
    opcode = 0x25;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "ll"){
    bool ok = false;
    opcode = 0x30;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "lui"){
    bool ok = false;
    opcode = 0x0f;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = 0x00;//registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "lw"){
    bool ok = false;
    opcode = 0x23;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "ori"){
    bool ok = false;
    opcode = 0x0d;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "slti"){
    bool ok = false;
    opcode = 0x0a;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sltiu"){
    bool ok = false;
    opcode = 0x0b;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sb"){
    bool ok = false;
    opcode = 0x28;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sc"){
    bool ok = false;
    opcode = 0x38;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sh"){
    bool ok = false;
    opcode = 0x29;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sw"){
    bool ok = false;
    opcode = 0x2b;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  return 0;
}
